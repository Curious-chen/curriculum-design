#pragma once
#define _CRT_SECURE_NO_DEPRECATE
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
//孩子兄弟父母表示法
typedef struct Treen
{
	int data;//存放邻接表数组下标
	struct Treen *fm;//父母
	struct Treen *fch;//第一个孩子
	struct Treen *nsib;//兄弟
}Treenode;//树节点

//建立链式队列
typedef struct Qn
{
	Treenode *data;
	struct Qn *next;
}Qnode;//队列节点
//入队列
//建立邻接表，存放先修关系图

//表节点
typedef struct arcn
{
	int adjvex;
	struct arcn * nextarc;
} arcnode;
//头节点
typedef struct
{
	char vexdata[30];//选修课名称
	int indegree;//入度
	int credit;//课程学分
	arcnode *firstarc;//第一个表节点
}vexnode;

//定义学期分配表节点
typedef struct arct
{
	int data;
	int aveterm;//平均分配学期号
	int greterm;//贪婪分配学期号
	struct arct * next;
}arcterm;

//定义学期分配头节点
typedef struct vext
{
	double aveScore;//平均分配得分
	double greScore;//贪婪分配得分
	arcterm * fclass;//指向第一节课
	struct vext * next;//指向下一个头结点
}vextrem;
