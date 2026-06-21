#ifndef AVL_TREE_H
#define AVL_TREE_H
 
#include "Pasien.h"
 
// 7. AVL TREE (Pencarian Pasien Checkout)
struct NodeAVL {
    int key;
    Pasien data;
    NodeAVL* left;
    NodeAVL* right;
    int height;
 
    NodeAVL(Pasien p);
};
 
int height(NodeAVL* n);
int getBalance(NodeAVL* n);
NodeAVL* rightRotate(NodeAVL* y);
NodeAVL* leftRotate(NodeAVL* x);
NodeAVL* insertAVL(NodeAVL* node, Pasien p);
NodeAVL* searchAVL(NodeAVL* root, int id);
 
#endif
