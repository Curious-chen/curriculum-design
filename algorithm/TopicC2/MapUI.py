# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'map.ui'
#
# Created by: PyQt5 UI code generator 5.9.2
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(1124, 850)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.mapBox = QtWidgets.QGroupBox(self.centralwidget)
        self.mapBox.setGeometry(QtCore.QRect(60, 70, 771, 701))
        self.mapBox.setObjectName("mapBox")
        self.pb_start = QtWidgets.QPushButton(self.centralwidget)
        self.pb_start.setGeometry(QtCore.QRect(960, 230, 75, 61))
        self.pb_start.setObjectName("pb_start")
        self.pb_reset = QtWidgets.QPushButton(self.centralwidget)
        self.pb_reset.setGeometry(QtCore.QRect(960, 350, 75, 61))
        self.pb_reset.setObjectName("pb_reset")
        self.groupBox = QtWidgets.QGroupBox(self.centralwidget)
        self.groupBox.setGeometry(QtCore.QRect(830, 70, 211, 101))
        self.groupBox.setObjectName("groupBox")
        self.horizontalLayout = QtWidgets.QHBoxLayout(self.groupBox)
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.label = QtWidgets.QLabel(self.groupBox)
        self.label.setStyleSheet("")
        self.label.setObjectName("label")
        self.horizontalLayout.addWidget(self.label)
        self.comboBox = QtWidgets.QComboBox(self.groupBox)
        self.comboBox.setObjectName("comboBox")
        self.comboBox.addItem("")
        self.horizontalLayout.addWidget(self.comboBox)
        self.horizontalLayout.setStretch(0, 1)
        self.horizontalLayout.setStretch(1, 3)
        self.groupBox_2 = QtWidgets.QGroupBox(self.centralwidget)
        self.groupBox_2.setGeometry(QtCore.QRect(870, 640, 198, 55))
        self.groupBox_2.setObjectName("groupBox_2")
        self.horizontalLayout_2 = QtWidgets.QHBoxLayout(self.groupBox_2)
        self.horizontalLayout_2.setObjectName("horizontalLayout_2")
        self.label_2 = QtWidgets.QLabel(self.groupBox_2)
        self.label_2.setObjectName("label_2")
        self.horizontalLayout_2.addWidget(self.label_2)
        self.lcdNumber = QtWidgets.QLCDNumber(self.groupBox_2)
        font = QtGui.QFont()
        font.setFamily("MingLiU_HKSCS-ExtB")
        font.setPointSize(11)
        self.lcdNumber.setFont(font)
        self.lcdNumber.setLayoutDirection(QtCore.Qt.LeftToRight)
        self.lcdNumber.setAutoFillBackground(False)
        self.lcdNumber.setStyleSheet("color:rgb(255, 0, 0)")
        self.lcdNumber.setDigitCount(1)
        self.lcdNumber.setMode(QtWidgets.QLCDNumber.Dec)
        self.lcdNumber.setSegmentStyle(QtWidgets.QLCDNumber.Flat)
        self.lcdNumber.setProperty("value", 0.0)
        self.lcdNumber.setProperty("intValue", 0)
        self.lcdNumber.setObjectName("lcdNumber")
        self.horizontalLayout_2.addWidget(self.lcdNumber)
        self.pb_fback = QtWidgets.QPushButton(self.centralwidget)
        self.pb_fback.setGeometry(QtCore.QRect(1000, 470, 75, 61))
        self.pb_fback.setObjectName("pb_fback")
        self.spinBox = QtWidgets.QSpinBox(self.centralwidget)
        self.spinBox.setGeometry(QtCore.QRect(900, 470, 81, 61))
        self.spinBox.setMinimum(1)
        self.spinBox.setMaximum(6)
        self.spinBox.setObjectName("spinBox")
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 1124, 23))
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
        self.mapBox.setTitle(_translate("MainWindow", "ChinaMap"))
        self.pb_start.setText(_translate("MainWindow", "贪心策略"))
        self.pb_reset.setText(_translate("MainWindow", "重置"))
        self.groupBox.setTitle(_translate("MainWindow", "选择"))
        self.label.setText(_translate("MainWindow", " 起点:"))
        self.comboBox.setItemText(0, _translate("MainWindow", "贵州省"))
        self.groupBox_2.setTitle(_translate("MainWindow", "计数"))
        self.label_2.setText(_translate("MainWindow", "已使用的颜色总数："))
        self.pb_fback.setText(_translate("MainWindow", "递归回溯"))

