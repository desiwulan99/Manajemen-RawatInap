#ifndef SIMPLE_TICKER_H
#define SIMPLE_TICKER_H
#include <string>
using namespace std;
 
// 2. ARRAY TERURUT DENGAN BUBBLE SORT (Running Text)
struct TickerMsg {
    int priority;
    string text;
};
 
class SimpleTicker {
    TickerMsg arr[5];
    int size;
 
public:
    SimpleTicker();
    string getMessage(int index);
};
 
#endif
