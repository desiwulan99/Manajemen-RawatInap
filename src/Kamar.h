#ifndef KAMAR_H     // Guard agar header tidak di-include berulang
#define KAMAR_H     // Header guard (sudah diproses)
 
#include "Pasien.h" // Struktur data pasien
#include <string>   // Library string
using namespace std;
 
// Struktur data kamar
struct Kamar {      
    string nomor;   // Nomor kamar
    string tipe;    // Tipe kamar (VIP, KELAS1, dll)
    bool terisi;    // Status kamar (true jika terisi)
    Pasien pasien;  // Data pasien yang menempati kamar
};
 
// Class untuk mengelola kamar rumah sakit
class KamarManager {
public:
    Kamar kamar[8];                 // Array kamar (total 8 kamar)
    int frontVIP, frontK1, frontK2, frontK3;
 
    KamarManager();                 // Konstruktor
    int allocateRoom(string tipe);  // Alokasi kamar sesuai tipe
    void drawGUI(int startX, int startY);
};
 
#endif
