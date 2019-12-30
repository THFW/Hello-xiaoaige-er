#include <stdio.h>

#define CALL(f, p)	(printf("Call function %s\n", #f), f(p))

int square(int n)
{
		return n * n;
}

int func(int x)
{
		return x;
}

int main()
{
		int result = 0;
		
		result = CALL(square, 4);
		
		printf("result = %d\n", result);
		
		result  = CALL(func, 10);
		
		printf("result = %d\n", result);
		
		return 0;
}