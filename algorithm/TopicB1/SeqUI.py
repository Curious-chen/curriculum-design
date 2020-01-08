# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'seq.ui'
#
# Created by: PyQt5 UI code generator 5.9.2
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_MainWindow(object):
    def setupUi(self, MainWindow, X, Y):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(959, 727)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.scoreBox = QtWidgets.QGroupBox(self.centralwidget)
        self.scoreBox.setGeometry(QtCore.QRect(70, 90, 481, 441))
        self.scoreBox.setObjectName("scoreBox")
        self.gridLayout = QtWidgets.QGridLayout(self.scoreBox)
        self.gridLayout.setObjectName("gridLayout")
        self.setScoreBox(X,Y)

        self.resultBox = QtWidgets.QGroupBox(self.centralwidget)
        self.resultBox.setGeometry(QtCore.QRect(610, 210, 181, 141))
        self.resultBox.setObjectName("resultBox")
        self.verticalLayout = QtWidgets.QVBoxLayout(self.resultBox)
        self.verticalLayout.setObjectName("verticalLayout")
        self.seqX = QtWidgets.QLabel(self.resultBox)
        self.seqX.setStyleSheet("background-color:rgb(160, 165, 255)")
        self.seqX.setText("")
        self.seqX.setObjectName("seqX")
        self.verticalLayout.addWidget(self.seqX)
        self.seqY = QtWidgets.QLabel(self.resultBox)
        self.seqY.setStyleSheet("background-color:rgb(160, 165, 255)")
        self.seqY.setText("")
        self.seqY.setObjectName("seqY")
        self.verticalLayout.addWidget(self.seqY)
        self.pb_start = QtWidgets.QPushButton(self.centralwidget)
        self.pb_start.setGeometry(QtCore.QRect(620, 400, 75, 71))
        self.pb_start.setObjectName("pb_start")
        self.pb_reset = QtWidgets.QPushButton(self.centralwidget)
        self.pb_reset.setGeometry(QtCore.QRect(730, 400, 75, 71))
        self.pb_reset.setObjectName("pb_reset")

        self.resultBox_2 = QtWidgets.QGroupBox(self.centralwidget)
        self.resultBox_2.setGeometry(QtCore.QRect(610, 20, 181, 141))
        self.resultBox_2.setObjectName("resultBox_2")
        self.verticalLayout_2 = QtWidgets.QVBoxLayout(self.resultBox_2)
        self.verticalLayout_2.setObjectName("verticalLayout_2")
        self.seqText1 = QtWidgets.QPlainTextEdit(self.resultBox_2)
        self.seqText1.setObjectName("seqText1")
        self.verticalLayout_2.addWidget(self.seqText1)
        self.seqText2 = QtWidgets.QPlainTextEdit(self.resultBox_2)
        self.seqText2.setObjectName("seqText2")
        self.verticalLayout_2.addWidget(self.seqText2)
        self.pb_sure = QtWidgets.QPushButton(self.centralwidget)
        self.pb_sure.setGeometry(QtCore.QRect(820, 60, 75, 71))
        self.pb_sure.setObjectName("pb_sure")
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 959, 23))
        self.menubar.setObjectName("menubar")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def setScoreBox(self, X, Y):
        for i in range(self.gridLayout.count()):
            self.gridLayout.itemAt(0).widget().close()
            self.gridLayout.removeWidget(self.gridLayout.itemAt(0).widget())

        for j, value in enumerate(Y):
            j += 1
            label = QtWidgets.QLabel(self.scoreBox)
            label.setStyleSheet("background-color:rgb(85, 255, 127)")
            label.setAlignment(QtCore.Qt.AlignCenter)
            label.setObjectName("label_{}_{}".format(0, j))
            label.setText(str(value))
            self.gridLayout.addWidget(label, 0, j, 1, 1)
        for i, value in enumerate(X):
            i += 1
            label = QtWidgets.QLabel(self.scoreBox)
            label.setStyleSheet("background-color:rgb(85, 255, 127)")
            label.setAlignment(QtCore.Qt.AlignCenter)
            label.setObjectName("label_{}_{}".format(i, 0))
            label.setText(str(value))
            self.gridLayout.addWidget(label, i, 0, 1, 1)
        m = len(X)
        n = len(Y)
        for i in range(1, m + 1):
            for j in range(1, n + 1):
                label = QtWidgets.QLabel(self.scoreBox)
                label.setStyleSheet("background-color:rgb(85, 255, 127)")
                label.setAlignment(QtCore.Qt.AlignCenter)
                name = "label_{}_{}".format(int(i), int(j))
                label.setObjectName(name)
                label.setText('0')
                print(label.objectName())
                self.gridLayout.addWidget(label, i, j, 1, 1)
    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
        self.resultBox.setTitle(_translate("MainWindow", "结果"))
        self.pb_start.setText(_translate("MainWindow", "动态规划"))
        self.pb_reset.setText(_translate("MainWindow", "重置"))
        self.resultBox_2.setTitle(_translate("MainWindow", "输入"))
        self.seqText1.setPlainText(_translate("MainWindow", "AGTGATG"))
        self.seqText2.setPlainText(_translate("MainWindow", "GTTAG"))
        self.pb_sure.setText(_translate("MainWindow", "确认"))
