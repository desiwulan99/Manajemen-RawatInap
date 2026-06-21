#include "AuthHashTable.h"
 
int AuthHashTable::hashFunction(string key) {
    int sum = 0;
    for (int i = 0; i < (int)key.length(); i++) {
        sum += (int)key[i];
    }
    return sum % 10;
}
 
AuthHashTable::AuthHashTable() {
    for (int i = 0; i < 10; i++) {
        table[i] = NULL;
    }
}
 
void AuthHashTable::insertUser(string u, string p) {
    int idx = hashFunction(u);
    AuthNode* n = new AuthNode;
    n->username = u;
    n->password = p;
    n->next = table[idx];
    table[idx] = n;
}
 
bool AuthHashTable::authenticate(string u, string p) {
    int idx = hashFunction(u);
    AuthNode* cur = table[idx];
    while (cur != NULL) {
        if (cur->username == u && cur->password == p) return true;
        cur = cur->next;
    }
    return false;
}
