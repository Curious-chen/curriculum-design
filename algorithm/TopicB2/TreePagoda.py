"""
    将正整数排成等边三角形（也叫数塔），三角形的底边有个数，
    下图给出了的一个例子。从三角形顶点出发通过一系列相邻整数（在图中用正方形表示），
    如何使得到达底边时的总和最大
"""

import numpy as np

"""
    https://www.jianshu.com/p/2a7f5cac0d58
"""
"""
    动态规划
    dp[i][j] = max(dp[i+1][j],dp[i+1][j+1])+date[i][j]
"""

"""
    (1) 初始化距离数组dp，令距离dp的最后一行复制树塔的最后一行的值
    (2) 从树塔倒数第二行开始，自底向上计算
    (3) 判断x点的左右孩子的大小，对应的距离dp = 左右孩子中的较大值加上树塔对应位置值
    (4) 重复2、3步骤，直到计算完树塔顶端
"""

class TreePagoda(object):
    def __init__(self, pagoda):
        self.pagoda = np.array(pagoda)

        # 初始化节点到树塔底的距离
        dp = self.pagoda.copy()
        dp[:-1, :] = 0
        self.dp = dp
        # 下一坐标
        self.next = dict()

    def run(self):

        index = len(self.pagoda) - 1
        for j, value in enumerate(self.pagoda[-1]):
            yield self.getIndex(index, j), 0, value
        for i in range(len(self.pagoda) - 2, -1, -1):  # 自底向上求得最优值
            layer = self.pagoda[i]
            for j in range(len(layer)):
                if layer[j] == 0:
                    break
                self.find(i, j)
                yield self.getIndex(i, j), self.getIndex(*self.next[(i, j)]), self.dp[i, j]

    def getIndex(self, i, j):
        return int(i * (i + 1) / 2 + j)

    def find(self, i, j):
        if self.dp[i + 1, j] > self.dp[i + 1, j + 1]:
            self.dp[i, j] = self.dp[i + 1, j] + self.pagoda[i, j]
            self.next[(i, j)] = (i + 1, j)
        else:
            self.dp[i, j] = self.dp[i + 1, j + 1] + self.pagoda[i, j]
            self.next[(i, j)] = (i + 1, j + 1)

    def createdPath(self):
        cu = (0, 0)
        yield self.getIndex(*cu)
        while True:
            cu = self.next[cu]
            yield self.getIndex(*cu)
            if cu[0] == len(self.pagoda) - 1:
                break


def Test():
    treePagoda = np.array(((9, 0, 0, 0, 0),
                           (12, 15, 0, 0, 0),
                           (10, 6, 8, 0, 0),
                           (2, 18, 9, 5, 0),
                           (19, 7, 10, 4, 16)))
    t = TreePagoda(treePagoda)
    y = t.run()
    for i in range(15):
        x = next(y)
        print(x)
    t.createdPath()
    print(t.dp)
    for i in t.createdPath():
        print(i)


if __name__ == '__main__':
    Test()
