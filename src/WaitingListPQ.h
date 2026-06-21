#ifndef WAITING_LIST_PQ_H
#define WAITING_LIST_PQ_H
 
#include "Pasien.h"
#include <string>
using namespace std;
 
// 6. PRIORITY QUEUE (Antrean IGD Prioritas Tertinggi)
struct NodePQ {
    Pasien data;
    int priority;
    NodePQ* next;
};
 
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
