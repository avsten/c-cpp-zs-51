#include <iostream>
#include <iomanip>
using namespace std;
#define N        12
#define THR_GOOD 35
#define THR_OK   20
const char *quality(int snr)
{
    if (snr >= THR_GOOD) return "Отличный";
    if (snr >= THR_OK)   return "Нормальный";
    return "Плохой";
}

int main()
{
    int snr[N] = { 42, 38, 25, 17, 33, 45, 29, 12,
                   36, 41, 22, 30 };
    int  minId = 0, maxId = 0;
    long sum = 0;
    int  cntGood = 0;
    int  cntOk   = 0;
    int  cntBad  = 0;
    for (int i = 0; i < N; i++) {
        sum += snr[i];
        if (snr[i] < snr[minId]) minId = i;
        if (snr[i] > snr[maxId]) maxId = i;
        if (snr[i] >= THR_GOOD) cntGood++;
        if (snr[i] >= THR_OK)   cntOk++;
        else                    cntBad++;
    }
    double avg = static_cast<double>(sum) / N; // среднее арифметическое (static_cast - преобразование в double переменной sum)
    int spread = snr[maxId] - snr[minId]; // разброс
    // ---------- Вывод отчёта ----------
    cout << "===== Отчёт по соте Wi-Fi (N=" << N << ") =====" << endl;
    cout << "Минимальный SNR : " << snr[minId] << " дБ (клиент "
         << std::setfill('0') << std::setw(2) << minId << std::setfill(' ')
         << ") — " << quality(snr[minId]) << endl;
    cout << "Максимальный SNR: " << snr[maxId] << " дБ (клиент "
         << std::setfill('0') << std::setw(2) << maxId << std::setfill(' ')
         << ") — " << quality(snr[maxId]) << endl;
    cout << "Средний SNR     : " << std::fixed << std::setprecision(2)
         << avg << " дБ" << endl;
    cout << "--------------------------------------" << endl;
    cout << "Клиентов с SNR >= " << THR_GOOD << " дБ : " << cntGood << endl;
    cout << "Клиентов с SNR >= " << THR_OK   << " дБ : " << cntOk   << endl;
    cout << "Клиентов с SNR <  " << THR_OK   << " дБ : " << cntBad;
    if (cntBad > 0)
        cout << "  <-- требуют внимания";
    cout << endl;
    cout << "--------------------------------------" << endl;
    cout << "Разброс (max-min) : " << spread << " дБ" << endl;
    cout << "Оценка соты: ";
    if (cntBad == 0)
        cout << "хорошая, проблемных клиентов нет";
    else if (cntBad > N / 2)
        cout << "плохая, большинство клиентов с низким SNR";
    else
        cout << "рабочая, но есть проблемные клиенты";
    cout << endl;
    return 0;
}