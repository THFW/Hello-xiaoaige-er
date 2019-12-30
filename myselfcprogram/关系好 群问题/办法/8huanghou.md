#include <stdio.h>
int notdanger(int row, int col, int (*chess)[8]);	//函数声明要放在主函数外
void EightQueen(int row,int col,int (*chess)[8]);
int sum = 0;
int main()
{
	int chess[8][8],i,j;
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		  chess[i][j]=0;
	}
	EightQueen(0,8,chess);
	printf("一共有 %d 中方案\n",sum);
	return 0;
} 
void EightQueen(int row,int col,int (*chess)[8])
{
	int chess2[8][8],i,j;
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			chess2[i][j]=chess[i][j];
		}
	}
	if (row==8)
	{
	 printf("第 %d 种解法",sum+1);
	 for(i=0;i<8;i++)
	  {
	   for(j=0;j<8;j++)
	   {
		printf("%d",(*(*chess2+i) + j));
	   }
		printf("\n");
	  }
			printf("\n");
	   sum ++;
	}
	else
	{
	 for(j=0;j<col;j++)
	  {
	   if(notdanger(row,j,chess))
	   {
		for(i=0;i<8;i++)
		{
		 *(*(chess2+row)+i)=0;
	    }
		 *(*(chess2+row)+j)=1;
		*(*(chess2+row)+j)=1;
		EightQueen(row+1,col,chess2);
	   }
	  }
	}			
}

int notdanger (int row,int j,int (*chess)[8])
{
	int i,k,flag1=0,flag2=0,flag3=0,flag4=0,flag5=0;
	/*判断列方向*/
	for(i=0;i<8;i++)
	{
	 	if((*(*chess+i)+j)!=0)
		{
			flag1=1;
			break;
		}
	}
	/*判断左上方*/
	for(i=row,k=j;i>=0&&k>=0;i--,k--)
	{
		if((*(*chess+i)+k)!=0)
		{
			flag2=1;
			break;
		}
	}
	/*判断右上方*/
	for(i=row,k=j;i>=0&&k<8;i--,k++)
	{
	 if((*(*chess+i)+k)!=0)
	 {
	  flag3=1;
	  break;
	 }
	}

	for(i=row,k=j;i<8 && k<8;i++, k++)
	{
	 if((*(*chess+i)+k) != 0)
	  {
	   flag4 = 1;
	   break;
	  }
	}
	for(i=row,k=j;i<8 && k>=0;i++,k--)
	{
	 if((*(*chess+i)+k) != 0)
	 {
	  flag5=1;
	  break;
	 }
	}
	if(flag1||flag2||flag3||flag4||flag5)
	{
	 return 0;
	}
	else
	{
	 return 1;
	}
}


#include <stdio.h>
#include <math.h>
int main(void)
{
	int s,k,i,j,t,x,f[9],g[9]; 
	long a,y;

	s=0;
	printf(" 高斯八皇后问题的解为:	\n");
	for(a=12345678;a<=87654321;a=a+9)
	{
	 y=a;
	 k=0;

	 for(i=1;i<=8;i++)	
		f[i]=0;

	 while(y>0)
	 {
	  x=y%10;
	  f[x]=f[x]+1;
	  y=y/10;
	  k++;
	  g[k]=x;				/*分离各数字,用f数组统计*/
	 }

	for(t=0,i=1;i<=8;i++)
	  if(f[i]!=1)	t=1;	/*数字1~8出现不为一次,返回*/
	if(1==t)	continue;
	for(k=1;k<=7;k++)
	for(j=k+1;j<=8;j++)
		if(fabs(g[j]-g[k]) == j-k)		t=1;
	if(t==1) continue;
	s++;					/*输出八皇后问题的解*/
	printf("%ld ",a);
	if(s%6==0) printf("\n");
	}	
printf("\n s=%d。",s);
}
