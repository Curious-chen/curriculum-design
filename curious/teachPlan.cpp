#include "curiousPlan.h"
#define MAXC 100 //�γ��������ֵ
#define MAXT 12 //ѧ���������ֵ
#define HCreditLimit 10 //ѧ������
#define LCreditLimit 7//ѧ������
/***
	 ��ѧ�ƻ���������
	 ���������ҵ�һ��ƫ���ϵ����֮ת��Ϊȫ���ϵ
	 ѧ�����ޣ���ÿѧ����ѧϰ�ܿγ�ѧ�֣�ʱ�䣩�����ֵ
	 ѧϰ�����������ȣ�����ѧ�ڵ�ѧ������
	 �γ̾����ܼ�����ǰ����ѧ����:ǰ����ѧ�ھ����ﵽѧ������

	 �������:
	 1.ѧ������
	 2.һѧ�ڵ�ѧ������
	 3.ÿ�ſεĿγ̺�(�̶���λ�ַ���)�����ÿγ̵�ѧ�֣����޿γ̵Ŀγ̺�

	 ���� 1
	 ����ͨ���ڽӱ���AOV��
	 ���ͨ����������AOV�������н���ҳ���
	 ������Ҫ�󽫿γ̻��ֵ�ÿһ��ѧ����


	 �ѵ�1����β��ҳ���������������
	 ���ṹ�������ֵܸ�ĸ���������������������

	 �ѵ�2������жϱ����Ƿ����Ҫ��
	 ѧϰ�����������ȣ���һ�����ޣ����������޶�Ϊһ��ѧ��
	 �γ̾����ܼ�����ǰ����ѧ��
***/


void EnQueue(Qnode * head, Treenode * data)
{
	Qnode * p = NULL;
	p = (Qnode *)malloc(sizeof(Qnode));
	p->data = data;
	while (head->next != NULL)
	{
		head = head->next;
	}
	p->next = head->next;
	head->next = p;
}
Treenode * DelQueue(Qnode * head)
{
	Qnode *p;
	if (head->next == NULL)
		return NULL;
	p = head->next;
	head->next = p->next;
	return p->data;
}
int getQueuesize(Qnode *root)
{
	int i = 0;
	root = root->next;
	while (root)
	{
		i++;
		root = root->next;
	}
	return i;
}

//�������޹�ϵͼ
void crt_adjlist(vexnode dig[], int len)
{
	arcnode *p;
	int k, m, i;
	gets_s(dig[0].vexdata, 30);
	printf("\n����ѧ�֣�����Ӧ�Ŀγ����ƣ�\n");
	for (i = 1; i <= len; i++)
	{
		//printf("�γ� %d:",i);
		//gets_s(dig[i].vexdata,30);
		/*dig[i].vexdata[0] = i;
		dig[i].vexdata[1] = '\0';
		dig[i].firstarc = NULL;
		dig[i].indegree = 0;*/
		scanf("%d", &dig[i].credit);
		scanf("%s", dig[i].vexdata);
		dig[i].firstarc = NULL;
		dig[i].indegree = 0;
	}
	printf("\nplease input the arc\n");
	scanf("%d", &k);
	while (k != 0)
	{
		scanf("%d", &m);
		p = (arcnode *)malloc(sizeof(arcnode));
		p->adjvex = m;
		p->nextarc = dig[k].firstarc;
		dig[k].firstarc = p;
		dig[m].indegree++;
		scanf("%d", &k);
	}
}

