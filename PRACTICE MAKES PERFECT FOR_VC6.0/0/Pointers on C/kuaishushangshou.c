/*这个程序从标准输入中读取输入行并在标准输出中打印这些输入行
**每个输入行 的后面一行是该行内容的一部分.
**
**输入第一行是一串列标号,串的最后以一个负数结尾 。
**这些列标号成对出现，说明需要打印的输入行的列的范围。
**例如， 0 3 10 12 -1 表示第0列到第3列，第10列到第12列的内容将被打印
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>		
#define MAX_COLS 20			/*所能处理的最大列号*/
#define MAX_INPUT 1000		/*每个输入行的最大长度*/

int read_column_numbers(int columns[], int max );
void rearrange( char *output, char const *input,
	int n_columns, int const columns[] );
	
int main()
{
	int n_columns;			/*进行处理的列标号*/
	int columns[MAX_COLS];	/*需要处理的列数*/
	char input[MAX_INPUT];	/*容纳输入行的数组*/
	char output[MAX_INPUT]; /*容纳输出行的数组*/
	
	/*
	**读取该串列标号
	*/
	n_columns = read_column_numbers( columns, MAX_COLS);
	
	/*
	**读取、处理和打印剩余的输入行
	*/
	while( gets( input ) != NULL ){
		printf(  "Original input : %s\n", input);
		rearrange(  output, input, n_columns, columns );
		printf("Rearranged line: %s\n", output );
	} 
	return EXIT_SUCCESS;
}	 