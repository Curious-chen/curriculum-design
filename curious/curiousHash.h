#pragma once
#define _CRT_SECURE_NO_DEPRECATE
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
typedef int mytype;
typedef int vextype;
//����绰�ű��ڵ�����
typedef struct
{
	char name[20];//���� ��'\0'����
	char number[12];//�绰����
	char address[50];//��ַ ��'\0'����
}hmjd;

//������������ϣ����
struct arcnode
{
	hmjd data;//��������
	struct arcnode * next;//��һ�����ڵ�
};
typedef struct arcnode *arcptr;
typedef struct vexnode
{
	vextype vexdata;//��������
	arcptr firstarc;//ָ���һ���ڽӵ�
}adjnode;