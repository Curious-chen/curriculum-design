#include "curiousHash.h"
#define MAXLEN 1800//�洢����
#define loadLen 1632 //��������

/***
	 ��ϣ����:
	 1.����������
	 2.ʣ��ȡ����
	 3.�������
	 ��ͻ��������
	 1.����̽�ⷨ
	 3.������
	 �绰�������ӣ�
	 1.�Զ������
	 2.����������
	 �ؼ���()��ӳ��
	 1.����������Ϊ�ַ�������仯��������̬������:�ַ����е�ÿһ���ַ�ת��Ϊ��Ӧ��ASILL��ֵ,�ټ��������ַ����е�λ�ã������Щֵ��ӷ���
	 2.�绰���� 11 ֱ��ʹ��long��ţ������ؼ��ɡ�


***/


//�ַ����Ƚ�
int equal(const char *x, const char *y)
{
	int i = 0;
	while ((x[i] != '\0') && (y[i] != '\0'))
	{
		if (x[i] != y[i])
			return 0;
		i++;
	}
	if ((x[i] == '\0') && (y[i] == '\0'))
		return 1;
	return 0;
}

//�ַ�����ֵ
void assign(const char *s, char *t)
{
	int i = 0;
	while (s[i] != '\0')
	{
		t[i] = s[i];
		i++;
	}
	t[i] = '\0';
}

//һ��hash����
int stringToNum(const char * s,int hash)
{
	int i = 0, j = 0;
	int num = 0;
	int c;
	if (hash == 0)
	{
		while (s[j] != '\0')j++;
		j--;
		while ((c = s[i++]) != '\0')
		{
			num += ((int)(c - '0')*(int)pow(10, j--));//ƫ��Ϊ��ǰ�ַ���ASILL+�������λ��
		}
	}
	else
	{
		while ((c = s[i++]) != '\0')
		{
			num = num * 31 + c;//ƫ��Ϊ��ǰ�ַ���ASILL+�������λ��
		}
	}
	return abs(num);
}

//���ι�ϣ����
int hashFunction(int mode, int index)
{
	if (mode == 0)//ֱ�Ӷ�ַ��
	{
		return index;
	}
	else//�������
	{
		srand((unsigned)index);//��key�����������
		return rand();
	}
}


//���ŵ�ַ���ṹ���ֵ
void setKfdz(hmjd tel[], int len, int keyword, int hash1, int hash2)//hash 0:ȡ�� modekeyword 0:���� 1���绰����
{
	FILE * fp;
	char name[20], address[50], number[12];
	int i = 0, j = 0, k = 0;
	int index = 0, hashKey;
	//��ʼ��tel
	for (i = 0; i < MAXLEN; i++)
	{
		tel[i].name[0] = '\0';
		tel[i].number[0] = '\0';
		tel[i].address[0] = '\0';
	}
	fp = fopen("./seachTel/sf.txt", "rb");
	for (i = 0; i < loadLen; i++)
	{
		fscanf(fp, "%s%s%s", name, number, address);
		if (keyword == 0)
			hashKey = hashFunction(hash2, stringToNum(name,hash1));
		else
			hashKey = hashFunction(hash2, stringToNum(number,hash1));

		index = hashKey % len;
		while (tel[index].name[0] != '\0')
		{
			index = (index + 1) % len;
		}
		assign(name, tel[index].name);
		assign(number, tel[index].number);
		assign(address, tel[index].address);
	}
	fclose(fp);

}

