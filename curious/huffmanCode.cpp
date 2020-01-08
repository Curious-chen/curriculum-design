#include "curiousHuffman.h"

//ѡ�����������ǰδ��ѡ�����Сֵ�������±�
void select(node tree[], int end, int *x)
{
	int i = end;
	int min = 0;
	//ȷ����ʼֵ
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

//������������
void sethuftree(node tree[], char mode, const char *filepath, int pdt[])
{
	int i, x1, x2;
	FILE *fp = NULL;

	//��ȡ��Ƶ��
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
		for (i = n + 1; i <= (2 * n - 1); i++)//n-1�κϲ�
		{
			select(tree, i - 1, &x1);//Ȩֵ��С��
			select(tree, i - 1, &x2);
			tree[x1].plink = i;
			tree[x2].plink = i;
			tree[i].llink = x1;
			tree[i].rlink = x2;
			tree[i].weight = tree[x1].weight + tree[x2].weight;
		}
		//���˹����������浽�ļ�huffman
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

//�����ַ����Ĺ����������
void huffcode(node tree[], element table[], int pdt[])
{
	int i, s, f; //s,f:tree�еĺ��Ӻ�˫��
	codetype c;
	for (i = 1; i <= n; i++)
	{
		c.start = n + 1;
		s = i;//��Ҷ��tree[i]��ʼ����
		while (f = tree[s].plink)//���ڵ�Ϊ˫�׽ڵ�Ϊ0�ĵ�
		{
			c.bits[--c.start] = (s == tree[f].llink) ? '0' : '1';
			s = f;
		}
		table[i].code = c;
		table[i].symbol = pdt[2 * i - 2];
	}
}

//��ʼ����������
void Initialization(char mode, const char * path, node tree[], int pdt[], element table[])
{
	sethuftree(tree, mode, path, pdt);//������������
	huffcode(tree, table, pdt);//�����ַ����Ĺ����������
}

//���ַ���ʽת��Ϊ��������ʽ
arrint * cTob(char text[], int len)
{
	//ע��len����'\0'
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
		if (((i + 1) % lenbits == 0) || ((i + 1) == len))//1�ֽڣ�8λ���ó�һ������Ԫ�أ����߶�������
		{
			bText->bits[j++] = c;
			c = 0;
		}
	}
	return bText;
}

//����������ʽת��Ϊ�ַ���ʽ
char * btoC(arrint bins[])
{
	int i = 0, j = 0, len = 0;
	char *textbin = NULL;
	char yd[8] = { 0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01 };
	len = bins->len;
	textbin = (char *)malloc(sizeof(char)*((len - 1) * 8 + bins->cyl + 1));//���һ��int��ŵ����ڶ�������ЧλΪ����
	for (i = 0; i < len - 1; i++)
	{
		for (j = 0; j < 8; j++)
		{
			textbin[j + i * 8] = ((bins->bits[i] & yd[j]) == 0 ? '0' : '1');
		}
	}
	for (j = 0; j < bins->cyl; j++)//������һλ����Ч��
		textbin[j + i * 8] = ((bins->bits[i] & yd[j]) == 0 ? '0' : '1');
	textbin[j + i * 8] = '\0';
	return textbin;
}

//fromPath:��Ҫѹ�������µ�ַ toPath :ѹ��������µ�ַ��table[]:�ַ����Ĺ����������
int  Coding(element table[], const char * fromPath, const const char *toPath,int *Cnum,int *Dnum)
{
	FILE *fp = NULL;
	char *text = NULL;
	char *textTobin = NULL;
	char c;
	int i = 0, j = 0, k = 0;
	int count = 0;
	arrint *bins = NULL;
	//��ȡ�����������ַ�
	if (!(fp = fopen(fromPath, "rb")))
	{
		puts("��ȡʧ��\n");
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
	printf("�ֽ�����ѹ��ǰ����%d\n", i * sizeof(char));
	(*Cnum) += i;
	textTobin[count] = '\0';
	bins = cTob(textTobin, count);
	free(textTobin);
	fp = NULL;
	if (!(fp = fopen(toPath, "wb")))
	{
		printf("�ļ�·�����Ϸ�\n");
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
		printf("�ֽ�����ѹ���󣩣�%d\n", bins->len * sizeof(char));
		printf("����ɹ�,�ѷ���codefile��\n");
		(*Dnum) += bins->len;
		free(bins->bits);
		free(bins);
	}
	return 1;
}

//fromPath:��Ҫ��ѹ�����µ�ַ toPath :��ѹ������µ�ַ��tree[]:����������table[]:�ַ����Ĺ����������
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
		printf("�ļ�������");

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
			printf("д��·����ʽ����ȷ\n");
		}
		else
		{
			while ((c = textOfbin[i++]) != '\0')
			{
				index = 2 * n - 1;////���ڵ�������±�
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
			printf("����ɹ����ѷ���textfile��\n");
			fclose(fp);
		}
	}
}