//���ļ��ж�ȡ����ͼ
vexnode * read_adjlist(const char * path,int *len)
{
	FILE * fp;
	vexnode *dig;
	arcnode *p;
	int i,k,m;
	fp = fopen(path,"rb");
	fscanf(fp,"%d",len);
	dig = (vexnode *)malloc(sizeof(vexnode)*((*len)+1));
	for (i = 1; i <= *len; i++)
	{
		fscanf(fp,"%d%s",&dig[i].credit,dig[i].vexdata);
		dig[i].firstarc = NULL;
		dig[i].indegree = 0;
	}
	fscanf(fp,"%d",&k);
	while (k != 0)
	{
		fscanf(fp,"%d", &m);
		p = (arcnode *)malloc(sizeof(arcnode));
		p->adjvex = m;
		p->nextarc = dig[k].firstarc;
		dig[k].firstarc = p;
		dig[m].indegree++;
		fscanf(fp,"%d", &k);
	}
	fclose(fp);
	return dig;
	
}
/***
	  ��������
	  ���ܣ�ͨ�����Ļ��ݣ�ȷ��Ӧ����ȥ��ֵ
	  Ȼ��ͳ�����Ϊ0�ĵ�
	  ���ԭ�����Ϊ������׼��
***/
int existArr(int arr[], int len, int value)
{
	int i;
	for (i = 0; i < len; i++)
	{
		if (arr[i] == value)
			return 1;
	}
	return 0;
}
void topSort(vexnode dig[], int len, Treenode * troot, Qnode *queue)
{
	arcnode *p = NULL;
	Treenode *t = NULL, *k = NULL, *tnode = troot;
	int *barr = NULL;
	int i, j, fch = 0;
	barr = (int *)malloc(sizeof(int)*len);
	for (i = 0; i < len; i++)//��ʼ�������±�Ϊ0
	{
		barr[i] = 0;
	}
	i = 0;
	while (tnode->data != 0)//���ڵ��±�Ϊ0
	{
		barr[i++] = tnode->data;
		tnode = tnode->fm;//���������˷�֧�Ľڵ��±걣��
	}
	for (j = 0; j < i; j++)
	{
		p = dig[barr[j]].firstarc;
		while (p != NULL)
		{
			dig[p->adjvex].indegree--;//��ȼ�һ
			p = p->nextarc;
		}

	}

	//�����Ϊ0�ĵ���������,ע�⣺���ϻ��ݵ�ֵ������
	for (j = 1; j <= len; j++)
	{
		if (existArr(barr, i, j) || dig[j].indegree != 0)
			continue;
		if (fch == 0)
		{
			t = (Treenode *)malloc(sizeof(Treenode));
			t->data = j;
			t->fm = troot;
			troot->fch = t;
			t->fch = NULL;
			t->nsib = NULL;
			EnQueue(queue, t);
			fch = 1;
		}
		else
		{
			k = (Treenode *)malloc(sizeof(Treenode));
			k->data = j;
			k->fm = troot;
			t->nsib = k;
			k->nsib = NULL;
			k->fch = NULL;
			t = k;
			EnQueue(queue, k);
		}
	}

	//���½���֧�ڵ����,�ָ�����ͼ
	for (j = 0; j < i; j++)
	{
		p = dig[barr[j]].firstarc;
		while (p != NULL)
		{
			dig[p->adjvex].indegree++;
			p = p->nextarc;
		}
	}
}

//��ʼ����
void IniTree(Treenode *root, vexnode dig[], int len, Qnode * queue)
{
	Treenode *p = NULL, *t = NULL;
	int i;
	root->data = 0;
	for (i = 1; i <= len; i++)
	{
		if (dig[i].indegree == 0)
		{
			p = (Treenode *)malloc(sizeof(Treenode));
			p->data = i;
			p->fm = root;
			root->fch = p;
			p->nsib = NULL;
			topSort(dig, len, p, queue);
			i++;
			break;
		}
	}
	for (i; i <= len; i++)
	{
		if (dig[i].indegree == 0)
		{
			t = (Treenode *)malloc(sizeof(Treenode));
			t->fm = root;
			t->data = i;
			t->nsib = NULL;
			p->nsib = t;
			p = t;
			topSort(dig, len, p, queue);
		}
	}

}

/***
	������
	�����֧�㣬������ͼ����ȥ��֧�㣬�ҵ���ǰ�������Ϊ0�ĵ�
***/
void setTree(Treenode *root, vexnode dig[], int len)
{
	Qnode *queue;
	Treenode *p = NULL;
	//��ʼ����
	queue = (Qnode *)malloc(sizeof(Qnode));
	queue->next = NULL;
	IniTree(root, dig, len, queue);
	while ((p = DelQueue(queue)) != NULL)
	{
		topSort(dig, len, p, queue);
	}
}


//ͨ���������п����г�������Ҷ�ӽڵ���ݼ���
void findAlltop(Treenode *root, Qnode * queue)
{
	if (root)
	{
		if (root->fch == NULL)
		{
			EnQueue(queue, root);
		}
		findAlltop(root->fch, queue);
		findAlltop(root->nsib, queue);
	}
}
void getAlltop(vextrem *hterm, Qnode *queue)
{
	Treenode * p;
	vextrem *t;
	arcterm *a;
	int i;
	hterm->next = NULL;
	while ((p = DelQueue(queue)) != NULL)
	{
		t = (vextrem *)malloc(sizeof(vextrem));
		t->fclass = NULL;
		i = 0;
		while (p->data != 0)
		{
			a = (arcterm *)malloc(sizeof(arcterm));
			a->aveterm = a->greterm = 0;
			a->data = p->data;
			a->next = t->fclass;
			t->fclass = a;  //ͷ�巨
			p = p->fm;
			i++;
		}
		if (i != 12)
			printf("%d\n", i);
		t->aveScore = t->greScore = 0;
		t->next = hterm->next;
		hterm->next = t;
	}
}

