#include <iostream>
#include <cstdio>
#include "myuint.hpp"

using namespace std;

int main() {
    
    // uint64_t a = 10;
    // std::cout << (a >> 1) << std::endl;


    myuint<256> i(10);
    myuint<256> j(20); 
    
    myuint<256> k(300);
    
    i = k;
    // i += 10;
    // k -= 1;
    
    unsigned char x = i.convert_to<uint16_t>();
    printf("%d\n",x);



    myuint<8> a(50);
    a += 300;

    //a should be 94
    unsigned char y = a.convert_to<uint8_t>();
    printf("%d\n",y);

    return 0;
}