#include "curiousHuffman.h"

//选择器，输出当前未被选择的最小值的数组下标
void select(node tree[], int end, int *x)
{
	int i = end;
	int min = 0;
	//确定初始值
	for (i = end; i >= 1; i--)
	{
		if (!tree[i].selectd)
			break;
	}
	min = tree[i].weight;
	*x = i;
	i--;
	for (i; i >= 1; i--)
	{
		if ((!tree[i].selectd) && (tree[i].weight < min))
		{
			min = tree[i].weight;
			*x = i;
			if (i <= n)
				break;
		}
	}
	tree[*x].selectd = 1;

}

//建立哈夫曼树
void sethuftree(node tree[], char mode, const char *filepath, int pdt[])
{
	int i, x1, x2;
	FILE *fp = NULL;

	//读取词频表
	fp = fopen(filepath, "rb");
	for (i = 0; i < 97 * 2; i += 2)
	{
		fscanf(fp, "%d%d", &pdt[i], &pdt[i + 1]);
	}
	fclose(fp);
	if (mode == 'w')
	{
		for (i = 1; i <= n; i++)
		{
			tree[i].weight = pdt[2 * i - 1];
			tree[i].selectd = 0;
			tree[i].rlink = tree[i].llink = -1;
		}
		for (i = n + 1; i <= 2 * n - 1; i++)
		{

			tree[i].selectd = 0;
			tree[i].plink = 0;
		}
		for (i = n + 1; i <= (2 * n - 1); i++)//n-1次合并
		{
			select(tree, i - 1, &x1);//权值最小的
			select(tree, i - 1, &x2);
			tree[x1].plink = i;
			tree[x2].plink = i;
			tree[i].llink = x1;
			tree[i].rlink = x2;
			tree[i].weight = tree[x1].weight + tree[x2].weight;
		}
		//将此哈夫曼树保存到文件huffman
		fp = fopen("./huffman/huffman", "wb");
		for (i = 1; i <= (2 * n - 1); i++)
		{
			fprintf(fp, "%d %d %d %d\n", tree[i].weight, tree[i].plink, tree[i].llink, tree[i].rlink);
		}
		fclose(fp);
	}
	else
	{
		fp = fopen(".//huffman/huffman", "rb");
		for (i = 1; i <= (2 * n - 1); i++)
		{
			fscanf(fp, "%d%d%d%d", &tree[i].weight, &tree[i].plink, &tree[i].llink, &tree[i].rlink);
		}
		fclose(fp);
	}
}

//建立字符集的哈夫曼编码表
void huffcode(node tree[], element table[], int pdt[])
{
	int i, s, f; //s,f:tree中的孩子和双亲
	codetype c;
	for (i = 1; i <= n; i++)
	{
		c.start = n + 1;
		s = i;//从叶子tree[i]开始上溯
		while (f = tree[s].plink)//根节点为双亲节点为0的点
		{
			c.bits[--c.start] = (s == tree[f].llink) ? '0' : '1';
			s = f;
		}
		table[i].code = c;
		table[i].symbol = pdt[2 * i - 2];
	}
}

//初始化哈夫曼树
void Initialization(char mode, const char * path, node tree[], int pdt[], element table[])
{
	sethuftree(tree, mode, path, pdt);//建立哈夫曼树
	huffcode(tree, table, pdt);//建立字符集的哈夫曼编码表
}

//将字符形式转化为二进制形式
arrint * cTob(char text[], int len)
{
	//注意len不算'\0'
	int i = 0, j = 0, c = 0;
	arrint *bText = (arrint *)malloc(sizeof(arrint));
	int lenbits = sizeof(char) * 8;
	int arragelen = len / lenbits + ((len % lenbits > 0) ? 1 : 0);
	bText->bits = (char *)malloc(sizeof(char)*arragelen);
	bText->len = arragelen;
	bText->cyl = len % lenbits > 0 ? len % lenbits : lenbits;
	for (i = 0; i < len; i++)
	{
		c += (text[i] - '0')*pow(2, lenbits - 1 - i % lenbits);
		if (((i + 1) % lenbits == 0) || ((i + 1) == len))//1字节（8位）得出一个整形元素，或者读完所有
		{
			bText->bits[j++] = c;
			c = 0;
		}
	}
	return bText;
}

