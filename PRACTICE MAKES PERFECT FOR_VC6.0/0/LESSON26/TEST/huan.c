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
LinkList create()	/*生成单向循环链表并返回*/
{
	int i;
	LinkList head, tail, new;
	head = NULL;
	printf("\ninput n(总人数):");
	scanf("%d",&n);
	printf("input m : ");
	scanf("%d",&m);
	for(i=1;i<=n;i++)
	{
		new = (LinkList)malloc(sizeof(LNode);
		new->No=i;
	}
	if(head = NULL)		/*链表的第一个节点插入*/
	{
		head=new;
		tail=head;
	} 
	else				/*链表的其余节点插入*/
	{
		tail->next=new;
		tail=head;
	} 
	tail->next=head;	/*循环单链表的生成*/
	return head; 
} 

void search