#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include<math.h>
//�������ݽṹ,�����ж������㷨�Ƿ��ȶ�
typedef struct
{
	int data;//�������
	int index;//����±�
}myInt;

typedef struct
{
	long long NOC; //Number of comparisons �Ƚϴ���
	long long NOM; //Number of Movements �ƶ�����
	int useTime; //ʹ��ʱ�� ��λms
	bool stable; //�Ƿ��ȶ�
}sign;