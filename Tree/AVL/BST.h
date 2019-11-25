#pragma once
#include<iostream>
constexpr auto ENDKEY = -1;
template<typename T1, typename T2>
constexpr auto max(T1 x, T2 y) { return x>y?x:y; }

using namespace std;

typedef struct Binary_Tree_node
{
	int data;	//������
	struct Binary_Tree_node* lchild, * rchild;		//���Һ��ӽ��
}Binode, * BiTree;

//���ʶ�����
void visit(int c, int level)
{
	printf("%dλ�ڵ�%d��\n", c, level);
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

//һ���������
int Binary_Tree_height(BiTree bst)
{
	if (bst == NULL)
		return 0;
	int l = Binary_Tree_height(bst->lchild);
	int r = Binary_Tree_height(bst->rchild);
	return max(l, r) + 1;
}

//������������������ֲ�ƽ����������ת

//�����͵���ת
void Lleft(BiTree &bst)
{
	BiTree lch = bst->lchild;		//���治ƽ��������ӽ��
	bst->lchild = lch->rchild;
	lch->rchild = bst;
	bst = lch;
}

//�����͵���ת
void Rright(BiTree &bst)
{
	BiTree rch = bst->rchild;		//���治ƽ������Һ��ӽ��
	bst->rchild = rch->lchild;
	rch->lchild = bst;
	bst = rch;
}

//������˫��ת
void Lright(BiTree &bst)
{
	//����������������������
	BiTree lch = bst->lchild;
	BiTree lrch = bst->lchild->rchild;
	bst->lchild = lrch;
	bst->lchild->lchild = lch;
	bst->lchild->lchild->rchild = NULL;		//���ܴ���bug	todo

	Lleft(bst);
}

//������˫��ת
void Rleft(BiTree &bst)
{
	//����������������������
	BiTree rch = bst->rchild;
	BiTree rlch = bst->rchild->lchild;
	bst->rchild = rlch;
	bst->rchild->rchild = rch;
	bst->rchild->rchild->lchild = NULL;

	Rright(bst);
}

void Check_Binary_Tree(BiTree  &bst)
{	
	if (bst == NULL)
		return;
	if (Binary_Tree_height(bst->lchild) - Binary_Tree_height(bst->rchild) > 1)
	{
		if (Binary_Tree_height(bst->lchild->lchild) > Binary_Tree_height(bst->lchild->rchild))
			Lleft(bst);
		else
			Lright(bst);
	}
	if (Binary_Tree_height(bst->rchild) - Binary_Tree_height(bst->lchild) > 1)
	{
		if (Binary_Tree_height(bst->rchild->rchild) > Binary_Tree_height(bst->rchild->lchild))
			Rright(bst);
		else
			Rleft(bst);
	}
	//Check_Binary_Tree(bst->lchild);
	//Check_Binary_Tree(bst->rchild);
}

//����û����ȵ�data
//������
void Insert_Binary_Tree(BiTree& bst ,int t)			//bst�Ǹ��ڵ�
{

	if (bst == NULL)	//��������Ҷ���
	{
		BiTree newp = new Binode;
		newp->data = t;
		newp->lchild = NULL;
		newp->rchild = NULL;
		bst = newp;	
	}
	else
	{
		if (t > bst->data)
			Insert_Binary_Tree(bst->rchild, t);
		else
			Insert_Binary_Tree(bst->lchild, t);
	}	
	Check_Binary_Tree(bst);
}

//����һ�ö���������
BiTree Create_Binary_Tree()
{
	BiTree bst = NULL;
	int t;
	cin >> t;
	while (t != ENDKEY)
	{
		Insert_Binary_Tree(bst, t);
		cin >> t;
	}
	return bst;
}

//������������ɾ��
BiTree Delete_Binary_Tree(BiTree bst, int t)
{
	Binode* newp, * f, * s, * q;	
	newp = bst;
	f = NULL;
	while (newp)					
	{
		if (newp->data == t)
			break;
		f = newp;				
		if (t > newp->data)
			newp = newp->rchild;
		else
			newp = newp->lchild;
	}
	if (newp == NULL)				
		return bst;
	if (newp->lchild == NULL)
	{
		if (f == NULL)					
			 bst = bst->rchild;
		else if (f->lchild == newp)
			f->lchild = newp->rchild;
		else							
			f->rchild = newp->rchild;

		delete[]newp;			
	}
	else if (newp->rchild == NULL)		
	{
		if (f == NULL)
			bst = bst->lchild;
		else if (f->lchild == newp)
			f->lchild = newp->lchild;
		else
			f->rchild = newp->lchild;

		delete[]newp;
	}
	else				
	{
		q = newp;
		s = newp->lchild;
		while (s->rchild)
		{
			q = s;				
			s = s->rchild;		
		}
		if (q == newp)
			q->lchild = s->lchild;	
		else	
			q->rchild = s->lchild;
		newp->data = s->data;
		delete[]s;
	}
	Check_Binary_Tree(bst);
	return bst;
}

//����������
BiTree Search_Binary_Tree(BiTree bst, int t)
{
	if (bst == NULL)
		return NULL;
	if (bst->data == t)
		return bst;
	else if (t > bst->data)
		return Search_Binary_Tree(bst->rchild, t);
	else
		return Search_Binary_Tree(bst->lchild, t);
}