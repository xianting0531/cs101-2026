#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOOK_COUNT 6
#define TITLE_LEN 128

typedef struct Books {
    int id;
    int price;
    char title[TITLE_LEN];
} book_t;

// 獨立函式：計算所有書籍的總價錢
int total_price(const book_t books[], int count) {
    int sum = 0;
    for (int i = 0; i < count; i++) {
        sum += books[i].price;
    }
    return sum;
}

// 獨立函式：在螢幕上輸出書籍資料
void list_books(const book_t books[], int count) {
    printf("%-4s %-8s %s\n", "Id", "Price", "Title");
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-4d %-8d %s\n", books[i].id, books[i].price, books[i].title);
    }
}

int main(void) {
    book_t books[BOOK_COUNT] = {
        {1, 1000, "All the Light We Cannot See"},
        {2, 300,  "The 38 Letters from J.D. Rockefeller to his son"},
        {3, 1000, "The Ballad of Songbirds and Snakes"},
        {4, 550,  "Killers of the Flower Moon"},
        {5, 870,  "Elon Musk"},
        {6, 1344, "Milk and Honey 12-Month 2024"}
    };

    // 1. 儲存書籍資料到二進位檔 Book.bin
    FILE *fp_write = fopen("Book.bin", "wb");
    if (fp_write == NULL) {
        perror("無法建立 Book.bin");
        return 1;
    }
    size_t written = fwrite(books, sizeof(book_t), BOOK_COUNT, fp_write);
    fclose(fp_write);

    if (written != BOOK_COUNT) {
        fprintf(stderr, "寫入 Book.bin 發生錯誤\n");
        return 1;
    }

    // 2. 從 Book.bin 讀取資料並顯示與計算總價
    FILE *fp_read = fopen("Book.bin", "rb");
    if (fp_read == NULL) {
        perror("無法開啟 Book.bin");
        return 1;
    }
    book_t loaded[BOOK_COUNT];
    size_t read_count = fread(loaded, sizeof(book_t), BOOK_COUNT, fp_read);
    fclose(fp_read);

    if (read_count != BOOK_COUNT) {
        fprintf(stderr, "讀取 Book.bin 發生錯誤\n");
        return 1;
    }

    list_books(loaded, BOOK_COUNT);
    printf("------------------------------------------------------------\n");
    printf("Total Price: %d\n", total_price(loaded, BOOK_COUNT));

    return 0;
}
