/*********************************************************

描述:这是一个C语言版本的、基于控制台的贪吃蛇游戏
在Windows7操作系统
用Visual C++ 6.0或者Dev-C++ 5.9.2 编译都可以通过
**********************************************************/

#include<string.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include<conio.h>
#include"LinkList.h"
#include"Point.h"
#include"voice.h"

char  GameOver	=	0;		//失败原因记录 1:咬到自己 2:撞墙 
/**********************************************************
功能:判断质点的位置是否已经与链表有位置上的重合【 x 和 y 】 
描述: 返回被重合的节点地址，NULL表示没有节点被重合

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
功能:依据输入信息插入一颗质点,并把这个质点充当头节点,并把新
的头节点地址返回 
描述: 

***********************************************************/
Node* CreatNodeByInput(Node* ListHead,char Command)
{   	
	Node* Body = NULL;


	Body = CreatNode();
	Body->pNext = ListHead;
	ListHead->pPre = Body;
	
	Body->x = ListHead->x;
	Body->y = ListHead->y;
	strcpy(Body->Icon,"■");
	strcpy(ListHead->Icon,"●"); 
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
功能:删除链表的最后一个节点 
描述: 

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
	{//如果这个被舍弃的蛇尾的节点位置和此时蛇头的位置重合 ，那就不用再去故意显示蛇尾了，因为自然被蛇头覆盖 
	}
	else
	{
		strcpy(View->Icon,"　");
		DisplayAPoint(View);
	}
	
	free(View);
}


