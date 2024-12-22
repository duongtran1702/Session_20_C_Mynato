#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
typedef struct {
	int code;
	char name[30];
	int selling_price;
	int purchase_price;
	int quantity;
	int quantity_sold;
}product;

void swap(product *a,product *b){
	product temp=*a;
	*a=*b;
	*b=temp;
}
void format_2nd(char *name){
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

void format_1st(char *name){   //space
	size_t len=strlen(name);
	int i=0;
	int j=0;
	int space_found=0;
	while(isspace(name[i])) i++;
	for(;i<len;i++){
		if(!isspace(name[i])){
			name[j++]=name[i];
			space_found=0;
		}
		else if(space_found==0){
			name[j++]=' ';
			space_found=1;
		}
	}
	if(j>0&&name[j-1]==' '){
		j-=1;
	}
	name[j]='\0';
}

void establish_shop(product **item,int *n,int *revenue){
	if(*item!=NULL){
		free(*item);
	}
	printf("Enter the number of products:");
	scanf("%d",n);
	getchar();
	if(*n<1){
		printf("Invalid number of products!\n");
		exit(1);
	}
	*item=(product*)malloc(*n*sizeof(product));
	if(*item==NULL){
		printf("Memory allocation failed !\n");
		exit(1);
	}
	printf("\n");
	for(int i=0;i<*n;i++){
		printf("Enter product %d-th:\n",i+1);
		(*item)[i].code=i+1000;
		printf("Enter name of product:");
		fgets((*item)[i].name,30,stdin);
		(*item)[i].name[strcspn((*item)[i].name,"\n")]='\0';
		format_1st((*item)[i].name);
		format_2nd((*item)[i].name);
		printf("Enter purchase price of this product:");
		scanf("%d",&(*item)[i].purchase_price);
		printf("Enter selling price of this product:");
		scanf("%d",&(*item)[i].selling_price);
		printf("Enter quantity of this product:");
		scanf("%d",&(*item)[i].quantity);
		getchar();
		printf("\n");   
	}
	printf("Assume the initial investment is fully allocated to the product.\n");
	*revenue=0;
}

void show_shop(product *item,int n){
	printf("--------SHOP--------\n");
	for(int i=0;i<n;i++){
		printf("Code product %d:\n",item[i].code);
		printf("Name product:%s\n",item[i].name);
		printf("Purchase price:%dk\n",item[i].purchase_price);
		printf("Selling price:%dk\n",item[i].selling_price);
		printf("Quantity:%d\n",item[i].quantity);
		printf("------------------------------------\n");
	}
}

int check_shop(product *item,char *name,int n){
	int flag=-1;
	for(int i=0;i<n;i++){
		if(strcmp(item[i].name,name)==0){
			flag=item[i].code;
			break;
		}
	}
	return flag;
}

void import_goods(product **item,int *n,int *revenue){
	printf("Enter the name of imported product :");
	char name[30];
	fgets(name,30,stdin);
	name[strcspn(name,"\n")]='\0';
	format_1st(name);
	format_2nd(name);
	int flag=check_shop(*item,name,*n);
	for(int i=0;i<*n;i++){
		if((*item)[i].code==flag){
			printf("The product is already in the shop.\n");
			printf("Enter quantity of product:");
			int quantity;
			scanf("%d",&quantity);
			(*item)[i].quantity+=quantity;
			*revenue-=quantity*(*item)[i].purchase_price;
		}
	}
	if(flag==-1){
		*n+=1;
		*item=(product*)realloc(*item,*n*sizeof(product));
		printf("The product is not yet in the shop.\n");
		strcpy((*item)[*n-1].name,name);
		(*item)[*n-1].code=*n+1000-1;
		printf("Enter purchase price of this product:");
		scanf("%d",&(*item)[*n-1].purchase_price);
		printf("Enter selling price of this product:");
		scanf("%d",&(*item)[*n-1].selling_price);
		printf("Enter quantity of this product:");
		scanf("%d",&(*item)[*n-1].quantity);
		*revenue-=(*item)[*n-1].quantity*(*item)[*n-1].purchase_price;
	}
	printf("Goods imported successfully.\n");
}

void update_product(product *item,int n){
	printf("Enter the code of product:",n);
	int code;
	scanf("%d",&code);
	getchar();
	int flag=0;
	for(int i=0;i<n;i++){
		if(item[i].code==code){	
			printf("Update information of product:\n");
			printf("Update name of product:");
			fgets(item[i].name,30,stdin);
			item[i].name[strcspn(item[i].name,"\n")]='\0';
			format_1st(item[i].name);
			format_2nd(item[i].name);
			printf("Enter purchase price of this product:");
			scanf("%d",&item[i].purchase_price);
			printf("Enter selling price of this product:");
			scanf("%d",&item[i].selling_price);
			printf("Enter quantity of this product:");
			scanf("%d",&item[i].quantity); 
			printf("Product information update successfully!\n");
			flag=1;
			break;
		}
	}
	if(flag==0){
		printf("This product does not exist!\n");
	}
}

void arrange_shop(product *item,int n){
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
				if(item[j].selling_price<item[temp].selling_price){
					temp=j;
				}
			}
			if(temp!=i){
				swap(&item[i],&item[temp]);
			}
		}
	}
	if(option=='b'){
		printf("Sort in descending order...\n");
		for(int i=0;i<n-1;i++){
			int temp=i;
			for(int j=i+1;j<n;j++){
				if(item[j].selling_price>item[temp].selling_price){
					temp=j;
				}
			}
			if(temp!=i){
				swap(&item[i],&item[temp]);
			}
		}
	}
	printf("Sorting the shop by selling price was successful!\n");	
}

