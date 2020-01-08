#include "curiousSort.h"
/***
	�ڲ������㷨�����ܷ���
	�㷨:ֱ�Ӳ�������ð�����򣬿������򣬼�ѡ�����򣬶����򣬹鲢����
	����ָ��:�Ƚϴ������ƶ�����������ʱ�䣬�ȶ���
	Ҫ�󣺱��ı�ʱ�������㷨���ܱ仯��������Ա��������۽��

	�ȶ��ԣ�
	�ٶ��ڴ�����ļ�¼�����У����ڶ��������ͬ�Ĺؼ��ֵļ�¼��
	������������Щ��¼����Դ��򱣳ֲ��䣬����ԭ�����У�r[i]=r[j]����r[i]��r[j]֮ǰ��
	���������������У�r[i]����r[j]֮ǰ��������������㷨���ȶ��ģ������Ϊ���ȶ��ġ�
***/

bool Ifstable(myInt r[], int n)
{
	int i;
	for (i = 1; i < n; i++)
	{
		if ((r[i].data == r[i + 1].data) && (r[i].index > r[i + 1].index))
			return false;
	}
	return true;
}

/***
	ֱ�Ӳ�������
	˼��:���������У����ϲ��������ļ�¼
	�ؼ�:���һ��������r[0],��Ҫ����ļ�¼��������
	˼·:......
***/
void zjinsert(myInt r[], int n)
{

	int i, j;
	for (i = 2; i <= n; i++)
	{
		r[0] = r[i];//���������ֵ���ŵ���������
		j = i - 1;//Ĭ�ϵ�һ����������ã�i-1�����������е����Ԫ�ؿ�ʼ�Ƚ�
		while (r[0].data < r[j].data)
		{
			r[j + 1] = r[j];//Ԫ�غ���
			j--;
		}
		r[j + 1] = r[0];
	}
}

/***
	ð������:
	˼�룺�ӵ�һ����¼��ʼ�����αȽϽ������Ӷ������ļ�¼�ŵ����
***/
void mppx(myInt r[], int n)
{
	int i, j, k;
	myInt x;
	i = 1; k = 1;
	while ((i < n) && (k > 0))
	{
		k = 0;
		for (j = 1; j <= n - i; j++)
		{
			if (r[j].data > r[j + 1].data)
			{
				k++;//�����˽���������Ҫ����ð������
				x = r[j]; r[j] = r[j + 1]; r[j + 1] = x;
			}
		}

	}
}

