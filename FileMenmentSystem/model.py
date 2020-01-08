"""
    model
    IndexNode
"""
import numpy as np


class IndexNode(object):
    """
        存放文件属性及索引
        从底部向上连续存储
        索引节点块大小80B
    """

    def __init__(self, pn, NAME, TYPE, MODE, OWNER, block_num=0):
        # 父节点编号
        self.pn = pn  # 4B
        # 文件名
        self.NAME = NAME  # 12B
        # 文件类型
        self.TYPE = TYPE  # 11B
        # 文件权限
        self.MODE = MODE  # 1B
        # 文件创建者
        self.OWNER = OWNER  # 12B
        # 占用的磁盘块数
        self.BLOCKNUM = block_num  # 4B
        # 大小
        self.SIZE = 0  # 4B 单位字节
        # 8 个地址项,使用4B即2**32表示内存块编号 5 2 1 的混合索引编号
        self.indexs = np.full([8, ], -1)  # 4*8 =32B


class Catalog(object):
    """
        目录块信息抽象
        每个目录项占16字节
        一个4KB大小的磁盘块可饲用256个索引项
    """

    def __init__(self):
        # 抽象化，多个磁盘块下的文件信息组合成一块
        # 每个文件信息块占16字节，12字节:文件名 4字节:索引节点编号
        self.files = dict()


class File(object):
    """
        文件信息存放块抽象化
    """

    def __init__(self):
        # 磁盘块大小
        # 占用磁盘空间大小
        self.occupy = 0


class IndexStack(object):
    """
        抽象化索引信息块
        10个4KB大小的磁盘块可用512个索引节点
    """

    def __init__(self, nodeList):
        self.nodes = nodeList
