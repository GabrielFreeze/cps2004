#include <iostream>
#include <cstdio>
#include "myuint.hpp"

using namespace std;

int main() {
    
    //Consider the following numbers.

    myuint<64> i(27);
    myuint<2> a(6); //Becomes 2 due to truncation of bitstring
    myuint<64> j(20); 
    myuint<64> k(300);
    myuint<64> l(0);    


    //i has now the value of k.
    i = k; //i is set to 300

    unsigned short x = i.convert_to<uint16_t>();
    printf("%d\n",x); //x = 300

    //Changing k will not change i.
    k = l;
    x = i.convert_to<uint16_t>();
    printf("%d\n",x);
    
    //Comparism between myuint
    if (j > i)
        std::cout << "j is greater than i" << std::endl;
    else 
        std::cout << "i is greater than j" << std::endl;

    if (i == 300) std::cout << "i == 300" << std::endl;
    if (i != 300) std::cout << "i != 300" << std::endl;
    if (i == 256) std::cout << "i == 256" << std::endl;


    
    
    i = a;
    x = i.convert_to<uint16_t>();
    printf("%d\n",x); //i = 2?



    i = 10;
    l = 20;

    x = i.convert_to<uint16_t>();
    printf("%d\n",x); //i = 10

    x = l.convert_to<uint16_t>();
    printf("%d\n",x); //l = 20

    i = std::move(l);

    x = i.convert_to<uint16_t>();
    printf("%d\n",x); // i = 20


    i = 32;
    j = i | 29;

    x = j.convert_to<uint16_t>();
    printf("%d\n",x); //x = 61
    
    i = 61;
    j = i & 35628;

    x = j.convert_to<uint16_t>();
    printf("%d\n",x); //x = 44


    i = ~i;    
    x = i.convert_to<uint8_t>();
    printf("%d\n",x); //x = 194 (Because its unsigned)



    i = 1024;
    for (int it = 0; it < 10; it++) {
        i >>= 1;
        x = i.convert_to<uint16_t>();
        printf("%d\n",x); 
    }
    std::cout << std::endl;
    
    i = 10;
    for (int it = 0; it < 10; it++) {
        i <<= 2;
        x = i.convert_to<uint16_t>(); //The most signifcant '1' will be lost after some number of iterations due to only being 2 bytes long.
        printf("%d\n",x); 
    }


    std::cout << std::endl;

    i = 10;
    for (int it = 0; it < 10; it++) {
        i <<= 2;
        uint64_t x = i.convert_to<uint64_t>(); //All data is preserved
        printf("%ld\n",x); 
    }

    std::cout << std::endl;

    i = 0;
    j = 1;


    i ^= j; //i should be 1
    x = i.convert_to<uint16_t>();
    printf("%d\n",x); 

    i = 1;
    i ^= 1; //i should be 0; 
    x = i.convert_to<uint16_t>();
    printf("%d\n",x); 

    i = 5;
    printf("%d\n",i.getLSB()); //1
    i = 10;
    printf("%d\n",i.getLSB()); // 0

    std::cout << std::endl;
    
    // printf("%d\n",i.getNthBit(0)); // 0
    // printf("%d\n",i.getNthBit(1)); // 1
    // printf("%d\n",i.getNthBit(2)); // 0
    // printf("%d\n",i.getNthBit(3)); // 1
    // printf("%d\n",i.getNthBit(4)); // 0
    // printf("%d\n",i.getNthBit(5)); // 0



    // i.setBit(0,1);
    // x = i.convert_to<uint16_t>();
    // printf("%d\n",x); //11


    // i.setBit(2,1);
    // x = i.convert_to<uint16_t>();
    // printf("%d\n",x); //15



    // i = 10;
    // i+= 10;
    // x = i.convert_to<uint16_t>();
    // printf("%d\n",x); //20

    return 0;
}