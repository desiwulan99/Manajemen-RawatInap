#ifndef AUTH_HASH_TABLE_H
#define AUTH_HASH_TABLE_H
 
#include <string>
using namespace std;
 
// 1. HASH TABLE (Sistem Login)
struct AuthNode {
    string username;
    string password;
    AuthNode* next;
};
 
class AuthHashTable {
    AuthNode* table[10];
 
    int hashFunction(string key);
public:
    AuthHashTable();
    void insertUser(string u, string p);
    bool authenticate(string u, string p);
};
 
#endif
