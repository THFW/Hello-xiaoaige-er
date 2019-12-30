#include <stdio.h>
#include <stdlib.h>

typedef struct Book{
	char book_name[100];
	int book_price, book_number;
	Book *next;
}Book_List;

void Create(Book_List *book, int n){
	Book_List *s = NULL, *r = NULL;
	int i = 0;

	//book = (Book_List *)malloc(sizeof(Book_List));
	r = book;
	for(; i < n; i ++){
		s = (Book_List *)malloc(sizeof(Book_List));
		printf("亲请输入书的名字, 价格, 数量: \n");
		scanf("%s%d%d", s->book_name, &s->book_price, &s->book_number);
		r->next = s;
		r = s;
	}
	r->next = NULL;
}

int main()
{
	Book_List *book, *p;
	int n = 1;

	book = (Book_List *)malloc(sizeof(Book_List));
	Create(book, n);
	p =  book->next;
	printf("%s%d%d\n",p->book_name, p->book_prince, p->book_number);
	//Display_Book(book);
	
	return 0;
}