/***
	�ж��Ƿ������������
***/
int existanceXx(vexnode *dig, int k, int m)
{
	arcnode *p = dig[k].firstarc;
	while (p)
	{
		if (p->adjvex == m)
			return 1;
		p = p->nextarc;
	}
	return 0;
}
int IFsuccess(vextrem * p,vexnode *dig,int sel)
{
	//����һ��ѧ����û�����޹�ϵ
	arcterm *t,*c;
	t = p->fclass;
	while (t->next)
	{
		c = t->next;
		
		if (sel == 0)//ƽ�����ֵ�ѧ�ڱȽ�
		{
			if (c->aveterm == 0)
				break;
			while (c &&(t->aveterm == c->aveterm))//������ͬѧ�ڵĿγ̱Ƚ��ж�
			{
				if (existanceXx(dig, t->data, c->data))
					return 0;
				c = c->next;
			}
		}
		else//̰�����ֵ�ѧ�ڱȽ�
		{
			if (c->greterm == 0)
				break;
			while (c && (t->greterm == c->greterm))
			{
				if (existanceXx(dig, t->data, c->data))
					return 0;
				c = c->next;
			}
		}
		t = t->next;
	}
	return 1;

	
}
//���ѧϰ�����������ȵ��б�
void wAveTerm(vextrem *hterm, vexnode * dig, int len, int tNum)
{
	vextrem * p = hterm->next;
	arcterm *t = NULL;
	double Avescore, aveCredit = 0;
	int termNum, countCredit, i, lowlimit;
	//����ܷ���
	for (i = 1; i <= len; i++)
	{
		aveCredit += dig[i].credit;
	}
	aveCredit = aveCredit / tNum;
	while (p)
	{
		lowlimit = LCreditLimit;
		t = p->fclass;
		if (!t)
			continue;
		while (1)
		{
			t = p->fclass;
			termNum = 1;
			countCredit = 0;
			Avescore = 0;
			while (t->next != NULL)
			{
				t->aveterm = termNum;

				countCredit += dig[t->data].credit;
				t->next->aveterm = termNum;
				if (!IFsuccess(p, dig, 0))
				{
					termNum++;
					if (termNum > tNum)
					{
						goto label;
					}
					Avescore += pow(aveCredit - countCredit, 2);//��ֵ��ƽ��
					countCredit = 0;//����
					goto label1;
				}
				if ((countCredit + dig[t->next->data].credit) > lowlimit)
				{
					if (termNum != tNum)
					{
						Avescore += pow(aveCredit - countCredit, 2);//��ֵ��ƽ��
						countCredit = 0;//����
						termNum++;
					}
				}
				label1:
				t = t->next;
			}
			t->aveterm = termNum;
			countCredit += dig[t->data].credit;
			if (countCredit >= HCreditLimit)
			{
			label:
				lowlimit++;
				if (lowlimit > HCreditLimit)
				{
					p->aveScore = -1;
					break;
				}
				t = p->fclass;
				while (t)
				{
					t->aveterm = 0;
					t = t->next;
				}
				continue;
			}
			if (IFsuccess(p, dig, 0))
			{
				p->aveScore = Avescore + pow(aveCredit - countCredit, 2);
			}
			else
				p->aveScore = -1;
			break;
		}
		p = p->next;
	}

}
void wGreTerm(vextrem *hterm, vexnode * dig, int tNum)
{
	vextrem * p = hterm->next;
	arcterm *t = NULL;
	int termNum, countCredit,highLimit;
	double grescore;
	while (p)
	{
		highLimit = HCreditLimit;
		t = p->fclass;
		if (!t)
			continue;
		while (1)//�ҵ�������Ҫ��Ļ���
		{
			t = p->fclass;
			termNum = 1;
			countCredit = 0;
			grescore = 0;
			while (t->next != NULL)
			{
				t->greterm = termNum;
				countCredit += dig[t->data].credit;

				t->next->greterm = termNum;//ʹ��һ��ֵͬ���ڣ���֤�Ƿ���У���ͬһ�����������޹�ϵ
				if (!IFsuccess(p, dig, 1))
				{
					termNum++;
					if (termNum > tNum)
					{
						goto label;
					}
					grescore += countCredit * pow(0.9, termNum-1);//��ֵ��ƽ��
					countCredit = 0;//����
					goto label1;
				}
				if ((countCredit + dig[t->next->data].credit) > highLimit)
				{
					if (termNum != tNum)
					{
						grescore += countCredit * pow(0.9, termNum);//����Խ���󣬷����õ�Խ��
						countCredit = 0;//����
						termNum++;
					}
				}
				label1:
				t = t->next;
			}
			t->greterm = termNum;
			countCredit += dig[t->data].credit;
			if (countCredit > HCreditLimit)
			{
				label:
				highLimit--;
				if (highLimit < LCreditLimit)
				{
					p->greScore = -1;
					break;
				}
				t = p->fclass;
				while (t)
				{
					t->greterm = 0;
					t = t->next;
				}
				continue;
			}
			if (IFsuccess(p, dig, 1))
			{
				p->greScore = grescore + countCredit * pow(0.9, termNum);
			}
			else
				p->greScore = -1;
			break;
		}
		p = p->next;
	}

}

