#include <stdio.h>


struct Test1
{               //�������      ƫ�Ƶ�ַ        ��С
    char c1;    //1             0            1
    short s;    //2             2            2
    char c2;    //1             4            1
    int i ;     //4             8            4
};



struct Test2
{               //�������      ƫ�Ƶ�ַ        ��С
    char c1;    //1            0             1
    char c2;    //1            1             1
    short s;    //2            2             2
    int   i;    //4            4             4
};


int main()
{
		printf("sizeof(struct Test1) = %d\n", sizeof(struct Test1));
		printf("sizeof(struct Test2) = %d\n", sizeof(struct Test2));

		return 0;
}