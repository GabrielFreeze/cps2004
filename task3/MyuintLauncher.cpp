#include <iostream>
#include <cstdio>
#include "myuint.hpp"

using namespace std;

int main() {
    
    myuint<128> i(10);
    myuint<2048> j(20);
    myuint<8>    k(20);

    i = j;

    unsigned short x = i.convert_to<uint16_t>();
    cout << x << endl;

    i = 10;
    if (i == j) cout << "i equals j" << endl;
    if (i != j) cout << "i does not equal j" << endl;


    if (j > k) cout << "j > k" << endl;
    if (k > j) cout << "k > j" << endl;
    if (j >= k) cout << "j >= k" << endl;
    if (j >= 13) cout << "j >= 13" << endl;
    if (k >= 40) cout << "k >= 40" << endl;
    

    
    i = 32;
    j = i | 29;

    x = j.convert_to<uint16_t>();
    printf("%d\n",x); //x = 61
    
    i = 61;
    j = i & 35628;

    x = j.convert_to<uint16_t>();
    printf("%d\n",x); //x = 44

    i = 61;
    i = ~i;    
    x = i.convert_to<uint8_t>();
    printf("%d\n",x); //x = 194 (Because its unsigned)

    i = 256;
    j = 1;

    i >>= j;
    
    x = i.convert_to<uint16_t>();
    printf("%d\n",x); 



    return 0;
}