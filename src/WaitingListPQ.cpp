// Implementasi priority queue untuk daftar tunggu pasien rumah sakit
#include "WaitingListPQ.h" // Header priority queue waiting list
#include "raylib.h"        // Library GUI Raylib
#include "AppFont.h"       // Font global aplikasi

// Konstruktor: inisialisasi list kosong
WaitingListPQ::WaitingListPQ() {
    head = NULL;
}

// Mengecek apakah priority queue kosong
bool WaitingListPQ::empty() {
    return head == NULL;
}

// Menambahkan pasien berdasarkan prioritas
void WaitingListPQ::enqueue(Pasien p) {
    int pr     = (p.asalMasuk == "IGD") ? 1 : 2;    // IGD lebih prioritas
    NodePQ* n  = new NodePQ;
    n->data     = p;
    n->priority = pr;
    n->next     = NULL;

    if (head == NULL || pr < head->priority) {
        n->next = head;                             // Masukkan di depan jika prioritas lebih tinggi
        head    = n;
        return;
    }

    NodePQ* cur = head;
    while (cur->next != NULL && cur->next->priority <= pr) {
        cur = cur->next;                            // Cari posisi sesuai prioritas
    }
    n->next   = cur->next;
    cur->next = n;
}

// Ambil pasien sesuai tipe kamar
Pasien WaitingListPQ::dequeueSuitable(string tipe) {
    Pasien kosong = {0, "", "", "", ""};
    if (head == NULL) return kosong;

    NodePQ* cur  = head;
    NodePQ* prev = NULL;

    while (cur != NULL) {
        if (cur->data.hakKamar == tipe) {
            if (prev == NULL) head      = cur->next;
            else              prev->next = cur->next;
            Pasien p = cur->data;
            delete cur;
            return p;
        }
        prev = cur;
        cur  = cur->next;
    }
    return kosong;
}

// Hapus pasien berdasarkan ID
bool WaitingListPQ::removeByID(int id) {
    NodePQ* cur  = head;
    NodePQ* prev = NULL;

    while (cur != NULL) {
        if (cur->data.id == id) {
            if (prev == NULL) head      = cur->next;
            else              prev->next = cur->next;
            delete cur;
            return true;
        }
        prev = cur;
        cur  = cur->next;
    }
    return false;
}

// Menampilkan waiting list di GUI
void WaitingListPQ::drawGUI(int x, int y) {
    if (head == NULL) {
        DrawTextEx(gFont, "Kosong", {(float)x, (float)y}, 12, 1, GRAY);
    }

    NodePQ* cur = head;
    int offsetY = 0;

    while (cur != NULL && offsetY < 250) {
        DrawTextEx(gFont, (to_string(cur->data.id) + " - " + cur->data.nama +
                  " (" + cur->data.asalMasuk + ")").c_str(),
                 {(float)x, (float)(y + offsetY)}, 12, 1, DARKGRAY);
        cur     = cur->next;
        offsetY = offsetY + 18;
    }
}