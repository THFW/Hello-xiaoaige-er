/*�������ӱ�׼�����ж�ȡ�����в��ڱ�׼����д�ӡ��Щ������
**ÿ�������� �ĺ���һ���Ǹ������ݵ�һ����.
**
**�����һ����һ���б��,���������һ��������β ��
**��Щ�б�ųɶԳ��֣�˵����Ҫ��ӡ�������е��еķ�Χ��
**���磬 0 3 10 12 -1 ��ʾ��0�е���3�У���10�е���12�е����ݽ�����ӡ
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>		
#define MAX_COLS 20			/*���ܴ��������к�*/
#define MAX_INPUT 1000		/*ÿ�������е���󳤶�*/

int read_column_numbers(int columns[], int max );
void rearrange( char *output, char const *input,
	int n_columns, int const columns[] );
	
int main()
{
	int n_columns;			/*���д�����б��*/
	int columns[MAX_COLS];	/*��Ҫ���������*/
	char input[MAX_INPUT];	/*���������е�����*/
	char output[MAX_INPUT]; /*��������е�����*/
	
	/*
	**��ȡ�ô��б��
	*/
	n_columns = read_column_numbers( columns, MAX_COLS);
	
	/*
	**��ȡ������ʹ�ӡʣ���������
	*/
	while( gets( input ) != NULL ){
		printf(  "Original input : %s\n", input);
		rearrange(  output, input, n_columns, columns );
		printf("Rearranged line: %s\n", output );
	} 
	return EXIT_SUCCESS;
}	 