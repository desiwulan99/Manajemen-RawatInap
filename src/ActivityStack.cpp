#include "ActivityStack.h"          // Header class ActivityStack
#include "raylib.h"                 // Library grafis Raylib
#include "AppFont.h"                // Font global aplikasi

ActivityStack::ActivityStack() {    // Konstruktor stack
    top = NULL;                     // Inisialisasi stack kosong
}

// Menambahkan aktivitas baru ke stack (LIFO)
void ActivityStack::push(string s) {
    NodeStack* n = new NodeStack;
    n->aktivitas  = s;
    n->next       = top;
    top           = n;
}

// Menampilkan isi stack aktivitas ke GUI dari atas ke bawah (dengan batas tampilan)
void ActivityStack::drawGUI(int x, int y) {
    NodeStack* cur = top;
    int offsetY    = 0;

    if (cur == NULL) {
         // Jika stack kosong, tampilkan pesan default
        DrawTextEx(gFont, "Belum ada aktivitas.", {(float)x, (float)y}, 12, 1, GRAY);
    }

    while (cur != NULL && offsetY < 250) {
        // Menampilkan setiap aktivitas dalam stack ke layar
        DrawTextEx(gFont, ("- " + cur->aktivitas).c_str(), {(float)x, (float)(y + offsetY)}, 12, 1, DARKGRAY);
        
        cur     = cur->next;
        offsetY = offsetY + 18;
    }
}