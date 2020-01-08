"""
    题目B1：基因序列比较
    1、题目描述
    设计算法，计算两给定基因序列的相似程度
    2、设计内容
    人类基因由4种核苷酸，分别用字母ACTG表示。
    要求编写一个程序，按以下规则比较两个基因序列并确定它们的相似程度。
    即给出两个基因序列AGTGATG和GTTAG，它们有多相似呢？测量两个基因相似度的一种方法称为对齐。
    使用对齐方法可以在基因的适当位置加入空格，让两个基因的长度相等，然后根据基因的分值矩阵计算分数。

"""
"""
    （1）初始化结果数组result的第一行及第一列。由于当X的规模m等于1时，意味着出了一个匹配的位置之外，
    Y序列的其他元素需要和空格匹配，所以该情况下，
    子问题由result[i][j] = max(s1,s2,s3)改变为result[i][0] = result[i-1][0] + get_score(X[i], '-')。当Y的规模n等于1时同理。

    （2）从i等于2和j等于2开始，根据result[i][j] = max(s1,s2,s3)，由底向上地计算结果，同时也可以利用另一个表用于记录路径。
    
    （3）返回结果表，其中result[m-1][n-1]为该问题的结果。

"""

from copy import deepcopy
import numpy as np


# 构建得分函数
def get_score(x, y):
    index = {
        'A': 0,
        'C': 1,
        'G': 2,
        'T': 3,
        '-': 4,
    }
    score_table = [
        [5, -1, -2, -1, -3],
        [-1, 5, -3, -2, -4],
        [-2, -3, 5, -2, -2],
        [-1, -2, -2, 5, -1],
        [-3, -4, -2, -1, float('-inf')]
    ]
    return score_table[index[x]][index[y]]


class Alignment(object):
    def __init__(self, M, N):
        X = deepcopy(M)
        Y = deepcopy(N)

        # 令两序列的第一元素始终相等
        X.insert(0, '')
        Y.insert(0, '')
        self.X = X
        self.Y = Y
        m = len(X)
        n = len(Y)
        # 初始化路径状态
        path = [['' for x in range(n)] for y in range(m)]
        self.path = np.array(path, dtype=str)
        # 初始化最优得分
        self.result = np.zeros((m, n))

    def aligment(self):
        # 动态规划初始条件
        m = len(self.X)
        n = len(self.Y)
        # 注意初始化
        for i in range(1, m):
            self.path[i][0] = '|'
            self.result[i][0] = self.result[i - 1][0] + get_score(self.X[i], '-')
            yield i, 0, self.result[i][0], self.getString(i, 0)

        for j in range(1, n):
            self.path[0][j] = '-'
            self.result[0][j] = self.result[0][j - 1] + get_score('-', self.Y[j])
            yield 0, j, self.result[0][j], self.getString(0, j)

        for i in range(1, m):
            for j in range(1, n):
                s1 = self.result[i - 1][j - 1] + get_score(self.X[i], self.Y[j])
                s2 = self.result[i - 1][j] + get_score(self.X[i], '-')
                s3 = self.result[i][j - 1] + get_score('-', self.Y[j])
                max_score = max(s1, s2, s3)
                self.result[i][j] = max_score
                # 第一种情况
                if s1 == max_score:
                    self.path[i][j] = '`'
                # 第二种情况
                if s2 == max_score:
                    self.path[i][j] = '|'
                # 第三种情况
                if s3 == max_score:
                    self.path[i][j] = '-'
                yield i, j, self.result[i][j], self.getString(i, j)

    def getString(self, i, j):

        seqX = ''
        seqY = ''
        while (i + j) != 0:
            flag = self.path[i][j]
            if flag == '-':
                seqX += '_'
                seqY += self.Y[j]
                j -= 1

            elif flag == '|':
                seqY += '_'
                seqX += self.X[i]
                i -= 1

            else:
                seqX += self.X[i]
                seqY += self.Y[j]
                j -= 1
                i -= 1
        return seqX[-1::-1], seqY[-1::-1]

    def getMaxScore(self):
        flag = self.path[-1][-1]
        i = len(self.X) - 1
        j = len(self.Y) - 1
        yield i, j
        while (i + j) > 0:
            if flag == '-':
                j -= 1

            elif flag == '|':
                i -= 1

            else:
                i -= 1
                j -= 1
            yield i, j
            flag = self.path[i][j]


if __name__ == '__main__':
    M = list('AGTGATG')
    N = list('GTTAG')
    t = Alignment(M, N)
    for i in t.aligment():
        print(i)
    print(t.path)
    for _ in t.getMaxScore():
        print(_)

