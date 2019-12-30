#include <stdio.h>
#include <stdlib.h>
int main(void)
{
	int hm, lm, i, j;
	int ** x;
	printf("行 列\n");
	scanf("%d %d", &hm, &lm);
	x = (int **)malloc(hm*sizeof(int));
	for(i = 0; i < hm; i++)
	{
		x[i] = (int *)malloc(lm *sizeof(int));
	}
	for( j= 0; j < hm; j++){
		for(i = 0; i < lm; i++){
			x[j][i] = 1;
		}		
	}	
	for ( j = 0; j < hm; j++) {
		for (i = 0; i < lm; i++) {
			printf("%d",x[j][i]);
		}
		printf("\n");
	}
	free(x);
	return 0;
}	
