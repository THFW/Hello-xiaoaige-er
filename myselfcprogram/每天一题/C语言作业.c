#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct PERSON
{
	char name[20];
	int count;
	struct PERSON *prior; 
	struct PERSON *next;
}people, *Person;

Person CreateNode(char name[]);	//����ڵ�
Person LinkNode(Person head, char name[]);	//���ӽڵ�
Person sortlist(Person head);	//����
Person countvotes(Person head, char name[]);// ��Ʊ
void printlist(Person head);	//��ӡ����
int lengthlist(Person head);	//�жϽڵ����
void printlistintofile(Person head);	////�������Զ����Ƶ���ʽд���ļ��� 
Person readfile(Person head);	//���ļ��ж�ȡ����
void deletelist(Person head);	//��������


//����ڵ�
Person CreateNode(char name[])
{
	Person p;
	p = (Person)malloc(sizeof(people));
	p->next = NULL;
	p->prior = NULL;
	p->count = 0;
	strcpy(p->name, name);
	return 0;
}

//���ӽڵ�    ˫������ �����������Ǹ�˫��ڵ�
Person LinkNode(Person head, char name[])
{
	if(NULL == head)
	{
		head = CreateNode(name);
		return head;
	}
	else
	{
		Person q;
		Person p;
		q = head;
		p = CreateNode(name);
		while(q->next != NULL)
		{
			q = q->next;
		}
		q->next = p;
		p->prior = q;
	}
	return head;
}

//�жϽڵ����
int lengthlist(Person head)
{
	Person p;
	p = head;
	int i = 0;
	while( p != NULL){
		++i;
		p = p ->next;
	}
	return i;
}

//����	������ѡ������ѽ  ������ð������ Ŷ�����ջ���ѡ��  ԭ�����㷨����	
//��һ�����������棬������ô�����			
//���Ǵ󼸵�д�Ĵ��밡		
Person sortlist(Person head)
{
	int i,j,z;
	char a[100];
	int len;
	len = lengthlist(head);
	Person p,q;
	p = head;
	for(i = 0,p = head; i <len; p = p->next,++i)
	{	
		for(j=i+1,q = p->next; j < len; q = q->next, ++j){
			  if(strcmp(p->name, q->name) > 0)
			  {
					strcpy(a,p->name);
					strcpy(p->name, q->name);
					strcpy(q->name,a);
					z = p->count;
					p->count = q->count;
					q->count = z; 
		      }
		}
	}
	return head;
}

//��Ʊ   ���Ȳ�����������鵽�ˣ�����������Ʊ����Ȼ�󷵻�����ͷ������鲻������������
//�㲻�����������while��Ϊ��֪��LinkNode���ص�p��ʾʲô��  
Person countvotes(Person head,char name[])
{
	Person p;
	int n = 0;
	p = head;
	while(p != NULL)
	{
		if(strcmp(p->name,name) == 0)
		{
			n=1;
			p->count++;
			return head;
		}
		p=p->next;
	}
	if(0 == n)
	{
		p = LinkNode(head,name);
		while(p->next != NULL)
		{
			p = p->next;
		}
		p->count=1;
	}
	return head;
}

//��ӡ����
void printlist(Person head)
{
	Person p;
	p = head;
	while(p != NULL)
	{
		printf("\t %-5s %d\n",p->name,p->count);
		p = p ->next;	
	}
}

//�������Զ����Ƶ���ʽд���ļ��� 
void printlistintofile(Person head)
{
	FILE *fp;
	if(!(fp = fopen("D:\\a.txt","wb")))
	{	
		printf("Error to open the file");
	}
	Person p;
	p = head;
	while(p != NULL)
	{
		fwrite(p,sizeof(people),1,fp);
		p = p->next;
	}
	fclose(fp);
}

//���ļ��ж�ȡ����
Person readfile(Person head)
{
	FILE *fp;
	Person p,q;
	int n;
	if(!(fp = fopen("D:\\a.txt","rb")))
	{
		printf("Error to open the file!");
	}
	
	//head = (Person) malloc(sizeof(people));
	q = head;
	//q->next = NULL;
	//q->prior = NULL;
	fseek(fp,0,0);
	while(n != ftell(fp))
	{
		p = (Person)malloc(sizeof(people));
		fread(p,sizeof(people),1,fp);
		if(q == NULL )
		{
			head = 0;
			q = head;
			q->prior = NULL;
			q->next = NULL;
		}
		else
		{
			q->next = p;
			p->prior = q;
			q = p;
			p->next = NULL;	
		}
	}
	return head;
}

//��������
void deletelist(Person head)
{
	Person p;
	p = head;
	while(p != NULL)
	{
		p = head->next;
		free(head);
		head = 0;
	}
}

int main()
{
	char name[100] = {0};
	int i = 0;
	FILE *fp;
	if(1/*!(fp = fopen("D:\\a.txt","r"))*/)
	{
		//��ʼ������
		Person head = NULL;
		printf("Please input five people's name:\n");
		for(i = 0; i < 5; i ++)
		{
			scanf("%s",name);
			head = LinkNode(head,name);
		}
		
		//������ӡ����
		printf("\nPresent condition is: \n");
		sortlist(head);
		printlist(head);
		printf("\n");

		//��Ʊ
		printf("if you want to exit, please input 'exit'.\n\tStart count now.\n");
		while(1){
				printf("Please input the candibine's name: ");
				
				scanf("%s",name);
				if(strcmp(name,"exit") == 0)
				{	
					break;
				}
				countvotes(head,name);
		}
		
		//��ӡ��������ս��
		printf("\nFinal result is:\n");
		sortlist(head);
		printlist(head);
		
		//�������Զ����Ƶķ�ʽд���ļ���
		printlistintofile(head);

		//��������
		deletelist(head);
	}
	else
	{
		Person head = NULL;
		//���ļ��ж�ȡ���ݲ���������,��ӡ
		head = readfile(head);
		
		//������ӡ����
		printf("Present condition is:\n");
		sortlist(head);
		printlist(head);
		printf("\n");

		//��Ʊ
		printf("if you want to exit, please input 'exit'.\n\tStart count now.\n");
		while(1){
			    printf("Please input the candidate's name: ");	
				
				scanf("%s",name);
				if(strcmp(name, "exit") == 0)
				{
					break;
				}		
				countvotes(head,name);
		};
		
		//��ӡ��������ս��
		printf("\nFinal result is:\n");
		sortlist(head);
		printlist(head);

		//��������	
		deletelist(head);
	}
	return 0;
}