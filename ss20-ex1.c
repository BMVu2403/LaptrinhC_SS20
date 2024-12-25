#include <stdio.h>

struct book {
    int id;
    char name[50];
    char author[50];
    float price;
};

void nhapThongTinsach(struct book *Book);
void hienThiThongTinSach(struct book Book[], int n);
void themSach(struct book Book[], int *n, int position);
void xoaSach(struct book Book[], int *n, int id);
void capNhatThongTinSach(struct book Book[], int n, int id);
void sapXepSachTheoGia(struct book Book[], int n, int tang);
void timKiemSachTheoTen(struct book Book[], int n, char name[]);
void timSachTheoTen(struct book Book[], int n, char name[]);

int main() {
    struct book Book[50];
    int choose;
    int n = 0;

    do {
        printf("menu\n");
        printf("1. nhap so luong va thong tin sach. \n");
        printf("2. hien thi thong tin sach. \n");
        printf("3. them sach vao vi tri. \n");
        printf("4. xoa sach theo ma sach. \n");
        printf("5. cap nhat thong tin sach theo ma. \n");
        printf("6. sap xep sach theo gia (tang/giam)\n");
        printf("7. tim kiem sach theo ten sach. \n");
        printf("8. tim sach theo ten sach. \n");
        printf("lua chon cua ban: ");
        scanf("%d", &choose);
        switch (choose) {
            case 1: {
                printf("nhap so luong phan tu sach: ");
                scanf("%d", &n);
                for (int i = 0; i < n; i++) {
                    printf("nhap thong tin quyen sach thu %d\n", i + 1);
                    nhapThongTinsach(&Book[i]);
                }
                break;
            }
            case 2: {
                hienThiThongTinSach(Book, n);
                break;
            }
            case 3: {
                printf("nhap vi tri can them sach: ");
                int position;
                scanf("%d", &position);
                if (position > n || position < 1) {
                    printf("vi tri khong hop le!\n");
                } else {
                    themSach(Book, &n, position - 1);
                }
                break;
            }
            case 4: {
                printf("nhap ma sach can xoa: ");
                int id;
                scanf("%d", &id);
                xoaSach(Book, &n, id);
                break;
            }
            case 5: {
                printf("nhap ma sach can cap nhat: ");
                int id;
                scanf("%d", &id);
                capNhatThongTinSach(Book, n, id);
                break;
            }
            case 6: {
                printf("sap xep theo gia tang (1) hay giam (0): ");
                int tang;
                scanf("%d", &tang);
                sapXepSachTheoGia(Book, n, tang);
                break;
            }
            case 7: {
                printf("nhap ten sach can tim: ");
                char name[50];
                fflush(stdin);
                fgets(name, sizeof(name), stdin);
                timKiemSachTheoTen(Book, n, name);
                break;
            }
            case 8: {
                printf("nhap ten sach can tim: ");
                char name[50];
                fflush(stdin);
                fgets(name, sizeof(name), stdin);
                timSachTheoTen(Book, n, name);
                break;
            }
        }
    } while (choose != 8);

    return 0;
}

void nhapThongTinsach(struct book *Book) {
    printf("nhap ma sach: ");
    scanf("%d", &Book->id);
    fflush(stdin);
    printf("nhap ten sach: ");
    fgets(Book->name, sizeof(Book->name), stdin);
    Book->name[strcspn(Book->name, "\n")] = 0;  
    printf("nhap ten tac gia: ");
    fgets(Book->author, sizeof(Book->author), stdin);
    Book->author[strcspn(Book->author, "\n")] = 0; 
    printf("nhap gia sach: ");
    scanf("%f", &Book->price);
    fflush(stdin);
}

void hienThiThongTinSach(struct book Book[], int n) {
    if (n == 0) {
        printf("danh sach rong!!!\n");
    } else {
        for (int i = 0; i < n; i++) {
            printf("quyen sach thu %d\n", i + 1);
            printf("ma sach: %d\n", Book[i].id);
            printf("ten sach: %s\n", Book[i].name);
            printf("tac gia: %s\n", Book[i].author);
            printf("gia sach: %.2f\n", Book[i].price);
        }
    }
}

void themSach(struct book Book[], int *n, int position) {
    if (*n >= 50) {
        printf("khong the them sach, danh sach da day!\n");
        return;
    }
    for (int i = *n; i > position; i--) {
        Book[i] = Book[i - 1];
    }
    nhapThongTinsach(&Book[position]);
    (*n)++;
}

void xoaSach(struct book Book[], int *n, int id) {
    int index = -1;
    for (int i = 0; i < *n; i++) {
        if (Book[i].id == id) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        printf("ma sach khong ton tai.\n");
        return;
    }
    for (int i = index; i < *n - 1; i++) {
        Book[i] = Book[i + 1];
    }
    (*n)--;
}

void capNhatThongTinSach(struct book Book[], int n, int id) {
    int index = -1;
    for (int i = 0; i < n; i++) {
        if (Book[i].id == id) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        printf("ma sach khong ton tai.\n");
        return;
    }
    printf("nhap thong tin moi cho sach ma %d:\n", id);
    nhapThongTinsach(&Book[index]);
}

void sapXepSachTheoGia(struct book Book[], int n, int tang) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((tang && Book[i].price > Book[j].price) || (!tang && Book[i].price < Book[j].price)) {
                struct book temp = Book[i];
                Book[i] = Book[j];
                Book[j] = temp;
            }
        }
    }
    printf("danh sach sach sau khi sap xep:\n");
    hienThiThongTinSach(Book, n);
}

void timKiemSachTheoTen(struct book Book[], int n, char name[]) {
    int found = 0;
    for (int i = 0; i < n; i++) {
        if (strstr(Book[i].name, name)) {
            printf("sach tim thay: %s\n", Book[i].name);
            found = 1;
        }
    }
    if (!found) {
        printf("khong tim thay sach theo ten.\n");
    }
}

void timSachTheoTen(struct book Book[], int n, char name[]) {
    int found = 0;
    for (int i = 0; i < n; i++) {
        if (strstr(Book[i].name, name)) {
            printf("sach tim thay: %s\n", Book[i].name);
            found = 1;
        }
    }
    if (!found) {
        printf("khong tim thay sach theo ten.\n");
    }
}



