#include <stdio.h>
#include <stdlib.h>
#include<windows.h>
#include <conio.h>
#include<time.h>

#define WX 50
#define WY 23

void gotoxy(int x, int y);


typedef struct snake{
    int x;
    int y;
    int length;
    struct snake *next;
}snake, *Snake;

typedef struct food{
    int x;
    int y;
    struct food *next;
}food, *Food;

void clean(Snake head);
void test(Snake head);
int getvalue(Snake o, int n);
int getvaluey(Snake o, int n);
void changevalue(Snake n, int i, int s);
void changevaluey(Snake n, int i, int s);
void control(Snake a);
void auto_move(Snake head,char direction, Food k);
void *show_food(Snake head);
int getlength(Snake k);
void the_end(Snake head);
int f = 0;//�Ƿ���ʳ��

//������̬����,������ĩβ���һ��x��y����
void createL(Snake head, int x, int y)
{
    Snake swap, newl;
    swap = head;
    while(swap->next != NULL)
    {
        swap = swap->next;
    }

    newl = (Snake)malloc(sizeof(snake));
    if(newl == NULL )
    {
        printf("error\n");
    }
    newl->x = x;
    newl->y = y;
    newl ->length = swap ->length + 1;
    swap->next = newl;
    newl->next = NULL;
}

void* _snake()//��ʼ����
{
    int i;
    Snake head;
    head =(Snake) malloc(sizeof(snake));
    head->next = NULL;
    head->x = 8;
    head->y = 3;
    head ->length = 1;

    for(i = 0; i < 3; i++)
    {
        createL(head, 7 - i, 3);
    }
    return (head);

}


void draw_snake(Snake head)
{
    gotoxy(head->x, head->y);
    putchar('@');//�����Դ�
    head = head->next;
    for( ;head->next != NULL;head = head->next)
    {
        gotoxy(head->x, head->y);
        putchar('*');//��������
    }
    gotoxy(head->x, head->y);
    putchar('*');//����β��
}

int getlength(Snake head)
{
    Snake swap = head;
    int n = 0;
     for( ; swap->next != NULL ;swap = swap ->next)
         {
             n = swap->length;
             /** ��������ͷ n ������ĳ���
             */
         }
         return n;
}
void *show_food(Snake head)
{
    srand(time(NULL));
    Food apple;

    apple = (Food)malloc(sizeof(food));
    apple ->next = NULL;
    while(1)
    {
        apple -> x = rand() % (WX - 1) + 1;
        apple -> y = rand() % (WY - 1) + 1;
        while(head ->next != NULL)
        {
            if(head->x == apple->x || head->y == apple->y)
                break;
            head = head ->next;
        }
        break;
    }

    gotoxy(apple -> x, apple -> y);
    putchar('#');

    return (apple);
}
int getvalue(Snake swap, int n)
{
    while(n--)
    {
        swap = swap ->next;
    }
    return swap->x;
}

int getvaluey(Snake swap, int n)
{
    while(n--)
    {
        swap = swap ->next;
    }
    return swap->y;
}

void changevalue(Snake swap, int i, int n)
{
   while(n--)
   {
       swap = swap ->next;
   }
   swap ->x = i;
}
void changevaluey(Snake swap, int i, int n)
{
   while(n--)
   {
       swap = swap ->next;
   }
   swap ->y = i;
}

void auto_move(Snake head,char direction,Food apple)
{
    Snake swap;
    int x = 0, y = 0, n = 0;
    while(!kbhit())
   {

       swap = head;//��ʼ����Ҫ����


        if(head ->x == apple->x && head ->y == apple->y)
        {
            f = 0;
            n = getlength(head);
            x = getvalue(swap,n);
            y = getvaluey(swap,n);/**����Ϊɶn+ 1����,����̫����*/
            createL(head,x , y);
        }
        clean(head);//������������Ըտ�ʼ����ֻ������
        /**
         *  ���������ڶ���ֵ��ֵ��������һ��
         *  �����Ͳ����ֵ������
            ���һ������洢��ǰ�ߵĳ���
         */
         n = getlength(head);

        while(n--)
        {
            x = getvalue(swap,n);//�õ���n�������ֵ
            y = getvaluey(swap,n);
            changevalue(swap, x, n+1);//�ѵ�n�������ֵд���n+1������
            changevaluey(swap, y, n+1);
        }
        switch(direction)
        {
            case 'w': head ->y -= 1;break;
            case 'a': head ->x -= 1;break;
            case 's': head ->y += 1;break;
            case 'd': head ->x += 1;break;
        }



        Sleep(160);
        draw_snake(head);
        the_end(head);
   }
}

void control(Snake head)
{
    char c, o = 0;
    Food apple;
    while(1)
    {
        if(!f)//�ж��Ƿ���ʳ��
        {
            f = 1;
            apple = show_food(head);
        }

       c = getch();
        if(c == 'w' || c == 'a' || c == 's' || c == 'd' )
        {
            if((c == 'w' && o != 's') || (c == 'a' && o != 'd') || (c == 'd' && o != 'a') || (c == 's' && o != 'w'))
                {
                    o = c;
                    auto_move(head, c, apple);
                }

        }

    }
}
void test(Snake head)
{
    for(; head->next != NULL;head = head->next )
    {
        printf("%d,%d\n",head->x,head->y);
    }
    printf("%d,%d\n",head->x,head->y);
}
void clean(Snake head)
{
    Snake swa;
    swa = head;
    while(swa->next != NULL)
    {
        swa = swa->next;
    }
    gotoxy(swa->x, swa->y);
    putchar(' ');
}

void the_end(Snake head)
{
    Snake swap = head;
    if(getlength(head) > 50)
    {
        system("cls");
        gotoxy(10,20);
        printf("YOU WIN!!");
        Sleep(2000);
        exit(0);
    }
    while(swap ->next != NULL)
    {
        swap = swap ->next;
        if(head ->x == swap ->x && head ->y == swap->y)
        {
            system("cls");
            gotoxy(10,20);
            printf("YOU DEATH!!");
            Sleep(2000);
            exit(0);
        }

    }
    if(head->x >= WX || head->y >= WY || head->x == 0 || head->y == 0)
    {
        system("cls");
        gotoxy(10,20);
        printf("YOU DEATH!!");
        Sleep(2000);
        exit(0);
    }
}
void gotoxy(int x, int y)//������λ��
{
    COORD wei;
    wei.X = x;
    wei.Y = y;
    //Windows����3��
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), wei);
}
void wall()
{
    int x,y;

    for(x = 0; x <= WX; x++)
    {
        if(x == 0 || x == WX)
        {
            for(y =0 ;y <= WY; y++)
            {
                gotoxy(x , y);
                printf("+");
            }
        }
        gotoxy(x, 0);
        printf("+");
        gotoxy(x, WY);
        printf("+");

    }

}
int main()
{
    Snake p;//����ͷָ��p

    wall();
     p = _snake();
    draw_snake(p);
    control(p);
    system("pause");
    return 0;
}
/*���ں�Щ�ط�����д�Ĳ��ã����ԳԵ�һ����Ҫ�ٰ�һ�·�����ų�����һ����wasd��Сд�����ƶ������������ͣ��
*/