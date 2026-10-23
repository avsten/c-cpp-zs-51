#include <stdio.h>

#define N 12

// Функция для оценивания качества сигнала
const char* snrQuality(int snr)
{
    if (snr >= 35)
    {
        return "Отличный";
    }
    else if (snr >= 20)
    {
        return "Хороший";
    }
    else if (snr >= 15) 
    {
        return "Приемлемый";
    }
    else
    {
        return "Плохой";
    }
}

int main()
{
    // Исходный массив SNR (использую положительные значения, чтобы совпало с примером вывода)
    int snr[N] = { 42, 38, 25, 17, 33, 45, 29, 12, 36, 41, 22, 30 };

    int i;
    int minSnr = snr[0];
    int maxSnr = snr[0];
    int minIndex = 0;
    int maxIndex = 0;
    int sumSnr = 0;
    int countGood = 0;
    int countOk = 0;
    int countBad = 0;
    float avgSnr;

    // Поиск min, max, суммы и подсчет клиентов по порогам
    for (i = 0; i < N; i++)
    {
        if (snr[i] < minSnr)
        {
            minSnr = snr[i];
            minIndex = i;
        }
        if (snr[i] > maxSnr)
        {
            maxSnr = snr[i];
            maxIndex = i;
        }
        
        sumSnr = sumSnr + snr[i];

        if (snr[i] >= 35)
        {
            countGood = countGood + 1;
        }
        if (snr[i] >= 20)
        {
            countOk = countOk + 1;
        }
    }

    // Расчет среднего значения и числа проблемных клиентов
    avgSnr = (float)sumSnr / N;
    countBad = N - countOk;

    // Вывод отчета
    printf("===== Отчёт по соте Wi-Fi (N=%d) =====\n", N);
    printf("Минимальный SNR : %d дБ (клиент %02d) — %s\n", minSnr, minIndex, snrQuality(minSnr));
    printf("Максимальный SNR: %d дБ (клиент %02d) — %s\n", maxSnr, maxIndex, snrQuality(maxSnr));
    printf("Средний SNR : %.2f дБ\n", avgSnr);
    printf("------------------------------------\n");
    printf("Клиентов с SNR >= 35 дБ : %d\n", countGood);
    printf("Клиентов с SNR >= 20 дБ : %d\n", countOk);
    printf("Клиентов с SNR < 20 дБ : %d <-- требуют внимания\n", countBad);
    printf("------------------------------------\n");
    printf("Разброс (max-min) : %d дБ\n", maxSnr - minSnr);

    if (countOk == N)
    {
        printf("Оценка соты: отличная\n");
    }
    else if (countOk >= N / 2)
    {
        printf("Оценка соты: рабочая, но есть проблемные клиенты\n");
    }
    else
    {
        printf("Оценка соты: плохая, много проблемных клиентов\n");
    }

    return 0;
}
