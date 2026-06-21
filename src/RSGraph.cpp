#include "RSGraph.h"
 
BFSQueue::BFSQueue() {
    f = 0;
    r = 0;
}
 
void BFSQueue::push(int val) {
    data[r++] = val;
}
 
int BFSQueue::pop() {
    return data[f++];
}
 
bool BFSQueue::isEmpty() {
    return f == r;
}
 
RSGraph::RSGraph() {
    for (int i = 0; i < 6; i++) {
        parent[i] = -1;
        for (int j = 0; j < 6; j++) {
            adj[i][j] = 0;
        }
    }
    // Layout Peta
    adj[0][1] = 1; adj[1][0] = 1; // Lobi <-> Lorong
    adj[1][2] = 1; adj[2][1] = 1; // Lorong <-> VIP
    adj[1][3] = 1; adj[3][1] = 1; // Lorong <-> Kelas 1
    adj[3][4] = 1; adj[4][3] = 1; // Kelas 1 <-> Kelas 2
    adj[4][5] = 1; adj[5][4] = 1; // Kelas 2 <-> Kelas 3
}
 
void RSGraph::doBFS(int start, int target) {
    for (int i = 0; i < 6; i++) parent[i] = -1;
 
    bool visited[6] = {false};
    BFSQueue q;
 
    q.push(start);
    visited[start] = true;
 
    while (!q.isEmpty()) {
        int cur = q.pop();
        if (cur == target) break;
 
        for (int i = 0; i < 6; i++) {
            if (adj[cur][i] == 1 && !visited[i]) {
                visited[i] = true;
                parent[i]  = cur;
                q.push(i);
            }
        }
    }
}
