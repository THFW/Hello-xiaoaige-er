#include <stdio.h>
#include <malloc.h>

#define MALLOC(type, x) (type*)malloc(sizeof(type)*x)

#define FREE(p) (free(p), p=NULL)

#define LOG(s) printf("[%s] {%s:%d} %s \n", _DATE_,_FILE_,_LINE_,s)

#define FOREACH(i, m) for(i=0; i<m; i++)
#define BEGAIN {
#define END	   }

int main()
{
	int x = 0;
	int* p = MALLOC(int, 5);
	
	LOG("Begin to run main code...");
	
	FOREACH(x, 5)
	BEGAIN
		p[x] = x;
	END
	
	FOREACH(x, 5)
	BEGIN
	
	FREE(p);
	
	LOG("End");
	
	return 0;
}