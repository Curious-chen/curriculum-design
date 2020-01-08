#pragma once
#define _CRT_SECURE_NO_DEPRECATE
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
//�����ֵܸ�ĸ��ʾ��
typedef struct Treen
{
	int data;//����ڽӱ������±�
	struct Treen *fm;//��ĸ
	struct Treen *fch;//��һ������
	struct Treen *nsib;//�ֵ�
}Treenode;//���ڵ�

//������ʽ����
typedef struct Qn
{
	Treenode *data;
	struct Qn *next;
}Qnode;//���нڵ�
//�����
//�����ڽӱ�������޹�ϵͼ

//��ڵ�
typedef struct arcn
{
	int adjvex;
	struct arcn * nextarc;
} arcnode;
//ͷ�ڵ�
typedef struct
{
	char vexdata[30];//ѡ�޿�����
	int indegree;//���
	int credit;//�γ�ѧ��
	arcnode *firstarc;//��һ����ڵ�
}vexnode;

//����ѧ�ڷ����ڵ�
typedef struct arct
{
	int data;
	int aveterm;//ƽ������ѧ�ں�
	int greterm;//̰������ѧ�ں�
	struct arct * next;
}arcterm;

//����ѧ�ڷ���ͷ�ڵ�
typedef struct vext
{
	double aveScore;//ƽ������÷�
	double greScore;//̰������÷�
	arcterm * fclass;//ָ���һ�ڿ�
	struct vext * next;//ָ����һ��ͷ���
}vextrem;
