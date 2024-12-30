#include <stdio.h>
#include <stdlib.h>
#include "function.h" 
#include "datatype.h"

int main(int argc, char *argv[]) {
	int choice1;
	int choice; 
	int n;
	Book book[100];
	loadBook(book,&n);  
	/*do{
		showMainMenu();
		scanf("%d",&choice);
		getchar();
		switch(choice){
			
		case 1:{
		// giao dien cua menu quan ly sach */
	do{
		showBookManage();
	    scanf("%d",&choice1);
	    getchar();
		switch(choice1){
			 case 1:{
			 	showBook(book,n);
			 	 
				break;
			 }
			 case 2:{
			 	addBook(book,&n);
			 	saveBook(book,n);
				break;
			 }
			 case 3:{
			 	fixBook(book,n);
			 	saveBook(book,n);
			 	
				break;
			 }
			 case 4:{
			 	deleteBook(book,&n);
			 	saveBook(book,n);
			 	
				break;
			 }
			 case 5:{
			 	searchBook(book,n);
			 	saveBook(book,n);
			 	
				break;
			 }
			 case 6:{
			 	sortBook(book,n);
			 	saveBook(book,n);
			 	
				break;
			 }
			 case 0:{
			 printf("thoat chuong trinh thanh cong \n");  
				break;
			 }
			 default:{
			 	printf("lua chon khong hop le,vui long chon lai\n");
				break;
			 }			
			 }
}while(choice1!=0);
	return 0;
		/*break;
		} 
		case 2:{
			//dao dien cua menu quan ly khach hang; 
			
			break;
		}
		case 0:{
			break;
		} 
		default:{
			break;
		}
	}
}while(choice!=0);*/ 
}


