from TopicB1.SeqUI import Ui_MainWindow
from PyQt5.QtWidgets import QApplication, QMainWindow, QPushButton, QLabel
from PyQt5.QtCore import QTimer
import sys
from TopicB1.alignment import Alignment


class Mywindow(QMainWindow, Ui_MainWindow):
    def __init__(self, parent=None):
        super(Mywindow, self).__init__(parent)
        self.timer = QTimer()
        self.setupUi(self, list(' AGTGATG'), list(' GTTAG'))
        self.pb_start.clicked.connect(self.dynamic)
        self.pb_reset.clicked.connect(self.setInitColor)
        self.pb_sure.clicked.connect(self.resetColorBox)
        self.timer.timeout.connect(self.UpdateTextColor)
        self.tar = list()

    def getSeqs(self):
        seq1 = list(str(self.seqText1.toPlainText()).strip())
        seq2 = list(str(self.seqText2.toPlainText()).strip())
        return seq1, seq2

    def resetColorBox(self):
        M, N = self.getSeqs()
        M.insert(0, ' ')
        N.insert(0, ' ')
        print(M,N)
        self.setScoreBox(M, N)

    def setTree(self):
        for i, p in enumerate(self.gb_tree.children()[1:]):
            p: QPushButton
            p.setText(self.treeText[i])

    def dynamic(self):

        # 生成动规划的过程
        M, N = self.getSeqs()
        print(M, N)
        alignment = Alignment(M, N)
        for status in alignment.aligment():
            print(status)
            self.addProcess(status, alignment.path)

        # 得分最高路径
        for path_index in alignment.getMaxScore():
            x, y = path_index
            self.tar.append([x, y, 0.1, '#ffff7f'])
        self.timer.start(100)

    def addProcess(self, status, path):
        x, y, value, seqs = status
        self.tar.append([x, y, 0.1, '#ffffff'])
        flag = path[x][y]
        if flag == '-':
            self.tar.append([x, y - 1, 0.1, '#ff5fff'])
            self.tar.append([x, y - 1, 0.1, 'rgb(170, 255, 255)'])
        elif flag == '|':
            self.tar.append([x - 1, y, 0.1, '#ff5fff'])
            self.tar.append([x - 1, y, 0.1, 'rgb(170, 255, 255)'])
        elif flag == '`':
            self.tar.append([x - 1, y - 1, 0.1, '#ff5fff'])
            self.tar.append([x - 1, y - 1, 0.1, 'rgb(170, 255, 255)'])
        self.tar.append([x, y, 0.2, seqs])
        self.tar.append([x, y, value, 'rgb(170, 255, 255)'])

    def UpdateTextColor(self):
        if len(self.tar) == 0:
            self.timer.stop()
            return None
        x, y, value, color = self.tar.pop(0)
        if value == 0.2:
            self.seqX.setText(color[0])
            self.seqY.setText(color[1])
            return None
        name = "label_{}_{}".format(int(x + 1), int(y + 1))
        print(name)
        print(x, y, value, color)
        qt = self.scoreBox.findChild(QLabel, name)
        qt: QLabel
        if value != 0.1:
            qt.setText(str(value))
        qt.setStyleSheet("background-color:{}".format(color))

    def setInitColor(self):
        for i in range(1, 9):
            for j in range(1, 7):
                name = "label_{}_{}".format(i, j)
                qt = self.scoreBox.findChild(QLabel, name)
                qt: QLabel
                qt.setText('0')
                qt.setStyleSheet("background-color:{}".format('rgb(85, 255, 127)'))
        self.seqX.setText("")
        self.seqY.setText("")


if __name__ == '__main__':
    app = QApplication(sys.argv)
    ui = Mywindow()
    ui.show()
    sys.exit(app.exec_())
