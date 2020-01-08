# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'barshow.ui'
#
# Created by: PyQt5 UI code generator 5.9.2
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(970, 707)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.BarDisplayGB = QtWidgets.QGroupBox(self.centralwidget)
        self.BarDisplayGB.setGeometry(QtCore.QRect(30, 60, 571, 491))
        self.BarDisplayGB.setObjectName("BarDisplayGB")
        self.pb_start = QtWidgets.QPushButton(self.centralwidget)
        self.pb_start.setGeometry(QtCore.QRect(690, 340, 75, 61))
        self.pb_start.setObjectName("pb_start")
        self.groupBox = QtWidgets.QGroupBox(self.centralwidget)
        self.groupBox.setGeometry(QtCore.QRect(630, 80, 276, 253))
        self.groupBox.setObjectName("groupBox")
        self.verticalLayout = QtWidgets.QVBoxLayout(self.groupBox)
        self.verticalLayout.setObjectName("verticalLayout")
        self.plainTextEdit = QtWidgets.QPlainTextEdit(self.groupBox)
        self.plainTextEdit.setObjectName("plainTextEdit")
        self.verticalLayout.addWidget(self.plainTextEdit)
        self.pb_sure = QtWidgets.QPushButton(self.groupBox)
        self.pb_sure.setObjectName("pb_sure")
        self.verticalLayout.addWidget(self.pb_sure)
        self.verticalLayout.setStretch(0, 3)
        self.verticalLayout.setStretch(1, 1)
        self.pb_reSet = QtWidgets.QPushButton(self.centralwidget)
        self.pb_reSet.setGeometry(QtCore.QRect(690, 420, 75, 61))
        self.pb_reSet.setObjectName("pb_reSet")
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 970, 23))
        self.menubar.setObjectName("menubar")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
        self.BarDisplayGB.setTitle(_translate("MainWindow", "barShow"))
        self.pb_start.setText(_translate("MainWindow", "开始"))
        self.groupBox.setTitle(_translate("MainWindow", "初始条件"))
        self.plainTextEdit.setPlainText(_translate("MainWindow", "8 5 3\n"
"8 0 0\n"
"4"))
        self.pb_sure.setText(_translate("MainWindow", "确认"))
        self.pb_reSet.setText(_translate("MainWindow", "重置"))

