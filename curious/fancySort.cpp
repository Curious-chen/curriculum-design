#include "curiousSort.h"
/***
	内部排序算法的性能分析
	算法:直接插入排序，冒泡排序，快速排序，简单选择排序，堆排序，归并排序。
	性能指标:比较次数，移动次数，排序时间，稳定性
	要求：表长改变时，排序算法性能变化情况，且以表格输出评价结果

	稳定性：
	假定在待排序的记录序列中，存在多个具有相同的关键字的记录，
	若经过排序，这些记录的相对次序保持不变，即在原序列中，r[i]=r[j]，且r[i]在r[j]之前，
	而在排序后的序列中，r[i]仍在r[j]之前，则称这种排序算法是稳定的；否则称为不稳定的。
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
	直接插入排序：
	思想:向有序序列，不断插入待排序的记录
	关键:设计一个监视哨r[0],将要插入的记录放入其中
	思路:......
***/
void zjinsert(myInt r[], int n)
{

	int i, j;
	for (i = 2; i <= n; i++)
	{
		r[0] = r[i];//即将插入的值，放到监视哨中
		j = i - 1;//默认第一个数已排序好，i-1：从有序序列的最后元素开始比较
		while (r[0].data < r[j].data)
		{
			r[j + 1] = r[j];//元素后移
			j--;
		}
		r[j + 1] = r[0];
	}
}

