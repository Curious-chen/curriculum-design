#pragma once
#define _CRT_SECURE_NO_DEPRECATE
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<io.h>
#define n 97
//树节点结构
typedef struct
{
	int weight;//权重
	int selectd;
	int plink, llink, rlink;//双亲及左右孩子指针(静态指针)
}node;

//哈夫曼编码表节点结构
typedef struct
{
	int start;//存放的起始位置
	char bits[n + 1];//存放编码位串
}codetype;
typedef struct
{
	char symbol;//储存字符
	codetype code;
}element;
//编码后的二进制结构
typedef struct
{
	int len;//数组长度
	char cyl;//记录最后一个元素（8位，1字节）中有几位有效
	char *bits;//存放编码位串
}arrint;