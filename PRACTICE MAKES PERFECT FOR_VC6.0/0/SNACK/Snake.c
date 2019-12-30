/*********************************************************

����:����һ��C���԰汾�ġ����ڿ���̨��̰������Ϸ
��Windows7����ϵͳ
��Visual C++ 6.0����Dev-C++ 5.9.2 ���붼����ͨ��
**********************************************************/

#include<string.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include<conio.h>
#include"LinkList.h"
#include"Point.h"
#include"voice.h"

char  GameOver	=	0;		//ʧ��ԭ���¼ 1:ҧ���Լ� 2:ײǽ 
/**********************************************************
����:�ж��ʵ��λ���Ƿ��Ѿ���������λ���ϵ��غϡ� x �� y �� 
����: ���ر��غϵĽڵ��ַ��NULL��ʾû�нڵ㱻�غ�

***********************************************************/
Node* NodePositionCheck(Node* ListHead,Node* ANode)
{
	Node* View = ListHead;
	while(View!=NULL)
	{
		if( View->x==ANode->x && View->y==ANode->y)
			return View;
		View = View->pNext;
	 } 
	 return NULL;
}

/**********************************************************
����:����������Ϣ����һ���ʵ�,��������ʵ�䵱ͷ�ڵ�,������
��ͷ�ڵ��ַ���� 
����: 

***********************************************************/
Node* CreatNodeByInput(Node* ListHead,char Command)
{   	
	Node* Body = NULL;


	Body = CreatNode();
	Body->pNext = ListHead;
	ListHead->pPre = Body;
	
	Body->x = ListHead->x;
	Body->y = ListHead->y;
	strcpy(Body->Icon,"��");
	strcpy(ListHead->Icon,"��"); 
	switch(Command)
	{	case 'w':
		case 'W':Body->y -= 1;Body->Direct = 'w';break;
		case 's':
		case 'S':Body->y += 1;Body->Direct = 's';break;
		case 'a':
		case 'A':Body->x -= 1;Body->Direct = 'a';break;
		case 'd':
		case 'D':Body->x += 1;Body->Direct = 'd';break;
	
	}

	
	DisplayAPoint(ListHead);
	DisplayAPoint(Body);
	return Body;
}
/**********************************************************
����:ɾ����������һ���ڵ� 
����: 

***********************************************************/
void DeleteLinkListEnd(Node* ListHead)
{
	Node* View = NULL;
	View = ListHead;
	
	while(View->pNext!=NULL)
	{
		View = View->pNext;
	}
	View->pPre->pNext = NULL;
	View->pPre = NULL;
	
	if(View->x == ListHead->x&&View->y == ListHead->y) 
	{//����������������β�Ľڵ�λ�úʹ�ʱ��ͷ��λ���غ� ���ǾͲ�����ȥ������ʾ��β�ˣ���Ϊ��Ȼ����ͷ���� 
	}
	else
	{
		strcpy(View->Icon,"��");
		DisplayAPoint(View);
	}
	
	free(View);
}


