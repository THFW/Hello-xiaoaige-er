#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
const int MAX_X=23;
const int MAX_Y=50;
const int MAX_food=50;
const int ESC=27;
const int SPACE=32;

typedef struct Lnode{
        int x;
        int y;
        struct Lnode *next;
}Lnode,*Linklist;

typedef struct{
        Linklist front;                                                      //snake.frontΪʳ�����꣬snake.front->nextΪ��β����������snake.frontΪ�׽���
        Linklist rear;                                                          //snake.rear Ϊ��ͷ
        int length;                                                                 //�ߵ���
}Queue;

Queue snake;

void gotoxy(int x,int y)                                           //������ 
{
        COORD wei;
        wei.X=y;
        wei.Y=x;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),wei);                //windows���
}

void wall()                                                            //����Χǽ 
{
        int i, j;
        for(i=0;i<=MAX_X;i++)
        {
                if(i==0||i==MAX_X)
                {
                        for(j=0;j<=MAX_Y;j++)
                        {
                                gotoxy(i,j);
                                putchar('+');
                        }
                }
                gotoxy(i,0);
                putchar('+');
                gotoxy(i,MAX_Y);
                putchar('+');
        }
}

void help_info()                                             //���������Ϣ 
{ 
        gotoxy(8,53);
        puts("��ESC���˳�,�ո����ͣ:");
        gotoxy(10,53);
        puts("��,��,��,��:w,s,a,d");
        gotoxy(12,53);
        puts("��Խ��,�ٶ�Ҳ��Խ��:");
        gotoxy(14,53);
        puts("���޷�������,��ر�");
        gotoxy(15,53);
        puts("��д��������״̬:");
}

void game_info()                                            //�����Ϸ��Ϣ 
{
        gotoxy(3,60);
        printf("��ǰ�߳���: %d",snake.length);
        gotoxy(5,60);
        printf(" ");
        gotoxy(5,60);
        printf("��ʤ������: %d",MAX_food-snake.length);
}

void enqueue(int x,int y)                                  //������� ��������
{
        Linklist p;
        p=(Linklist)malloc(sizeof(Lnode));
        p->x=x;
        p->y=y;
        snake.rear->next=p;
        snake.rear=p;
        snake.rear->next=NULL;
        snake.length++;
}

void dequeue()                                         //���г��� 
{
        Linklist p=snake.front->next, q=snake.front;
        p->x=q->x;
        p->y=q->y;
        snake.front=p;
        free(q);
        snake.length--;
}

void init_snake()                                      //��ʼ������ �����ڴ������Ͻǣ���ʼ����Ϊ3
{
        snake.rear=snake.front=(Linklist)malloc(sizeof(Lnode));
        snake.rear->next=NULL;
        for(int i=0;i<3;i++)
        {
                enqueue(1,i+1);                                          //��(1,1) (1,2) (1,3)��Ӽ�����
        }
        snake.length=3;
}

void show_food()                                         //�������ʳ�� 
{
        srand(time(NULL));
        Linklist p=snake.front->next, q=snake.front; 
        while(1)
        {
                q->x=rand()%(MAX_X-1)+1;
                q->y=rand()%(MAX_Y-1)+1;
                while(p)                                                         //��������ʳ���غϵ����ȥ��
                {
                        if(p->x==q->x&&p->y==q->y) break;
                        p=p->next;
                }
                if(!p) break;
        }
        gotoxy(q->x,q->y);
        putchar('#');                                                    //��ʳ��λ�������#��
}

void hua_snake(int i)                                     //���� ��i==1�������i==0�����ͷ
{
        Linklist p=snake.rear;
        gotoxy(p->x,p->y);
        if(i)
                putchar('*');
        else putchar('@');
}





void clear_wei()                                                         //ɾȥ��β
{
        Linklist p=snake.front->next;
        gotoxy(p->x,p->y);
        putchar(' ');
        p=p->next;
        gotoxy(p->x,p->y);
        putchar('*');
}

int flag()                                                                           //�ж��Ƿ�ײǽ��ײ�Լ� 
{
        if(snake.length>=MAX_food)
        {
                system("cls");
                gotoxy(10,20);
                puts("ȷ����û��WG����ô�ѵ���Ϸ�㶼Ӯ�ˡ���");       //����ô���������֪��ô
                Sleep(5000);
                exit(0);
        }
        Linklist p=snake.front->next, q=snake.rear;
        while(p!=q)                              //������Ҫ��⣬�ж���ͷ�������Ƿ���ײ�������ײbreak����� �����˵���䣻���û�к�������ײ����p=q, Ȼ����Ҫ�ж����Ƿ���Χǽ��ײ������ײ����������ˣ���û��ײ������һ�������ߣ�����1
        {
                if(p->x==q->x&&p->y==q->y) break;
                p=p->next;
        }
        if(p==q)
        {
                if(p->x>=1&&p->x<MAX_X&&p->y>=1&&p->y<MAX_Y) return 1;
        }
        system("cls");
        gotoxy(10,30);
        puts("���������������ˣ���");
        Sleep(5000);
        exit(0);
}

