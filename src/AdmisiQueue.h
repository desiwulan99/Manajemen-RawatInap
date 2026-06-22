#ifndef ADMISI_QUEUE_H      // Guard agar header tidak di-include berulang
#define ADMISI_QUEUE_H      // Header guard (sudah diproses)

#include "Pasien.h"         // Struktur data pasien
 
// 5. CIRCULAR LINKED LIST QUEUE (Antrean Admisi - FIFO)
// Menggunakan circular single linked list dengan pointer tail (last)
// Enqueue = insertEnd (sisip di akhir), Dequeue = deleteFirstNode (hapus di depan)
 
struct NodeQ {
    Pasien data;
    NodeQ* next;
};
 
// Class queue admisi pasien (FIFO menggunakan circular linked list)
class AdmisiQueue {
    NodeQ* last; // pointer ke ekor (tail) circular linked list
 
public:
    AdmisiQueue();
    bool empty();
    void enqueue(Pasien p);
    Pasien dequeue();
    void drawGUI(int x, int y);
};
 
#endif
