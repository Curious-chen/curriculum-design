#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include<math.h>
//定义数据结构,用于判断排序算法是否稳定
typedef struct
{
	int data;//存放数据
	int index;//存放下标
}myInt;

typedef struct
{
	long long NOC; //Number of comparisons 比较次数
	long long NOM; //Number of Movements 移动次数
	int useTime; //使用时间 单位ms
	bool stable; //是否稳定
}sign;