#ifndef AVL_TREE_H       // Guard agar header tidak di-include berulang
#define AVL_TREE_H       // Header guard (sudah diproses)

#include "Pasien.h"     // Struktur data pasien

// 7. AVL TREE (Pencarian Pasien Checkout)
struct NodeAVL {
    int key;
    Pasien data;
    NodeAVL* left;
    NodeAVL* right;
    int height;
 
    NodeAVL(Pasien p);
};
 
int height(NodeAVL* n);                         // Menghitung tinggi node
int getBalance(NodeAVL* n);                     // Menghitung balance factor
NodeAVL* rightRotate(NodeAVL* y);               // Rotasi kanan
NodeAVL* leftRotate(NodeAVL* x);                // Rotasi kiri
NodeAVL* insertAVL(NodeAVL* node, Pasien p);    // Insert AVL
NodeAVL* searchAVL(NodeAVL* root, int id);      // Search AVL
 
#endif
