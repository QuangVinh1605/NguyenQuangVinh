#include "datatype.h"
#include <stdio.h>
#include <stdlib.h>

void showMainMenu() {
    printf("*** HE THONG QUAN LY THU VIEN ***\n");
    printf("\n");
    printf("\t CHON VAI TRO\n");
    printf("========================================\n");
    printf("[1] Quan Ly Sach\n");
    printf("[2] Quan Ly Khach Hang\n");
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
int isDuplicateID(Book book[],int n,char id[]){
		for(int j=0;j<n;j++){
				if(strcmp(id ,book[j].bookID)==0){
					return 1;
				} 
			}
			return 0;
}
int isDuplicateName(Book book[],int n,char name[]){
	for(int j=0;j<n;j++){
				if(strcmp(name ,book[j].bookName)==0){
					return 1;
				} 
			}
			return 0;
}
void toLowerCase(char str[]) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
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

    if (*n + count > 100) {
        printf("Khong du bo nho de them sach. Vui long thu lai voi so luong nho hon.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        printf("\nNhap thong tin sach thu %d:\n", *n + 1);

        do {
            printf("Ma sach (6 ky tu): ");
            fgets(book[*n].bookID, sizeof(book[*n].bookID), stdin);
            book[*n].bookID[strcspn(book[*n].bookID, "\n")] = '\0';

            if (strlen(book[*n].bookID) == 0) {
                printf("Ma sach khong duoc de trong. Vui long nhap lai.\n");
            } else if (strlen(book[*n].bookID) != 6) {
                printf("Ma sach phai co dung 6 ky tu. Vui long nhap lai.\n");
            } else if (isDuplicateID(book, *n, book[*n].bookID)) {
                printf("Ma sach da ton tai. Vui long nhap ma khac.\n");
            } else {
                break;
            }
        } while (1);
        do {
            printf("Ten sach: ");
            fgets(book[*n].bookName, sizeof(book[*n].bookName), stdin);
            book[*n].bookName[strcspn(book[*n].bookName, "\n")] = '\0';

            if (strlen(book[*n].bookName) == 0) {
                printf("Ten sach khong duoc de trong. Vui long nhap lai.\n");
            } else if(isDuplicateName(book,*n,book[*n].bookName)){
            	printf("ten sach da ton tai.Vui long nhap ten khac.\n");
			}else{
		
              break;
            }
        } while (1);

        do {
            printf("Tac gia: ");
            fgets(book[*n].author, sizeof(book[*n].author), stdin);
            book[*n].author[strcspn(book[*n].author, "\n")] = '\0';

            if (strlen(book[*n].author) == 0) {
                printf("Tac gia khong duoc de trong. Vui long nhap lai.\n");
            } else {
                break;
            }
        } while (1);

        do {
            printf("The loai: ");
            fgets(book[*n].category, sizeof(book[*n].category), stdin);
            book[*n].category[strcspn(book[*n].category, "\n")] = '\0';

            if (strlen(book[*n].category) == 0) {
                printf("The loai khong duoc de trong. Vui long nhap lai.\n");
            } else {
                break;
            }
        } while (1);

        printf("Gia tien: ");
        while (scanf("%f", &book[*n].price) != 1 || book[*n].price < 0) {
            getchar();
            printf("Gia tien khong hop le. Vui long nhap lai: ");
        }
        getchar();

        (*n)++;
    }

    printf("\nDa them %d sach thanh cong.\n", count);
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
     printf("thong tin sach hien tai:\n");
     printSeparator(112);
        printf("| %-10s | %-40s | %-20s | %-20s | %-5s |\n", "ID", "Ten sach", "Tac gia", "The loai", "Gia");
         printSeparator(112);
        printf("| %-10s | %-40s | %-20s | %-20s | %-5.2f |\n",book[flag].bookID, book[flag].bookName, book[flag].author, book[flag].category, book[flag].price);
        printSeparator(112);

        do {
            printf("Ten sach: ");
            fgets(book[flag].bookName, sizeof(book[flag].bookName), stdin);
            book[flag].bookName[strcspn(book[flag].bookName, "\n")] = '\0';

            if (strlen(book[flag].bookName) == 0) {
                printf("Ten sach khong duoc de trong. Vui long nhap lai.\n");
			}else{
		
              break;
            }
        } while (1);

        do {
            printf("Tac gia: ");
            fgets(book[flag].author, sizeof(book[flag].author), stdin);
            book[flag].author[strcspn(book[flag].author, "\n")] = '\0';

            if (strlen(book[flag].author) == 0) {
                printf("Tac gia khong duoc de trong. Vui long nhap lai.\n");
            } else {
                break;
            }
        } while (1);

        do {
            printf("The loai: ");
            fgets(book[flag].category, sizeof(book[flag].category), stdin);
            book[flag].category[strcspn(book[flag].category, "\n")] = '\0';

            if (strlen(book[flag].category) == 0) {
                printf("The loai khong duoc de trong. Vui long nhap lai.\n");
            } else {
                break;
            }
        } while (1);

        printf("Gia tien: ");
        while (scanf("%f", &book[flag].price) != 1 || book[flag].price < 0) {
            getchar();
            printf("Gia tien khong hop le. Vui long nhap lai: ");
        }
        getchar();
    printf("Cap nhat thong tin thanh cong.\n");
}
void deleteBook(Book book[], int *n) {
    char id[20];
    int conform;
    printf("Nhap vao ID sach ma ban muon xoa: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';
    
    int flag = -1;
    for (int i = 0; i < *n; i++) {
        if (strcmp(book[i].bookID, id) == 0) {
            flag = i;
			printf("ban co chac chan muon xoa khong: \n");
			printf("[1].co\n");
			printf("[2].khong\n");
			printf("nhap lua chon: \n");
			scanf("%d",&conform);
			getchar();
			if(conform==1){
			
            for (int j = i; j < *n - 1; j++) {
                book[j] = book[j + 1];
            }
            (*n)--;
            break;  
        }else if(conform==2){
        	printf("da thoat ra menu\n");
        	return;
		}
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

    if (choice != 1 || choice != 2) {
        printf("Lua chon khong hop le. Vui long thu lai.\n");
        return;
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if ((choice==1&&book[j].price>book[j+1].price)||(choice==2&&book[j].price<book[j+1].price)) {
                Book temp = book[j];
                book[j] = book[j + 1];
                book[j + 1] = temp;
            }
        }
    }

    printf("Danh sach sach sau khi sap xep:\n");
    showBook(book, n);
}
void searchBook(Book book[], int n) {
    char name[50], tempBookName[50], tempInput[50];
    printf("Moi ban nhap vao ten sach ma ban muon tim kiem: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';
    int found = 0;
    strcpy(tempInput, name);
    toLowerCase(tempInput);

    printf("\nKet qua tim kiem:\n");

    for (int i = 0; i < n; i++) {
        strcpy(tempBookName, book[i].bookName);
        toLowerCase(tempBookName);

    if (strstr(tempBookName, tempInput) != NULL) {
    if (!found) {
    printSeparator(112);
    printf("| %-10s | %-40s | %-20s | %-20s | %-5s |\n", "ID", "Ten sach", "Tac gia", "The loai", "Gia");
    printSeparator(112);
    found = 1;
    }
    printf("| %-10s | %-40s | %-20s | %-20s | %-5.2f |\n",
    book[i].bookID, book[i].bookName, book[i].author, book[i].category, book[i].price);
    }
    }

    if (found) {
        printSeparator(112);
    } else {
        printf("Khong tim thay sach nao phu hop voi ten '%s'.\n", name);
    }
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

