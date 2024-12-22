#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
typedef struct Book{
	int code;
	char title[30];
	char author[30];
	int price;
}library;

void format(char *name){
	size_t len=strlen(name);
	int new_word=1;
	for(int i=0;i<len;i++){
		if(isspace(*(name+i))){
			new_word=1;
		}
		else if(new_word==1){
			*(name+i)=toupper(*(name+i));
			new_word=0;
		}
		else{
			*(name+i)=tolower(*(name+i));
		}
	}
}
void establish_library(library **book,int *n){
	free(*book);
	printf("Enter the number of books :");
	scanf("%d",n);
	if(*n<1){
		printf("Invalid number of book !\n");
		exit(1);
	}
	getchar();
	*book=(library*)malloc(*n*sizeof(library));
	if(*book==NULL){
		printf("Memory allocation failed !\n");
		exit(1);
	}
	for(int i=0;i<*n;i++){
		printf("Enter book %d-th:\n",i+1);
		(*book)[i].code=i+1000;
		printf("Enter title book :");
		fgets((*book)[i].title,30,stdin);
		(*book)[i].title[strcspn((*book)[i].title,"\n")]='\0';
		format((*book)[i].title);
		printf("Enter price book:");
		scanf("%d",&(*book)[i].price);
		getchar();
		printf("Enter author book:");
		fgets((*book)[i].author,30,stdin);
		(*book)[i].author[strcspn((*book)[i].author,"\n")]='\0';
		format((*book)[i].author);
		printf("\n");
	}
}

void show_library(library *book,int n){
	printf("--------LIBRARY--------\n");
	for(int i=0;i<n;i++){
		printf("Book %d:\n",book[i].code);
		printf("Title book: %s\n",book[i].title);
		printf("Price of book: %dvnd\n",book[i].price);
		printf("Author of book: %s\n",book[i].author);
		printf("------------------------------------\n");
	}
}

void add_book(library **book,int *n){
	*n+=1;
	*book=(library *)realloc(*book,*n*sizeof(library));
	printf("Enter the location(0-%d):",*n);
	int pos;
	scanf("%d",&pos);
	getchar();
	if(pos==0){
		pos=1;
	}
	if(pos<1||pos>*n){
		printf("Invalid location!\n");
		return;
	}
	for(int i=*n;i>=pos;i--){
		book[i]=book[i-1];
	}
	printf("New book:\n");
	(*book)[pos-1].code=*n+1000-1;
	printf("Enter title of book :");
	fgets((*book)[pos-1].title,30,stdin);
	(*book)[pos-1].title[strcspn((*book)[pos-1].title,"\n")]='\0';
	format((*book)[pos-1].title);
	printf("Enter price of book:");
	scanf("%d",&(*book)[pos-1].price);
	getchar();
	printf("Enter author book:");
	fgets((*book)[pos-1].author,30,stdin);
	(*book)[pos-1].author[strcspn((*book)[pos-1].author,"\n")]='\0';
	format((*book)[pos-1].author);
	printf("Add book successfully!\n");
}

void delete_book(library **book,int *n){
	printf("Enter the code of book:",*n);
	int code;
	scanf("%d",&code);
	getchar();
	int flag=0;
	for(int i=0;i<*n;i++){
		if((*book)[i].code==code){
			for(int j=i;j<*n-1;j++){
				(*book)[j]=(*book)[j+1];
			}
			flag=1;
			*n-=1;
			*book=(library *)realloc(*book,*n*sizeof(library));
			printf("Delete dish successfully!\n");
			break;
		}
	}
	if(flag==0){
		printf("This book does not exist!\n");
	}
}

void update_book(library *book,int n){
	printf("Enter the code of book:",n);
	int code;
	scanf("%d",&code);
	getchar();
	int flag=0;
	for(int i=0;i<n;i++){
		if(book[i].code==code){	
			printf("Update book:\n");
			printf("Update title of book :");
			fgets(book[i].title,30,stdin);
			book[i].title[strcspn(book[i].title,"\n")]='\0';
			format(book[i].title);
			printf("Enter price of book:");
			scanf("%d",&book[i].price);
			getchar();
			printf("Enter author book:");
			fgets(book[i].author,30,stdin);
			book[i].author[strcspn(book[i].author,"\n")]='\0';
			format(book[i].author);
			printf("Update book successfully!\n");
			break;
		}
	}
	if(flag==0){
		printf("This book does not exist!\n");
	}
}

void swap(library *x,library*y){
	library temp=*x;
	*x=*y;
	*y=temp;
}

void arrange_library(library *book,int n){
	printf("a. Sort ascending.\n");
	printf("b. Sort descending.\n");
	char option;
	do{
		printf("Choose a or b:");
		scanf(" %c",&option);
	}while(option!='a'&&option!='b');
	if(option=='a'){
		printf("Sort in ascending order...\n");
		for(int i=0;i<n-1;i++){
			int temp=i;
			for(int j=i+1;j<n;j++){
				if(book[j].price<book[temp].price){
					temp=j;
				}
			}
			if(temp!=i){
				swap(&book[i],&book[temp]);
			}
		}
	}
	if(option=='b'){
		printf("Sort in descending order...\n");
		for(int i=0;i<n-1;i++){
			int temp=i;
			for(int j=i+1;j<n;j++){
				if(book[j].price>book[temp].price){
					temp=j;
				}
			}
			if(temp!=i){
				swap(&book[i],&book[temp]);
			}
		}
	}
	printf("Sorting the library by price was successfully!\n");	
}

void search_book(library *book,int n){
	printf("Enter title of book :");
	char title[30];
	fgets(title,30,stdin);
	title[strcspn(title,"\n")]='\0';
	format(title);
	int flag=-1;
	for(int i=0;i<n;i++){
		if(strcmp(book[i].title,title)==0){
			flag=i;
		}
	}
	if(flag!=-1){
		printf("Information of book:\n");
		printf("Code of book:%d\n",book[flag].code);
		printf("Price of book: %dvnd\n",book[flag].price);
		printf("Author of book: %s\n",book[flag].author);
	}
	else {
		printf("Book does not exist!\n");
	}
}

void show_menu() {
    printf("\n===== Menu =====\n");
    printf("1. Build a library\n");
    printf("2. Show library\n");
    printf("3. Add book\n");
    printf("4. Delete book\n");
    printf("5. Update book\n");
    printf("6. Arrange library\n");
    printf("7. Search book\n");
    printf("8. Exit\n");
    printf("================\n");
}

int main(){
	library *book=NULL;
	int n=0;
	do{
		show_menu();
		int choice;
		printf("Enter your choice:");
		scanf("%d",&choice);
		getchar();
		if(choice==1){
			establish_library(&book,&n);
		}
		else if(choice==2){
			show_library(book,n);
		}
		else if(choice==3){
			add_book(&book,&n);
		}
		else if(choice==4){
			delete_book(&book,&n);
		}
		else if(choice==5){
			update_book(book,n);
		}
		else if(choice==6){
			arrange_library(book,n);
		}
		else if(choice==7){
			search_book(book,n);
		}
		else if(choice==8){
			printf("Exit!\n");
			free(book);
			return 0;
		}
		else {
			printf("Invalid choice !\n");
		}
	}while(1);
	return 0;
}
