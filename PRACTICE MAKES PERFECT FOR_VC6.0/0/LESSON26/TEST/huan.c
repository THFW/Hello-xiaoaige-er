#include<stdio.h>
#include<stdlib.h>
#define NULL 0
typedef struct point
{
	int data;
	int No;
	struct point *next;
}LNode,*LlinkList;
int n,m;
LinkList create()	/*���ɵ���ѭ����������*/
{
	int i;
	LinkList head, tail, new;
	head = NULL;
	printf("\ninput n(������):");
	scanf("%d",&n);
	printf("input m : ");
	scanf("%d",&m);
	for(i=1;i<=n;i++)
	{
		new = (LinkList)malloc(sizeof(LNode);
		new->No=i;
	}
	if(head = NULL)		/*����ĵ�һ���ڵ����*/
	{
		head=new;
		tail=head;
	} 
	else				/*���������ڵ����*/
	{
		tail->next=new;
		tail=head;
	} 
	tail->next=head;	/*ѭ�������������*/
	return head; 
} 

void search