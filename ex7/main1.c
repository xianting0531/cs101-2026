#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SETS 5
#define NUM_COUNT 7
#define MIN_NUM 1
#define MAX_NUM 69

// 產生一組 7 個不重複 (1~69) 的號碼：前 6 個升冪排序，第 7 個保留抽取順序
void generate_lotto_set(int out[NUM_COUNT]) {
    int pool[MAX_NUM];
    for (int i = 0; i < MAX_NUM; i++) {
        pool[i] = i + MIN_NUM;
    }

    // 洗牌 (Fisher-Yates shuffle) 抽出前 7 個不重複數字
    for (int i = 0; i < NUM_COUNT; i++) {
        int j = i + rand() % (MAX_NUM - i);
        int temp = pool[i];
        pool[i] = pool[j];
        pool[j] = temp;
        out[i] = pool[i];
    }

    // 對前 6 個數字做氣泡排序（由小到大）
    for (int i = 0; i < NUM_COUNT - 2; i++) {
        for (int j = 0; j < NUM_COUNT - 2 - i; j++) {
            if (out[j] > out[j + 1]) {
                int temp = out[j];
                out[j] = out[j + 1];
                out[j + 1] = temp;
            }
        }
    }
}

int main(void) {
    int n;

    printf("歡迎光臨長庚樂透彩購買機台\n");
    while (1) {
        printf("請問您要買幾組樂透彩：");
        if (scanf("%d", &n) == 1 && n >= 1 && n <= MAX_SETS) {
            break;
        }
        printf("請輸入 1 到 %d 之間的整數！\n", MAX_SETS);
        // 清除無效輸入緩衝區
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {}
    }

    srand((unsigned int)time(NULL));

    int tickets[MAX_SETS][NUM_COUNT];
    for (int i = 0; i < n; i++) {
        generate_lotto_set(tickets[i]);
    }

    FILE *fp = fopen("lotto.txt", "w");
    if (fp == NULL) {
        perror("無法開啟 lotto.txt");
        return 1;
    }

    // 取得目前系統時間並移除尾端 '\n'
    time_t now = time(NULL);
    char time_buf[64];
    strcpy(time_buf, ctime(&now));
    size_t len = strlen(time_buf);
    if (len > 0 && time_buf[len - 1] == '\n') {
        time_buf[len - 1] = '\0';
    }

    fprintf(fp, "=========== lotto649 ===========\n");
    fprintf(fp, "= %s =\n", time_buf);

    for (int i = 0; i < MAX_SETS; i++) {
        fprintf(fp, "[%d]: ", i + 1);
        if (i < n) {
            for (int k = 0; k < NUM_COUNT; k++) {
                fprintf(fp, "%02d", tickets[i][k]);
                if (k < NUM_COUNT - 1) {
                    fprintf(fp, " ");
                }
            }
        } else {
            for (int k = 0; k < NUM_COUNT; k++) {
                fprintf(fp, "--");
                if (k < NUM_COUNT - 1) {
                    fprintf(fp, " ");
                }
            }
        }
        fprintf(fp, "\n");
    }

    fprintf(fp, "=========== csie@CGU ===========\n");
    fclose(fp);

    printf("以為您購買的 %d 組樂透組合輸出至 lotto.txt\n", n);
    return 0;
}
