#ifndef ACTIVITY_STACK_H
#define ACTIVITY_STACK_H
 
#include <string>
using namespace std;
 
// 4. STACK (Pencatatan Log Aktivitas - LIFO)
struct NodeStack {
    string aktivitas;
    NodeStack* next;
};
 
class ActivityStack {
    NodeStack* top;
 
public:
    ActivityStack();
    void push(string s);
    void drawGUI(int x, int y);
};
#endif