//将二进制形式转化为字符形式
char * btoC(arrint bins[])
{
	int i = 0, j = 0, len = 0;
	char *textbin = NULL;
	char yd[8] = { 0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01 };
	len = bins->len;
	textbin = (char *)malloc(sizeof(char)*((len - 1) * 8 + bins->cyl + 1));//最后一个int存放倒数第二个的有效位为多少
	for (i = 0; i < len - 1; i++)
	{
		for (j = 0; j < 8; j++)
		{
			textbin[j + i * 8] = ((bins->bits[i] & yd[j]) == 0 ? '0' : '1');
		}
	}
	for (j = 0; j < bins->cyl; j++)//获得最后一位的有效量
		textbin[j + i * 8] = ((bins->bits[i] & yd[j]) == 0 ? '0' : '1');
	textbin[j + i * 8] = '\0';
	return textbin;
}

//fromPath:需要压缩的文章地址 toPath :压缩后的文章地址，table[]:字符集的哈夫曼编码表
int  Coding(element table[], const char * fromPath, const const char *toPath,int *Cnum,int *Dnum)
{
	FILE *fp = NULL;
	char *text = NULL;
	char *textTobin = NULL;
	char c;
	int i = 0, j = 0, k = 0;
	int count = 0;
	arrint *bins = NULL;
	//读取文章中所有字符
	if (!(fp = fopen(fromPath, "rb")))
	{
		puts("读取失败\n");
		return 0;
	}
	while ((c = fgetc(fp)) != -1)
	{
		i++;
		for (j = 1; j <= n; j++)
		{
			if (table[j].symbol == c)
			{
				k = table[j].code.start;
				for (k; k <= n; k++)
				{
					count++;
				}
				break;
			}
		}
	}
	text = (char *)malloc(sizeof(char)*i);
	textTobin = (char *)malloc(sizeof(char)*(count + 1));

	i = 0;
	count = 0;
	fseek(fp, 0L, 0);
	while ((c = fgetc(fp)) != -1)
	{
		text[i++] = c;
		for (j = 1; j <= n; j++)
		{
			if (table[j].symbol == c)
			{
				k = table[j].code.start;
				for (k; k <= n; k++)
				{
					textTobin[count++] = table[j].code.bits[k];
				}
				break;
			}
		}
	}
	printf("字节数（压缩前）：%d\n", i * sizeof(char));
	(*Cnum) += i;
	textTobin[count] = '\0';
	bins = cTob(textTobin, count);
	free(textTobin);
	fp = NULL;
	if (!(fp = fopen(toPath, "wb")))
	{
		printf("文件路径不合法\n");
	}
	else
	{
		fprintf(fp, "%d%c", bins->len, bins->cyl);
		for (i = 0; i < bins->len; i++)
		{
			fprintf(fp, "%c", bins->bits[i]);
			if (i == 197)
				j++;
		}
		fclose(fp);
		printf("字节数（压缩后）：%d\n", bins->len * sizeof(char));
		printf("编译成功,已放入codefile中\n");
		(*Dnum) += bins->len;
		free(bins->bits);
		free(bins);
	}
	return 1;
}

