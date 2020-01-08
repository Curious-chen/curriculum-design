import turtle

"""
    如下图所示，先垂直绘制一根线段，然后在线段长度的三分之一处和三分之二处分别以固定夹角绘制另外两根线段，
    长度分别为原线段的2/3和1/3. 如此反复，直至线段长度小于某个较小的值。其中，线条颜色以及长度，夹角都可以自行进行微调
"""

"""
    解题思路
        由题目分析，该题宜采用递归回溯策略解决，对于递归式，必须先设置一个结束条件，即当线段长度小于某值(sh)时，递归结束。
        对于递归的一次过程，可以分成3个部分：
        向前走1/3的距离，右转一定角度，分出2/3线段长度，角度回溯到主干，即向左转相同角度。
        向前走1/3的距离，左转一定角度，分出1/3线段长度，角度回溯到主干，即向右转相同角度
        向前走1/3的距离，保持方向不变，回溯倒退到起点位置。
        如此递归回溯下去，分形树便绘制完成。
        
"""

"""
    （1）	设定递归结束条件，即可绘制的最小线段长度sh
    （2）	输入起始长度n
    （3）	判断 n 是否大于最小线段长度sh
    （4）	绘制n/3长度后,右转一定角度，分出n/3*2的长度进行递归，即进入步骤(3),
    左转相同角度，进入步骤(5)
    （5）	继续绘制n/3长度后, 左转一定角度，分出n/3的长度进行递归,即进入步骤(3)
    右转相同角度，进入步骤(6)
    (6)     最后绘制n/3长度后，保持方向不变回溯，即画笔落点回退长度n

"""


def selectColor(length, sh, pensize):
    if pensize < 0:
        pensize = 0
    turtle.pensize(pensize)
    if length <= sh:
        turtle.pencolor('green')
    else:
        turtle.pencolor('brown')


def draw_branch(branch_length, sh, angle, pensize):
    # 递归结束条件
    if branch_length > sh:
        # 向前走1/3的距离
        selectColor(branch_length / 3 * 2, sh, pensize)  # 1/3处无分支，则设为红色
        turtle.forward(branch_length / 3)
        # 若右侧有分支，则右转画出分支
        turtle.right(angle)
        draw_branch(branch_length / 3 * 2, sh, angle, pensize - 1)
        turtle.left(angle)  # 画完后，回到主支方向
        # 向前走1/3的距离
        selectColor(branch_length / 3, sh, pensize)  # 2/3处无分支，则设为绿色
        turtle.forward(branch_length / 3)
        # 若侧左侧有分支，则右转画出分支
        turtle.left(angle)
        draw_branch(branch_length / 3, sh, angle, pensize - 1)
        turtle.right(angle)  # 画完后，回到主支方向
        # 向前走1/3的距离
        selectColor(branch_length / 9 * 2, sh, pensize)  # 主支的最后1/3小于限定值，则化成绿色
        turtle.forward(branch_length / 3)
        # 退回到原点处
        turtle.penup()
        turtle.backward(branch_length)
        turtle.pendown()


def main():
    """
        主函数
    """
    turtle.speed(100)
    turtle.left(90)
    # 抬起画笔
    turtle.penup()
    turtle.backward(200)
    turtle.pendown()
    turtle.color('brown')
    draw_branch(442, 5, 30, 10)
    turtle.exitonclick()


if __name__ == '__main__':
    main()