/***
	冒泡排序:
	思想：从第一个记录开始，依次比较交换，从而将最大的记录放到最后
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
				k++;//发生了交换，即还要进行冒泡排序
				x = r[j]; r[j] = r[j + 1]; r[j + 1] = x;
			}
		}

	}
}

/***
	快速排序
	思想:
	关键：基准记录
***/
void kspx(myInt r[], int t, int w)
{
	int i, j;
	myInt x;
	if (t < w)//递归结束条件
	{
		i = t; j = w; x = r[i];
		while (i < j)
		{
			while ((r[j].data >= x.data) && (j > i))//找到比基准记录小的记录
			{
				j--;
			}
			if (j > i)
			{
				r[i] = r[j];//交换两者,此时i下标的记录一定小于基准记录，即i指向后一单元
				i++;
			}
			while ((r[i].data <= x.data) && (j > i))//找到比基准记录大的记录
			{
				i++;
			}
			if (j > i)
			{
				r[j] = r[i];//交换两者,此时j下标的记录一定大于基准记录，即j指向前一单元
				j--;
			}
		}
		r[i] = x;//彻底完成交换，以便递归处理正确，此时j==i
		kspx(r, t, i - 1);//递归处理右区间
		kspx(r, j + 1, w,);//递归处理左区间
	}
}
void useKspx(myInt r[], int n）
{
	kspx(r, 1, n);
	end_t = clock();

}

/***
	简单选择排序:
	思路:每次从待排序的记录中选择最大(最小)的放置有序序列中
***/
void zjxz(myInt r[], int n)
{

	myInt x;
	int i, j, k;
	for (i = 1; i < n; i++)//进行n-1趟排序
	{
		k = i;//假设第i个最小
		for (j = i + 1; j <= n; j++)
		{
			if (r[j].data < r[k].data)
				k = j;
		}
		if (i != k)//将最小值放置开头
		{
			x = r[k]; r[k] = r[i]; r[i] = x;
		}
	}
}

/***
	推排序:
	使用思想：使用完全二叉树建立堆，将最大(最小)记录排至根节点
***/
//筛选，并重建堆,选出最大的放到根节点上
void sxf(myInt r[], int t, int w)
{
	int i, j;
	myInt x;
	i = t;
	x = r[i];//待筛节点放入铺助单元x中
	j = 2 * i;//j是i的左孩子
	while (j <= w)
	{
		if ((j < w) && (r[j].data < r[j + 1].data))
		{
			j++;//若存在右子树且右子树关键字大，则从右分支开始筛选
		}
		if (x.data < r[j].data)
		{
			r[i] = r[j]; i = j;//r[j]与双亲位置对调
			j = j * 2;//往下搜索

		}
		else
		{
			j = w + 1;//根不大于它的孩子时，调整完毕，退出循环
		}
	}
	r[i] = x;
}

void dpx(myInt r[], int n)
{
	int i;
	myInt x;
	//建初始堆
	for (i = n / 2; i >= 1; i--)//从n/2处开始筛选，因为完全二叉树的第n/2个记录刚好是最后一个右孩纸的节点
	{
		sxf(r, i, n, &s->NOC, &s->NOM);
	}
	for (i = n; i >= 2; i--)//n-1趟排序，
	{
		x = r[1]; r[1] = r[i]; r[i] = x;//将第一条记录和当前堆中的最后一条记录互换（最大值为第一条记录）
		sxf(r, 1, i - 1, &s->NOC, &s->NOM);//筛r[1]节点，得到具有n-i个节点的堆
	}
}

/***
	归并排序:
	思想:
***/
void hb(myInt r[], int h, int m, int w, myInt t[])
{
	int i, j, k;
	i = h;
	j = m + 1;
	k = h - 1;
	while ((i <= m) && (j <= w))//有一个有序子表遍历完成，循环结束
	{
		k++;

		if (r[i].data <= r[j].data)
			t[k] = r[i++];//i后移
		else
			t[k] = r[j++];//j后移
	}
	if (i > m)//第一个有序表遍历完
	{
		while (j <= w)//复制第二个有序表的剩余所有记录
		{
			t[++k] = r[j++];
		}
	}
	else//第二个有序表遍历完
	{
		while (i <= m)//复制第一个有序表的剩余所有记录
		{
			t[++k] = r[i++];
		}
	}
}
void ytgb(int s, int n, myInt r[], myInt t[])
{
	int i = 1;
	while (i <= (n - 2 * s + 1))//判断n是否支持对s去余为0
	{
		hb(r, i, i + s - 1, i + 2 * s - 1, t, NOC, NOM);
		i = i + 2 * s;//i指向下一队有序子表的起点
	}
	if (i < (n - s + 1))//剩余两个子表，其中一个长度小于s
	{
		hb(r, i, i + s - 1, n, t, NOC, NOM);
	}
	else//剩下一个子表
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
		ytgb(s, n, r, t);//一趟归并，结果存到t数组中
		s = s * 2;//子序列的长度扩大一倍
		if (s < n)
		{
			ytgb(s, n, t, r);//再次归并，结果存在r数组中（趟数为偶数）
			s = s * 2;
		}
		else
		{
			i = 1;//若趟数为奇数，将t数组复制到r数组
			while (i <= n)
				r[i] = t[i++];
		}
	}
}

void getRomdomInt(myInt r[], int n)
{
	int i;
	srand((unsigned)n);//以长度作为随机数种子，即长度一样时，产生的随机数一样
	for (i = 1; i <= n; i++)
	{
		r[i].data = rand() % (int)(n*0.99);//保证一定有重复的
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
	printf("1、直接插入排序\n");
	printf("2、冒泡排序\n");
	printf("3、快速排序\n");
	printf("4、简单排序\n");
	printf("5、堆排序\n");
	printf("6、归并排序\n");
	printf("7、cls\n");
	printf("8、exit\n");
}
int fancySort()
{
	int sel=1;
	sortMenu();
	printf("请选择:");
	scanf("%d",&sel);
	while (1)
	{
		if (sel == 7)
		{
			system("CLS");
			sortMenu();
			printf("请选择:");
			scanf("%d", &sel);
			continue;
		}
		if (sel == 8)
			return 0;
		showpx(sel);
		sortMenu();
		printf("请选择:");
		scanf("%d", &sel);
	}
}
/*int main()
{
	fancySort();
	system("pause");
}*/