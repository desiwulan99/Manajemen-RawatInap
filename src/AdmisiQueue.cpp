#include "AdmisiQueue.h"
#include "raylib.h"
#include "AppFont.h"

AdmisiQueue::AdmisiQueue() {
    last = NULL;
}

bool AdmisiQueue::empty() {
    return last == NULL;
}

// Penyisipan di akhir (enqueue) - mengikuti pola insertEnd circular
void AdmisiQueue::enqueue(Pasien p) {
    NodeQ* baru = new NodeQ;
    baru->data  = p;
    baru->next  = NULL;

    if (last == NULL) {
        // Daftar kosong: inisialisasi dengan simpul baru
        // Simpul menunjuk ke dirinya sendiri (struktur melingkar)
        last       = baru;
        baru->next = baru;
    } else {
        // Sisipkan setelah ekor saat ini, lalu perbarui ekor
        // Simpul baru menunjuk ke head (last->next)
        baru->next  = last->next;
        // Ekor lama menunjuk ke simpul baru
        last->next  = baru;
        // Perbarui pointer ekor ke simpul baru
        last        = baru;
    }
}

// Penghapusan di depan (dequeue) - mengikuti pola deleteFirstNode circular
Pasien AdmisiQueue::dequeue() {
    Pasien kosong = {0, "", "", "", ""};

    if (last == NULL) {
        return kosong;
    }

    NodeQ* head = last->next; // head = last->next pada circular list
    Pasien p    = head->data;

    if (head == last) {
        // Hanya ada satu simpul dalam daftar
        delete head;
        last = NULL;
    } else {
        // Lebih dari satu simpul
        last->next = head->next;
        delete head;
    }

    return p;
}

void AdmisiQueue::drawGUI(int x, int y) {
    if (last == NULL) {
        DrawTextEx(gFont, "Kosong", {(float)x, (float)y}, 12, 1, GRAY);
        return;
    }

    // Traversal circular list dari head hingga kembali ke head
    NodeQ* head    = last->next;
    NodeQ* cur     = head;
    int offsetY    = 0;

    while (offsetY < 250) {
        DrawTextEx(gFont, (to_string(cur->data.id) + " - " + cur->data.nama).c_str(),
                 {(float)x, (float)(y + offsetY)}, 12, 1, DARKGRAY);
        cur     = cur->next;
        offsetY = offsetY + 18;
        if (cur == head) break; // sudah kembali ke awal
    }
}