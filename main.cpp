#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int n;
    cout << "Сколько клиентов? ";
    cin >> n;

    if (n <= 0 || n > 100) {
        cout << "Неверное количество клиентов (нужно от 1 до 100)" << endl;
        return 0;
    }

    int snr[100];
    for (int i = 0; i < n; i++) {
        cout << "SNR клиента " << i << " (дБ): ";
        cin >> snr[i];
    }

    int good, norm;
    cout << "Порог 'отличный' (например 35): ";
    cin >> good;
    cout << "Порог 'нормальный' (например 20): ";
    cin >> norm;

    int minV = snr[0], maxV = snr[0];
    int minI = 0, maxI = 0;
    int sum = 0;
    int cntGood = 0, cntNorm = 0, cntBad = 0;

    for (int i = 0; i < n; i++) {
        if (snr[i] < minV) { minV = snr[i]; minI = i; }
        if (snr[i] > maxV) { maxV = snr[i]; maxI = i; }
        sum += snr[i];

        if (snr[i] >= good) cntGood++;
        if (snr[i] >= norm) cntNorm++;
        if (snr[i] < norm)  cntBad++;
    }

    double avg = (double)sum / n;

    cout << endl;
    cout << "===== Отчёт по соте Wi-Fi (N=" << n << ") =====" << endl;

    cout << "Минимальный SNR : " << minV << " дБ (клиент "
         << setw(2) << setfill('0') << minI << setfill(' ') << ") — ";
    if (minV >= good) cout << "Отличный";
    else if (minV >= norm) cout << "Нормальный";
    else cout << "Плохой";
    cout << endl;

    cout << "Максимальный SNR: " << maxV << " дБ (клиент "
         << setw(2) << setfill('0') << maxI << setfill(' ') << ") — ";
    if (maxV >= good) cout << "Отличный";
    else if (maxV >= norm) cout << "Нормальный";
    else cout << "Плохой";
    cout << endl;

    cout << "Средний SNR     : " << fixed << setprecision(2) << avg << " дБ" << endl;
    cout << "--------------------------------------" << endl;

    cout << "Клиентов с SNR >= " << good << " дБ : " << cntGood << endl;
    cout << "Клиентов с SNR >= " << norm << " дБ : " << cntNorm << endl;
    cout << "Клиентов с SNR <  " << norm << " дБ : " << cntBad;
    if (cntBad > 0) cout << " <-- требуют внимания";
    cout << endl;
    cout << "--------------------------------------" << endl;

    cout << "Разброс (max-min) : " << maxV - minV << " дБ" << endl;

    cout << "Оценка соты: ";
    if (cntBad == 0) cout << "хорошая, проблемных клиентов нет";
    else if (cntBad <= n / 2) cout << "рабочая, но есть проблемные клиенты";
    else cout << "плохая, нужно менять расположение точки";
    cout << endl;

    return 0;
}
