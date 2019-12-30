
#ifndef _POINT_
#define _POINT_

#include"LinkList.h"
#include<windows.h>
/**********************************************************
功能:隐藏光标
描述: 

***********************************************************/
void HideCursor()								
{
 CONSOLE_CURSOR_INFO cursor_info = {1, 0}; 
 SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
/***********************************************
功能:在指定位置显示一个字符串 color是可以指定颜色的字节 
描述:(坐标轴x,坐标轴y,要显示的字符串)
O--------------------->x
|
|
|
|
|
|
ˇ
y


************************************************/
void WIN32display(int x,int y,const char* c,char Color)				
{
	COORD pos;
	HANDLE hOutput;
	pos.X = x+x;
	pos.Y = y+1;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput , pos);
	SetConsoleTextAttribute(hOutput, Color);
	printf("%s",c);
}
/**********************************************************
功能:展示一颗质点 
描述: 

***********************************************************/
void DisplayAPoint(Node *APoint)
{
	WIN32display(APoint->x,APoint->y,APoint->Icon,APoint->Color);


}
/**********************************************************
功能:从屏幕上擦除一颗质点 
描述: 

***********************************************************/
void ErasureAPoint(Node *APoint)
{
	WIN32display(APoint->x,APoint->y,"　",APoint->Color);


}
/**********************************************************
功能:展示所有质点 
描述: 

***********************************************************/
void DisplayAPointList(Node *Point)
{
	
	Node* View = NULL;
	View = Point;
	while(View!=NULL)
	{	
		DisplayAPoint(View);
		View = View->pNext;
	}
}
/**********************************************************
功能:擦除所有质点 
描述: 

***********************************************************/
void ErasurePointList(Node *Point)
{
	
	Node* View = NULL;
	View = Point;
	while(View!=NULL)
	{	
		ErasureAPoint(View);
	}
}
/**********************************************************
功能:移动一个质点  W S A D 上下左右 
描述: 

***********************************************************/
void MoveAPoint(Node *APoint,char Command)
{
	
	ErasureAPoint(APoint);
	
	switch(Command)
	{	case 'w':
		case 'W':APoint->y -= 1;break;
		case 's':
		case 'S':APoint->y += 1;break;
		case 'a':
		case 'A':APoint->x -= 1;break;
		case 'd':
		case 'D':APoint->x += 1;break;
	}
	
	DisplayAPoint(APoint);
	
}
#endif


