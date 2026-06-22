#ifndef AUTH_HASH_TABLE_H   // Guard agar header tidak di-include berulang
#define AUTH_HASH_TABLE_H   // Header guard (sudah diproses)

#include <string>           // Library string
using namespace std;
 
// 1. HASH TABLE (Sistem Login)
struct AuthNode {
    string username;
    string password;
    AuthNode* next;
};
 
// Class hash table untuk sistem login (menyimpan user, menambah akun, dan validasi login)
class AuthHashTable {
    AuthNode* table[10];
 
    int hashFunction(string key);
public:
    AuthHashTable();
    void insertUser(string u, string p);
    bool authenticate(string u, string p);
};
 
#endif
