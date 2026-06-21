#include "AVLTree.h"
#include <algorithm>
using namespace std;
 
NodeAVL::NodeAVL(Pasien p) {
    key    = p.id;
    data   = p;
    left   = NULL;
    right  = NULL;
    height = 1;
}
 
int height(NodeAVL* n) {
    if (n == NULL) return 0;
    return n->height;
}
 
int getBalance(NodeAVL* n) {
    if (n == NULL) return 0;
    return height(n->left) - height(n->right);
}
 
NodeAVL* rightRotate(NodeAVL* y) {
    NodeAVL* x  = y->left;
    NodeAVL* T2 = x->right;
 
    // Lakukan rotasi
    x->right = y;
    y->left  = T2;
 
    // Update ketinggian
    y->height = 1 + max(height(y->left),  height(y->right));
    x->height = 1 + max(height(x->left),  height(x->right));
 
    return x;
}
 
NodeAVL* leftRotate(NodeAVL* x) {
    NodeAVL* y  = x->right;
    NodeAVL* T2 = y->left;
 
    // Lakukan rotasi
    y->left  = x;
    x->right = T2;
 
    // Update ketinggian
    x->height = 1 + max(height(x->left),  height(x->right));
    y->height = 1 + max(height(y->left),  height(y->right));
 
    return y;
}
 
NodeAVL* insertAVL(NodeAVL* node, Pasien p) {
    // Penyisipan BST normal
    if (node == NULL) return new NodeAVL(p);
 
    if      (p.id < node->key) node->left  = insertAVL(node->left,  p);
    else if (p.id > node->key) node->right = insertAVL(node->right, p);
    else return node; // key sama tidak diizinkan
 
    // Update tinggi ancestor
    node->height = 1 + max(height(node->left), height(node->right));
 
    // Cek balance factor
    int balance = getBalance(node);
 
    // Left-Left
    if (balance > 1  && p.id < node->left->key)
        return rightRotate(node);
    // Right-Right
    if (balance < -1 && p.id > node->right->key)
        return leftRotate(node);
    // Left-Right
    if (balance > 1  && p.id > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    // Right-Left
    if (balance < -1 && p.id < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
 
    return node;
}
 
NodeAVL* searchAVL(NodeAVL* root, int id) {
    if (root == NULL || root->key == id) return root;
    if (id < root->key) return searchAVL(root->left,  id);
    return             searchAVL(root->right, id);
}