//fromPath:需要解压的文章地址 toPath :解压后的文章地址，tree[]:哈夫曼树，table[]:字符集的哈夫曼编码表
void Decoding(const char *frompath, const char *topath, node tree[], element table[])
{
	int i = 0, j = 0;
	char c;
	int index = 0;
	char * textOfbin = NULL;
	arrint *p = (arrint *)malloc(sizeof(arrint));
	FILE *fp = NULL;
	if (!(fp = fopen(frompath, "rb")))
	{
		printf("文件不存在");

	}
	else
	{
		fscanf(fp, "%d%c", &p->len, &p->cyl);
		p->bits = (char *)malloc(sizeof(char)*p->len);
		fread(p->bits, sizeof(char), p->len, fp);
		fgets(p->bits, p->len, fp);
		textOfbin = btoC(p);
		free(p->bits);
		free(p);
		fclose(fp);

		if (!(fp = fopen(topath, "wb")))
		{
			printf("写入路径格式不正确\n");
		}
		else
		{
			while ((c = textOfbin[i++]) != '\0')
			{
				index = 2 * n - 1;////根节点的数组下标
				while (1)
				{
					if (c == '1')
						index = tree[index].rlink;
					else
						index = tree[index].llink;
					if (index <= n)
					{
						printf("%c", table[index].symbol);
						fprintf(fp, "%c", table[index].symbol);
						break;
					}
					else
						c = textOfbin[i++];
				}
			}
			free(textOfbin);
			printf("解码成功，已放入textfile中\n");
			fclose(fp);
		}
	}
}

//打印压缩文件，并将之以二进制字符形式显示，fromPath:需要打印的压缩的文章地址 toPath :以二进制字符形式保存后的文章地址
void Print(const char * fromPath, const char *toPath)
{
	FILE *fp;
	arrint *p = NULL;
	char *tOfbinc = NULL;
	int i = 0;
	char c;
	if (!(fp = fopen(fromPath, "rb")))
	{
		printf("源文件路径有问题\n");
	}
	else
	{
		p = (arrint *)malloc(sizeof(arrint));
		fscanf(fp, "%d%c", &p->len, &p->cyl);
		p->bits = (char *)malloc(sizeof(char)*p->len);
		fgets(p->bits, p->len, fp);
		tOfbinc = btoC(p);
		free(p->bits);
		free(p);
		while (c = tOfbinc[i++])//'\0'=0时结束
		{
			printf("%c", c);
			if (i % 50 == 0)
				printf("\n");
		}
		printf("\n");
		if (!(fp = fopen(toPath, "wb")))
		{
			printf("目的文件路径有问题\n");
		}
		else
		{
			fputs(tOfbinc, fp);
			printf("写入成功,已载入codeprint中\n");
			fclose(fp);
			free(tOfbinc);
		}


	}
}

//以凹入表的形式打印树结构
void TreePrint(node tree[], element table[])
{
	int  stack[2 * n];//存放先序遍历顺序
	int p;
	int level[2 * n][2], i, s, top, width = 1;// 2*n为树节点数量  2{ 0：缩进数 1：它是父节点的什么（左右或孩子）0‘0’:左孩纸，1‘1’：右孩子，2‘r’:根}
	char type;
	FILE * fp = NULL;
	char *nz;
	if (!(fp = fopen("./huffman/treeprint", "rb")))
	{
		fp = fopen("./huffman/treeprint", "wb");
		top = 1;
		stack[top] = 2 * n - 1;
		level[top][0] = 0;
		level[top][1] = 'r'; // 2表示根节点
		while (top > 0)
		{
			p = stack[top];
			s = level[top][0];
			for (i = 1; i <= s; i++)
			{
				printf("   |   ");
				fprintf(fp, "   |   ");
			}
			if (tree[p].llink != -1)
			{
				printf(" (%c)  ", level[top][1]);
				fprintf(fp, " (%c)  ", level[top][1]);
			}
			else
			{
				if (table[p].symbol != '\n')
				{
					printf("{%c}(%c)", table[p].symbol, level[top][1]);
					fprintf(fp, "{%c}(%c)", table[p].symbol, level[top][1]);
				}
				else
				{
					printf("{\\n}(%c)", level[top][1]);
					fprintf(fp, "{\\n}(%c)", level[top][1]);
				}
			}
			for (i = s + 1; i <= 2 * n; i += 4)
			{
				printf("-");
				fprintf(fp, "-");
			}
			printf("\n");
			fprintf(fp, "\n");
			top--;
			if (tree[p].rlink != -1)
			{
				top++;
				stack[top] = tree[p].rlink;
				level[top][0] = s + width;
				level[top][1] = '1';
			}
			if (tree[p].llink != -1)
			{
				top++;
				stack[top] = tree[p].llink;
				level[top][0] = s + width;
				level[top][1] = '0';
			}

		}
	}
	else
	{
		i = 0;
		while (fgetc(fp) != -1)i++;
		nz = (char *)malloc(sizeof(char)*i + 1);
		fseek(fp, 0L, 0);
		i = 0;
		while ((nz[i] = fgetc(fp)) != -1)i++;
		nz[i] = '\0';
		puts(nz);
		free(nz);

	}
	fclose(fp);
}

