#include "datatype.h"
#include <stdio.h>
#include <stdlib.h>

void showMainMenu() {
    printf("*** HE THONG QUAN LY THU VIEN ***\n");
    printf("\n");
    printf("\t CHON VAI TRO\n");
    printf("========================================\n");
    printf("[1] Quan tri vien\n");
    printf("[0] Thoat chuong trinh\n");
    printf("========================================\n");
    printf("Nhap lua chon cua ban: ");
}

void showLogin() {
    printf("*** HE THONG QUAN LY THU VIEN ***\n");
    printf("\n");
    printf("\t\t DANG NHAP\n");
    printf("==========================\n");
    printf("Email: ");
    printf("Mat khau: ");
    printf("==========================\n");
}

void printSeparator(int width) {
    for (int i = 0; i < width; i++) {
        printf("-");
    }
    printf("\n");
}

//CHUC NANG QUAN LI SACH; 
void showBookManage() {
    printf("*** HE THONG QUAN LY THU VIEN ***\n");
    printf("\n");
    printf("\t\t MENU SACH\n");
    printf("======================\n");
    printf("[1] Hien thi danh sach sach\n");
    printf("[2] Them sach\n");
    printf("[3] Sua thong tin sach (khong duoc sua ID)\n");
    printf("[4] Xoa sach\n");
    printf("[5] Tim kiem sach theo ten\n");
    printf("[6] Sap xep sach theo gia tien\n");
    printf("[0] Thoat\n");
    printf("======================\n");
    printf("Nhap lua chon cua ban: ");
}

void loadBook(Book book[], int *n) {
    FILE *file = fopen("booklibrary.bin", "rb");
    if (file == NULL) {
        *n = 0;
        return;
    }
    fread(n, sizeof(int), 1, file);
    fread(book, sizeof(Book), *n, file);
    fclose(file);
}

void saveBook(Book book[], int n) {
    FILE *file = fopen("booklibrary.bin", "wb");
    if (file == NULL) {
        printf("Khong the luu vao file.\n");
        return;
    }
    fwrite(&n, sizeof(int), 1, file);
    fwrite(book, sizeof(Book), n, file);
    fclose(file);
}

void showBook(Book book[], int n) {
    if (n == 0) {
        printf("Khong co sach trong danh sach.\n");
        return;
    }

    printf("DANH SACH SACH\n");
    printSeparator(112);
    printf("| %-10s | %-40s | %-20s | %-20s | %-5s |\n", "ID", "Ten sach", "Tac gia", "The loai", "Gia");
    printSeparator(112);

    for (int i = 0; i < n; i++) {
        printf("| %-10s | %-40s | %-20s | %-20s | %-5.2f |\n",book[i].bookID, book[i].bookName, book[i].author, book[i].category, book[i].price);
        printSeparator(112);
    }
}

