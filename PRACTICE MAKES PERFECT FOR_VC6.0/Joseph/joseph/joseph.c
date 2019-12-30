#include <stdio.h>
#include <stdlib.h>

#define NULL1 0
typedef struct point
{
	int data;
	int No;
	struct point *next;
}LNode,*LinkList;
int n,m;
LinkList create()	/*生成单向循环链表并返回*/
{
	int i;
	LinkList head,tail,new1;
	head = NULL1;
	printf("\ninput n(总人数):");
	scanf("%d",&n);
	printf("\ninput m: \n"); 
	scanf("%d",&m);
	for(i=1;i<=n;i++)
	{
		new1 = (LinkList)malloc(sizeof(LNode));
		new1->No=i;
		if(head==NULL1)			/*链表的第一个节点插入*/
		{
			head=new1;	tail=head;
		} 
		else					/*链表的其余节点插入*/ 
		{
			tail->next=new1; tail = new1;
		}
		tail->next=head;		/*循环单链表的生成*/
		return head; 
	}
} 
	
void search(LinkList head)
{/* 用循环链表实现报数问题*/
	int count,num;
	LinkList pre,p;
	num=0; count=1;
	p=head;
	printf("\noutput data: ");
	while(num < n)
	{
		do/*累计报数*/
		{
			count++;pre=p; p=p->next; 
		}while(count<m);
		pre->next=p->next;	/*报m的人出列*/
		printf("%5d",p->No);
		free(p);
		p=pre->next;
		count = 1;
		num++;
	}
}

int main()
{
	LinkList head;
	system("cls");	//clrscr();
	head=create();
	search(head);
	getchar();
	getchar();
	return 0;
}