/****************************������************************/ 
void main()
{	
	Node* Snake 	= 	NULL;
	Node* Food  	= 	NULL;
	int   StepVaule =   0;
	int   Speed		=	15000;
	int   Score		=	0;
	char  *ScoreStr =   NULL;
	char  flash     =   0;
	char  KeyVaule	=	'p';
	char  ColorFont =   0;
	
	int   MapXStart	=	0;
	int   MapYStart =   0;
	int   MapXSize	=	20;
	int   MapYSize	=	20;
	char  BuildColor=	0;
	int  i = 0;
	
	srand(time(NULL));
	BuildColor 	= 	rand()%6 +1 +0x08;
	ColorFont	=	rand()%6 +1 +0x08;
	//��ʾ����
	{	
		WIN32display(MapXStart+MapXSize+2,MapYStart+3,"C����:̰������Ϸ",ColorFont);
		WIN32display(MapXStart+MapXSize+2,MapYStart+4,"���뻷����WINDOWS_7 VC6.0����DEVC++",ColorFont);
		WIN32display(MapXStart+MapXSize+2,MapYStart+5,"W:��",ColorFont);
		WIN32display(MapXStart+MapXSize+2,MapYStart+6,"S:��",ColorFont);
		WIN32display(MapXStart+MapXSize+2,MapYStart+7,"A:��",ColorFont);
		WIN32display(MapXStart+MapXSize+2,MapYStart+8,"D:��",ColorFont);
		WIN32display(MapXStart+MapXSize+2,MapYStart+9,"ע��:��Ӣ��״̬������",ColorFont);
		WIN32display(MapXStart+MapXSize+2,MapYStart+10,"�ſ��Դﵽ����Ч��",ColorFont);
		WIN32display(MapXStart+MapXSize+2,MapYStart+13,"��Ϸ�Ѿ���ͣ��������p��ʼ��Ϸ",ColorFont);
		WIN32display(MapXStart+MapXSize+2,MapYStart+15,"�浽��50�־��Զ���ʾԴ������",ColorFont);
	}	
	
	//MessageBox(NULL,"�浽50�ָ�Դ��","̰����",MB_OK);
	ScoreStr = (char *)malloc(sizeof(char)*100);
	ScoreStr = itoa(Score,ScoreStr,10);
	HideCursor();
	srand((unsigned)time(NULL));
	//����ǽ�� 
	for(i=MapXStart;i<=MapXSize+MapXStart;i++)
	{	WIN32display(i,MapYStart,"��",BuildColor);
		WIN32display(i,MapYStart+MapYSize,"��",BuildColor);
	}	
	for(i=MapYStart;i<=MapYSize+MapYStart;i++)
	{
		WIN32display(MapYStart,i,"��",BuildColor);
		WIN32display(MapYStart+MapYSize,i,"��",BuildColor);
	}
	//������������ͷ�͵�һ��ʳ�� 
	Snake = LinkListOperator.CreatNode();
	
	strcpy(Snake->Icon,"��");
	Snake->x = 10;
	Snake->y = 10;
	Snake->Direct = 'w';
	Snake = CreatNodeByInput(Snake,'w');
	Snake = CreatNodeByInput(Snake,'w');
	DisplayAPointList(Snake); 
	
	Food = LinkListOperator.CreatNode();
	strcpy(Food->Icon,"��");
	Food->x = rand()%(MapXSize-1)+MapXStart+1;
	Food->y = rand()%(MapYSize-1)+MapYStart+1;
	DisplayAPoint(Food);
	//��ʼ���Ʒְ� 
	WIN32display(MapXStart+MapXSize+2,MapYStart+12,"Score:",ColorFont);
	WIN32display(MapXStart+MapXSize+2+7,MapYStart+12,ScoreStr,ColorFont);
	//��ʽ��ʼ��Ϸ 
	 while(!GameOver)
	 {	
			if(KeyVaule=='p')							//Pause��ͣ����
				{	
					VoiceOfPause();
					WIN32display(MapXStart+MapXSize+2,MapYStart+13,"��Ϸ�Ѿ���ͣ��������p��ʼ��Ϸ",ColorFont);
					while(1)
					{
						KeyVaule = getch();
						KeyVaule |=  0x20;
						if(KeyVaule=='p')
						{	VoiceOfPause();
							WIN32display(MapXStart+MapXSize+2,MapYStart+13,"������Ϸ...����p��������ͣ��Ϸ",ColorFont);
							KeyVaule=0;
							break;
						}
					}
				}
					
		
	 		StepVaule++;
	 		
	 		if(StepVaule>Speed)
	 			StepVaule=0;
	 	
			if(kbhit())											//����а�������
			{	
				KeyVaule = getch();
				
				KeyVaule |=  0x20;								//�Ѱ���ֵͳһ���Сд���㴦�� 

				if((KeyVaule=='w'&&Snake->Direct=='s') ||
					(KeyVaule=='s'&&Snake->Direct=='w')||
					(KeyVaule=='a'&&Snake->Direct=='d')||
					(KeyVaule=='d'&&Snake->Direct=='a')||
					(KeyVaule!='w'&&KeyVaule!='s'&&KeyVaule!='a'&&KeyVaule!='d'))
				{	//��Ч����
				
				}
				
				else
				{
				
					Snake = CreatNodeByInput(Snake,KeyVaule);
					
					StepVaule=0;
					flash = 1;
				}
				
			}
			else
			{	if(StepVaule==Speed)
				{	StepVaule=0;
					
					Snake = CreatNodeByInput(Snake,Snake->Direct);
					flash = 1;
				}
			}
			if(flash)
			{
			
				if(Snake->x!=Food->x||Snake->y!=Food->y)	
				{
					DeleteLinkListEnd(Snake);
					if(NodePositionCheck(Snake->pNext,Snake)!=NULL)
					{	//�����ͷ���Լ������ط��Ľڵ�λ���غ��� 
						GameOver = 1;//ҧ���Լ�
					}
				}
				else
				{	Score++;
					ScoreStr = itoa(Score,ScoreStr,10);
					WIN32display(MapXStart+MapXSize+2,MapYStart+12,"Score:",ColorFont);
					WIN32display(MapXStart+MapXSize+2+7,MapYStart+12,ScoreStr,ColorFont);
					if(Score==50)
					{	MessageBox(NULL,"���浽��50��:���� http://pan.baidu.com/s/1dF9zfe5","��ϲ��",MB_OK);
						KeyVaule = 'p';
						}	
					//ʳ�ﱻ���ˣ����´���ʳ�� 
					do
					{	
						//free(Food);
						//Food = NULL;
						
						//Food = LinkListOperator.CreatNode();
						//strcpy(Food->Icon,"��");
						VoiceOfEatFood();
						Food->Color = rand()%7 + 0x08;			//�����ɫ 
						Food->x = rand()%(MapXSize-1)+MapXStart+1;
						Food->y = rand()%(MapYSize-1)+MapYStart+1;
					}
					while(NodePositionCheck(Snake,Food));
				
					DisplayAPoint(Food);
					
				}
			}
			flash = 0;
			
			if(Snake->x >= MapXStart +MapXSize  ||Snake->x <= MapXStart ||Snake->y>= MapYStart +MapYSize|| Snake->y<= MapYStart)
			{	GameOver=2;//ײǽ 
				
			}
			
	}
	switch(GameOver)
	{	
		case 1:WIN32display(MapXStart+MapXSize+5,MapYStart,"��ҧ�����Լ�",ColorFont);VoiceOfFail();break;
		case 2:WIN32display(MapXStart+MapXSize+5,MapYStart,"��ײ����ǽ",ColorFont);VoiceOfFail();break;
	}
	getchar();
	DestroyLinkList(Snake);
	DestroyANode(Food);
	Score = 0; 
	
}
