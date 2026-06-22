#ifndef WAITING_LIST_PQ_H       // Guard agar file header tidak di-include berulang
#define WAITING_LIST_PQ_H       // Header guard (sudah diproses)
 
#include "Pasien.h"             // Struktur data pasien
#include <string>               // Library string
using namespace std;
 
// 6. PRIORITY QUEUE (Antrean IGD Prioritas Tertinggi)
struct NodePQ {
    Pasien data;
    int priority;
    NodePQ* next;
};
 
// Class priority queue untuk waiting list
class WaitingListPQ {
    NodePQ* head;
    
public:
    WaitingListPQ();
    bool empty();
    void enqueue(Pasien p);
    Pasien dequeueSuitable(string tipe);
    bool removeByID(int id);
    void drawGUI(int x, int y);
};
 
#endif
