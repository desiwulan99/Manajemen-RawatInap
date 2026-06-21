#include "ActivityStack.h"
#include "raylib.h"
#include "AppFont.h"

ActivityStack::ActivityStack() {
    top = NULL;
}

void ActivityStack::push(string s) {
    NodeStack* n = new NodeStack;
    n->aktivitas  = s;
    n->next       = top;
    top           = n;
}

void ActivityStack::drawGUI(int x, int y) {
    NodeStack* cur = top;
    int offsetY    = 0;

    if (cur == NULL) {
        DrawTextEx(gFont, "Belum ada aktivitas.", {(float)x, (float)y}, 12, 1, GRAY);
    }

    while (cur != NULL && offsetY < 250) {
        DrawTextEx(gFont, ("- " + cur->aktivitas).c_str(), {(float)x, (float)(y + offsetY)}, 12, 1, DARKGRAY);
        cur     = cur->next;
        offsetY = offsetY + 18;
    }
}