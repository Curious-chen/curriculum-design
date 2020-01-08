from FileUI import Ui_MainWindow
from openUI import Ui_Dialog
from PyQt5.QtWidgets import QApplication, QMainWindow, QAbstractItemView, QTreeWidgetItem, QMenu, QAction, \
    QTableWidgetItem, QHeaderView, QDialog
from PyQt5 import QtGui, QtCore
from handle import FileManagement
from model import *
import random, json, sys


class MyOpenLog(QDialog, Ui_Dialog):
    def __init__(self):
        super(MyOpenLog, self).__init__()
        self.setupUi(self)
        self.FM = None
        self.FM: FileManagement
        self.ID = None
        self.pushButton.clicked.connect(self.rewrite)

    def rewrite(self):
        name = self.lE_name.text()
        SIZE = int(self.lE_size.text())
        power = self.lE_power.text()
        cdict = json.loads(self.plainTextEdit.toPlainText())
        cdict['name'] = name
        cdict['SIZE'] = SIZE
        cdict['power'] = power
        # 改变其值
        self.plainTextEdit.setPlainText(json.dumps(cdict))
        self.write()
        # 重新复制
        self.read()

    def showEvent(self, a0: QtGui.QShowEvent) -> None:
        self.read()
        print('打开了')

    def closeEvent(self, a0: QtGui.QCloseEvent) -> None:
        self.write()
        print('关闭了')

    def read(self):
        self.inform = self.FM.open(self.ID)
        self.plainTextEdit.setPlainText(self.inform)
        # 将数据加载到写入项中
        info_dict = json.loads(self.inform)
        self.lE_name.setText(info_dict['name'])
        self.lE_size.setText(str(info_dict['SIZE']))
        self.lE_power.setText(info_dict['power'])

    def write(self):
        ctext = self.plainTextEdit.toPlainText()
        # 当文件该变了
        if ctext != self.inform:
            print(ctext)
            self.FM.change(self.ID, self.pn, ctext, self.inform)
            self.mainWindow.showCatalog()
            self.mainWindow.showStatus()


