
#ifndef _POINT_
#define _POINT_

#include"LinkList.h"
#include<windows.h>
/**********************************************************
����:���ع��
����: 

***********************************************************/
void HideCursor()								
{
 CONSOLE_CURSOR_INFO cursor_info = {1, 0}; 
 SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
/***********************************************
����:��ָ��λ����ʾһ���ַ��� color�ǿ���ָ����ɫ���ֽ� 
����:(������x,������y,Ҫ��ʾ���ַ���)
O--------------------->x
|
|
|
|
|
|
��
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
����:չʾһ���ʵ� 
����: 

***********************************************************/
void DisplayAPoint(Node *APoint)
{
	WIN32display(APoint->x,APoint->y,APoint->Icon,APoint->Color);


}
/**********************************************************
����:����Ļ�ϲ���һ���ʵ� 
����: 

***********************************************************/
void ErasureAPoint(Node *APoint)
{
	WIN32display(APoint->x,APoint->y,"��",APoint->Color);


}
/**********************************************************
����:չʾ�����ʵ� 
����: 

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
����:���������ʵ� 
����: 

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
����:�ƶ�һ���ʵ�  W S A D �������� 
����: 

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