void getPlan(vextrem *hterm, int * avePlan, int *grePlan)
{
	vextrem * p = hterm->next;
	int i = 1;
	double minAve=-1, maxGre=-1;
	*avePlan = *grePlan = -1;
	minAve = 100;
	maxGre = p->greScore;
	while (p)
	{
		if ((p->aveScore!=-1)&&(p->aveScore < minAve))
		{
			minAve = p->aveScore;
			*avePlan = i;
		}
		if ((p->greScore!=-1)&&(p->greScore > maxGre))
		{
			maxGre = p->greScore;
			*grePlan = i;
		}
		i++;
		p = p->next;
	}
}

//չʾ�ƻ�
void show(vextrem *hterm, int index, vexnode *dig, int sel)
{
	arcterm * p = NULL;
	vextrem *node = NULL;
	FILE * fp = NULL;
	int i = 1, flag, count = 0;
	while (hterm->next != NULL)
	{
		if (i == index)
			break;
		hterm = hterm->next;
		i++;
	}
	node = hterm->next;
	p = node->fclass;
	flag = 0;
	if (sel == 0)
	{
		fp = fopen("./teachPlan/ave.txt","wb");
		printf("\nѧϰ�����������ȣ���������:\n");
		fprintf(fp,"\nѧϰ�����������ȣ���������:\n");
		printf("���ȶ�:%-5.2f\n",node->aveScore);
		fprintf(fp,"���ȶ�:%-5.2f\n", node->aveScore);
		while (p)
		{
			if (flag != p->aveterm)
			{
				if (flag != 0)
				{
					printf("\n��ѧ��:%d\n", count);
					fprintf(fp,"\n��ѧ��:%d\n", count);
					count = 0;
				}
				printf("\n\n��%dѧ��:\n\n", p->aveterm);
				fprintf(fp,"\n\n��%dѧ��:\n\n", p->aveterm);
				flag = p->aveterm;
			}
			count += dig[p->data].credit;
			printf("�γ�����: %s ѧ��: %d\n", dig[p->data].vexdata, dig[p->data].credit);
			fprintf(fp,"�γ�����: %s ѧ��: %d\n", dig[p->data].vexdata, dig[p->data].credit);
			p = p->next;
		}
		printf("\n��ѧ��:%d\n", count);
		fprintf(fp,"\n��ѧ��:%d\n", count);
		fclose(fp);
	}
	else
	{
		fp = fopen("./teachPlan/more.txt", "wb");
		printf("\n�γ̼�����ǰ����ѧ���У���������:\n");
		fprintf(fp,"\n�γ̼�����ǰ����ѧ���У���������:\n");
		printf("̰����:%-5.2f\n", node->greScore);
		fprintf(fp,"̰����:%-5.2f\n", node->greScore);
		while (p)
		{
			if (flag != p->greterm)
			{
				if (flag != 0)
				{
					printf("\n��ѧ��:%d\n", count);
					fprintf(fp,"\n��ѧ��:%d\n", count);
					count = 0;
				}
				printf("\n\n��%dѧ��:\n\n", p->greterm);
				fprintf(fp,"\n\n��%dѧ��:\n\n", p->greterm);
				flag = p->greterm;
			}
			count += dig[p->data].credit;
			printf("�γ�����: %s ѧ��: %d \n", dig[p->data].vexdata, dig[p->data].credit);
			fprintf(fp,"�γ�����: %s ѧ��: %d \n", dig[p->data].vexdata, dig[p->data].credit);
			p = p->next;
		}
		printf("\n��ѧ��:%d\n", count);
		fprintf(fp,"\n��ѧ��:%d\n", count);
		fclose(fp);
	}
}

