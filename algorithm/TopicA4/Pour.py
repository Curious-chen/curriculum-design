"""
    泊松分酒问题
    created by Curious
    2019/10/21 14:02
"""

"""
    西蒙.丹尼斯.泊松是著名的法国数学家和物理学家。据说在他遇到某个古老的谜题之后，
    就开始对数学感兴趣了，这个谜题是这样的：
    给定一个装满水的8品脱壶以及两个容量分别为5品脱和3品脱的空壶，
    如何通过完全灌满或者到空这些壶从而使得某个壶精确地装有4品脱的水？
"""

"""
    https://cloud.tencent.com/developer/ask/117460
"""

"""
    解题思路
        1.广度优先遍历
        2.将基于当前三个壶水的情况，列出所有可能的倒水情况
        3.修剪分支，即得出得壶水的情况若产生过，则不将这种情况加入队列中
        4.重复上述步骤，直到遇到有一个水壶水量为4的情况
"""

"""
    (1) 初始化队列，将水壶情况(8,0,0)入队列
    (2) 判断队列是否为空
    (3) 取出队首元素，即获得水壶水量情况，
    (4) 通过六种可能的倒水行为，产生新的六种水壶水量情况
    (5) 判断其中是否存在有水壶水量为4的情况，若有则结束程序，否则进入步骤2
"""
class Pour(object):
    def __init__(self, capacity, situation: list, endValue=4):
        self.capacity = tuple(capacity)
        # 用字典存放广度遍历的所有情况
        self.pointList = dict()
        # 定义水壶情况 (壶1,壶2.壶3):(壶1,壶2.壶3)[ps:父节点状况]
        # 开始情况的父节点设为None
        situation.extend([0, 0, 0])
        self.pointList[tuple(situation)] = -1  # 记录开始节点
        # 初始化队列，并将开始节点加入队列中
        self.queue = list()
        self.enqueue(situation)
        self.endValue = endValue
        self.pathList = list()
    def run(self):
        """
            广度优先遍历
        :return:
        """
        while len(self.queue) != 0:
            point = self.delqueue()
            # 遍历六种倒水可能
            for i in range(3):
                for j in range(1, 3):
                    if not self.pour(point, i, (i + j) % 3):
                        self.createPath()
                        return True
        print("不存在")
        return False
    def pour(self, situation: list, a, b):
        """
            a ->b 倒水
        """
        # 去除灌水壶的水量为0和被灌水壶容量满的情况的情况
        if situation[a] == 0 or situation[b] == self.capacity[b]:
            return True
        # b 需要多少水能倒满
        b_need = self.capacity[b] - situation[b]
        # a 需要给多少才能为空
        a_take = situation[a]
        # 如果能倒空
        temp = situation.copy()

        # 灌满或灌空
        if a_take >= b_need:
            temp[a] = a_take - b_need
            temp[b] = self.capacity[b]
            temp[5] = b_need
        else:
            temp[a] = 0
            temp[b] = temp[b] + a_take
            temp[5] = a_take
        temp[3], temp[4] = a, b
        # 判断该情况是否出现过
        if tuple(temp) not in self.pointList:
            self.enqueue(temp)  # 加入队列
            self.enPointList(situation, temp)  # 加如情况存在字典
            if self.endValue in temp:
                return False
        return True
    def enqueue(self, point):
        self.queue.append(point)
    def delqueue(self):
        if len(self.queue) != 0:
            return self.queue.pop(0)
        return None
    def enPointList(self, f_point, point):
        self.pointList[tuple(point)] = tuple(f_point)
    def createPath(self):
        point = tuple(self.queue[-1])
        self.pathList.insert(0, point)
        while True:
            point = self.pointList[point]
            if point == -1:
                break
            self.pathList.insert(0, point)


def Test():
    # 水壶容量
    capacity = (8, 5, 3)
    # 初始时，水壶中水的情况
    situation = [8, 0, 0]
    pour = Pour(capacity, situation, 4)
    pour.run()
    for i in pour.pathList:
        print(i)
    print()


if __name__ == '__main__':
    Test()
