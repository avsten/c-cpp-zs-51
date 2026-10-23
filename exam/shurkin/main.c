#include <stdio.h>

#define N 12
#define GOOD_SNR 35
#define ACCEPTABLE_SNR 20

int main(void) {
    /* Данные из задания */
    int snr[N] = {
        -42, -38, -25, -17, -33, -45,
        -29, -12, -36, -41, -22, 30
    };

    int min_index = 0;
    int max_index = 0;
    int sum = 0;
    int count_good = 0;       /* SNR >= 35 дБ */
    int count_acceptable = 0; /* SNR >= 20 дБ */
    int count_bad = 0;        /* SNR < 20 дБ */

    for (int i = 0; i < N; ++i) {
        if (snr[i] < snr[min_index]) {
            min_index = i;
        }
        if (snr[i] > snr[max_index]) {
            max_index = i;
        }

        sum += snr[i];

        if (snr[i] >= GOOD_SNR) {
            ++count_good;
        }
        if (snr[i] >= ACCEPTABLE_SNR) {
            ++count_acceptable;
        } else {
            ++count_bad;
        }
    }

    double average = (double)sum / N;
    int spread = snr[max_index] - snr[min_index];

    printf("===== Отчёт по соте Wi-Fi (N=%d) =====\n", N);
    printf("Минимальный SNR : %d дБ (клиент %02d)\n",
           snr[min_index], min_index + 1);
    printf("Максимальный SNR: %d дБ (клиент %02d)\n",
           snr[max_index], max_index + 1);
    printf("Средний SNR     : %.2f дБ\n", average);
    printf("--------------------------------------\n");
    printf("Клиентов с SNR >= %d дБ: %d\n",
           GOOD_SNR, count_good);
    printf("Клиентов с SNR >= %d дБ: %d\n",
           ACCEPTABLE_SNR, count_acceptable);
    printf("Клиентов с SNR < %d дБ : %d",
           ACCEPTABLE_SNR, count_bad);
    if (count_bad > 0) {
        printf(" <-- требуют внимания");
    }
    printf("\n");
    printf("--------------------------------------\n");
    printf("Разброс (max-min)       : %d дБ\n", spread);

    if (count_bad == 0) {
        printf("Оценка соты: хорошее качество по заданному порогу\n");
    } else if (count_bad <= 2) {
        printf("Оценка соты: рабочая, но есть проблемные клиенты\n");
    } else {
        printf("Оценка соты: есть заметные проблемы с качеством канала\n");
    }

    return 0;
}
