#ifndef KAMAR_H
#define KAMAR_H
 
#include "Pasien.h"
#include <string>
using namespace std;
 
struct Kamar {
    string nomor;
    string tipe;
    bool terisi;
    Pasien pasien;
};
 
class KamarManager {
public:
    Kamar kamar[8];
    int frontVIP, frontK1, frontK2, frontK3;
 
    KamarManager();
    int allocateRoom(string tipe);
    void drawGUI(int startX, int startY);
};
 
#endif
