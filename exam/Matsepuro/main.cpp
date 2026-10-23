#include <stdio.h>
#include <iostream>
    

int main()
    {
        int N = 12;
        int snr[N] = {-42, -38, -25, -17, -33, -45, -29, -12, -36, -41, -22, 30};
        int maxVal = snr[0], maxIdx=0;
        int minVal = snr[0], minIdx=0;
        int sum = 0;
        int a = 0;
        int b = 0;
        int c = 0;
        
        for (int i=0;i<N;++i) {
            if (snr[i] > maxVal) {maxVal = snr[i]; maxIdx=i;}
            if (snr[i] < minVal) {minVal = snr[i]; minIdx=i;}
            sum += snr[i];
        }
        
        double average = static_cast<double>(sum) / N;
        
        std::cout << "===== Отчёт по соте Wi-Fi (N=12) ====="<< "\n"; 
        std::cout << "Максимальный SNR: " << maxVal << " дБ (клиент " << maxIdx+1 <<")"<< "\n"; 
        std::cout << "Минимальный SNR: " << minVal << " дБ (клиент " << minIdx+1 <<")"<< "\n"; 
        std::cout << "Средний SNR: " << average << " дБ" << "\n";
        std::cout << "--------------------------------------" << "\n";
        
        for (int i=0;i<N;++i) {
            if (snr[i]>=35) {a++;}
            if (snr[i]>=20) {b++;}
            if (snr[i]<20) {c++;}
        }
        
        std::cout << "Клиентов с SNR >= 35: " << a << "\n";
        std::cout << "Клиентов с SNR >= 20: " << b << "\n";
        std::cout << "Клиентов с SNR < 20: " << c << "\n";
        std::cout << "--------------------------------------" << "\n";
        std::cout << "Разброс: " << maxVal-minVal << " дБ" << "\n";
        
        if (c==0)
        std::cout << "Оценка соты: " << " отличная, проблемных клиентов нет" << "\n";
        else if (c>0&&c<=3)
        std::cout << "Оценка соты: " << " рабочая, но есть проблемные клиенты" << "\n";
        else 
        std::cout << "Оценка соты: " << " плохая, есть проблемные клиенты" << "\n";

        return 0;
    }


    