void addBook(Book book[], int *n) {
    int count;
    printf("Nhap so sach ban muon them: ");
    scanf("%d", &count);
    getchar();

    for (int i = 0; i < count; i++) {
        printf("Nhap thong tin sach thu %d:\n", *n + 1);
        printf("Ma sach: ");
        fgets(book[*n].bookID, sizeof(book[*n].bookID), stdin);
        book[*n].bookID[strcspn(book[*n].bookID, "\n")] = '\0';

        printf("Ten sach: ");
        fgets(book[*n].bookName, sizeof(book[*n].bookName), stdin);
        book[*n].bookName[strcspn(book[*n].bookName, "\n")] = '\0';

        printf("Tac gia: ");
        fgets(book[*n].author, sizeof(book[*n].author), stdin);
        book[*n].author[strcspn(book[*n].author, "\n")] = '\0';

        printf("The loai: ");
        fgets(book[*n].category, sizeof(book[*n].category), stdin);
        book[*n].category[strcspn(book[*n].category, "\n")] = '\0';

        printf("Gia tien: ");
        scanf("%f", &book[*n].price);
        getchar();

        (*n)++;
    }
    printf("da them sach thanh cong\n"); 
    saveBook(book, *n);
}
void fixBook(Book book[], int n) {
    char id[20];
    printf("Nhap vao ID sach ban muon sua thong tin: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';

    int flag = -1;
    for (int i = 0; i < n; i++) {
        if (strcmp(id, book[i].bookID) == 0) {
            flag = i;
            break;
        }
    }

    if (flag == -1) {
        printf("ID khong ton tai trong danh sach.\n");
        return;
    }

    printf("Nhap thong tin moi cho sach co ID %s:\n", book[flag].bookID);

    printf("Ten sach: ");
    fgets(book[flag].bookName, sizeof(book[flag].bookName), stdin);
    book[flag].bookName[strcspn(book[flag].bookName, "\n")] = '\0';

    printf("Tac gia: ");
    fgets(book[flag].author, sizeof(book[flag].author), stdin);
    book[flag].author[strcspn(book[flag].author, "\n")] = '\0';

    printf("The loai: ");
    fgets(book[flag].category, sizeof(book[flag].category), stdin);
    book[flag].category[strcspn(book[flag].category, "\n")] = '\0';

    printf("Gia sach: ");
    scanf("%f", &book[flag].price);
    getchar();

    printf("Cap nhat thong tin thanh cong.\n");
}
void deleteBook(Book book[], int *n) {
    char id[20];
    printf("Nhap vao ID sach ma ban muon xoa: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';

    int flag = -1;
    for (int i = 0; i < *n; i++) {
        if (strcmp(book[i].bookID, id) == 0) {
            flag = i; 
            for (int j = i; j < *n - 1; j++) {
                book[j] = book[j + 1];
            }
            (*n)--;
            break;  
        }
    }

    if (flag == -1) {
        printf("ID khong ton tai trong danh sach.\n");
        return;
    }

    printf("Xoa sach thanh cong.\n");
}
void sortBook(Book book[], int n) {
    int choice;
    printf("Chon thu tu sap xep:\n");
    printf("[1] Sap xep tang dan theo gia tien\n");
    printf("[2] Sap xep giam dan theo gia tien\n");
    printf("Nhap lua chon cua ban: ");
    scanf("%d", &choice);
    getchar();

    if (choice != 1 && choice != 2) {
        printf("Lua chon khong hop le. Vui long thu lai.\n");
        return;
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            int condition = (choice == 1) ? (book[j].price > book[j + 1].price) : (book[j].price < book[j + 1].price);
            if (condition) {
                Book temp = book[j];
                book[j] = book[j + 1];
                book[j + 1] = temp;
            }
        }
    }

    printf("Danh sach sach sau khi sap xep:\n");
    showBook(book, n);
}
void searchBook(Book book[],int n){
	char name[50];
	printf("moi ban nhap vao ten sach ma ban muon tim kiem: ");
	fgets(name,sizeof(name),stdin);
	name[strcspn(name,"\n")]='\0';
	int flag=-1;
	for(int i=0;i<n;i++){
		if(strcasecmp(book[i].bookName,name)==0){
		flag=i;
		break;
	}
}
	if(flag==-1){
		printf("khong tim thay sach.\n");
		return;
	}
	printf("ma sach: %s\n",book[flag].bookID);
		printf("tac gia: %s\n",book[flag].author);
		printf("the loai: %s\n",book[flag].category);
		printf("gia tien: %2f\n",book[flag].price);
	
}

//CHUC NANG QUAN LI KHACH HANG 
void showCustomerManage() {
    printf("*** HE THONG QUAN LY THU VIEN ***\n");
    printf("\n");
    printf("\t\t MENU KHACH HANG\n");
    printf("=======================\n");
    printf("[1] Hien thi danh sach khach hang\n");
    printf("[2] Them khach hang\n");
    printf("[3] Sua thong tin khach hang\n");
    printf("[4] Khoa/Mo khoa khach hang\n");
    printf("[5] Tim kiem khach hang theo ten\n");
    printf("[6] Cho muon sach\n");
    printf("[7] Tra sach\n");
    printf("=======================\n");
    printf("Nhap lua chon cua ban: ");
}

