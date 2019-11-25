#include<stdio.h>
#include<stdlib.h>
typedef char elemtype;
//���
typedef struct Binode
{
	char data;
	struct Binode *lchild, *rchild;
}Binode, *BiTree;

//���򴴽�һ�ö������������˳�򴴽�һ��������
void PcreateBiTree(BiTree &T)			//*T��һ�����ָ�� 			BiTree *T ���൱��	struct Binode **T		 
{
	char c;
	scanf("%c", &c);
	if (' ' == c)
	{
		T = NULL;
	}
	else
	{
		T = (struct Binode *)malloc(sizeof(struct Binode));
		T->data = c;
		PcreateBiTree(T->lchild);
		PcreateBiTree(T->rchild);
	}
}

//���ʶ�����
void visit(char c,int level)
{
	printf("%cλ�ڵ�%d��\n", c, level);
}

//�������������
void Preorder_Traverse(BiTree T, int level)
{
	if (T)
	{
		visit(T->data, level);
		Preorder_Traverse(T->lchild, level + 1);
		Preorder_Traverse(T->rchild, level + 1);
	}
}

//�������������
void  Aftorder_Traverse(BiTree T, int level)
{
	if (T)
	{
		Aftorder_Traverse(T->lchild, level + 1);
		Aftorder_Traverse(T->rchild, level + 1);
		visit(T->data, level);
	}
}

//�������
void Midorder_Traverse(BiTree T, int level)
{
	if (T)
	{
		Midorder_Traverse(T->lchild, level + 1);
		visit(T->data, level);
		Midorder_Traverse(T->rchild, level + 1);	
	}
}
int main()
{
	int level = 1;
	BiTree T = NULL;
	PcreateBiTree(T);
	Midorder_Traverse(T, level);
	printf("************************************\n");
	Preorder_Traverse(T, level);
	printf("************************************\n");
	Aftorder_Traverse(T, level);
	system("pause");
}
