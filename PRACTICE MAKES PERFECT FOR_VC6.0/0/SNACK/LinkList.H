/*
************************************************************************************
通用双链表
使用方法:Node可以定义节点类，可以自己添加东西，并修改相应的展示函数DisplayNode
为了方便操作，把所有的函数都集成在一个结构体里面，用LinkListFunction定义了一个
LinkListOperator，只要用(LinkListOperator.)即可呼出操作
示范代码:
	Node* Head = NULL;
	Node* New  = NULL;
	
	Head =  LinkListOperator.CreatNode();
	New  =  LinkListOperator.CreatNode();
	LinkListOperator.AddNode(New,Head);
	LinkListOperator.DisplayList(Head);


	最后修改:20170831

************************************************************************************
*/
#ifndef _LinkList_
#define _LinkList_

#include<stdio.h>
#include<malloc.h>
/************************************结构体类型定义********************************/

typedef struct LinkNode						//链表节点
{
	int No;
	//这里可以自己添加元素-------------
	int x;
	int y;
	char Icon[10];
	char Direct;
	char Color;
	//这里可以自己添加元素-------------
	struct LinkNode *pPre;
	struct LinkNode *pNext;

}Node;

typedef struct Function						//链表操作库
{
	Node*	(*CreatNode)(void);							//Node* CreatNode(void)
	void	(*DisplayNode)(Node* ANode);				//void DisplayNode(Node* ANode)
	void	(*AddNode)(Node *AddNode,Node* ListHead);	//void AddNode(Node *AddNode,Node* ListHead) 
	char    (*DeleteNode)(Node *DelNode);				//char DeleteNode(Node *DelNode)
	void	(*DisplayList)(Node* ListHead);				//void DisplayList(Node* ListHead)
	//未完待续
}LinkListFunction;


/************************************子函数定义***********************************/
/**********************************************************************************

功能:展示一个节点
描述:
**********************************************************************************/
void DisplayNode(Node* ANode)
{
	if(ANode!=NULL)
	{
		printf("%d\n",ANode->No);
	}
}

/**********************************************************************************

功能:建立一个结点并返回它的地址
描述:
**********************************************************************************/

Node* CreatNode(void)
{
	Node* ANode = NULL;
	ANode = (Node*)malloc(sizeof(Node));
	ANode->pNext = NULL;
	ANode->pPre	 = NULL;
	ANode->No    = 0;
	ANode->Color = rand()%7+0x08;			//赋予彩色 
	
	return ANode;
}

/**********************************************************************************

功能:头插法新增节点
描述:Node *AddNode,Node* ListHead依次是指向待插入的节点的指针，和指向被插入链表头节
点的指针
**********************************************************************************/
void AddNode(Node *AddNode,Node* ListHead) 
{	
	Node* View = NULL;
	char RepeatCheck = 0;			//重复性检查标志位:待插入的节点是否原本就存在于链表之中?
	if(AddNode != NULL)				//待插入节点的指针是不是为NULL?
	{
		View = ListHead;
		while(View!=NULL)
		{
			if(AddNode==View)
			{
				RepeatCheck = 1;	//这表示待插入的节点其实已经存在于链表中了
				break;
			}
			else
				View = View->pNext;
		}
		if(!RepeatCheck)
		{
			AddNode ->pNext = ListHead->pNext;
			ListHead->pNext = AddNode;
			AddNode->pPre   = ListHead;
			if(	AddNode ->pNext!=NULL)
			{
				AddNode ->pNext ->pPre = AddNode;
			}
		}
		else
		{
			printf("您想插入的节点实际上已经存在，无需重复插入.\n");
		}
	}
	else
	{
		printf("您不能插入一个本来就不存在的节点！\n");
	}

}
/**********************************************************************************

功能:删除一个节点
描述:Node *DelNode要首先给出指向节点的指针
返回1表示删除成功，返回0表示由于特殊原因没有执行删除操作
**********************************************************************************/
char DeleteNode(Node *DelNode)
{	if(DelNode->pPre!=NULL)
	{
		DelNode->pPre->pNext = DelNode->pNext;
		if(DelNode->pNext!=NULL)
		{
			DelNode->pNext->pPre = DelNode->pPre;
		}
		DelNode->pNext= NULL;
		DelNode->pPre = NULL;
		free(DelNode);
		return 1;
	}
	else
	{
		printf("这是头节点或者是一个独立的节点！不允许删除\n");
		return 0;
	}
}


/**********************************************************************************

功能:展示链表
描述:Node* ListHead要给出头节点
**********************************************************************************/
void DisplayList(Node* ListHead)
{
	Node* View = NULL;
	View = ListHead;
	while(View!=NULL)
	{
		DisplayNode(View);
		View = View->pNext;
	}
	
}
/**********************************************************************************

功能:销毁节点
描述:Node* ANode要给出头节点,返回1表示已经销毁，返回0表示本来已经是空，无需销毁 
**********************************************************************************/
char DestroyANode(Node* ANode)
{	if(ANode!=NULL)
	{	
		ANode->pNext = NULL;
		ANode->pPre  = NULL;
		free(ANode);
		return 1;
	}
	else
		return 0;
	
}
/**********************************************************************************

功能:销毁链表
描述:Node* ListHead要给出头节点
**********************************************************************************/
void DestroyLinkList(Node* LinkList)
{
	Node* View = LinkList;
	Node* temp = NULL;
	while(View!=NULL)
	{	
		temp = View->pNext;
		free(View);
		View = temp;
		
	}
	
}

/*********************************全局变量定义**********************************/
//全局变量LinkListOperator:操作库
LinkListFunction LinkListOperator={CreatNode,DisplayNode,AddNode,DeleteNode,DisplayList};

/*********************************仿制C++类的封装*******************************/
//仿制类: LinkListClass
typedef struct LinkListClass
{
	Node *ListHead;
	LinkListFunction LinkListOperator;
}LinkListClass;
/**********************************************************************************

功能:LinkListClass的构造函数
描述:
**********************************************************************************/ 
LinkListClass*  LinkListClassInit() 
{	LinkListClass* LinkList;
	LinkList  = (LinkListClass*)malloc(sizeof(LinkListClass)) ;
	LinkList->ListHead	=	NULL;
	
	LinkList->LinkListOperator.AddNode 		= 	AddNode;
	LinkList->LinkListOperator.CreatNode	=	CreatNode;
	LinkList->LinkListOperator.DeleteNode	=	DeleteNode;
	LinkList->LinkListOperator.DisplayList	=	DisplayList;
	LinkList->LinkListOperator.DisplayNode	=	DisplayNode;
	return LinkList;
}
#endif
