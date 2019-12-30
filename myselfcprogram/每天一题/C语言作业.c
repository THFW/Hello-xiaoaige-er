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

Person CreateNode(char name[]);	//创造节点
Person LinkNode(Person head, char name[]);	//连接节点
Person sortlist(Person head);	//排序
Person countvotes(Person head, char name[]);// 计票
void printlist(Person head);	//打印链表
int lengthlist(Person head);	//判断节点个数
void printlistintofile(Person head);	////将链表以二进制的形式写入文件中 
Person readfile(Person head);	//从文件中读取链表
void deletelist(Person head);	//销毁链表


//创造节点
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

//连接节点    双向链表。 看不出，还是个双向节点
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

//判断节点个数
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

//排序	哈哈，选择排序呀  好像是冒泡排序 哦。最终还是选择  原谅我算法不好	
//第一次在链表里面，看到这么排序的			
//这是大几的写的代码啊		
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

//计票   首先查找链表，如果查到了，就增加它的票数，然后返回链表头，如果查不到，则新增。
//搞不懂插入这里的while因为不知道LinkNode返回的p表示什么。  
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

//打印链表
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

//将链表以二进制的形式写入文件中 
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

//从文件中读取链表
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

//销毁链表
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
		//初始化链表
		Person head = NULL;
		printf("Please input five people's name:\n");
		for(i = 0; i < 5; i ++)
		{
			scanf("%s",name);
			head = LinkNode(head,name);
		}
		
		//排序后打印链表
		printf("\nPresent condition is: \n");
		sortlist(head);
		printlist(head);
		printf("\n");

		//记票
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
		
		//打印链表的最终结果
		printf("\nFinal result is:\n");
		sortlist(head);
		printlist(head);
		
		//将链表以二进制的方式写入文件中
		printlistintofile(head);

		//销毁链表
		deletelist(head);
	}
	else
	{
		Person head = NULL;
		//从文件中读取数据并创建链表,打印
		head = readfile(head);
		
		//排序后打印链表
		printf("Present condition is:\n");
		sortlist(head);
		printlist(head);
		printf("\n");

		//记票
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
		
		//打印链表的最终结果
		printf("\nFinal result is:\n");
		sortlist(head);
		printlist(head);

		//销毁链表	
		deletelist(head);
	}
	return 0;
}