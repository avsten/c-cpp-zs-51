#include <stdio.h>
#include <locale.h>

#define N 12
#define SNR_EXCELLENT 35
#define SNR_GOOD      20

typedef enum { QUALITY_POOR = 0, QUALITY_WEAK, QUALITY_GOOD, QUALITY_EXCELLENT } Quality;

typedef struct {
    const char *mac;
    int snr;
} Client;

const Client clients[N] = {
    {"5C:51:88:00:00:01", -42},
    {"5C:51:88:00:00:02", -38},
    {"5C:51:88:00:00:03", -25},
    {"5C:51:88:00:00:04", -17},
    {"5C:51:88:00:00:05", -33},
    {"5C:51:88:00:00:06", -45},
    {"5C:51:88:00:00:07", -29},
    {"5C:51:88:00:00:08", -12},
    {"5C:51:88:00:00:09", -36},
    {"5C:51:88:00:00:10", -41},
    {"5C:51:88:00:00:11", -22},
    {"5C:51:88:00:00:12",  30}
};

static Quality classify(int snr)
{
    if (snr >= SNR_EXCELLENT) return QUALITY_EXCELLENT;
    if (snr >= SNR_GOOD)      return QUALITY_GOOD;
    if (snr >= 0)             return QUALITY_WEAK;
    return QUALITY_POOR;
}

static const char *quality_name(Quality q)
{
    switch (q) {
        case QUALITY_EXCELLENT: return "Отличный";
        case QUALITY_GOOD:      return "Хороший";
        case QUALITY_WEAK:      return "Слабый";
        default:                return "Плохой";
    }
}

static void find_extremes(int *i_min, int *i_max)
{
    *i_min = *i_max = 0;
    for (int i = 1; i < N; i++) {
        if (clients[i].snr < clients[*i_min].snr) *i_min = i;
        if (clients[i].snr > clients[*i_max].snr) *i_max = i;
    }
}

static int count_ge(int threshold)
{
    int c = 0;
    for (int i = 0; i < N; i++)
        if (clients[i].snr >= threshold) c++;
    return c;
}

static const char *evaluate_cell(int bad)
{
    if (bad == 0)     return "отличная";
    if (bad <= N / 4) return "рабочая, но есть проблемные клиенты";
    if (bad <= N / 2) return "рабочая с замечаниями";
    return "требует внимания: большинство клиентов с плохим каналом";
}

int main(void)
{
    setlocale(LC_ALL, "Russian");

    int i_min, i_max;
    find_extremes(&i_min, &i_max);

    int total = 0;
    for (int i = 0; i < N; i++) total += clients[i].snr;
    double avg = (double)total / N;

    int excellent = count_ge(SNR_EXCELLENT);
    int good      = count_ge(SNR_GOOD);
    int bad       = N - good;
    int spread    = clients[i_max].snr - clients[i_min].snr;

    printf("======== Отчёт по соте Wi-Fi (N=%d) ========\n\n", N);
    printf("Минимальный SNR : %d дБ (клиент %s) — %s\n",
        clients[i_min].snr, clients[i_min].mac,
        quality_name(classify(clients[i_min].snr)));
    printf("Максимальный SNR: %d дБ (клиент %s) — %s\n",
        clients[i_max].snr, clients[i_max].mac,
        quality_name(classify(clients[i_max].snr)));
    printf("Средний SNR : %.2f дБ\n\n", avg);

    printf("Клиентов с SNR >= %d дБ : %d\n", SNR_EXCELLENT, excellent);
    printf("Клиентов с SNR >= %d дБ : %d\n", SNR_GOOD, good);
    printf("Клиентов с SNR <  %d дБ : %d (плохой канал)\n\n", SNR_GOOD, bad);

    printf("Разброс (max-min) : %d дБ\n\n", spread);
    printf("Оценка соты: %s\n", evaluate_cell(bad));

    return 0;
}
