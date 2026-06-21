#ifndef ADMISI_QUEUE_H
#define ADMISI_QUEUE_H
 
#include "Pasien.h"
 
// 5. CIRCULAR LINKED LIST QUEUE (Antrean Admisi - FIFO)
// Menggunakan circular single linked list dengan pointer tail (last)
// Enqueue = insertEnd (sisip di akhir), Dequeue = deleteFirstNode (hapus di depan)
 
struct NodeQ {
    Pasien data;
    NodeQ* next;
};
 
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
