#include "Kamar.h"      // Implementasi manajemen kamar rumah sakit
#include "raylib.h"     // Library grafis Raylib
#include "AppFont.h"    // Font global aplikasi

// Konstruktor: inisialisasi data kamar awal
KamarManager::KamarManager() {
    kamar[0] = {"V01", "VIP",    false};
    kamar[1] = {"V02", "VIP",    false};
    kamar[2] = {"101", "KELAS1", false};
    kamar[3] = {"102", "KELAS1", false};
    kamar[4] = {"201", "KELAS2", false};
    kamar[5] = {"202", "KELAS2", false};
    kamar[6] = {"301", "KELAS3", false};
    kamar[7] = {"302", "KELAS3", false};

    // Pointer rotasi untuk sistem pembagian kamar tiap kelas
    frontVIP = 0; frontK1 = 2; frontK2 = 4; frontK3 = 6;
}

// Fungsi alokasi kamar berdasarkan tipe
int KamarManager::allocateRoom(string tipe) {
    int start, end, *fp;

    if      (tipe == "VIP")                      { start = 0; end = 1; fp = &frontVIP; }
    else if (tipe == "KELAS1" || tipe == "Deluxe"){ start = 2; end = 3; fp = &frontK1; }
    else if (tipe == "KELAS2")                   { start = 4; end = 5; fp = &frontK2; }
    else if (tipe == "KELAS3" || tipe == "Standar"){ start = 6; end = 7; fp = &frontK3; }
    else return -1;

    int size = end - start + 1;
    for (int i = 0; i < size; i++) {
        int idx = start + ((*fp - start + i) % size);
        if (!kamar[idx].terisi) {
            *fp = start + (((idx - start) + 1) % size);
            return idx;
        }
    }
    return -1;
}

// Menampilkan status kamar di GUI
void KamarManager::drawGUI(int startX, int startY) {
    int boxW = 125, boxH = 80, padding = 15;

    for (int i = 0; i < 8; i++) {
        int x = startX + i * (boxW + padding);
        int y = startY;

        // Warna berdasarkan status kamar
        Color bgColor     = kamar[i].terisi ? Fade(RED,   0.15f) : Fade(GREEN, 0.15f);
        Color borderColor = kamar[i].terisi ? MAROON       : DARKGREEN;

        // Background & Border Kamar
        DrawRectangle(x, y, boxW, boxH, bgColor);
        DrawRectangleLines(x, y, boxW, boxH, borderColor);

        // Menampilkan informasi kamar (nomor, tipe, status, dan nama pasien jika terisi) pada tampilan GUI
        DrawTextEx(gFont, TextFormat("Kamar %s (%s)", kamar[i].nomor.c_str(), kamar[i].tipe.c_str()),
                 {(float)(x + 8), (float)(y + 8)}, 10, 1, DARKGRAY);

        if (kamar[i].terisi) {
            DrawTextEx(gFont, "TERISI",                    {(float)(x + 8), (float)(y + 35)}, 12, 1, MAROON);
            DrawTextEx(gFont, kamar[i].pasien.nama.c_str(), {(float)(x + 8), (float)(y + 55)}, 10, 1, BLACK);
        } else {
            DrawTextEx(gFont, "KOSONG", {(float)(x + 8), (float)(y + 35)}, 12, 1, DARKGREEN);
        }
    }
}