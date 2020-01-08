"""
    已知中国地图，对各省进行着色，要求相邻省所使用的颜色不同，并保证使用的颜色总数最少
    created by Curious
    2019/11/22 10:27
"""

"""
    根据研究，四种颜色能将所有地图着色
    而中国地图，明显需要至少两种以上颜色进行着色
    
    1.设定可用颜色数为2
    2.使用回溯法遍历中国地图的关系图
    3.若满足着色条件则着色，否则回溯
    
    着色条件
    1. 和相邻区域的颜色不同
    2. 在1条件下，能取出其他颜色
"""

"""
    https://blog.csdn.net/maoye/article/details/90157850
    
    中国各省名称+ 经纬度
    https://blog.csdn.net/weixin_40285832/article/details/94465184
    
    地图着色问题
    https://blog.csdn.net/S_hen_/article/details/86243869
"""

"""
    （1）输入相邻关系图 记图节点个数n,边的条数e
    （2）选择一个点为起点加入待遍历队列。
    （3）从队列中取出第一个元素，判断它的邻接点的上色情况,
    （4）在颜色序列中去除相邻点的颜色，并将未上色点加入队列，取出序列的首元素，为该元素染色(贪心选择)
    （5）重复第（2）步直到队列为空。
"""

"""
    m-着色优化问题
    将即将着色的所有点排成一个序列(有利于回溯，检查染色是否冲突只用检查序列前面的)
    
"""
from matplotlib import pyplot as plt
import matplotlib as mpl

# 解决中文编码问题
mpl.rcParams['font.sans-serif'] = [u'simHei']
mpl.rcParams['axes.unicode_minus'] = False

adj_dict = {
    '北京': ['河北', '天津'],
    '天津': ['北京', '河北'],
    '河北': ['北京', '天津', '山东', '河南', '山西', '内蒙古', '辽宁'],
    '山西': ['内蒙古', '陕西', '河南', '河北', '北京'],
    '陕西': ['山西', '河南', '湖北', '重庆', '四川', '甘肃', '宁夏', '内蒙古'],
    '内蒙古': ['黑龙江', '吉林', '辽宁', '河北', '山西', '宁夏', '甘肃', '陕西'],
    '河南': ['河北', '湖北', '陕西', '安徽', '山西', '山东'],
    '黑龙江': ['内蒙古', '吉林'],
    '吉林': ['内蒙古', '辽宁', '黑龙江'],
    '辽宁': ['内蒙古', '吉林', '河北'],
    '山东': ['河北', '河南', '江苏', '安徽'],
    '宁夏': ['陕西', '内蒙古', '甘肃'],
    '甘肃': ['陕西', '新疆', '青海', '四川', '宁夏', '内蒙古'],
    '青海': ['西藏', '新疆', '甘肃', '四川'],
    '西藏': ['新疆', '青海', '四川', '云南'],
    '新疆': ['西藏', '甘肃', '青海'],
    '云南': ['西藏', '四川', '贵州', '广西'],
    '湖北': ['陕西', '河南', '安徽', '江西', '湖南', '重庆'],
    '重庆': ['陕西', '贵州', '湖北', '湖南', '四川'],
    '四川': ['重庆', '陕西', '青海', '甘肃', '云南', '贵州', '西藏'],
    '上海': ['浙江', '江苏'],
    '广东': ['福建', '江西', '湖南', '广西', '海南'],
    '广西': ['广东', '湖南', '贵州', '云南'],
    '安徽': ['浙江', '江西', '河南', '山东', '江苏', '湖北'],
    '贵州': ['湖南', '广西', '四川', '重庆', '云南'],
    '海南': ['广东'],
    '湖南': ['江西', '重庆', '贵州', '广东', '广西', '湖北'],
    '江苏': ['山东', '河南', '安徽', '浙江', '上海'],
    '江西': ['浙江', '福建', '安徽', '湖北', '湖南', '广东'],
    '浙江': ['江西', '上海', '江苏', '福建', '安徽'],
    '福建': ['浙江', '江西', '广东', '台湾'],
    '台湾': ['福建'],
}
mapping = {
    '黑龙江': '黑龙江省',
    '内蒙古': '内蒙古自治区',
    '新疆': '新疆维吾尔自治区',
    '吉林': '吉林省',
    '辽宁': '辽宁省',
    '甘肃': '甘肃省',
    '河北': '河北省',
    '北京': '北京市',
    '山西': '山西省',
    '天津': '天津市',
    '陕西': '陕西省',
    '宁夏': '宁夏回族自治区',
    '青海': '青海省',
    '山东': '山东省',
    '西藏': '西藏自治区',
    '河南': '河南省',
    '江苏': '江苏省',
    '安徽': '安徽省',
    '四川': '四川省',
    '湖北': '湖北省',
    '重庆': '重庆市',
    '上海': '上海市',
    '浙江': '浙江省',
    '湖南': '湖南省',
    '江西': '江西省',
    '云南': '云南省',
    '贵州': '贵州省',
    '福建': '福建省',
    '广西': '广西壮族自治区',
    '台湾': '台湾省',
    '广东': '广东省',
    # '香港': '香港特别行政区',
    # '澳门': '澳门特别行政区',
    '海南': '海南省',
}

