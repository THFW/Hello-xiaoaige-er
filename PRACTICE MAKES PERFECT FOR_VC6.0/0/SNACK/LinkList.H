/*
************************************************************************************
ͨ��˫����
ʹ�÷���:Node���Զ���ڵ��࣬�����Լ����Ӷ��������޸���Ӧ��չʾ����DisplayNode
Ϊ�˷�������������еĺ�����������һ���ṹ�����棬��LinkListFunction������һ��
LinkListOperator��ֻҪ��(LinkListOperator.)���ɺ�������
ʾ������:
	Node* Head = NULL;
	Node* New  = NULL;
	
	Head =  LinkListOperator.CreatNode();
	New  =  LinkListOperator.CreatNode();
	LinkListOperator.AddNode(New,Head);
	LinkListOperator.DisplayList(Head);


	����޸�:20170831

************************************************************************************
*/
#ifndef _LinkList_
#define _LinkList_

#include<stdio.h>
#include<malloc.h>
/************************************�ṹ�����Ͷ���********************************/

typedef struct LinkNode						//�����ڵ�
{
	int No;
	//��������Լ�����Ԫ��-------------
	int x;
	int y;
	char Icon[10];
	char Direct;
	char Color;
	//��������Լ�����Ԫ��-------------
	struct LinkNode *pPre;
	struct LinkNode *pNext;

}Node;

typedef struct Function						//����������
{
	Node*	(*CreatNode)(void);							//Node* CreatNode(void)
	void	(*DisplayNode)(Node* ANode);				//void DisplayNode(Node* ANode)
	void	(*AddNode)(Node *AddNode,Node* ListHead);	//void AddNode(Node *AddNode,Node* ListHead) 
	char    (*DeleteNode)(Node *DelNode);				//char DeleteNode(Node *DelNode)
	void	(*DisplayList)(Node* ListHead);				//void DisplayList(Node* ListHead)
	//δ�����
}LinkListFunction;


/************************************�Ӻ�������***********************************/
/**********************************************************************************

����:չʾһ���ڵ�
����:
**********************************************************************************/
void DisplayNode(Node* ANode)
{
	if(ANode!=NULL)
	{
		printf("%d\n",ANode->No);
	}
}

/**********************************************************************************

����:����һ����㲢�������ĵ�ַ
����:
**********************************************************************************/

Node* CreatNode(void)
{
	Node* ANode = NULL;
	ANode = (Node*)malloc(sizeof(Node));
	ANode->pNext = NULL;
	ANode->pPre	 = NULL;
	ANode->No    = 0;
	ANode->Color = rand()%7+0x08;			//�����ɫ 
	
	return ANode;
}

/**********************************************************************************

����:ͷ�巨�����ڵ�
����:Node *AddNode,Node* ListHead������ָ�������Ľڵ��ָ�룬��ָ�򱻲�������ͷ��
���ָ��
**********************************************************************************/
void AddNode(Node *AddNode,Node* ListHead) 
{	
	Node* View = NULL;
	char RepeatCheck = 0;			//�ظ��Լ���־λ:������Ľڵ��Ƿ�ԭ���ʹ���������֮��?
	if(AddNode != NULL)				//������ڵ��ָ���ǲ���ΪNULL?
	{
		View = ListHead;
		while(View!=NULL)
		{
			if(AddNode==View)
			{
				RepeatCheck = 1;	//���ʾ������Ľڵ���ʵ�Ѿ���������������
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
			printf("�������Ľڵ�ʵ�����Ѿ����ڣ������ظ�����.\n");
		}
	}
	else
	{
		printf("�����ܲ���һ�������Ͳ����ڵĽڵ㣡\n");
	}

}
/**********************************************************************************

����:ɾ��һ���ڵ�
����:Node *DelNodeҪ���ȸ���ָ��ڵ��ָ��
����1��ʾɾ���ɹ�������0��ʾ��������ԭ��û��ִ��ɾ������
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
		printf("����ͷ�ڵ������һ�������Ľڵ㣡������ɾ��\n");
		return 0;
	}
}


/**********************************************************************************

����:չʾ����
����:Node* ListHeadҪ����ͷ�ڵ�
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

����:���ٽڵ�
����:Node* ANodeҪ����ͷ�ڵ�,����1��ʾ�Ѿ����٣�����0��ʾ�����Ѿ��ǿգ��������� 
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

����:��������
����:Node* ListHeadҪ����ͷ�ڵ�
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

/*********************************ȫ�ֱ�������**********************************/
//ȫ�ֱ���LinkListOperator:������
LinkListFunction LinkListOperator={CreatNode,DisplayNode,AddNode,DeleteNode,DisplayList};

/*********************************����C++��ķ�װ*******************************/
//������: LinkListClass
typedef struct LinkListClass
{
	Node *ListHead;
	LinkListFunction LinkListOperator;
}LinkListClass;
/**********************************************************************************

����:LinkListClass�Ĺ��캯��
����:
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