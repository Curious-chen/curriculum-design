# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'FileUI.ui'
#
# Created by: PyQt5 UI code generator 5.13.1
#
# WARNING! All changes made in this file will be lost!


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(1293, 862)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.groupBox = QtWidgets.QGroupBox(self.centralwidget)
        self.groupBox.setGeometry(QtCore.QRect(60, 100, 911, 641))
        self.groupBox.setObjectName("groupBox")
        self.horizontalLayout = QtWidgets.QHBoxLayout(self.groupBox)
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.treeWidget = QtWidgets.QTreeWidget(self.groupBox)
        self.treeWidget.setObjectName("treeWidget")
        self.treeWidget.headerItem().setText(0, "1")
        self.horizontalLayout.addWidget(self.treeWidget)
        self.tableWidget = QtWidgets.QTableWidget(self.groupBox)
        self.tableWidget.setObjectName("tableWidget")
        self.tableWidget.setColumnCount(0)
        self.tableWidget.setRowCount(0)
        self.horizontalLayout.addWidget(self.tableWidget)
        self.horizontalLayout.setStretch(0, 2)
        self.horizontalLayout.setStretch(1, 5)
        self.groupBox_2 = QtWidgets.QGroupBox(self.centralwidget)
        self.groupBox_2.setGeometry(QtCore.QRect(1020, 140, 191, 171))
        self.groupBox_2.setObjectName("groupBox_2")
        self.gridLayout = QtWidgets.QGridLayout(self.groupBox_2)
        self.gridLayout.setObjectName("gridLayout")
        self.label_3 = QtWidgets.QLabel(self.groupBox_2)
        self.label_3.setStyleSheet("background-color:rgb(170, 255, 127)")
        self.label_3.setAlignment(QtCore.Qt.AlignCenter)
        self.label_3.setObjectName("label_3")
        self.gridLayout.addWidget(self.label_3, 0, 0, 1, 1)
        self.label_user = QtWidgets.QLabel(self.groupBox_2)
        self.label_user.setStyleSheet("background-color:rgb(170, 255, 127)")
        self.label_user.setAlignment(QtCore.Qt.AlignCenter)
        self.label_user.setObjectName("label_user")
        self.gridLayout.addWidget(self.label_user, 0, 1, 1, 1)
        self.label = QtWidgets.QLabel(self.groupBox_2)
        self.label.setStyleSheet("background-color:rgb(170, 255, 127)")
        self.label.setAlignment(QtCore.Qt.AlignCenter)
        self.label.setObjectName("label")
        self.gridLayout.addWidget(self.label, 1, 0, 1, 1)
        self.label_free = QtWidgets.QLabel(self.groupBox_2)
        self.label_free.setStyleSheet("background-color:rgb(170, 255, 127)")
        self.label_free.setText("")
        self.label_free.setAlignment(QtCore.Qt.AlignCenter)
        self.label_free.setObjectName("label_free")
        self.gridLayout.addWidget(self.label_free, 1, 1, 1, 1)
        self.label_2 = QtWidgets.QLabel(self.groupBox_2)
        self.label_2.setStyleSheet("background-color:rgb(255, 170, 255)")
        self.label_2.setAlignment(QtCore.Qt.AlignCenter)
        self.label_2.setObjectName("label_2")
        self.gridLayout.addWidget(self.label_2, 2, 0, 1, 1)
        self.label_count = QtWidgets.QLabel(self.groupBox_2)
        self.label_count.setStyleSheet("background-color:rgb(255, 170, 255)")
        self.label_count.setText("")
        self.label_count.setAlignment(QtCore.Qt.AlignCenter)
        self.label_count.setObjectName("label_count")
        self.gridLayout.addWidget(self.label_count, 2, 1, 1, 1)
        self.groupBox_3 = QtWidgets.QGroupBox(self.centralwidget)
        self.groupBox_3.setGeometry(QtCore.QRect(1020, 350, 221, 111))
        self.groupBox_3.setStyleSheet("background-color:rgb(85, 255, 255)")
        self.groupBox_3.setObjectName("groupBox_3")
        self.gridLayout_2 = QtWidgets.QGridLayout(self.groupBox_3)
        self.gridLayout_2.setObjectName("gridLayout_2")
        self.label_5 = QtWidgets.QLabel(self.groupBox_3)
        self.label_5.setStyleSheet("background-color:rgb(85, 255, 255)")
        self.label_5.setAlignment(QtCore.Qt.AlignCenter)
        self.label_5.setObjectName("label_5")
        self.gridLayout_2.addWidget(self.label_5, 0, 0, 1, 1)
        self.lE_user = QtWidgets.QLineEdit(self.groupBox_3)
        self.lE_user.setObjectName("lE_user")
        self.gridLayout_2.addWidget(self.lE_user, 0, 1, 1, 1)
        self.label_6 = QtWidgets.QLabel(self.groupBox_3)
        self.label_6.setStyleSheet("background-color:rgb(85, 255, 255)")
        self.label_6.setAlignment(QtCore.Qt.AlignCenter)
        self.label_6.setObjectName("label_6")
        self.gridLayout_2.addWidget(self.label_6, 1, 0, 1, 1)
        self.lE_pass = QtWidgets.QLineEdit(self.groupBox_3)
        self.lE_pass.setText("")
        self.lE_pass.setEchoMode(QtWidgets.QLineEdit.Password)
        self.lE_pass.setObjectName("lE_pass")
        self.gridLayout_2.addWidget(self.lE_pass, 1, 1, 1, 1)
        self.pb_login = QtWidgets.QPushButton(self.centralwidget)
        self.pb_login.setGeometry(QtCore.QRect(1170, 490, 75, 71))
        self.pb_login.setObjectName("pb_login")
        self.lE_currentDir = QtWidgets.QLineEdit(self.centralwidget)
        self.lE_currentDir.setGeometry(QtCore.QRect(340, 70, 621, 31))
        self.lE_currentDir.setObjectName("lE_currentDir")
        self.label_7 = QtWidgets.QLabel(self.centralwidget)
        self.label_7.setGeometry(QtCore.QRect(230, 70, 91, 31))
        self.label_7.setStyleSheet("background-color:rgb(170, 255, 127)")
        self.label_7.setAlignment(QtCore.Qt.AlignCenter)
        self.label_7.setObjectName("label_7")
        self.pb_logout = QtWidgets.QPushButton(self.centralwidget)
        self.pb_logout.setGeometry(QtCore.QRect(1050, 490, 75, 71))
        self.pb_logout.setObjectName("pb_logout")
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 1293, 23))
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
        self.groupBox.setTitle(_translate("MainWindow", "文件查看"))
        self.groupBox_2.setTitle(_translate("MainWindow", "status"))
        self.label_3.setText(_translate("MainWindow", "用户"))
        self.label_user.setText(_translate("MainWindow", "root"))
        self.label.setText(_translate("MainWindow", "空闲"))
        self.label_2.setText(_translate("MainWindow", "总计"))
        self.groupBox_3.setTitle(_translate("MainWindow", "登录"))
        self.label_5.setText(_translate("MainWindow", "用户"))
        self.lE_user.setText(_translate("MainWindow", "root"))
        self.label_6.setText(_translate("MainWindow", "密码"))
        self.pb_login.setText(_translate("MainWindow", "登录"))
        self.label_7.setText(_translate("MainWindow", "当前目录"))
        self.pb_logout.setText(_translate("MainWindow", "注销"))