//���ŵ�ַ������
int findKfdz(hmjd tel[], int len,int mode, const char *word, int hash1, int hash2, int *ctcs)
{
	int hashKey, index;
	hashKey = hashFunction(hash2, stringToNum(word,hash1));

	index = hashKey % len;
	do
	{
		*ctcs = *ctcs + 1;

		if (mode == 0)
		{
			if (equal(tel[index].name, word))
			{
				//printf("����:%s\n�绰:%s\n��ַ:%s\n", tel[index].name, tel[index].number, tel[index].address);
				return index;
			}
		}
		else
		{
			if (equal(tel[index].number, word))
			{
				//printf("����:%s\n�绰:%s\n��ַ:%s\n", tel[index].name, tel[index].number, tel[index].address);
				return index;
			}
		}
		index = (index + 1) % len;
	} while (index != (hashKey % len));
	return -1;
}
//��������ʼ��
void setLl(adjnode tel[], int len, int keyword, int hash1, int hash2)
{
	FILE * fp;
	char name[20], address[50], number[12];
	arcptr a = NULL;
	arcptr t = NULL;
	int i = 0, j = 0, k = 0;
	int index = 0, hashKey;
	//��ʼ��tel
	for (i = 0; i < len; i++)
	{
		tel[i].firstarc = NULL;
	}
	fp = fopen("./seachTel/sf.txt", "rb");
	for (i = 0; i < loadLen; i++)
	{
		a = (arcptr)malloc(sizeof(arcnode));
		fscanf(fp, "%s%s%s", name, number, address);
		assign(name, a->data.name);
		assign(number, a->data.number);
		assign(address, a->data.address);
		if (keyword == 0)
			hashKey = hashFunction(hash2, stringToNum(name,hash1));
		else
			hashKey = hashFunction(hash2, stringToNum(number,hash1));
		index = hashKey % len;
		if (tel[index].firstarc == NULL)
		{
			tel[index].firstarc = a;
			a->next = NULL;
		}
		else
		{
			t = tel[index].firstarc;
			while (t->next != NULL)
			{
				t = t->next;
			}
			a->next = t->next;
			t->next = a;

		}
	}
}

//����������
int findLl(adjnode tel[], int len, int keyword, const char * word, int hash1, int hash2, int *czcs)
{
	int hashKey, index;
	arcnode * t = NULL;
	hashKey = hashFunction(hash2, stringToNum(word,hash1));
	index = hashKey % len;
	t = tel[index].firstarc;
	if (t == NULL)
	{
		return -1;
	}

	while (t)
	{
		*czcs = *czcs + 1;
		if (keyword == 0)
		{
			if (equal(t->data.name, word))
			{
				return index;
			}
		}
		else
		{
			if (equal(t->data.number, word))
			{
				return index;
			}
		}
		t = t->next;
	}
	return -1;
}

void testKfdz()
{
	hmjd tel1[MAXLEN];
	hmjd tel2[MAXLEN];
	FILE * fp = NULL;
	int ctcs1, ctcs2, i,nNum=0,tNum=0;
	char name[20], address[50], number[12];
	setKfdz(tel1, MAXLEN, 0, 0, 1);
	setKfdz(tel2, MAXLEN, 1, 0, 1);
	fp = fopen("./seachTel/sf.txt", "rb");
	for (i = 0; i < loadLen; i++)
	{
		ctcs1 = ctcs2 = 0;
		fscanf(fp, "%s%s%s", name, number, address);
		findKfdz(tel1, MAXLEN, 0, name, 0, 1, &ctcs1);
		findKfdz(tel2, MAXLEN, 1, number, 0, 1, &ctcs2);
		nNum += ctcs1; tNum += ctcs2;
		printf("%-4d%-4d",ctcs1,ctcs2);
		if ((i + 1) % 10 == 0)
			printf("\n");
	}
	fclose(fp);
	printf("\n\n����̽��(����)�ܲ��ҳ���:%-7dƽ�����ҳ���:%-5.1f\n\n", nNum,((double)nNum) / loadLen);
	printf("\n\n����̽��(�绰)�ܲ��ҳ���:%-7dƽ�����ҳ���:%-5.1f\n\n", tNum,((double)tNum) / loadLen);
}

void testLl()
{
	adjnode tel1[MAXLEN];
	adjnode tel2[MAXLEN];
	FILE * fp = NULL;
	int ctcs1, ctcs2, i, nNum = 0, tNum = 0;
	char name[20], address[50], number[12];
	setLl(tel1, MAXLEN, 0, 0, 1);
	setLl(tel2, MAXLEN, 1, 0, 1);
	fp = fopen("./seachTel/sf.txt", "rb");
	for (i = 0; i < loadLen; i++)
	{
		ctcs1 = ctcs2 = 0;
		fscanf(fp, "%s%s%s", name, number, address);
		findLl(tel1, MAXLEN, 0, name, 0, 1, &ctcs1);
		findLl(tel2, MAXLEN, 1, number, 0, 1, &ctcs2);
		nNum += ctcs1; tNum += ctcs2;
		printf("%-4d%-4d", ctcs1, ctcs2);
		//printf("����:%s\n�绰:%s\n��ַ:%s\n\n\n", name, number,address);
		if ((i + 1) % 10 == 0)
			printf("\n");
	}
	fclose(fp);
	printf("\n\n������(����)�ܲ��ҳ���:%-7dƽ�����ҳ���:%-5.1f\n\n", nNum,(nNum + 0.0) / loadLen);
	printf("\n\n������(�绰)�ܲ��ҳ���:%-7dƽ�����ҳ���:%-5.1f\n\n", tNum,(tNum + 0.0) / loadLen);
}

