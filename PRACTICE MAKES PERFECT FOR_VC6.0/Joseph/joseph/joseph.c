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
LinkList create()	/*���ɵ���ѭ����������*/
{
	int i;
	LinkList head,tail,new1;
	head = NULL1;
	printf("\ninput n(������):");
	scanf("%d",&n);
	printf("\ninput m: \n"); 
	scanf("%d",&m);
	for(i=1;i<=n;i++)
	{
		new1 = (LinkList)malloc(sizeof(LNode));
		new1->No=i;
		if(head==NULL1)			/*����ĵ�һ���ڵ����*/
		{
			head=new1;	tail=head;
		} 
		else					/*���������ڵ����*/ 
		{
			tail->next=new1; tail = new1;
		}
		tail->next=head;		/*ѭ�������������*/
		return head; 
	}
} 
	
void search(LinkList head)
{/* ��ѭ������ʵ�ֱ�������*/
	int count,num;
	LinkList pre,p;
	num=0; count=1;
	p=head;
	printf("\noutput data: ");
	while(num < n)
	{
		do/*�ۼƱ���*/
		{
			count++;pre=p; p=p->next; 
		}while(count<m);
		pre->next=p->next;	/*��m���˳���*/
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