/***
	��������
	˼��:
	�ؼ�����׼��¼
***/
void kspx(myInt r[], int t, int w)
{
	int i, j;
	myInt x;
	if (t < w)//�ݹ��������
	{
		i = t; j = w; x = r[i];
		while (i < j)
		{
			while ((r[j].data >= x.data) && (j > i))//�ҵ��Ȼ�׼��¼С�ļ�¼
			{
				j--;
			}
			if (j > i)
			{
				r[i] = r[j];//��������,��ʱi�±�ļ�¼һ��С�ڻ�׼��¼����iָ���һ��Ԫ
				i++;
			}
			while ((r[i].data <= x.data) && (j > i))//�ҵ��Ȼ�׼��¼��ļ�¼
			{
				i++;
			}
			if (j > i)
			{
				r[j] = r[i];//��������,��ʱj�±�ļ�¼һ�����ڻ�׼��¼����jָ��ǰһ��Ԫ
				j--;
			}
		}
		r[i] = x;//������ɽ������Ա�ݹ鴦����ȷ����ʱj==i
		kspx(r, t, i - 1);//�ݹ鴦��������
		kspx(r, j + 1, w,);//�ݹ鴦��������
	}
}
void useKspx(myInt r[], int n��
{
	kspx(r, 1, n);
	end_t = clock();

}

/***
	��ѡ������:
	˼·:ÿ�δӴ�����ļ�¼��ѡ�����(��С)�ķ�������������
***/
void zjxz(myInt r[], int n)
{

	myInt x;
	int i, j, k;
	for (i = 1; i < n; i++)//����n-1������
	{
		k = i;//�����i����С
		for (j = i + 1; j <= n; j++)
		{
			if (r[j].data < r[k].data)
				k = j;
		}
		if (i != k)//����Сֵ���ÿ�ͷ
		{
			x = r[k]; r[k] = r[i]; r[i] = x;
		}
	}
}

/***
	������:
	ʹ��˼�룺ʹ����ȫ�����������ѣ������(��С)��¼�������ڵ�
***/
//ɸѡ�����ؽ���,ѡ�����ķŵ����ڵ���
void sxf(myInt r[], int t, int w)
{
	int i, j;
	myInt x;
	i = t;
	x = r[i];//��ɸ�ڵ����������Ԫx��
	j = 2 * i;//j��i������
	while (j <= w)
	{
		if ((j < w) && (r[j].data < r[j + 1].data))
		{
			j++;//���������������������ؼ��ִ�����ҷ�֧��ʼɸѡ
		}
		if (x.data < r[j].data)
		{
			r[i] = r[j]; i = j;//r[j]��˫��λ�öԵ�
			j = j * 2;//��������

		}
		else
		{
			j = w + 1;//�����������ĺ���ʱ��������ϣ��˳�ѭ��
		}
	}
	r[i] = x;
}

void dpx(myInt r[], int n)
{
	int i;
	myInt x;
	//����ʼ��
	for (i = n / 2; i >= 1; i--)//��n/2����ʼɸѡ����Ϊ��ȫ�������ĵ�n/2����¼�պ������һ���Һ�ֽ�Ľڵ�
	{
		sxf(r, i, n, &s->NOC, &s->NOM);
	}
	for (i = n; i >= 2; i--)//n-1������
	{
		x = r[1]; r[1] = r[i]; r[i] = x;//����һ����¼�͵�ǰ���е����һ����¼���������ֵΪ��һ����¼��
		sxf(r, 1, i - 1, &s->NOC, &s->NOM);//ɸr[1]�ڵ㣬�õ�����n-i���ڵ�Ķ�
	}
}

/***
	�鲢����:
	˼��:
***/
void hb(myInt r[], int h, int m, int w, myInt t[])
{
	int i, j, k;
	i = h;
	j = m + 1;
	k = h - 1;
	while ((i <= m) && (j <= w))//��һ�������ӱ������ɣ�ѭ������
	{
		k++;

		if (r[i].data <= r[j].data)
			t[k] = r[i++];//i����
		else
			t[k] = r[j++];//j����
	}
	if (i > m)//��һ������������
	{
		while (j <= w)//���Ƶڶ���������ʣ�����м�¼
		{
			t[++k] = r[j++];
		}
	}
	else//�ڶ�������������
	{
		while (i <= m)//���Ƶ�һ��������ʣ�����м�¼
		{
			t[++k] = r[i++];
		}
	}
}
void ytgb(int s, int n, myInt r[], myInt t[])
{
	int i = 1;
	while (i <= (n - 2 * s + 1))//�ж�n�Ƿ�֧�ֶ�sȥ��Ϊ0
	{
		hb(r, i, i + s - 1, i + 2 * s - 1, t, NOC, NOM);
		i = i + 2 * s;//iָ����һ�������ӱ�����
	}
	if (i < (n - s + 1))//ʣ�������ӱ�����һ������С��s
	{
		hb(r, i, i + s - 1, n, t, NOC, NOM);
	}
	else//ʣ��һ���ӱ�
	{
		while (i <= n)
		{
			t[i] = r[i++];
		}
	}
}
void llgbpx(myInt r[], int n, sign *si)
{
	int i, s = 1;
	myInt *t = (myInt *)malloc(sizeof(myInt)*(n + 1));
	while (s < n)
	{
		ytgb(s, n, r, t);//һ�˹鲢������浽t������
		s = s * 2;//�����еĳ�������һ��
		if (s < n)
		{
			ytgb(s, n, t, r);//�ٴι鲢���������r�����У�����Ϊż����
			s = s * 2;
		}
		else
		{
			i = 1;//������Ϊ��������t���鸴�Ƶ�r����
			while (i <= n)
				r[i] = t[i++];
		}
	}
}

void getRomdomInt(myInt r[], int n)
{
	int i;
	srand((unsigned)n);//�Գ�����Ϊ��������ӣ�������һ��ʱ�������������һ��
	for (i = 1; i <= n; i++)
	{
		r[i].data = rand() % (int)(n*0.99);//��֤һ�����ظ���
		r[i].index = i;
	}

}
void show(sign *s)
{
	printf("Number of comparisons:{ %lld }\n", s->NOC);
	printf("Number of Movements:{ %lld }\n", s->NOM);
	printf("useTime:{ %d ms}\n", s->useTime);
	if (s->stable)
		printf("stable:{true}\n");
	else
		printf("stable:{false}\n");
}
void showpx(int sel)
{
	myInt *arr;
	sign t;
	int i;
	for (i = 50000; i <= 150000; i+=10000)
	{
		arr = (myInt *)malloc(sizeof(myInt) * (i+1));
		getRomdomInt(arr, i);
		switch (sel)
		{
		case 1:zjinsert(arr, i, &t); break;
		case 2:mppx(arr, i, &t); break;
		case 3:useKspx(arr, i, &t); break;
		case 4:zjxz(arr, i, &t); break;
		case 5:dpx(arr, i, &t); break;
		case 6:llgbpx(arr, i, &t); break;
		}
		printf("NOC:%-20lld NOM:%-20lld useTime:%7d ms\n",t.NOC,t.NOM,t.useTime);
		free(arr);
	}
	if (t.stable)
		printf("stable:                 true              \n");
	else
		printf("stable:                false               \n");
}
void sortMenu()
{
	printf("1��ֱ�Ӳ�������\n");
	printf("2��ð������\n");
	printf("3����������\n");
	printf("4��������\n");
	printf("5��������\n");
	printf("6���鲢����\n");
	printf("7��cls\n");
	printf("8��exit\n");
}
int fancySort()
{
	int sel=1;
	sortMenu();
	printf("��ѡ��:");
	scanf("%d",&sel);
	while (1)
	{
		if (sel == 7)
		{
			system("CLS");
			sortMenu();
			printf("��ѡ��:");
			scanf("%d", &sel);
			continue;
		}
		if (sel == 8)
			return 0;
		showpx(sel);
		sortMenu();
		printf("��ѡ��:");
		scanf("%d", &sel);
	}
}
/*int main()
{
	fancySort();
	system("pause");
}*/