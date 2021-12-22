#include <iostream>
#include <cstdio>
#include "myuint.hpp"

using namespace std;

int main() {
    
    myuint<128> i(10);
    myuint<128> j(20); 
    
    myuint<128> k(30);
    
    i = k;
    i += 10;
    k -= 1;
    
    unsigned short x = k.convert_to<uint16_t>();
    cout << x << endl;
    return 0;
}