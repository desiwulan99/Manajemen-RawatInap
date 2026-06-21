#ifndef PASIEN_H
#define PASIEN_H
 
#include <string>
using namespace std;
 
// Struktur data dasar yang dipakai hampir semua modul lain
struct Pasien {
    int id;
    string nama;
    string asalMasuk;
    string jaminan;
    string hakKamar;
};
 
#endif
