#ifndef RS_GRAPH_H          // Guard agar file header tidak di-include berulang
#define RS_GRAPH_H          // Header guard (sudah diproses)

// 3. GRAPH & BFS (Peta Rute)
// Queue sederhana untuk BFS
struct BFSQueue {
    int data[50];
    int f, r;
 
    BFSQueue();
    void push(int val);
    int pop();
    bool isEmpty();
};

// Class graph rumah sakit
class RSGraph {
public:
    // 0: Lobi, 1: Lorong Utama, 2: VIP, 3: KELAS 1, 4: KELAS 2, 5: KELAS 3
    int adj[6][6];
    int parent[6];
 
    RSGraph();
    void doBFS(int start, int target);
};
 
#endif