int countleaf(Treenode *root)
{
	int i;
	if (root == NULL)
		i = 0;
	else if (root->fch == NULL)
		i = 1 + countleaf(root->nsib);
	else
		i = countleaf(root->fch) + countleaf(root->nsib);
	return i;
}


void showxxGraph(vexnode dig[],int n)
{
	int i;
	arcnode *p;
	for (i = 1; i <= n; i++)
	{
		printf("���ڵ�:{ �±�:%-2d �γ�����:%s ѧ��:%-2d ���:%-1d } ��ڵ���:",i,dig[i].vexdata,dig[i].credit,dig[i].indegree);
		p = dig[i].firstarc;
		while (p)
		{
			printf("%-3d ",p->adjvex);
			p = p->nextarc;
		}
		printf("\n");
	}
}
void planMenu1(int n)
{
	switch (n)
	{
	case 1:printf("1�����ļ��ж�ȡ�γ����޹�ϵͼ\n");
	case 2:printf("2���Ӽ��������ȡ�γ����޹�ϵͼ\n"); break;
	case 3:printf("3��չʾ�γ����޹�ϵͼ\n");
	case 4:printf("4���������ṹ������п��ܼƻ���\n"); break;
	case 5:printf("5����ʾ����Ҷ����{�ƻ���}\n");
	case 6:printf("6��ѧϰ������������\n");
	case 7:printf("7���γ̾����ܼ�����ǰ����ѧ��\n"); break;
	case 8:printf("8����ʾѧϰ�����������ȵ����Ų���\n");
	case 9:printf("9����ʾ�γ̾����ܼ�����ǰ����ѧ�ڵ����Ų���\n");
	case 10:printf("10���������ʾ10������\n");
	case 11:printf("11��cls\n");
	case 12:printf("12��exit\n");
	}
}
int teachPlan()
{
	vexnode * dig=NULL;
	Treenode *root = (Treenode *)malloc(sizeof(Treenode));
	Qnode *queue = (Qnode *)malloc(sizeof(Qnode));
	vextrem *hterm = (vextrem *)malloc(sizeof(vextrem));
	int len = 12, avePlan, grePlan, termNum = 6,sel=1,num=1,i,j;
	root->nsib = NULL;
	queue->next = NULL;
	planMenu1(num);
	printf("��ѡ��");
	scanf("%d",&sel);
	while (1)
	{
		switch (sel)
		{
			case 1:dig = read_adjlist("./teachPlan/xxGraph.txt", &len); num += 2; break;
			case 2:printf("����γ�����:{12}"); scanf("%d", &len); printf("����ѧ������:{6}"); scanf("%d", &termNum);
				dig = (vexnode *)malloc(sizeof(vexnode)*(len + 1)); crt_adjlist(dig, len); num += 2; break;
			case 3:showxxGraph(dig, len); break;
			case 4:setTree(root, dig, len); num += 2; break;
			case 5:	printf("Ҷ����:%d\n", countleaf(root)); findAlltop(root, queue);
				printf("�ƻ���:%d\n", getQueuesize(queue)); getAlltop(hterm, queue); num++; break;
			case 6:	wAveTerm(hterm, dig, len, termNum); num++; break;
			case 7:wGreTerm(hterm, dig, termNum); getPlan(hterm, &avePlan, &grePlan); num++; break;
			case 8:show(hterm, avePlan, dig, 0); break;
			case 9:show(hterm, grePlan, dig, 1); break;
			case 10:j = (int)(clock() % (countleaf(root) - 10));
				for (i = j; i < j + 10; i++)
				{
					show(hterm, i, dig, i % 2);
				}
				break;
			case 11:system("CLS"); break;
			default:
				return 0;
				break;
		}
		planMenu1(num);
		printf("��ѡ��");
		scanf("%d", &sel);
	}
	return 1;
}
/*int main()
{
	teachPlan();
	system("pause");
}*/
/*
2 C01
3 C02
4 C03
3 C04
2 C05
3 C06
4 C07
4 C08
7 C09
5 C10
2 C11
3 C12
1 2 1 3 1 4 1 12 2 3 3 5 3 7 3 8 4 5 5 7 6 8 9 10 9 11 9 12 10 12 11 6 0
*/

