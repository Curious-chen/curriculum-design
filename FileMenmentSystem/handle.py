"""
    控制模块
"""

from model import *
import numpy as np
import json


class FileManagement(object):
    """
        文件系统管理模块
    """

    def __init__(self, SIZE=(2 ** 12) * 100, BLOCK_SIZE=2 ** 12):
        # 磁盘空间大小,以字节为单位,默认400kb
        self.SIZE = SIZE
        # 磁盘大小，以字节为单位，默认4kb
        self.BLOCK_SIZE = BLOCK_SIZE
        # 将磁盘分块
        self.BLOCK_NUM = int(SIZE / BLOCK_SIZE)
        # 磁盘块信息,-1表示磁盘空闲
        self.BLOCKLIST = list([-1 for _ in range(self.BLOCK_NUM)])

        # 空闲磁盘块
        self.free_blocks = list()
        self.init_free_block()
        # 对文件进行磁盘管理,加载磁盘管理模块
        self.DM = DiskManagement(self.BLOCKLIST, self.BLOCK_NUM, self.free_blocks)
        # 初始化目录信息
        self.initCatlog()

        # 用户
        self.user = 'root'

    # 登录控制
    def login(self, name, password):
        userDict = {'root': 'root', 'Curious': 'root', 'Uncle': 'root'}
        if name in userDict:
            if userDict[name] == password:
                self.user = name
                return True
        return False

    # 用户权限控制
    def getPower(self, owner, power, op):
        if op == 'open':
            # root用户,和文件夹拥有者拥有所有权限
            if self.user == 'root' or self.user == owner:
                return True
            # 可读，则可打开
            if len(power) >= 5 and power[-2] == 'r':
                return True
        if op in ['mkdir', 'rm', 'touch']:
            # root用户,和文件夹拥有者拥有所有权限
            if self.user == 'root' or self.user == owner:
                return True
            # 可写，则可创建
            if len(power) >= 5 and power[-1] == 'w':
                return True
        if op == 'change':
            if self.user == owner and power[2] == 'w':
                return True
            if self.user != owner and power[-1] == 'w':
                return True
        # 格式化磁盘权限
        if op == 'clear' and self.user == 'root':
            return True
        # 权限不足
        print("{}没有{:^8s}权限{}".format('*' * 20, op, '*' * 20))
        return False

    def initCatlog(self, length=10):
        #######################
        # 1、初始化索引栈
        #######################
        # 引导目录索引
        root_node = IndexNode(0, '引导目录', 'catalog', 'drwr_', 'root', block_num=1)  # 抽象化索引信息块

        # 定义索引节点在磁盘中的位置
        self.IS = IndexStack(list([root_node]))
        # 分配固定的索引空间
        for i in range(-length, 0, 1):
            print(i)
            self.BLOCKLIST[i] = self.IS
            self.free_blocks.pop()

        # 分配固定的索引表
        self.BLOCKLIST[0] = self.free_blocks
        self.free_blocks.remove(0)
        part_catalog = Catalog()
        #
        # 分配根目录项存放空间，即建立索引项 索引节点编号 ->磁盘编号
        self.DM.alloc(root_node, part_catalog)
        #######################
        # 2、添加目录
        #######################

        # 目录1:root
        self.mkdir('root', 'drwr_', 'root', 0)
        #  目录2:home
        self.mkdir('home', 'drwr_', 'root', 0)

        #  目录3:Curious
        self.mkdir('Curious', 'drwr_', 'Curious', 2)
        #  目录4:Uncle
        self.mkdir('Uncle', 'drwr_', 'Uncle', 2)

    def init_free_block(self):
        """
            通过索引寻找
            初始化空闲区域
        :return:
        """
        for i, v in enumerate(self.BLOCKLIST):
            if v == -1:
                self.free_blocks.append(i)

    def getCurrentDir(self, ID):
        abs_path = str()
        while True:
            work_node = self.IS.nodes[ID]
            work_node: IndexNode
            abs_path = '/' + work_node.NAME + abs_path
            ID = work_node.pn
            if ID == 0:
                break
        return abs_path

    def getID(self):
        """
            获得目录ID
        """
        i = 0
        for v in self.IS.nodes:
            if v == -1:
                return i
            i += 1
        # 若当前栈中无索引节点释放
        return i

    def mkdir(self, name, mode, owner, pn):
        """
            创建文件夹

        """
        # 1、建立索引节点
        index_node = IndexNode(pn, name, 'catalog', mode, owner, block_num=1)

        cn = self.getID()  # 获得索引节点编号
        # 2、更新父目录
        if not self.updataDir(pn, name, cn):  # 目录项:文件名 - >索引节点编号
            # 重名
            return False
        # 3、更新索引栈 ：将索引节点加入索引栈中
        if cn < len(self.IS.nodes):
            self.IS.nodes[cn] = index_node
        else:
            # 将索引节点加入索引栈中
            self.IS.nodes.append(index_node)

        # 4、索引节点编号 -> 磁盘块编号:分配空间，并存放目录项信息
        # 创建抽象化文件目录信息
        part_catalog = Catalog()
        # 获取磁盘块,写入目录信息
        self.DM.alloc(index_node, part_catalog)  # 编辑索引项，定义索引节点编号 -> 磁盘块编号
        return True

    def rm(self, pn, cn):
        """

        :param pn: 父目录编号
        :param cn:  操作文件索引编号
        """
        # 索引节点编号->磁盘块编号->目录项文件信息
        parentDict = self.BLOCKLIST[self.IS.nodes[pn].indexs[0]].files

        # 获得操作文件的索引节点块(FCB)
        root_node = self.IS.nodes[cn]

        # 从父目录的目录文件信息中移除目录项
        parentDict.pop(root_node.NAME)

        # 向上递归修改文件大小
        pn = root_node.pn
        # 向上修改所有父目录的大小
        while True:
            # 父目录索引
            indexNode = self.IS.nodes[pn]
            indexNode: IndexNode
            # 修改目录大小
            indexNode.SIZE = indexNode.SIZE - root_node.SIZE

            # 到达引导目录，结束
            if pn == 0:
                break
            # 改为上一层ID
            pn = indexNode.pn

        # 获得应该删除的所有索引
        del_indexs = list()
        if root_node.TYPE == 'catalog':
            # 递归的删除索引节点
            # 抽象化的目录项信息,获得其中一个，即可抽象获得不同磁盘块的所有目录项
            v = root_node.indexs[0]
            # v:磁盘块编号
            # 从磁盘块中取出目录项信息
            catalog = self.BLOCKLIST[v]
            catalog: Catalog
            # 获得所有目录项
            t = [(name, ID) for name, ID in catalog.files.items()]
            for item in t:
                name, ID = item  # ID:索引编号
                # 获得目录项对应的索引节点
                index_node = self.IS.nodes[ID]
                index_node: IndexNode
                if index_node.TYPE == 'catalog':
                    self.rm(cn, ID)

        # 添加该文件占用的所用磁盘块编号
        del_indexs.extend(filter(lambda v: v != -1, root_node.indexs))
        # 链接删除，即将空闲磁盘块加入空闲栈
        self.DM.freeBlock(del_indexs)
        # 删除当前索引节点
        self.IS.nodes[cn] = -1

    def updataDir(self, pn, name, cn, old_name=None):
        """
            未解决:目录项总大小超出占用的目录块大小
            # 添加目录项 文件名 - >索引节点编号
        """
        # 获得父目录索引节点
        index_node = self.IS.nodes[pn]
        # 得到目录项所在磁盘块编号
        first_num = index_node.indexs[0]  # 获得编号
        # 得到目录项信息
        part_catalog = self.BLOCKLIST[first_num]
        part_catalog: Catalog
        # 添加文件目录项
        if name in part_catalog.files:
            print("重名")
            return False
        if old_name:
            part_catalog.files.pop(old_name)
        part_catalog.files.update({name: cn})
        return True

    def change(self, ID, pn, new_informa, old_informa):
        # 获得索引节点
        index_node = self.IS.nodes[ID]
        index_node: IndexNode

        # 判断是否拥有权限
        if self.getPower(index_node.OWNER, index_node.MODE, 'change'):
            # 获得改变前后信息
            new_informa = json.loads(new_informa)
            old_informa = json.loads(old_informa)
            if new_informa['name'] != old_informa['name']:
                # 更新目录项
                if not self.updataDir(pn, new_informa['name'], ID, old_name=old_informa['name']):
                    return False
                # 更新索引项
                index_node.NAME = new_informa['name']
            elif new_informa['power'] != old_informa['power']:
                index_node.MODE = new_informa['power']
            elif new_informa['SIZE'] != old_informa['SIZE']:
                self.vim(ID, new_informa['SIZE'] - old_informa['SIZE'])

    def vim(self, ID, SIZE):
        """
            写入数据：
            按索引，修改所有父目录大小
            注意:磁盘分配问题没有解决
        :param ID:
        :return:
        """
        # 获得文件属性
        indexNode = self.IS.nodes[ID]
        indexNode: IndexNode
        # 修改文件大小
        indexNode.SIZE = indexNode.SIZE + SIZE

        # 没有分配空间
        if indexNode.BLOCKNUM == 0:
            # 创建文件数据块
            part_file = File()
            part_file.occupy = SIZE
        else:
            part_file = self.BLOCKLIST[indexNode.indexs[0]]
        # 修改占用磁盘块数
        import math
        indexNode.BLOCKNUM = math.ceil(indexNode.SIZE / self.BLOCK_SIZE)
        # 索引编号 - 磁盘块
        self.DM.alloc(indexNode, part_file)
        pn = indexNode.pn
        # 向上修改所有父目录的大小
        while True:
            # 父目录索引
            indexNode = self.IS.nodes[pn]
            indexNode: IndexNode
            # 修改目录大小
            indexNode.SIZE = indexNode.SIZE + SIZE
            # 到达引导目录，结束
            if pn == 0:
                break
            # 改为上一层ID
            pn = indexNode.pn

    def open(self, ID):
        """
            针对文件
        """
        # 通过ID找到索引节点
        indexNode = self.IS.nodes[ID]
        indexNode: IndexNode
        # 以json形式返回文件信息
        inform = {'name': indexNode.NAME, 'TYPE': indexNode.TYPE, 'power': indexNode.MODE,
                  'blocknum': indexNode.BLOCKNUM, 'SIZE': indexNode.SIZE,
                  'indexs': [int(i) for i in indexNode.indexs]}
        inform = json.dumps(inform)
        return inform

    def touch(self, name, mode, owner, pn):
        """
            创建数据文件
                创建时，不需要分配空间,只需要添加目录项即可
        :param pn 当前目录索引ID
        """

        # 添加索引项
        indexNode = IndexNode(pn, name, 'file', mode, owner)
        cn = self.getID()  # 获得索引节点编号
        # 更新当前目录
        if not self.updataDir(pn, name, cn):  # 文件名 - >索引节点编号
            # 重名
            return False
        if cn < len(self.IS.nodes):
            self.IS.nodes[cn] = indexNode
        else:
            # 将索引节点加入索引栈中
            self.IS.nodes.append(indexNode)
        return True

    def empty_format(self):
        if self.getPower('', '', 'clear'):
            # 清空磁盘
            for i, v in enumerate(self.BLOCKLIST):
                if v != -1:
                    self.BLOCKLIST[i] = -1
            # 清空索引
            self.IS.nodes.clear()

            # 重新建立空闲表
            self.free_blocks.clear()
            self.init_free_block()

            # 重建引导区
            self.initCatlog()


