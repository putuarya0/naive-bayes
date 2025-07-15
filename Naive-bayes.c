#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define Jumlah_fitur 10

typedef struct EmailNode {
    float fitur[Jumlah_fitur];
    int label;
    struct EmailNode* next;
} EmailNode;

int totalData = 0;
int jumlah_label_1 = 0;
int jumlah_label_0 = 0;

EmailNode *Head = NULL, *Baru, *bantu;

void tambahdata(float fitur[Jumlah_fitur], int label) {
    Baru = (struct EmailNode*) malloc(sizeof(struct EmailNode));
    if (Baru == NULL) {
        printf("Gagal alokasi memori\n");
        exit(1);
    }

    for (int i = 0; i < Jumlah_fitur; i++) {
        Baru->fitur[i] = fitur[i];
    }

    Baru->label = label;
    Baru->next = Head;
    Head = Baru;
}

void bacaCSV(const char* nama_file) {
    FILE* file = fopen(nama_file, "r");
    if (!file) {
        printf("Gagal membaca file %s\n", nama_file);
        exit(1);
    }

    char baris[512];
    float fitur[Jumlah_fitur];
    int label;
    int line_number = 0;

    while (fgets(baris, sizeof(baris), file)) {
        if (line_number++ == 0) continue; 

        char* token = strtok(baris, ",");
        int i = 0;

        while (token != NULL && i < Jumlah_fitur) {
            fitur[i++] = atof(token);
            token = strtok(NULL, ",");
        }

        if (token != NULL) {
            label = atoi(token);
            tambahdata(fitur, label);
        }
    }

    fclose(file);
}

void tampilkanData() {
    bantu = Head;

    if (Head == NULL) {
        printf("\nTidak ada data\n");
        return;
    }

    while (bantu != NULL) {
        printf("fitur : ");
        for (int i = 0; i < Jumlah_fitur; i++) {
            printf("%.2f, ", bantu->fitur[i]);
        }

        printf("| label : %d\n", bantu->label);
        bantu = bantu->next;
    }
}

void hitungPrior() {
    bantu = Head;

    if (bantu == NULL) {
        printf("\nTidak ada data.\n");
        return;
    }

    while (bantu != NULL) {
        totalData++;
        if (bantu->label == 0) {
            jumlah_label_0++;
        } else if (bantu->label == 1) {
            jumlah_label_1++;
        }
        bantu = bantu->next;
    }

    printf("\nTotal data : %d\n", totalData);
    printf("Label 0 : %d -> p(0) = %.2f\n", jumlah_label_0, (float)jumlah_label_0 / totalData);
    printf("Label 1 : %d -> p(1) = %.2f\n", jumlah_label_1, (float)jumlah_label_1 / totalData);
}

int prediksi(float fitur_uji[Jumlah_fitur]) {
    float prior_0 = (float)jumlah_label_0 / totalData;
    float prior_1 = (float)jumlah_label_1 / totalData;

    float skor_0 = prior_0;
    float skor_1 = prior_1;

    bantu = Head;
    float mean_0[Jumlah_fitur] = {0}, mean_1[Jumlah_fitur] = {0};

    int count_0 = 0, count_1 = 0;

    while (bantu != NULL) {
        if (bantu->label == 0) {
            for (int i = 0; i < Jumlah_fitur; i++) {
                mean_0[i] += bantu->fitur[i];
            }
            count_0++;
        } else {
            for (int i = 0; i < Jumlah_fitur; i++) {
                mean_1[i] += bantu->fitur[i];
            }
            count_1++;
        }
        bantu = bantu->next;
    }

    for (int i = 0; i < Jumlah_fitur; i++) {
        mean_0[i] /= count_0;
        mean_1[i] /= count_1;

        float jarak_0 = fabs(fitur_uji[i] - mean_0[i]);
        float jarak_1 = fabs(fitur_uji[i] - mean_1[i]);

        if (jarak_0 < jarak_1)
            skor_0 += 1;
        else
            skor_1 += 1;
    }

    printf("\nSkor 0: %.2f\nSkor 1: %.2f\n", skor_0, skor_1);

    return (skor_0 > skor_1) ? 0 : 1;
}

int main() {
    bacaCSV("C:\\vs_code\\Struktur data\\Project akhir\\spambase_10features.csv");

    printf("\n== Data yang dibaca ==\n");
    tampilkanData();

    hitungPrior();

    float fitur_uji[Jumlah_fitur];

    printf("\nMasukkan fitur uji (gunakan float seperti 0.00, 0.32, dst):\n");
    printf("Penjelasan fitur:\n");
    printf("Fitur[0]  : Persentase kata 'make'\n");
    printf("Fitur[1]  : Persentase kata 'address'\n");
    printf("Fitur[2]  : Persentase kata 'all'\n");
    printf("Fitur[3]  : Persentase kata '3d'\n");
    printf("Fitur[4]  : Persentase kata 'our'\n");
    printf("Fitur[5]  : Persentase kata 'over'\n");
    printf("Fitur[6]  : Persentase kata 'remove'\n");
    printf("Fitur[7]  : Persentase kata 'internet'\n");
    printf("Fitur[8]  : Persentase kata 'order'\n");
    printf("Fitur[9]  : Persentase kata 'mail'\n");

    for (int i = 0; i < Jumlah_fitur; i++) {
        printf("Fitur[%d] = ", i);
        scanf("%f", &fitur_uji[i]);
    }

    int hasil = prediksi(fitur_uji);
    printf("\nPrediksi label (0 = bukan spam, 1 = spam): %d\n", hasil);

    return 0;
}