//��ӡѹ���ļ�������֮�Զ������ַ���ʽ��ʾ��fromPath:��Ҫ��ӡ��ѹ�������µ�ַ toPath :�Զ������ַ���ʽ���������µ�ַ
void Print(const char * fromPath, const char *toPath)
{
	FILE *fp;
	arrint *p = NULL;
	char *tOfbinc = NULL;
	int i = 0;
	char c;
	if (!(fp = fopen(fromPath, "rb")))
	{
		printf("Դ�ļ�·��������\n");
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
		while (c = tOfbinc[i++])//'\0'=0ʱ����
		{
			printf("%c", c);
			if (i % 50 == 0)
				printf("\n");
		}
		printf("\n");
		if (!(fp = fopen(toPath, "wb")))
		{
			printf("Ŀ���ļ�·��������\n");
		}
		else
		{
			fputs(tOfbinc, fp);
			printf("д��ɹ�,������codeprint��\n");
			fclose(fp);
			free(tOfbinc);
		}


	}
}

//�԰�������ʽ��ӡ���ṹ
void TreePrint(node tree[], element table[])
{
	int  stack[2 * n];//����������˳��
	int p;
	int level[2 * n][2], i, s, top, width = 1;// 2*nΪ���ڵ�����  2{ 0�������� 1�����Ǹ��ڵ��ʲô�����һ��ӣ�0��0��:��ֽ��1��1�����Һ��ӣ�2��r��:��}
	char type;
	FILE * fp = NULL;
	char *nz;
	if (!(fp = fopen("./huffman/treeprint", "rb")))
	{
		fp = fopen("./huffman/treeprint", "wb");
		top = 1;
		stack[top] = 2 * n - 1;
		level[top][0] = 0;
		level[top][1] = 'r'; // 2��ʾ���ڵ�
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
	element table[n + 1];//0��Ԫ���洢�����������������ڵ��˫��
	int pdt[2 * n];
	char *text_bin = NULL;
	char *text = NULL;
	const char * path = "./huffman/pdt.txt";
	int count,Cnum,Dnum;
	count = Cnum = Dnum = 0;
	Initialization('r', path, tree, pdt, table);
	if ((Handle = _findfirst("./huffman/ks_data/*.*", &FileInfo)) == -1L)

		printf("û���ҵ�ƥ�����Ŀ\n");

	else

	{
		_findnext(Handle, &FileInfo);
		printf("%s\n", FileInfo.name);
		while (_findnext(Handle, &FileInfo) == 0)
		{
			printf("��ʼѹ��{%s}\n", combine("./huffman/ks_data/", FileInfo.name));
			Coding(table, combine("./huffman/ks_data/", FileInfo.name), combine("./huffman/codefile/", FileInfo.name),&Cnum,&Dnum);
			printf("\n\n");
			count++;
		}
		_findclose(Handle);
		printf("count:%-5dƪ���� %-10d�ֽ� ѹ����:%-10d�ֽ�  ѹ����:%-4.2f%c\n", count,Cnum,Dnum,((double)Dnum)/Cnum*100,'%');


	}

}
//�˵�

void hufumanMenu()
{
	printf("1��Initialization\n");
	printf("2��Coding\n");
	printf("3��Decoding\n");
	printf("4��Print\n");
	printf("5��Tree printing\n");
	printf("6��CodingAll\n");
	printf("7��cls\n");
	printf("8��Exit\n");
}
//������������
int  huffmanEncoder()
{
	node tree[2 * n];
	element table[n + 1];//0��Ԫ���洢�����������������ڵ��˫��
	int pdt[2 * n];
	char *text_bin = NULL;
	char *text = NULL;
	const char * path = "./huffman/pdt.txt";
	int sel=0;
	hufumanMenu();
	printf("��ѡ��:");
	scanf("%d",&sel);
	while (1)
	{
		switch (sel)
		{
		case 1:Initialization('r', path, tree, pdt, table); printf("��ʼ�����\n\n"); break;
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
		printf("��ѡ��:");
		scanf("%d", &sel);
	}

}
/*int main()
{
	huffmanEncoder();
	system("pause");
	return 0;
}*/