/****************************主函数************************/ 
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
	//显示界面
	{	
		WIN32display(MapXStart+MapXSize+2,MapYStart+3,"C语言:贪吃蛇游戏",ColorFont);
		WIN32display(MapXStart+MapXSize+2,MapYStart+4,"编译环境：WINDOWS_7 VC6.0或者DEVC++",ColorFont);
		WIN32display(MapXStart+MapXSize+2,MapYStart+5,"W:上",ColorFont);
		WIN32display(MapXStart+MapXSize+2,MapYStart+6,"S:下",ColorFont);
		WIN32display(MapXStart+MapXSize+2,MapYStart+7,"A:左",ColorFont);
		WIN32display(MapXStart+MapXSize+2,MapYStart+8,"D:右",ColorFont);
		WIN32display(MapXStart+MapXSize+2,MapYStart+9,"注意:在英文状态下输入",ColorFont);
		WIN32display(MapXStart+MapXSize+2,MapYStart+10,"才可以达到控制效果",ColorFont);
		WIN32display(MapXStart+MapXSize+2,MapYStart+13,"游戏已经暂停，请输入p开始游戏",ColorFont);
		WIN32display(MapXStart+MapXSize+2,MapYStart+15,"玩到了50分就自动显示源码链接",ColorFont);
	}	
	
	//MessageBox(NULL,"玩到50分给源码","贪吃蛇",MB_OK);
	ScoreStr = (char *)malloc(sizeof(char)*100);
	ScoreStr = itoa(Score,ScoreStr,10);
	HideCursor();
	srand((unsigned)time(NULL));
	//绘制墙壁 
	for(i=MapXStart;i<=MapXSize+MapXStart;i++)
	{	WIN32display(i,MapYStart,"※",BuildColor);
		WIN32display(i,MapYStart+MapYSize,"※",BuildColor);
	}	
	for(i=MapYStart;i<=MapYSize+MapYStart;i++)
	{
		WIN32display(MapYStart,i,"※",BuildColor);
		WIN32display(MapYStart+MapYSize,i,"※",BuildColor);
	}
	//建立初步的蛇头和第一个食物 
	Snake = LinkListOperator.CreatNode();
	
	strcpy(Snake->Icon,"■");
	Snake->x = 10;
	Snake->y = 10;
	Snake->Direct = 'w';
	Snake = CreatNodeByInput(Snake,'w');
	Snake = CreatNodeByInput(Snake,'w');
	DisplayAPointList(Snake); 
	
	Food = LinkListOperator.CreatNode();
	strcpy(Food->Icon,"★");
	Food->x = rand()%(MapXSize-1)+MapXStart+1;
	Food->y = rand()%(MapYSize-1)+MapYStart+1;
	DisplayAPoint(Food);
	//初始化计分板 
	WIN32display(MapXStart+MapXSize+2,MapYStart+12,"Score:",ColorFont);
	WIN32display(MapXStart+MapXSize+2+7,MapYStart+12,ScoreStr,ColorFont);
	//正式开始游戏 
	 while(!GameOver)
	 {	
			if(KeyVaule=='p')							//Pause暂停按键
				{	
					VoiceOfPause();
					WIN32display(MapXStart+MapXSize+2,MapYStart+13,"游戏已经暂停，请输入p开始游戏",ColorFont);
					while(1)
					{
						KeyVaule = getch();
						KeyVaule |=  0x20;
						if(KeyVaule=='p')
						{	VoiceOfPause();
							WIN32display(MapXStart+MapXSize+2,MapYStart+13,"正在游戏...按下p键可以暂停游戏",ColorFont);
							KeyVaule=0;
							break;
						}
					}
				}
					
		
	 		StepVaule++;
	 		
	 		if(StepVaule>Speed)
	 			StepVaule=0;
	 	
			if(kbhit())											//如果有按键按下
			{	
				KeyVaule = getch();
				
				KeyVaule |=  0x20;								//把按键值统一变成小写方便处理 

				if((KeyVaule=='w'&&Snake->Direct=='s') ||
					(KeyVaule=='s'&&Snake->Direct=='w')||
					(KeyVaule=='a'&&Snake->Direct=='d')||
					(KeyVaule=='d'&&Snake->Direct=='a')||
					(KeyVaule!='w'&&KeyVaule!='s'&&KeyVaule!='a'&&KeyVaule!='d'))
				{	//无效按键
				
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
					{	//如果蛇头和自己其他地方的节点位置重合了 
						GameOver = 1;//咬到自己
					}
				}
				else
				{	Score++;
					ScoreStr = itoa(Score,ScoreStr,10);
					WIN32display(MapXStart+MapXSize+2,MapYStart+12,"Score:",ColorFont);
					WIN32display(MapXStart+MapXSize+2+7,MapYStart+12,ScoreStr,ColorFont);
					if(Score==50)
					{	MessageBox(NULL,"你玩到了50分:链接 http://pan.baidu.com/s/1dF9zfe5","恭喜你",MB_OK);
						KeyVaule = 'p';
						}	
					//食物被吃了，重新创建食物 
					do
					{	
						//free(Food);
						//Food = NULL;
						
						//Food = LinkListOperator.CreatNode();
						//strcpy(Food->Icon,"★");
						VoiceOfEatFood();
						Food->Color = rand()%7 + 0x08;			//随机彩色 
						Food->x = rand()%(MapXSize-1)+MapXStart+1;
						Food->y = rand()%(MapYSize-1)+MapYStart+1;
					}
					while(NodePositionCheck(Snake,Food));
				
					DisplayAPoint(Food);
					
				}
			}
			flash = 0;
			
			if(Snake->x >= MapXStart +MapXSize  ||Snake->x <= MapXStart ||Snake->y>= MapYStart +MapYSize|| Snake->y<= MapYStart)
			{	GameOver=2;//撞墙 
				
			}
			
	}
	switch(GameOver)
	{	
		case 1:WIN32display(MapXStart+MapXSize+5,MapYStart,"您咬到了自己",ColorFont);VoiceOfFail();break;
		case 2:WIN32display(MapXStart+MapXSize+5,MapYStart,"您撞到了墙",ColorFont);VoiceOfFail();break;
	}
	getchar();
	DestroyLinkList(Snake);
	DestroyANode(Food);
	Score = 0; 
	
}
