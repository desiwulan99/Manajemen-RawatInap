#ifndef SIMPLE_TICKER_H      // Guard agar file header tidak di-include berulang
#define SIMPLE_TICKER_H      // Header guard (sudah diproses)

#include <string>            // Library string
using namespace std;
 
// 2. ARRAY TERURUT DENGAN BUBBLE SORT (Running Text)
struct TickerMsg {
    int priority;
    string text;
};
 
// Class untuk sistem running text
class SimpleTicker {
    TickerMsg arr[5];
    int size;
 
public:
    SimpleTicker();
    string getMessage(int index);   // Ambil pesan berdasarkan index
};
 
#endif