class MyWindows(QMainWindow, Ui_MainWindow):
    def __init__(self):
        super(MyWindows, self).__init__()

        self.my_openDiglog = MyOpenLog()
        self.setupUi(self)
        # 设置列数，和标签
        self.tableWidget.setColumnCount(6)
        self.tableWidget.setHorizontalHeaderLabels(['name', 'ID', 'type', 'power', 'SIZE', 'OWNER'])

        # TODO 优化 2 设置水平方向表格为自适应的伸缩模式
        self.tableWidget.horizontalHeader().setSectionResizeMode(QHeaderView.Stretch)

        # 设置右键菜单
        self.tableWidget.setSelectionMode(QAbstractItemView.ExtendedSelection)
        self.tableWidget.setContextMenuPolicy(QtCore.Qt.CustomContextMenu)
        self.tableWidget.customContextMenuRequested[QtCore.QPoint].connect(self.myListWidgetContext)

        # 设为选择一行
        self.tableWidget.setSelectionBehavior(QAbstractItemView.SelectRows)
        # TODO 优化3 将表格变为禁止编辑
        self.tableWidget.setEditTriggers(QAbstractItemView.NoEditTriggers)
        self.tableWidget.doubleClicked.connect(self.deal_file)

        # 设置目录
        self.treeWidget.setHeaderLabel('目录')
        self.treeWidget.setSelectionMode(QAbstractItemView.ExtendedSelection)
        self.treeWidget.setColumnCount(1)
        self.treeWidget.itemClicked.connect(self.deal_treeItem)

        # 记录当前工作目录索引编号
        self.currentDir = 0

        # 初始化目录展示
        self.FM = FileManagement()
        self.showIndexes(self.treeWidget, 0)
        self.my_openDiglog.FM = self.FM

        # 默认登出
        self.pb_login.clicked.connect(self.login)
        self.pb_logout.clicked.connect(self.logout)
        self.logout()

    def logout(self):
        self.tableWidget.close()
        self.treeWidget.close()
        self.label_count.setText('')
        self.label_user.setText('')
        self.label_free.setText('')

    def login(self):
        dir_num = {'root': 1, 'Curious': 3, 'Uncle': 4}
        # 获得用户名
        user = self.lE_user.text()
        password = self.lE_pass.text()
        if self.FM.login(user, password):
            self.tableWidget.show()
            self.treeWidget.show()
            # 显示磁盘空闲状态
            self.showStatus()
            # 设置磁盘的总块数
            block_num_occ = self.FM.BLOCK_NUM
            self.label_user.setText(user)
            self.label_count.setText(f'{block_num_occ}')
            # 定位用户目录
            self.currentDir = dir_num[user]
            # table结构展示目录
            self.showCatalog()

    # tableWight点击事件处理
    def deal_file(self, q: QtCore.QModelIndex):
        print(type(q))
        print(q.row())
        c_row = q.row()
        name = self.tableWidget.item(c_row, 0).data(0)
        ID = self.tableWidget.item(c_row, 1).data(0)
        TYPE = self.tableWidget.item(c_row, 2).data(0)
        print(name, ID, TYPE)
        if TYPE == 'catalog':
            self.currentDir = int(ID)
            self.showCatalog()
        else:
            self.open()

    # treeWight点击事件处理
    def deal_treeItem(self, qTreeWidgetItem: QTreeWidgetItem):
        NAME = qTreeWidgetItem.text(0)
        INDEX = int(qTreeWidgetItem.text(1))
        TYPE = qTreeWidgetItem.text(2)
        if TYPE == 'catalog':
            print('>>>' * 50)
            print('当前文件信息:', NAME, INDEX, TYPE)
            self.currentDir = int(INDEX)
            self.showCatalog()
            print('>>>' * 50)

    # 树形式展开文件系统
    def showIndexes(self, p, i):
        indexs = self.FM.IS.nodes[i].indexs
        # 5 2 1 的data数据所在块编号

        # 数据抽象化后，目录索引项的0即可表示整个目录项
        catlog = self.FM.BLOCKLIST[indexs[0]]  # 抽象化的目录信息
        catlog: Catalog
        # 遍历所有目录项
        for name, nodeIndex in catlog.files.items():
            # 定义树节点
            t = QTreeWidgetItem(p)
            t.setText(0, name)
            t.setText(1, f'{nodeIndex}')
            # 获得文件FCB控制块
            indexNode = self.FM.IS.nodes[nodeIndex]
            # 读出文件类型
            t.setText(2, indexNode.TYPE)
            print(indexNode.TYPE)
            # 递归显示目录
            if indexNode.TYPE == 'catalog':
                print(indexNode.NAME, indexNode.indexs)
                self.showIndexes(t, nodeIndex)

    def set_table_item(self, row, data: list):
        self.tableWidget.setRowCount(row + 1)  # 设置显示的行数
        for i, v in enumerate(data):
            newItem = QTableWidgetItem(v)
            self.tableWidget.setItem(row, i, newItem)

    def showCatalog(self):
        # 显示当前目录
        INDEX = self.currentDir
        self.lE_currentDir.setText(self.FM.getCurrentDir(INDEX))
        # 清空
        # 修改当前目录
        rootNode = self.FM.IS.nodes[INDEX]
        rootNode: IndexNode
        print(rootNode.NAME, rootNode.indexs)
        rows = 1
        # 获得目录项所处的第一个磁盘块表编号
        ind = rootNode.indexs[0]
        # 抽象化的目录信息，可得所有目录项
        catlog = self.FM.BLOCKLIST[ind]
        catlog: Catalog
        self.set_table_item(rows - 1, ['.', str(INDEX), 'catalog', rootNode.MODE, str(rootNode.SIZE), rootNode.OWNER])
        rows += 1
        self.set_table_item(rows - 1, ['..', str(rootNode.pn), 'catalog'])
        rows += 1
        for name, nodeIndex in catlog.files.items():
            print(name, nodeIndex)
            # 获得该文件索引节点、获得属性
            indexNode = self.FM.IS.nodes[nodeIndex]
            self.set_table_item(rows - 1,
                                [name, str(nodeIndex), indexNode.TYPE, indexNode.MODE, str(indexNode.SIZE),
                                 indexNode.OWNER])
            rows += 1

    print('>>>' * 50)

    # tableWight 右键菜单设置
    def myListWidgetContext(self, q: QtCore.QPoint):
        popMenu = QMenu()
        popMenu.addAction((QAction(u'open', self)))
        popMenu.addAction(QAction(u'mkdir', self))
        popMenu.addAction(QAction(u'touch', self))
        popMenu.addAction(QAction(u'rm', self))
        popMenu.addAction(QAction(u'Format disk', self))
        popMenu.triggered[QAction].connect(self.processtrigger)
        popMenu.exec_(QtGui.QCursor.pos())

    # tableWight 右键菜单事件处理
    def processtrigger(self, q: QAction):
        print(type(q), ":", q.text())
        op = q.text()

        if op == 'mkdir':
            self.mkdir('catalog{:0>3d}'.format(random.randint(1, 1000)))
        elif op == 'touch':
            self.touch('file{:0>3d}'.format(random.randint(1, 1000)))
        elif op == 'open':
            self.open()
        elif op == 'rm':
            self.rm()
        elif op == 'Format disk':
            self.currentDir = 0
            self.FM.empty_format()
            self.showCatalog()
            # 重置树形目录
            self.treeWidget.clear()
            self.showIndexes(self.treeWidget, 0)
        self.showStatus()

    # 展示磁盘状态
    def showStatus(self):
        block_num_free = len(self.FM.free_blocks)
        self.label_free.setText(f'{block_num_free}')

    def mkdir(self, name):
        print(self.currentDir, name)
        node = self.FM.IS.nodes[self.currentDir]
        node: IndexNode
        # 判断是否有创建目录的权限
        if self.FM.getPower(node.OWNER, node.MODE, 'mkdir'):
            self.FM.mkdir(name, 'drwrw', self.FM.user, self.currentDir)
            self.treeWidget.clear()
            self.showIndexes(self.treeWidget, 0)
            self.showCatalog()

    def rm(self):
        print('>>>' * 20, 'rm', '>>>' * 20)
        length = self.tableWidget.rowCount()
        # 如果item被选择，则删除
        for i in range(2, length):
            item = self.tableWidget.item(i, 1)
            if item.isSelected():
                ID = int(item.data(0))
                node = self.FM.IS.nodes[ID]
                node: IndexNode
                if self.FM.getPower(node.OWNER, node.MODE, 'rm'):
                    self.FM.rm(self.currentDir, int(ID))
        self.showCatalog()
        # 重置树形目录
        self.treeWidget.clear()
        self.showIndexes(self.treeWidget, 0)

        print('>>>' * 42)

    def touch(self, name):
        print('>>>' * 20, 'touch', '>>>' * 20)
        # 获得文件信息
        node = self.FM.IS.nodes[self.currentDir]
        node: IndexNode
        # 判断是否有touch权限
        if self.FM.getPower(node.OWNER, node.MODE, 'touch'):
            self.FM.touch(name, '~rwrw', self.FM.user, self.currentDir)
            self.treeWidget.clear()
            self.showIndexes(self.treeWidget, 0)
            self.showCatalog()
        print('>>>' * 42)

    def open(self):
        print('>>>' * 20, 'open', '>>>' * 20)
        length = self.tableWidget.rowCount()
        # 如果item被选择，则打开
        for i in range(length):
            item = self.tableWidget.item(i, 1)
            if item.isSelected():
                ID = int(item.data(0))
                # 获得文件信息
                node = self.FM.IS.nodes[ID]
                node: IndexNode
                # 权限判断
                if self.FM.getPower(node.OWNER, node.MODE, 'open'):
                    # 打开对话框
                    self.my_openDiglog.ID = ID
                    self.my_openDiglog.pn = self.currentDir
                    self.my_openDiglog.mainWindow = self
                    self.my_openDiglog.show()
                break
        print('>>>' * 42)


if __name__ == '__main__':
    app = QApplication(sys.argv)
    fileWin = MyWindows()
    fileWin.show()
    sys.exit(app.exec_())
