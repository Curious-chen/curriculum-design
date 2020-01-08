#pragma once
#define _CRT_SECURE_NO_DEPRECATE
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
typedef int mytype;
typedef int vextype;
//定义电话号薄节点类型
typedef struct
{
	char name[20];//姓名 以'\0'结束
	char number[12];//电话号码
	char address[50];//地址 以'\0'结束
}hmjd;

//拉链法创建哈希查找
struct arcnode
{
	hmjd data;//表结点数据
	struct arcnode * next;//下一拉链节点
};
typedef struct arcnode *arcptr;
typedef struct vexnode
{
	vextype vexdata;//定点类型
	arcptr firstarc;//指向第一个邻接点
}adjnode;