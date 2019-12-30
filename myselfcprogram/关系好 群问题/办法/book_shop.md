#include <stdio.h>
#include <stdlib.h>

typedef struct Book
{
	char book_name[100];
	int book_price, book_number;
	Book *next;
} Book_List;

void Create(Book_List *book, int n)
{
	Book_List *s = NULL, *r = NULL;
	int i = 0;
	
    //book = (Book_List *)malloc(sizeof(Book_List));//调用create函数前，就把空间分配好
	r=book;
	for( ; i < 3; i++){
		s = (Book_List *)malloc(sizeof(Book_List));
		printf("亲请输入书的名字,价格,数量:\n");
		scanf("%s%d%d",s->book_name, &s->book_price,&s->book_number);	
	r->next = s;
	r = s;
	}
	r->next = NULL;
}

void Add_Book(Book_List **book){
		Book_List *s, *r;
		char c ;//= 'n';
		r = *book;
		while((r->next) != NULL){
			r = r->next;
		}
		while(1){
			s = (Book_List *)malloc(sizeof(Book_List));
			printf("请输入书的名字,价格,数量:\n");
			scanf("%s%d%d",s->book_name, &s->book_price,&s->book_number);
			r->next = s;
			r->next = NULL;
			printf("是否继续添加新的书籍,如果不是,请输入n/N:\n");
			scanf("%c", &c);
			if(c == 'n' || c == 'N')
				break;
		}
		return ;
}

int main()
{
	Book_List *book, *p;
	int n = 1;
	
	book = (Book_List *)malloc(sizeof(Book_List));
	Create(book, n);
	p = book->next;
	printf("%s%d%d\n",p->book_name, p->book_price, p->book_number);

	return 0;
}
//指针的长度一般来说是由系统决定的（编译器也可以修改），
//是编译器一开始就知道的长度，
//而结构体的长度 要等到程序进行编译的才知道。
