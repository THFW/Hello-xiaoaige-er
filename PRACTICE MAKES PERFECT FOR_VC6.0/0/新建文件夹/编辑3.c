#include <stdio.h>


struct Test1
{               //对齐参数      偏移地址        大小
    char c1;    //1             0            1
    short s;    //2             2            2
    char c2;    //1             4            1
    int i ;     //4             8            4
};



struct Test2
{               //对齐参数      偏移地址        大小
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