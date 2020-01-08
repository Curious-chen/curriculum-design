from TopicB2.treeUI import Ui_MainWindow
from PyQt5.QtWidgets import QApplication, QMainWindow, QFileDialog, QPushButton
from PyQt5.QtCore import QTimer
import sys
import os
from TopicB2.TreePagoda import TreePagoda
import numpy as np


class Mywindow(QMainWindow, Ui_MainWindow):
    def __init__(self, parent=None):
        super(Mywindow, self).__init__(parent)
        self.setupUi(self)
        self.toolButton.clicked.connect(self.selectFile)
        self.pushButton.clicked.connect(self.changeTree)
        self.pb_restart.clicked.connect(self.setInitColor)
        self.pb_plan.clicked.connect(self.dynamic)
        self.treeText = [pb.text() for pb in self.gb_tree.children()[1:]]
        self.tar = list()


    def selectFile(self):
        file_name = QFileDialog.getOpenFileName(self, 'open file dialog', r'H:\py\python-machineLearn\source\tree')
        self.recordPaths.addItem(file_name[0])
        self.recordPaths.setCurrentIndex(1)
        print(file_name)

    def changeTree(self):
        path = self.recordPaths.currentText()
        if os.path.exists(path):
            with open(path, 'r', encoding='utf-8') as f:
                context = f.read().split()
                if len(context) == len(self.treeText):
                    self.treeText = context
                    self.setInitColor()

    def setTree(self):
        for i, p in enumerate(self.gb_tree.children()[1:]):
            p: QPushButton
            p.setText(self.treeText[i])

    def dynamic(self):

        # 生成动规划的过程
        pagoda = self.conv()
        print(pagoda)
        tree = TreePagoda(pagoda)
        for status in tree.run():
            print(status)
            self.addProcess(status)
        for pathIndex in tree.createdPath():
            self.tar.append([pathIndex, -1, 'yellow'])
        self.timer = QTimer()
        self.timer.start(1000)
        self.timer.timeout.connect(self.UpdateTextColor)

    def addProcess(self, status):
        currentIndex, nextIndex, value = status
        self.tar.append([currentIndex, -1, 'rgb(170, 85, 127)'])
        if nextIndex != 0:
            self.tar.append([nextIndex, -1, 'rgb(170, 85, 127)'])
            self.tar.append([nextIndex, -1, 'rgb(234, 237, 255)'])
        self.tar.append([currentIndex, value, 'yellow'])
        self.tar.append([currentIndex, value, 'rgb(234, 237, 255)'])

    def conv(self):
        layer = 0
        pododa = list()
        for i, value in enumerate(self.treeText):
            pododa.append(int(value))
            if (layer * (layer + 1)) / 2 + layer == i:
                for j in range(4 - layer):
                    pododa.append(0)
                layer += 1
        pododa = np.array(pododa).reshape([5, 5])
        return pododa

    def UpdateTextColor(self):
        if len(self.tar) == 0:
            self.timer.stop()
            return None
        index, value, color = self.tar.pop(0)
        qb = self.gb_tree.children()[index + 1]
        qb: QPushButton
        if value != -1:
            qb.setText(str(value))
        qb.setStyleSheet("background-color:{}".format(color))

    def setInitColor(self):
        for i, qb in enumerate(self.gb_tree.children()[1:]):
            qb.setText(self.treeText[i])
            qb.setStyleSheet("background-color:{rgb(234, 237, 255)}")


if __name__ == '__main__':
    app = QApplication(sys.argv)
    ui = Mywindow()
    ui.show()
    sys.exit(app.exec_())
