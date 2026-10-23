#include <stdio.h>   

#define N 12         // количество клиентов
#define GOOD 35      // порог "отличного" канала, дБ
#define OK 20        // порог "рабочего" канала, дБ

int main()
{
    
    int snr[N] = { 42, 38, 25, 17, 33, 45, 29, 12,
                   36, 41, 22, 30 };

    int minSnr = snr[0];   
    int maxSnr = snr[0];   
    int minI = 0;          
    int maxI = 0;          
    int sum = 0;           
    int cntGood = 0;       
    int cntOk = 0;         
    int cntBad = 0;        
    // Проходим по всем клиентам, i - номер текущего клиента
    for (int i = 0; i < N; i++) {
        sum = sum + snr[i];          

        if (snr[i] < minSnr) {       
            minSnr = snr[i];         
            minI = i;                
        }
        if (snr[i] > maxSnr) {       
            maxSnr = snr[i];
            maxI = i;
        }

        if (snr[i] >= GOOD) {       
            cntGood++;
        }
        if (snr[i] >= OK) {         
            cntOk++;
        } else {                     
            cntBad++;
        }
    }

    
    double avg = sum / 12.0;

   
    printf("===== Отчёт по соте Wi-Fi (N=%d) =====\n", N);

    // %02d - число из двух цифр с нулём впереди (7 -> 07)
    printf("Минимальный SNR : %d дБ (клиент %02d) — ", minSnr, minI);
    if (minSnr >= GOOD) printf("Отличный\n");
    else if (minSnr >= OK) printf("Хороший\n");
    else printf("Плохой\n");

    printf("Максимальный SNR: %d дБ (клиент %02d) — ", maxSnr, maxI);
    if (maxSnr >= GOOD) printf("Отличный\n");
    else if (maxSnr >= OK) printf("Хороший\n");
    else printf("Плохой\n");

    // %.2f - вещественное число с двумя знаками после запятой
    printf("Средний SNR     : %.2f дБ\n", avg);

    printf("--------------------------------------\n");
    printf("Клиентов с SNR >= %d дБ : %d\n", GOOD, cntGood);
    printf("Клиентов с SNR >= %d дБ : %d\n", OK, cntOk);
    printf("Клиентов с SNR <  %d дБ : %d", OK, cntBad);
    if (cntBad > 0) {
        printf(" <-- требуют внимания");
    }
    printf("\n");
    printf("--------------------------------------\n");

    printf("Разброс (max-min) : %d дБ\n", maxSnr - minSnr);

    // Итоговая оценка: смотрим, сколько плохих клиентов
    printf("Оценка соты: ");
    if (cntBad == 0) {
        printf("хорошая, проблемных клиентов нет\n");
    } else if (cntBad <= 3) {        // до 3 плохих из 12 - ещё норм
        printf("рабочая, но есть проблемные клиенты\n");
    } else {
        printf("плохая, требуется оптимизация покрытия\n");
    }

    return 0;
}