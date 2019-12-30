#include <stdio.h>

int main()
{
	int i = 0;
	int* pI;
	char* pC;
	float* pF;
	
	pI = &i;
	
	*pI = 10;
	
	printf("%p, %p, %d\n", pI, &i, i);//0xaabbcc 0xaabbcc 10
	printf("%d, %d, %p\n", sizeof(int*), sizeof(pI), &pI);//
	printf("%d, %d, %p\n", sizeof(char*), sizeof(pC), &pC);
	printf("%d, %d, %p\n", sizeof(float*), sizeof(pF), &pF);
	
	return 0;
}