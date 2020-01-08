#include "curiousHash.h"
#define MAXLEN 1800//存储容量
#define loadLen 1632 //传入容量

/***
	 哈希函数:
	 1.除留余数法
	 2.剩余取整法
	 3.随机数法
	 冲突处理方法：
	 1.线性探测法
	 3.拉链法
	 电话号码的添加：
	 1.自定义添加
	 2.随机生成添加
	 关键字()的映射
	 1.姓名：姓名为字符串，需变化成数字形态，方法:字符串中的每一个字符转化为对应的ASILL码值,再加上其在字符串中的位置，最后将这些值相加返回
	 2.电话号码 11 直接使用long存放，并返回即可。


***/


//字符串比较
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

//字符串赋值
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

//一次hash函数
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
			num += ((int)(c - '0')*(int)pow(10, j--));//偏移为当前字符的ASILL+它的相对位置
		}
	}
	else
	{
		while ((c = s[i++]) != '\0')
		{
			num = num * 31 + c;//偏移为当前字符的ASILL+它的相对位置
		}
	}
	return abs(num);
}

//二次哈希函数
int hashFunction(int mode, int index)
{
	if (mode == 0)//直接定址法
	{
		return index;
	}
	else//随机数法
	{
		srand((unsigned)index);//以key当随机数种子
		return rand();
	}
}


//开放地址法结构存放值
void setKfdz(hmjd tel[], int len, int keyword, int hash1, int hash2)//hash 0:取余 modekeyword 0:姓名 1：电话号码
{
	FILE * fp;
	char name[20], address[50], number[12];
	int i = 0, j = 0, k = 0;
	int index = 0, hashKey;
	//初始化tel
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

//开放地址法查找
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
				//printf("姓名:%s\n电话:%s\n地址:%s\n", tel[index].name, tel[index].number, tel[index].address);
				return index;
			}
		}
		else
		{
			if (equal(tel[index].number, word))
			{
				//printf("姓名:%s\n电话:%s\n地址:%s\n", tel[index].name, tel[index].number, tel[index].address);
				return index;
			}
		}
		index = (index + 1) % len;
	} while (index != (hashKey % len));
	return -1;
}
//拉链法初始化
void setLl(adjnode tel[], int len, int keyword, int hash1, int hash2)
{
	FILE * fp;
	char name[20], address[50], number[12];
	arcptr a = NULL;
	arcptr t = NULL;
	int i = 0, j = 0, k = 0;
	int index = 0, hashKey;
	//初始化tel
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

//拉链法查找
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
	printf("\n\n线性探测(名字)总查找长度:%-7d平均查找长度:%-5.1f\n\n", nNum,((double)nNum) / loadLen);
	printf("\n\n线性探测(电话)总查找长度:%-7d平均查找长度:%-5.1f\n\n", tNum,((double)tNum) / loadLen);
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
		//printf("姓名:%s\n电话:%s\n地址:%s\n\n\n", name, number,address);
		if ((i + 1) % 10 == 0)
			printf("\n");
	}
	fclose(fp);
	printf("\n\n拉链法(名字)总查找长度:%-7d平均查找长度:%-5.1f\n\n", nNum,(nNum + 0.0) / loadLen);
	printf("\n\n拉链法(电话)总查找长度:%-7d平均查找长度:%-5.1f\n\n", tNum,(tNum + 0.0) / loadLen);
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
		printf("查询数:%-4d 姓名冲突数:%-4d 冲突率:%-4.2f%% 电话号码冲突数:%-4d 冲突率:%-4.2f%%\n", j, ctN, (ctN + 0.0) / j*100, ctT, (ctT + 0.0) / j*100);
	}
}

void hashMenu(int n)
{
	switch (n)
	{
	case 1:printf("1、哈希函数1\n"); 
	case 2:printf("2、哈希函数2\n");
	case 3:printf("3、哈希函数3\n"); 
	case 4:printf("4、哈希函数4\n"); 
	case 5:printf("5、开放地址法下的平均查找长度\n");
	case 6:printf("6、拉链法下的平均查找长度\n");
	case 7:printf("7、cls\n");
	case 8:printf("8、exit\n");
	}
}
int hashSearch()
{
	int sel;
	hashMenu(1);
	printf("请选择:");
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
		printf("请选择:");
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