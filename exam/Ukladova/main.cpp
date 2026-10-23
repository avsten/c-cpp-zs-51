#include <stdio.h>
#include <locale.h>

#define N 12
#define QUALITY_GOOD 35
#define QUALITY_OK   20

const int snr[N] = { -42, -38, -25, -17, -33, -45, -29, -12, -36, -41, -22, 30 };

const char* quality_label(int value)
{
    if (value >= QUALITY_GOOD)
        return "Отличный";
    if (value >= QUALITY_OK)
        return "Нормальный";
    if (value >= 0)
        return "Слабый";
    return "Плохой";
}

int main()
{
    setlocale(LC_ALL, "ru");
    int imin = 0;          
    int imax = 0;         
    int count_good = 0;     
    int count_ok = 0;       
    int count_bad = 0;     
    double sum = 0.0;

    for (int i = 0; i < N; i++) 
    {
        sum += snr[i];
        if (snr[i] < snr[imin]) 
            imin = i;
        if (snr[i] > snr[imax]) 
            imax = i;
        if (snr[i] >= QUALITY_GOOD)
            count_good++;
        if (snr[i] >= QUALITY_OK)
            count_ok++;
        else
            count_bad++;
    }
    double avg = sum / N;
    int spread = snr[imax] - snr[imin];

    const char* cell_result;
    if (count_bad == 0 && avg >= QUALITY_GOOD)
        cell_result = "отличная";
    else if (count_bad == 0)
        cell_result = "рабочая, проблемных клиентов нет";
    else if (count_bad <= 3)
        cell_result = "рабочая, но есть проблемные клиенты";
    else
        cell_result = "требует внимания: много проблемных клиентов";

    printf("======== Отчёт по соте Wi-Fi (N=%d) ========\n\n", N);
    printf("Минимальный SNR : %d дБ (клиент %02d) — %s\n",
        snr[imin], imin, quality_label(snr[imin]));
    printf("Максимальный SNR: %d дБ (клиент %02d) — %s\n",
        snr[imax], imax, quality_label(snr[imax]));
    printf("Средний SNR : %.2f дБ\n\n", avg);
    printf("Клиентов с SNR >= %d дБ : %d\n", QUALITY_GOOD, count_good);
    printf("Клиентов с SNR >= %d дБ : %d\n", QUALITY_OK, count_ok);
    printf("Клиентов с SNR <  %d дБ : %d\n\n", QUALITY_OK, count_bad);
    printf("Разброс (max-min) : %d дБ\n", spread);
    printf("Оценка соты: %s\n", cell_result);
}