#include <stdio.h>

#define N 12
#define TH_GOOD 20   /* порог "хорошего" канала, дБ */
#define TH_EXCL 35   /* порог "отличного" канала, дБ */

/* Значения SNR в дБ (SNR в задании положительный: 12..45 дБ) */
static const int snr[N] = { 42, 38, 25, 17, 33, 45, 29, 12,
                            36, 41, 22, 30 };

static const char *quality(int v)
{
    if (v >= TH_EXCL) return "Отличный";
    if (v >= TH_GOOD) return "Хороший";
    return "Плохой";
}

int main(void)
{
    int min_i = 0, max_i = 0;
    int cnt_excl = 0, cnt_good = 0, cnt_bad = 0;
    long sum = 0;

    for (int i = 0; i < N; i++) {
        if (snr[i] < snr[min_i]) min_i = i;
        if (snr[i] > snr[max_i]) max_i = i;
        sum += snr[i];
        if (snr[i] >= TH_EXCL) cnt_excl++;
        if (snr[i] >= TH_GOOD) cnt_good++;
        else                   cnt_bad++;
    }

    double avg = (double)sum / N;

    printf("===== Отчёт по соте Wi-Fi (N=%d) =====\n", N);
    printf("Минимальный SNR : %d дБ (клиент %02d) — %s\n",
           snr[min_i], min_i, quality(snr[min_i]));
    printf("Максимальный SNR: %d дБ (клиент %02d) — %s\n",
           snr[max_i], max_i, quality(snr[max_i]));
    printf("Средний SNR     : %.2f дБ\n", avg);
    printf("--------------------------------------\n");
    printf("Клиентов с SNR >= %d дБ : %d\n", TH_EXCL, cnt_excl);
    printf("Клиентов с SNR >= %d дБ : %d\n", TH_GOOD, cnt_good);
    printf("Клиентов с SNR <  %d дБ : %d%s\n", TH_GOOD, cnt_bad,
           cnt_bad ? " <-- требуют внимания" : "");
    printf("--------------------------------------\n");
    printf("Разброс (max-min) : %d дБ\n", snr[max_i] - snr[min_i]);

    printf("Оценка соты: ");
    if (cnt_bad == 0)
        printf("отличная, проблемных клиентов нет\n");
    else if (cnt_bad * 3 <= N)
        printf("рабочая, но есть проблемные клиенты\n");
    else
        printf("неудовлетворительная, требуется перенастройка\n");

    return 0;
}
