#ifndef ACTIVITY_STACK_H        // Guard agar file header tidak di-include berulang
#define ACTIVITY_STACK_H        // Header guard (sudah diproses)

#include <string>               // Library string
using namespace std;
 
// 4. STACK (Pencatatan Log Aktivitas - LIFO)
struct NodeStack {
    string aktivitas;
    NodeStack* next;
};
 
// Stack untuk menyimpan aktivitas (LIFO) dan menampilkannya di GUI
class ActivityStack {
    NodeStack* top;
 
public:
    ActivityStack();
    void push(string s);
    void drawGUI(int x, int y);
};

#endif