void showVhash(int sel)
{
	hmjd tel1[MAXLEN], tel2[MAXLEN];
	FILE * fp = NULL;
	int ctcs1, ctcs2, i,j,ctT,ctN;
	char name[20], address[50], number[12];
	switch (sel)
	{
	case 1:setKfdz(tel1, MAXLEN, 0, 0, 0); setKfdz(tel2, MAXLEN, 1, 0, 0); break;
	case 2:setKfdz(tel1, MAXLEN, 0, 0, 1); setKfdz(tel2, MAXLEN, 1, 0, 1); break;
	case 3:setKfdz(tel1, MAXLEN, 0, 1, 0); setKfdz(tel2, MAXLEN, 1, 1, 0); break;
	case 4:setKfdz(tel1, MAXLEN, 0, 1, 1); setKfdz(tel2, MAXLEN, 1, 1, 1); break;
	}
	for (j = 500; j <= 1000; j += 50)
	{
		ctN = ctT =0;
		fp = fopen("./seachTel/sf.txt", "rb");
		for (i = 0; i < j; i++)
		{
			ctcs1 = ctcs2 = 0;
			fscanf(fp, "%s%s%s", name, number, address);
			switch (sel)
			{
			case 1:findKfdz(tel1, MAXLEN, 0, name, 0, 0, &ctcs1); findKfdz(tel2, MAXLEN, 1, number, 0, 0, &ctcs2); break;
			case 2:findKfdz(tel1, MAXLEN, 0, name, 0, 1, &ctcs1); findKfdz(tel2, MAXLEN, 1, number, 0, 1, &ctcs2); break;
			case 3:findKfdz(tel1, MAXLEN, 0, name, 1, 0, &ctcs1); findKfdz(tel2, MAXLEN, 1, number, 1, 0, &ctcs2); break;
			case 4:findKfdz(tel1, MAXLEN, 0, name, 1, 1, &ctcs1); findKfdz(tel2, MAXLEN, 1, number, 1, 1, &ctcs2); break;
			}
			if (ctcs1 > 1)
				ctN++;
			if (ctcs2 > 1)
				ctT++;
		}
		fclose(fp);
		printf("��ѯ��:%-4d ������ͻ��:%-4d ��ͻ��:%-4.2f%% �绰�����ͻ��:%-4d ��ͻ��:%-4.2f%%\n", j, ctN, (ctN + 0.0) / j*100, ctT, (ctT + 0.0) / j*100);
	}
}

void hashMenu(int n)
{
	switch (n)
	{
	case 1:printf("1����ϣ����1\n"); 
	case 2:printf("2����ϣ����2\n");
	case 3:printf("3����ϣ����3\n"); 
	case 4:printf("4����ϣ����4\n"); 
	case 5:printf("5�����ŵ�ַ���µ�ƽ�����ҳ���\n");
	case 6:printf("6���������µ�ƽ�����ҳ���\n");
	case 7:printf("7��cls\n");
	case 8:printf("8��exit\n");
	}
}
int hashSearch()
{
	int sel;
	hashMenu(1);
	printf("��ѡ��:");
	scanf("%d",&sel);
	while (1)
	{
		switch (sel)
		{
		case 1:showVhash(sel); break;
		case 2:showVhash(sel); break;
		case 3:showVhash(sel); break;
		case 4:showVhash(sel); break;
		case 5:testKfdz(); break;
		case 6:testLl(); break;
		case 7:system("CLS"); break;
		default:
			return 0;
			break;
		}
		hashMenu(1);
		printf("��ѡ��:");
		scanf("%d", &sel);
	}
	return 1;
}
int main()
{
	hashSearch();
	printf("hellow hashmap\n");
	system("pause");
}