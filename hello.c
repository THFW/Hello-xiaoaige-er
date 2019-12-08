#include<stdio.h>
#include <string.h>
#define M 100
int main()
{
    int a=0,b=0,c=0,d=0,e=0,n=0;
	char aa[M]={'\0'};

//	while(1){
	b=0,c=0,d=0,e=0;
	for(a=0;a<M;a++)
	{
		scanf("%c",&aa[a]);
		if(aa[a]=='\n')
			break;
		else
			n++;
	}
	if(aa[0]!='\n')
	{for(a=0;a<n;a++)
	{
		if((aa[a]>='A'&&aa[a]<='Z')||(aa[a]>='a'&&aa[a]<='z'))
			b++;
		else if(aa[a]==' ')
			c++;
		else if(aa[a]>='0'&&aa[a]<='9')
			d++;
		else
			e++;
	}
	printf("%d\n%d\n%d\n%d\n%d\n",b,c,d,e,'`');
	}
	else
	{
		printf("\n");
	}
//	}
    return 0;
}