const char * combine(const char *x, const char *y)
{
	int i = 0;
	int count = 0;
	char *z;
	while (x[i++] != '\0')count++;
	i = 0;
	while (y[i++] != '\0')count++;
	z = (char *)malloc(sizeof(char)*(count + 1));
	count = 0;
	i = 0;
	while (x[i++] != '\0')z[count++] = x[i - 1];
	i = 0;
	while (y[i++] != '\0')z[count++] = y[i - 1];
	z[count] = '\0';
	return (const char *)z;
}

void CodingAll()
{
	long Handle;
	struct _finddata_t FileInfo;
	node tree[2 * n];
	element table[n + 1];//0单元不存储东西，用来当做根节点的双亲
	int pdt[2 * n];
	char *text_bin = NULL;
	char *text = NULL;
	const char * path = "./huffman/pdt.txt";
	int count,Cnum,Dnum;
	count = Cnum = Dnum = 0;
	Initialization('r', path, tree, pdt, table);
	if ((Handle = _findfirst("./huffman/ks_data/*.*", &FileInfo)) == -1L)

		printf("没有找到匹配的项目\n");

	else

	{
		_findnext(Handle, &FileInfo);
		printf("%s\n", FileInfo.name);
		while (_findnext(Handle, &FileInfo) == 0)
		{
			printf("开始压缩{%s}\n", combine("./huffman/ks_data/", FileInfo.name));
			Coding(table, combine("./huffman/ks_data/", FileInfo.name), combine("./huffman/codefile/", FileInfo.name),&Cnum,&Dnum);
			printf("\n\n");
			count++;
		}
		_findclose(Handle);
		printf("count:%-5d篇文章 %-10d字节 压缩后:%-10d字节  压缩率:%-4.2f%c\n", count,Cnum,Dnum,((double)Dnum)/Cnum*100,'%');


	}

}
//菜单

void hufumanMenu()
{
	printf("1、Initialization\n");
	printf("2、Coding\n");
	printf("3、Decoding\n");
	printf("4、Print\n");
	printf("5、Tree printing\n");
	printf("6、CodingAll\n");
	printf("7、cls\n");
	printf("8、Exit\n");
}
//哈弗曼主程序
int  huffmanEncoder()
{
	node tree[2 * n];
	element table[n + 1];//0单元不存储东西，用来当做根节点的双亲
	int pdt[2 * n];
	char *text_bin = NULL;
	char *text = NULL;
	const char * path = "./huffman/pdt.txt";
	int sel=0;
	hufumanMenu();
	printf("请选择:");
	scanf("%d",&sel);
	while (1)
	{
		switch (sel)
		{
		case 1:Initialization('r', path, tree, pdt, table); printf("初始化完成\n\n"); break;
		case 2:Coding(table, "./huffman/ks_data/100.txt", "./huffman/codefile/100.txt",&sel,&sel); break;
		case 3:Decoding("./huffman/codefile/100.txt", "./huffman/textfile/100.txt", tree, table); break;
		case 4:Print("./huffman/codefile/100.txt", "./huffman/codeprint/100.txt"); break;
		case 5:TreePrint(tree, table); break;
		case 6:CodingAll(); break;
		case 7:system("CLS"); break;
		default: return 0;
		}
		printf("\n\n");
		hufumanMenu();
		printf("请选择:");
		scanf("%d", &sel);
	}

}
/*int main()
{
	huffmanEncoder();
	system("pause");
	return 0;
}*/