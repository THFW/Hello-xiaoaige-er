#include <stdio.h>

int main()
{
		int a[5] = {0};
		int b[2];
		int* p = NULL;
		
		p = a;
		
		printf("a = %p\n", a);
		printf("p = %p\n", p);
		printf("&p = %p\n", &p);
		printf("sizeof(a) = %d\n", sizeof(a));
		printf("sizeof(p) = %d\n", sizeof(p));
		
		printf("\n");
	
		p = b;
		
		printf("b = %p\n", b);
		printf("p = %p\n", p);
		printf("&p = %p\n", &p);
		printf("sizeof(a) = %d\n", sizeof(b));
		printf("sizeof(p) = %d\n", sizeof(p));
		
		b = a;
	
		return 0;
}