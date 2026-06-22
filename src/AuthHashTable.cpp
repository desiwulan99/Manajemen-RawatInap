// Implementasi hash table untuk autentikasi user
#include "AuthHashTable.h"      

// Fungsi hash untuk menentukan index berdasarkan username
int AuthHashTable::hashFunction(string key) {   
    int sum = 0;
    for (int i = 0; i < (int)key.length(); i++) {
        sum += (int)key[i];
    }
    return sum % 10;
}

// Konstruktor hash table: menginisialisasi semua bucket menjadi NULL (kosong)
AuthHashTable::AuthHashTable() {
    for (int i = 0; i < 10; i++) {
        table[i] = NULL;
    }
}

// Menambahkan user ke hash table
void AuthHashTable::insertUser(string u, string p) {
    int idx = hashFunction(u);
    AuthNode* n = new AuthNode;
    n->username = u;
    n->password = p;
    n->next = table[idx];
    table[idx] = n;
}

// Mengecek login user
bool AuthHashTable::authenticate(string u, string p) {
    int idx = hashFunction(u);
    AuthNode* cur = table[idx];
    while (cur != NULL) {
        if (cur->username == u && cur->password == p) return true;
        cur = cur->next;
    }
    return false;
}