class DiskManagement(object):
    """
        磁盘管理
    """

    def __init__(self, block_list, block_size, free_blocks: list):
        # 磁盘分块列表
        self.block_list = block_list
        # 每一分片磁盘大小
        self.block_size = block_size
        # 空闲块队列索引
        self.free_blocks = free_blocks

    def alloc(self, index_node: IndexNode, baseINFO):
        """
            首次适应算法,找到应该分配的块节点编号，写入文件或目录信息
            编辑了索引项
            重写了信息
        """
        # 获得应分有的磁盘块
        block_num = index_node.BLOCKNUM
        # 获得已占用的磁盘块
        occupy_indexs = list(filter(lambda x: x != -1, index_node.indexs))
        occupy_num = len(occupy_indexs)
        if block_num > occupy_num:
            # 还需要几块
            occupy_indexs.extend(self.findFreeBlock(block_num - occupy_num))
        elif block_num < occupy_num:
            # 释放超出的内存块
            t = block_num - occupy_num
            self.freeBlock(occupy_indexs[t:])
            occupy_indexs = occupy_indexs[:t]

        # 重写
        for i in occupy_indexs:
            self.block_list[i] = baseINFO

        # 重新编辑索引项
        index_node.indexs = np.full([8, ], -1)
        for i, v in enumerate(occupy_indexs):
            index_node.indexs[i] = v

    def findFreeBlock(self, num):
        for _ in range(num):
            yield self.free_blocks.pop(0)

    # 释放
    def freeBlock(self, indexs):
        # 将磁盘块加入空闲表
        self.free_blocks.extend(indexs)


if __name__ == '__main__':
    t = FileManagement()
    t.open(0)
