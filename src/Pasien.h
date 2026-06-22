#ifndef PASIEN_H        // Guard agar file header tidak di-include berulang
#define PASIEN_H        // Header guard (sudah diproses)
 
#include <string>       // Library string
using namespace std;
 
// Struktur data dasar yang dipakai hampir semua modul lain
struct Pasien {
    int id;             // ID pasien
    string nama;        // Nama pasien
    string asalMasuk;   // Asal masuk pasien
    string jaminan;     // Jenis jaminan (BPJS/asuransi/dll)
    string hakKamar;    // Hak kamar yang didapat pasien
};
 
#endif
