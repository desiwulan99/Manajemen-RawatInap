#include "SimpleTicker.h"
 
SimpleTicker::SimpleTicker() {
    size = 5;
    // Data 
    arr[0] = {3, "INFO: Kawasan Rumah Sakit adalah area bebas asap rokok. Terima kasih."};
    arr[1] = {1, "URGENT: Harap selalu patuhi protokol kesehatan rumah sakit."};
    arr[2] = {4, "INFO: Mari biasakan cuci tangan menggunakan hand sanitizer."};
    arr[3] = {2, "INFO: Jam besuk pasien rawat inap adalah pukul 10.00-12.00 dan 17.00-19.00 WIB."};
    arr[4] = {5, "Selamat datang di Sistem Manajemen Rawat Inap Rumah Sakit."};
 
    // BUBBLE SORT berdasarkan prioritas
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j].priority > arr[j + 1].priority) {
                TickerMsg temp = arr[j];
                arr[j]         = arr[j + 1];
                arr[j + 1]     = temp;
            }
        }
    }
}
 
string SimpleTicker::getMessage(int index) {
    return arr[index % size].text;
}
