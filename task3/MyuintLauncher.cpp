#include <iostream>
#include <cstdio>
#include "myuint.hpp"

using namespace std;

int main() {
    
    //Consider the following numbers.

    myuint<256> i(10);
    myuint<256> j(20); 
    myuint<256> k(300);
    myuint<256> l(0);    


    //i has now the value of k.
    i = k; //i is set to 300

    unsigned char x = i.convert_to<uint16_t>();
    printf("%d\n",x); //x = 44

    //Changing k will not change i.
    k = l;
    x = i.convert_to<uint16_t>();
    printf("%d\n",x);
    // std::cout << i;
    //TODO: add i
    
    //Comparism between myuint
    if (j > i)
        std::cout << "j is greater than i" << std::endl;
    else 
        std::cout << "i is greater than j" << std::endl;

    if (i == 300) std::cout << "i == 300" << std::endl;
    if (i != 300) std::cout << "i != 300" << std::endl;
    if (i == 256) std::cout << "i == 256" << std::endl;

    i = 52;
    i |= 29;
    

    x = i.convert_to<uint16_t>();
    printf("%d\n",x); //x = 61

    i &= 35628;

    x = i.convert_to<uint16_t>();
    printf("%d\n",x); //x = 44


    i = ~i;    
    x = i.convert_to<uint8_t>();
    printf("%d\n",x); //x = 211 (Because its unsigned)



    i = 1;
    for (int it = 0; it < 10; it++) {
        i <<= 1;
        x = i.convert_to<uint8_t>();
        printf("%d\n",x); //x = 211 (Because its unsigned)
    }



    return 0;
}