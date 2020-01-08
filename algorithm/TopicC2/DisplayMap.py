import os

os.environ['PROJ_LIB'] = r'H:\anaconda\envs\tensorflow\Library\share'

from PyQt5.QtWidgets import QApplication, QMainWindow, QGridLayout
from PyQt5.QtCore import QTimer

from TopicC2.MapUI import Ui_MainWindow

from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
import matplotlib.pyplot as plt

import sys

from mpl_toolkits.basemap import Basemap
from matplotlib.patches import Polygon
from TopicC2.Color import ToColor


class MyFigure(FigureCanvas):
    def __init__(self, width=3.9, height=2.7, dpi=100):
        # 创建一个Figure,该Figure为matplotlib下的Figure，不是matplotlib.pyplot下面的Figure
        self.fig = plt.figure(figsize=(width, height), dpi=dpi)
        # 在父类中激活Figure窗口，此句必不可少，否则不能显示图形
        super(MyFigure, self).__init__(self.fig)
        # 调用Figure下面的add_subplot方法，类似于matplotlib.pyplot下面的subplot(1,1,1)方法
        self.axes = self.fig.add_subplot(111)


class MapDisp(QMainWindow, Ui_MainWindow):
    def __init__(self):
        super(MapDisp, self).__init__()
        self.setupUi(self)

        # 以字典形式，存放省区域对应的矩形位置 省名:[位置1，位置2]
        self.provinces = dict()
        self.PrepareMapCanvas()
        # 存放颜色种类
        self.color = set()
        # 开启定时器
        self.timer = QTimer()
        self.timer.timeout.connect(self.updateMap)
        self.pb_start.clicked.connect(self.greedy)
        self.pb_reset.clicked.connect(self.reSetColor)
        self.pb_fback.clicked.connect(self.flashBack)

    def PrepareMapCanvas(self):
        self.MapFigure = MyFigure()
        self.MapFigureLayout = QGridLayout(self.mapBox)
        self.MapFigureLayout.addWidget(self.MapFigure)
        self.patches = self.MapFigure.axes.patches
        path = 'H:/py/python-machineLearn/source/'
        m = Basemap(llcrnrlon=77, llcrnrlat=14, urcrnrlon=140, urcrnrlat=51, projection='lcc', lat_1=33, lat_2=45,
                    lon_0=100)
        m.readshapefile(path + "china-shapefiles-master/china", 'china', drawbounds=True)
        m.readshapefile(path + "china-shapefiles-master/china_nine_dotted_line", 'nine_dotted', drawbounds=True)
        for n, seg in enumerate(m.china):
            statename = m.china_info[n]['OWNER'].replace("\x00", "").strip()
            poly = Polygon(seg, facecolor='#ffffff', edgecolor='#000000')
            self.MapFigure.axes.add_patch(poly)
            if statename in self.provinces:
                self.provinces[statename].append(n)
            else:
                self.provinces[statename] = [n]
                self.comboBox.addItem(statename)
        print(self.provinces)

    def greedy(self):
        start_name = self.comboBox.currentText()
        strategy = ToColor(start_name)
        self.path = strategy.greedy()
        self.timer.start(200)

    def flashBack(self):
        start_name = self.comboBox.currentText()
        color_s = int(self.spinBox.text())
        print("可使用颜色种类", color_s)
        strategy = ToColor(start_name)
        self.path = strategy.flashBack(color_s)
        self.timer.start(50)

    def updateMap(self):

        name, color = next(self.path)
        print(name)
        if name == -1:
            self.timer.stop()
            return None
        if name in self.provinces:
            print(name)
            for index in self.provinces[name]:
                self.patches[index].set_facecolor(color)
                self.patches[index].set_edgecolor(color)
        if color != '#ffffff':
            self.color.add(color)
        print(color)
        self.lcdNumber.display(str(len(self.color)))
        self.MapFigure.draw()

    def reSetColor(self):
        for p in self.patches:
            p.set_facecolor('#ffffff')
            p.set_edgecolor('#000000')
        self.lcdNumber.display('0')
        self.color = set()
        self.MapFigure.draw()


if __name__ == '__main__':
    app = QApplication(sys.argv)
    map_disp = MapDisp()
    map_disp.show()
    sys.exit(app.exec_())