"""
    策略 1：贪心算法 + 广度遍历
"""

from copy import deepcopy


class ToColor(object):
    def __init__(self, startNode='贵州省'):
        self.all_color = ['r', 'g', 'b', 'y', 'c', 'm', 'k']
        self.proColor = {_: 'w' for _ in adj_dict.keys()}
        # 初始化开始节点
        for k, value in mapping.items():
            if value == startNode:
                self.other_nodes = [k]
                self.startNode = k
                break

    def greedy(self):
        """
            贪心加并广度遍历解决此问题
        :return:
        """
        while self.other_nodes:
            name = self.other_nodes.pop(0)
            color_list = deepcopy(self.all_color)
            # 给p上一种邻接点没有用过的颜色
            for pName in adj_dict[name]:
                # 如果区域没有染色
                if self.proColor[pName] == 'w' and pName not in self.other_nodes:
                    self.other_nodes.append(pName)
                # 相邻区域染色，则去除相邻区域颜色
                elif self.proColor[pName] in color_list:
                    color_list.remove(self.proColor[pName])
            # 贪心选择，避免选择的颜色数变多
            self.proColor[name] = color_list.pop(0)
            yield mapping[name], self.proColor[name]
        yield -1, -1

    def flashBack(self, seq_color=5):
        """
            科学研究表明，五种颜色能为任何地图着色
            给定颜色数，判断其是否能遍历完地图
            策略：深度回溯
        :return:
        """

        # 生成着色序列
        seq = list(self.proColor.keys())

        # 将起始节点设为第一个
        seq.remove(self.startNode)
        seq.insert(0, self.startNode)
        length = len(self.proColor)
        color_state = list(-1 for _ in range(length))
        k = 0
        while True:
            if k == length or k == -1:
                if k == -1:
                    print("不存在")
                yield -1, -1
                break
            color_state[k] += 1  # 染色
            if color_state[k] < seq_color:
                if not self.conflict(k, seq, color_state):
                    # 染色
                    yield mapping[seq[k]], self.all_color[color_state[k]]
                    k += 1
                else:
                    yield mapping[seq[k]], self.all_color[color_state[k]]
                    # 回退
                    yield mapping[seq[k]], '#ffffff'
            else:
                # 回溯
                yield mapping[seq[k]], '#ffffff'
                color_state[k] = -1
                k -= 1

    def conflict(self, k, seq, color_state):
        """
            检测是否冲突
        :param index:
        :param color_state:
        :param seq:
        :return:
        """
        # 区域名
        name = seq[k]
        # 找出第k个节点前面已经涂色的邻接节点
        indexs = list(filter(lambda index: seq[index] in adj_dict[name], range(k)))
        if color_state[k] in [color_state[index] for index in indexs]:  # 已经有相邻节点涂了这种颜色
            return True
        return False  # 无冲突






def matlabShow():
    x = list(range(len(mapping.keys())))
    print(len(x))
    values = {'gd':list(),'sd5':list(),'sd4':list()}

    for v in mapping.values():
        t = ToColor(v)
        gd = len(list(t.greedy()))
        sd4 = len(list(t.flashBack(4)))
        sd5 = len(list(t.flashBack(5)))
        values['gd'].append(gd)
        values['sd5'].append(sd5)
        values['sd4'].append(sd4)
    plt.figure()
    plt.plot(x, values['gd'], label='广度贪心')
    plt.plot(x, values['sd5'], label='深度回溯')
    plt.legend(loc='best')
    # 设置x,y轴的刻度单位一致
    plt.title("深度颜色数:5")
    plt.show()
    plt.figure()
    plt.plot(x, values['gd'], label='广度贪心')
    plt.plot(x, values['sd4'], label='深度回溯')
    plt.legend(loc='best')
    # 设置x,y轴的刻度单位一致
    plt.title("深度颜色数:4")
    plt.show()


if __name__ == '__main__':
    matlabShow()
