#pragma once
#define _CRT_SECURE_NO_DEPRECATE
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<io.h>
#define n 97
//���ڵ�ṹ
typedef struct
{
	int weight;//Ȩ��
	int selectd;
	int plink, llink, rlink;//˫�׼����Һ���ָ��(��ָ̬��)
}node;

//�����������ڵ�ṹ
typedef struct
{
	int start;//��ŵ���ʼλ��
	char bits[n + 1];//��ű���λ��
}codetype;
typedef struct
{
	char symbol;//�����ַ�
	codetype code;
}element;
//�����Ķ����ƽṹ
typedef struct
{
	int len;//���鳤��
	char cyl;//��¼���һ��Ԫ�أ�8λ��1�ֽڣ����м�λ��Ч
	char *bits;//��ű���λ��
}arrint;