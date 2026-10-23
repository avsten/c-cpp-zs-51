#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define CLIENTS 12

typedef struct {
    int id;
    int snr;
} Subscriber;

typedef struct {
    int min_snr, max_snr;
    int min_id,  max_id;
    int spread;
    double avg_snr;
    int hist[4];
    int total;
} Snapshot;

static const Subscriber subscribers[CLIENTS] = {
    { 1, -42}, { 2, -38}, { 3, -25}, { 4, -17},
    { 5, -33}, { 6, -45}, { 7, -29}, { 8, -12},
    { 9, -36}, {10, -41}, {11, -22}, {12,  30}
};

static const char *QUALITY_NAMES[4] = {
    "Плохой", "Слабый", "Нормальный", "Отличный"
};

static int bucket_of(int snr)
{
    if (snr >= 35) return 3;
    if (snr >= 20) return 2;
    if (snr >= 0)  return 1;
    return 0;
}

static const char *quality_text(int snr)
{
    return QUALITY_NAMES[bucket_of(snr)];
}

static int cmp_subscriber(const void *lhs, const void *rhs)
{
    const Subscriber *a = (const Subscriber *)lhs;
    const Subscriber *b = (const Subscriber *)rhs;
    return (a->snr > b->snr) - (a->snr < b->snr);
}

static Snapshot collect(void)
{
    Snapshot snap = {0};
    Subscriber sorted[CLIENTS];
    long long acc = 0;

    for (int i = 0; i < CLIENTS; i++) {
        sorted[i] = subscribers[i];
        snap.hist[bucket_of(subscribers[i].snr)]++;
        acc += subscribers[i].snr;
    }

    qsort(sorted, CLIENTS, sizeof(Subscriber), cmp_subscriber);

    snap.min_snr = sorted[0].snr;
    snap.max_snr = sorted[CLIENTS - 1].snr;
    snap.min_id  = sorted[0].id;
    snap.max_id  = sorted[CLIENTS - 1].id;
    snap.spread  = snap.max_snr - snap.min_snr;
    snap.avg_snr = (double)acc / CLIENTS;
    snap.total   = CLIENTS;

    return snap;
}

static int count_ge(int threshold)
{
    int n = 0;
    for (int i = 0; i < CLIENTS; i++)
        if (subscribers[i].snr >= threshold) n++;
    return n;
}

static const char *verdict(const Snapshot *s)
{
    double bad_ratio = (double)(s->hist[0] + s->hist[1]) / s->total;
    if (bad_ratio == 0.0) return "НОРМА — все каналы в порядке";
    if (bad_ratio < 0.25) return "ДОПУСТИМО — единичные сбои";
    if (bad_ratio < 0.50) return "ВНИМАНИЕ — есть проблемные клиенты";
    return "КРИТИЧНО — требуется вмешательство";
}

static void draw_hist_row(const char *name, int count, int peak, int total)
{
    const int width = 15;
    int filled  = peak > 0 ? (count * width + peak / 2) / peak : 0;
    int percent = total > 0 ? (count * 100 + total / 2) / total : 0;

    printf("  %-10s |", name);
    for (int i = 0; i < width; i++)
        putchar(i < filled ? '=' : ' ');
    printf("| %3d%%  (%2d)\n", percent, count);
}

int main(void)
{
    setlocale(LC_ALL, "Russian");

    Snapshot snap = collect();
    int best_count = count_ge(35);
    int ok_count   = count_ge(20);
    int bad_count  = CLIENTS - ok_count;

    int peak = 0;
    for (int i = 0; i < 4; i++)
        if (snap.hist[i] > peak) peak = snap.hist[i];

    printf("[Сота Wi-Fi]  опрошено клиентов: %d\n\n", CLIENTS);

    printf("  КРАЙНИЕ ЗНАЧЕНИЯ КАНАЛА\n");
    printf("    худший -> клиент #%02d   %4d дБ   [%s]\n",
        snap.min_id, snap.min_snr, quality_text(snap.min_snr));
    printf("    лучший -> клиент #%02d   %4d дБ   [%s]\n\n",
        snap.max_id, snap.max_snr, quality_text(snap.max_snr));

    printf("  СТАТИСТИКА СОТЫ\n");
    printf("    среднее SNR ..... %.2f дБ\n", snap.avg_snr);
    printf("    размах max-min .. %d дБ\n\n", snap.spread);

    printf("  ПОРОГОВЫЕ СЧЁТЧИКИ\n");
    printf("    не ниже 35 дБ ... %d\n", best_count);
    printf("    не ниже 20 дБ ... %d\n", ok_count);
    printf("    ниже 20 дБ ...... %d   <- требуют внимания\n\n", bad_count);

    printf("  ГИСТОГРАММА КАЧЕСТВА\n");
    for (int i = 3; i >= 0; i--)
        draw_hist_row(QUALITY_NAMES[i], snap.hist[i], peak, CLIENTS);
    printf("\n");

    printf("  ВЕРДИКТ: %s\n", verdict(&snap));

    return 0;
}