void search_product(product *item,int n){
	printf("Enter name of product you want to find:");
	char name[30];
	fgets(name,30,stdin);
	name[strcspn(name,"\n")]='\0';
	format_1st(name);
	format_2nd(name);
	int flag=-1;
	for(int i=0;i<n;i++){
		if(strcmp(item[i].name,name)==0){
			flag=i;
		}
	}
	if(flag!=-1){
		printf("Information of product:\n");
		printf("Code of product:%d\n",item[flag].code);
		printf("Purchase price: %dk\n",item[flag].purchase_price);
		printf("Selling price: %dk\n",item[flag].selling_price);	
		printf("Quantity: %d\n",item[flag].quantity);
	}
	else {
		printf("product does not exist!\n");
	}
}

void sell_product(product *item,int n,int *revenue){
	int quantity;
	for(int i=0;i<n;i++){
		printf("%d.%s:%dk\n",item[i].code,item[i].name,item[i].selling_price);
		printf("Enter quantity you want to buy:");
		scanf("%d",&quantity);
		if(item[i].quantity==0){
			printf("This product is sold out.\n");
		}
		else if(quantity<=item[i].quantity){
			item[i].quantity_sold=quantity;
			item[i].quantity=item[i].quantity-quantity;
			printf("Sold successfully.\n");
			if(item[i].quantity==0){
				printf("This product is sold out.\n");
			}
			*revenue+=item[i].quantity_sold*item[i].selling_price;
		}
		else{
			printf("Not enough quantity to sell.\n");
		}
	}
}

void current_revenue(int revenue){
	printf("Current revenue of the shop:%dk\n",revenue);
}

void show_menu() {
    printf("\n===== Menu =====\n");
    printf("1. Build a shop\n");
    printf("2. Show product of shop\n");
    printf("3. Import goods\n");
    printf("4. Update information of product\n");
    printf("5. Arrange product by price\n");
    printf("6. Search product\n");
    printf("7. Sell products\n");
    printf("8. Current revenue\n");
    printf("9. Exit\n");
    printf("================\n");
}

int main(){
	product *item=NULL;
	int n=0;
	int first=0;
	int revenue;
	do{
		show_menu();
		int choice;
		printf("Enter your choice:");
		scanf("%d",&choice);
		getchar();
		if(choice==1){
			establish_shop(&item,&n,&revenue);
		}
		else if(choice==2){
			show_shop(item,n);
		}
		else if(choice==3){
			import_goods(&item,&n,&revenue);
		}
		else if(choice==4){
			update_product(item,n);
		}
		else if(choice==5){
			arrange_shop(item,n);
		}
		else if(choice==6){
			search_product(item,n);
		}
		else if(choice==7){
			sell_product(item,n,&revenue);
		}
		else if(choice==8){
			current_revenue(revenue);
		}
		else if(choice==9){
			printf("Exit!\n");
			free(item);
			return 0;
		}
		else {
			printf("Invalid choice !\n");
		}
	}while(1);
	return 0;
}