void snake_auto_move(char tmp)      //���Լ��� ��T-T�Ƚ��鷳,tmp��̰���߷���
{
        int x, y;
        do{                                       //while(!kbhit()&&flag()) kbhit()������������ڼ����ϰ�ĳ��������1�����������̷���0Ҳ���ǵ��㲻�����̶�����ǰ��һ���ǿ��еĻ���ô����ǰ��
                clear_wei();                                                  //��ǰ�ߵ�ʱ����Ҫ����βɾ��
                hua_snake(1);                                    //�ٻ������һ��
                x=snake.rear->x;
                y=snake.rear->y;
                switch(tmp)                                          //ǰ��
                {
                case 'w':x--;break;
                case 's':x++;break;
                case 'a':y--;break;
                case 'd':y++;break;
                }
                enqueue(x,y);                                             //���ߵ�һ�������µ���ͷ���������
                if(x==snake.front->x&&y==snake.front->y)         //���Ƿ�Ե�ʳ��
                {
                        game_info(); 
                        show_food();                                                  //�Ե��Ļ���Ҫ�ٳ���һ��ʳ��
                }
                else dequeue();                                  //��û�Ե�ʳ���Ϊǰ����������һ���µ���ͷ��Ϊ��֤�����Ȳ��䣬��Ҫ��β��ɾȥһ��
                hua_snake(0);                                        //���µ���ͷ��ͷ���껭һ���µ�
                int speed=-2*snake.length + 157;         //�ٶȣ��ɺ�����֪���ߵĳ���Խ��speedԽС����Sleep(speed)������Ϣʱ��Խ�̴Ӷ�ʵ������Խ������ǰ�����ٶ�Խ��
                Sleep(speed);
        }while(!kbhit()&&flag());                           //ÿѭ��һ����һ���Ӷ�ʵ���ߵĶ�̬�ƶ�
}

void snake_move()              //��ҿ��Ʒ������Ϸ���� 
{
        char c, c1=0;
        static char temp=0;
        if(!temp)                                //���ڳ�ʼ����ʱ�������ҷ���ǰ����
        {
                temp='d';
                snake_auto_move(temp); 
        }
        while(1)
        {
                c=getch();
                if(c==ESC)                                   //����ESC��ر���Ϸ
                {
                        system("cls");
                        gotoxy(10,30); 
                        puts("��Ϸ�˳��ɹ�!");
                        exit(0);
                }
                if(c1==SPACE)                         //c�ǵ�ǰ���ļ���c1��ǰһ�ΰ��ļ������c1=SPACE���ո����ͣ����ΰ��ļ�C����SPACE����Ϸ����
                {
                        if(c==SPACE)
                        {
                                c1=0;
                                gotoxy(6,20);
                                printf("            ");
                                snake_auto_move(temp);
                        }
                        continue;
                }
                if(c==SPACE)                               //���C=SPACE��C1!=SPACE����ͣ
                {
                        c1=SPACE;
                        gotoxy(6,20);
                        printf("��ͣ�С�����");
                        continue; 
                }
                if(c=='s'||c=='w'||c=='a'||c=='d')    //�����ΰ��ļ�C��ǰһ����ǰ���ķ���temp�෴���������ΰ�����Ϊ���߼�������tempǰ��
                {
                        if(c=='s'&&temp=='w'||c=='w'&&temp=='s'||c=='a'&&temp=='d'||c=='d'&&temp=='a')
                        {
                                snake_auto_move(temp);
                                continue;
                        }
                }
                break;
        }
        temp=c;                                                                //�ı䷽��
        snake_auto_move(temp);
}

int main(void)                                                    //main
{
        system("title ̰����");
        system("mode con cols=77 lines=25");
        system("color");
        system("color FC");
        help_info();
        wall();
        init_snake();
        show_food();
        
        game_info();
        while(flag()){
                snake_move();
        }
        system("pause");
        return 0;
}

/*
 ̰���������漸��������
wall()         //����Χǽ
gogoxy()    // �������꣬Ҳ���������Ǵ����Ĵ�������һ�����̰꣬�������������ƶ���ʳ��������ֶ���Ҫ�������ꡣ
enqueue()   //��ӣ�̰�������Զ��д���ģ�ÿ����ǰ��һ�������˸��µ����꣬���µ�������Ӽ�̰�����ƶ���
dequeue()  //���ӣ���û�гԵ�ʳ�������£�̰���ߵĳ����ǲ���ģ��ƶ���ʱ������ӣ���ô�����г��ӣ�ʹ�ó��Ȳ��䡣
show_food()   //ʳ����������ֵģ���ô�ÿ⺯��rand��srand���ɣ�������Ҫע�����ʳ����ܳ������ߵ������У�����������Ҫ���� 
                                                                                                                                                                       �����������
hua_snake()  //��ÿ��ǰ��һ������Ҫ���ߵ���һ���ط���ͷ����������λ����β��
clear_wei()   //����һ�������û�Ե�ʳ��Ļ�����Ҫ����βɾ��
flag()    //�ж���ײ��ǽ����ײ���Լ�������û��

 ����Ҫ������������
snake_auto_move()   //��û���������ŵ�����£�����һֱ��һ�������˶���  = = 
snake_move()   //�������������£��߻�ı䷽��
*/