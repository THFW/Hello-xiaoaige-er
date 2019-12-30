#include <stdio.h>
#pragma pack(1)
typedef struct bb
{
	int id;			//[0]...[3]
	double weight;	//[8].......[15]原则 1
	float height;	//[16]......[19],\
	//总长要为8的整数倍,补齐[20].....[23]	原则3 
}BB;

typedef struct aa
{
	char name[2];		//[0],[1]
	int id;				//[4].....[7]	原则1
	double score;		//[8]....[15]
	short grade;		//[16],[17]
	BB b;				//[24]......[47]  原则2 
}AA; 

int main()
{
	AA a;
  	printf("sizeof(a) = %d\n",sizeof(a));
  	printf("sizeof(BB) = %d\n",sizeof(BB)); 	   

	return 0;	
} 







/*
#include<stdio.h>
  typedef struct{
  	int i;
  	double b;
  	char c;
  }A;
  
  typedef struct {
  	char c;
  	A a;
  }D;
  
  int main()
  {
  	printf("sizeof(A) = %d\n",sizeof(A));
  	printf("sizeof(D) = %d\n",sizeof(D)); 
	  
	return 0; 	
  }
  */