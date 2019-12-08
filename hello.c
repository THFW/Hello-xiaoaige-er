#include<stdio.h>
#include <string.h>
#define M 100
int main()
{
    int a=0,b=0,c=0,d=0,e=0,n=0;
	char aa[M];
	char * bb="";
	b=0,c=0,d=0,e=0;
	gets(aa);
	for(a=0;a<M;a++)
	{
		if(aa[a]=='\0')
		break;	
		else
		n++;
	}
	for(a=0;a<n;a++)
	{
		if(((aa[a]>='A'&&aa[a]<='Z')||(aa[a]>='a'&&aa[a]<='z')))
			b++;
		else if(aa[a]==' ')
			c++;
		else if(aa[a]>='0'&&aa[a]<='9')
			d++;
		else
			e++;
	}

	if(strcmp(aa,bb)!=0)
	{
		printf("%d\n%d\n%d\n%d",b,c,d,e);
	}

    return 0;
}
