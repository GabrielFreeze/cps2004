#include <iostream>
#include <cstdio>
#include "myuint.hpp"

using namespace std;

int main() {
    
    myuint<128> i(10);
    myuint<2048> j(20);
    myuint<16>    k(20);

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

    i = 10;
    j = 20;
    i ^= j;
    x = i.convert_to<uint16_t>();
    printf("%d\n",x); 

    i = 18;
    i.set_bit(0,1);
    x = i.convert_to<uint16_t>();
    printf("%d\n",x); //19

    i.set_bit(1,0);
    x = i.convert_to<uint16_t>();
    printf("%d\n",x); //17


    i = 45;
    printf("%d\n",i.get_bit(0));//1
    printf("%d\n",i.get_bit(1));//0
    printf("%d\n",i.get_bit(2));//1
    printf("%d\n",i.get_bit(3));//1
    printf("%d\n",i.get_bit(4));//0
    printf("%d\n",i.get_bit(5));//1

    i = 18213;
    j = 23984;
    k = i + j;
    x = k.convert_to<uint16_t>();
    printf("%d\n",x); //42,197

    i = 0;
    i += 198;
    x = i.convert_to<uint16_t>();
    printf("%d\n",x); //198

    myuint<4> t(8);
    t += 6846854554;
    x = t.convert_to<uint16_t>();
    printf("%d\n",x); //Keeps overflowing to the correct value. 2

    i = 50;
    i -= 18;
    x = i.convert_to<uint16_t>();
    printf("%d\n",x); //32


    i = 50;
    i -= 51;
    x = i.convert_to<uint16_t>();
    printf("%d\n",x); //Overflows to pow(2,128)-1. Gets truncated to 65,535 because of uint16_t conversion

    i = 20;
    i -= 0;
    x = i.convert_to<uint16_t>();
    printf("%d\n",x);//20

    i = 0;
    i++;
    ++i;
    x = i.convert_to<uint16_t>();
    printf("%d\n",x);//2

    
    x = (i--).convert_to<uint16_t>();
    printf("%d\n",x); //2
    
    x = i.convert_to<uint16_t>();
    printf("%d\n",x); //1


    i = 10;
    j = 20;
    k = i*j;
    x = k.convert_to<uint16_t>();
    printf("%d\n",x); //200

    i = 100;
    j = 10;
    i /= j;
    x = i.convert_to<uint16_t>();
    printf("%d\n",x); //10

    return 0;
}