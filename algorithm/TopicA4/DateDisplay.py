from TopicA4.DataDisplayUI import Ui_MainWindow
from PyQt5.QtWidgets import QApplication, QMainWindow, QGridLayout
from PyQt5.QtCore import QTimer
import sys
import numpy as np

"""
    在PyQt5设计的GUI界面中显示matplotlib绘制的图形
        https://blog.csdn.net/panrenlong/article/details/80183519
    
"""
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.figure import Figure
from Pour import Pour
from matplotlib.patches import Rectangle


# from matplotlib.axes._subplots

class MyFifure(FigureCanvas):
    def __init__(self, parent=None, width=3.9, height=2.7, dpi=100):
        # 其中构造函数Figure()用来创建一个类似Matlab的figure()或matplotlib.pyplot的figure()。
        # 其中：width，height, 为窗口尺寸，5 英寸 * 4 英寸，分辨率为dpi = 10
        self.fig = Figure(figsize=(width, height), dpi=100)
        super(MyFifure, self).__init__(self.fig)
        # 它是用来创建子图，如图matlab的subplot(2,2,1),表示共有4个子图，当前为第一个子图。具体应用如下：
        self.ax = self.fig.add_subplot(111)
        print(type(self.ax))

    def test(self):
        x = [1, 2, 3, 4, 5, 6, 7]
        y = [2, 1, 3, 5, 6, 4, 3]

        #
        self.ax.plot(x, y)


class ImgDisp(QMainWindow, Ui_MainWindow):
    def __init__(self, parent=None):
        super(ImgDisp, self).__init__(parent)
        self.pathList = list()
        self.setupUi(self)
        self.PrepareBarCanvas()
        self.timer = QTimer()
        self.timer.timeout.connect(self.UpdateImgs)
        self.pb_start.clicked.connect(self.startShow)
        self.pb_sure.clicked.connect(self.reSetBar)
        self.pb_reSet.clicked.connect(self.reSetBar)
        self.updateList = list()

    def Init_Widgets(self):
        date = str(self.plainTextEdit.toPlainText()).split()
        print(date)
        date = list(int(_) for _ in date)
        # 水壶容量
        self.capacity = tuple(date[:3])
        # 初始时，水壶中水的情况
        self.situation = date[3:-1]
        self.endD = date[-1]

    def startShow(self):
        self.pour()
        self.timer.start(2)

    def reSetBar(self):
        self.Init_Widgets()
        self.BarFigure.ax.cla()
        self.repeatDrawBar(self.situation)
        self.BarFigure.draw()

    def repeatDrawBar(self, s):
        self.BarFigure.ax.set_xlim(-1, 7)
        self.BarFigure.ax.set_ylim(0, max(self.capacity) + 2)
        self.bar = self.BarFigure.ax.bar(np.array([0, 3, 6]), np.array(s),
                                         color=['#d65f5f', '#5fba7d', '#abcdef'], width=0.6)
        self.patches = self.bar.patches
        for i, r in enumerate(self.patches):
            r.set_label('capacity:{:^3d}'.format(self.capacity[i]))

    def PrepareBarCanvas(self):
        self.Init_Widgets()
        self.BarFigure = MyFifure()
        self.BarFigureLayout = QGridLayout(self.BarDisplayGB)
        self.BarFigureLayout.addWidget(self.BarFigure)
        self.repeatDrawBar(self.situation)
        self.BarFigure.draw()  # 开始绘制
        self.patches = self.bar.patches

    def pour(self):
        pour = Pour(self.capacity, self.situation, self.endD)
        pour.run()
        path = pour.pathList

        # 以0.1的水量为迭代倒水
        for i, p in enumerate(path[1:]):
            p = list(p)
            a, b = p[-3:-1]
            length = p[-1]
            temp = list(path[i]).copy()
            for _ in np.arange(0, length, 0.1):
                temp[a] = temp[a] - 0.1
                temp[b] = temp[b] + 0.1
                self.pathList.append(temp[:3])

    def UpdateImgs(self):
        if len(self.pathList) == 0:
            print("关闭")
            self.timer.stop()
            return None
        self.BarUpdate(self.pathList.pop(0))

    def BarUpdate(self, heights):
        x = np.array(heights).astype(float)
        print(x)
        for i, rectangle in enumerate(self.patches):
            rectangle: Rectangle
            rectangle.set_height(x[i])
            rectangle.set_label('capacity:{:^3d}'.format(self.capacity[i]))
            self.BarFigure.ax.text(i * 3 - 0.3, self.capacity[i] + 0.2,
                                   '{:^4.2f}/{:^3d}'.format(float(x[i]), self.capacity[i]))

        self.bar.patches = self.patches
        self.BarFigure.ax.legend()
        self.BarFigure.draw()  # 开始绘制
        self.BarFigure.ax.cla()
        self.repeatDrawBar(x)


if __name__ == '__main__':
    app = QApplication(sys.argv)
    ui = ImgDisp()
    ui.show()
    sys.exit(app.exec_())
