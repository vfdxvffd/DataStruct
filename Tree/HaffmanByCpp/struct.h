#pragma once
#include<iostream>
#include<cstring>
using namespace std;

//���ȼ�����
typedef struct QNode
{
	struct TNode* val;			//���Ľ��,��ʵҲ����������
	int priority;				//���ȼ�
	struct QNode* next;			//ָ����
}*Node;
typedef struct Queue
{
	int size;					//���д�С
	struct QNode* front;		//����ͷָ��
}queue;

//��
typedef struct TNode
{
	char data;					//�ַ�ֵ
	struct TNode* left;			//����
	struct TNode* right;		//�Һ���
}*Tree;

//��
typedef struct BNode
{
	char code[256];					//����
	char symbol;				//�ַ�
	struct BNode* next;			//ָ����һ��
}*bNode;
typedef struct Table
{
	struct BNode* first;		//��ͷ
	struct BNode* last;			//��β
}*table;

//���еĺ���

//��ʼ��
queue Init_queue()
{
	queue q;
	q.size = 0;
	q.front = new struct QNode;
	if (!q.front)
	{
		printf("����ʧ�ܣ�\n");
		exit(1);
	}
	q.front->next = NULL;
	return q;
}

//���룬�������ȼ�
bool EnQueue(queue& q, Tree avl, int weight)
{
	Node newp = new struct QNode;
	newp->val = avl;
	newp->priority = weight;
	//�ձ�
	if (q.size == 0 || q.front == NULL)
	{
		newp->next = NULL;
		q.front = newp;
		q.size = 1;
		return true;
	}
	else		//�м�λ�ã���Ҫ����
	{
		if (weight <= q.front->priority)		//�ȵ�һ����С
		{
			newp->next = q.front;
			q.front = newp;
			q.size++;
			return true;
		}
		else
		{
			Node beforp = q.front;
			while (beforp->next != NULL)
			{
				if (weight <= beforp->next->priority)
				{
					newp->next = beforp->next;
					beforp->next = newp;
					q.size++;
					return true;
				}
				else
				{
					beforp = beforp->next;
				}
			}
			//��Ҫ���ڶ������
			if (beforp->next == NULL)
			{
				newp->next = NULL;
				beforp->next = newp;
				q.size++;
				return true;
			}
		}
	}
	return true;
}

//��������
queue Create_Queue()
{
	queue q = Init_queue();
	while (1)
	{
		char symbol;
		int weight;
		cin >> symbol >> weight;

		if (weight == 0)
			break;

		Tree t = new struct TNode;
		t->data = symbol;
		t->left = NULL;
		t->right = NULL;
		EnQueue(q, t, weight);
	}
	return q;
}

//�����������ȼ���С��
Tree Dequeue(queue& q)
{
	if (q.front == NULL)
	{
		cout << "�նӣ�" << endl;
		exit(1);
	}
	Node p = q.front;
	q.front = p->next;
	Tree e = p->val;
	q.size--;
	delete[] p;
	return e;
}


//���ĺ���

//����һ����
Tree Create_Tree(queue& q)
{
	while (q.size != 1)
	{
		int priority = q.front->priority + q.front->next->priority;
		Tree left = Dequeue(q);
		Tree right = Dequeue(q);

		Tree newTNode = new struct TNode;
		newTNode->left = left;
		newTNode->right = right;

		EnQueue(q, newTNode, priority);
	}
	Tree root = new struct TNode;
	root = Dequeue(q);
	return root;
}

//��ĺ���


void travel(Tree root, table& t, char code[256], int k)
{
	if (root->left == NULL && root->right == NULL)
	{
		code[k] = '\0';

		bNode b = new struct BNode;
		b->symbol = root->data;
		strcpy(b->code, code);
		b->next = NULL;

		//β�����뷨
		if (t->first == NULL)		//�ձ�
		{
			t->first = b;
			t->last = b;
		}
		else
		{
			t->last->next = b;
			t->last = b;
		}
	}
	if (root->left != NULL)
	{
		code[k] = '0';
		travel(root->left, t, code, k + 1);
	}
	if (root->right != NULL)
	{
		code[k] = '1';
		travel(root->right, t, code, k + 1);
	}

}

//����һ�ű�
table Create_Table(Tree root)
{
	table t = new struct Table;
	t->first = NULL;
	t->last = NULL;

	char code[256];
	int k = 0;
	travel(root, t, code, k);
	return t;
}