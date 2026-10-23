#include <stdio.h>
#include <windows.h>
#define N 12

int snr[N] = { 42, 38, 25, 17, 33, 45, 29, 12, 36, 41, 22, 30 };

int main() {
    SetConsoleOutputCP(65001);

    int mn = 0, mx = 0, a = 0, b = 0, c = 0, s = 0;
    for (int i = 0; i < N; i++) {
        if (snr[i] < snr[mn]) mn = i;
        if (snr[i] > snr[mx]) mx = i;
        s += snr[i];
        if (snr[i] >= 35) a++;
        if (snr[i] >= 20) b++; else c++;
    }

    printf("===== Wi-Fi cell report (N=%d) =====\n", N);
    printf("Minimum SNR : %d dB (client %02d) - %s\n",
           snr[mn], mn + 1, snr[mn] >= 35 ? "Excellent"
                         : snr[mn] >= 20 ? "Working" : "Poor");
    printf("Maximum SNR: %d dB (client %02d) - %s\n",
           snr[mx], mx + 1, snr[mx] >= 35 ? "Excellent"
                         : snr[mx] >= 20 ? "Working" : "Poor");
    printf("Average SNR     : %.2f dB\n", (float)s / N);
    printf("----------------------------------\n");
    printf("Clients with SNR >= 35 dB : %d\n", a);
    printf("Clients with SNR >= 20 dB : %d\n", b);
    printf("Clients with SNR <  20 dB : %d%s\n",
           c, c ? "  <- need attention" : "");
    printf("----------------------------------\n");
    printf("Spread (max-min) : %d dB\n", snr[mx] - snr[mn]);
    printf("Cell assessment: %s\n",
           c ? "working, but there are problem clients" : "good");
    return 0;
}
