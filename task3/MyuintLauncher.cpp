#include <iostream>
#include <cstdio>
#include "myuint.hpp"

using namespace std;

int main() {
    
    myuint<128> i(10);
    myuint<2048> j(20);
    myuint<16>    k(20);
    
    cout << "\nSetting i = j\n";
    i = j;
    unsigned short x = i.convert_to<uint16_t>();
    cout << "i =" << x << endl;

    cout << "\nComparing i with j\n";
    i = 10;
    if (i == j) cout << "i equals j" << endl;
    if (i != j) cout << "i does not equal j" << endl;

    cout << "\nMore Comparisms\n";
    if (j > k) cout << "j > k" << endl;
    if (k > j) cout << "k > j" << endl;
    if (j >= k) cout << "j >= k" << endl;
    if (j >= 13) cout << "j >= 13" << endl;
    if (k >= 40) cout << "k >= 40" << endl;
    

    cout << "\nPerforming bitwise or\n";
    i = 32;
    k = 29;
    j = i | k;
    x = j.convert_to<uint16_t>();
    printf("%d\n",x); //x = 61
    

    cout << "\nPerforming bitwise and\n";
    i = 61;
    j = i & 35628;
    x = j.convert_to<uint16_t>();
    printf("%d\n",x); //x = 44

    cout << "\nPerforming bitwise not\n";
    i = 61;
    i = ~i;    
    x = i.convert_to<uint8_t>();
    printf("%d\n",x); //x = 194 (Because its unsigned)

    cout << "\nPerforming bitwise right shift\n";
    i = 256;
    j = 1;
    i >>= j;
    x = i.convert_to<uint16_t>();
    printf("%d\n",x); 


    cout << "\nPerforming bitwise left shift\n";
    i = 256;
    j = 2;
    i <<= j;
    x = i.convert_to<uint16_t>();
    printf("%d\n",x); 

    cout << "\nPerforming bitwise xor\n";
    i = 10;
    j = 20;
    i ^= j;
    x = i.convert_to<uint16_t>();
    printf("%d\n",x); 

    cout << "\nFlipping a bit\n";
    i = 18;
    i.set_bit(0,1);
    x = i.convert_to<uint16_t>();
    printf("%d\n",x); //19

    cout << "\nFlipping a bit\n";
    i.set_bit(1,0);
    x = i.convert_to<uint16_t>();
    printf("%d\n",x); //17

    cout << "\nRetrieving individual bits\n";
    i = 45;
    printf("%d\n",i.get_bit(0));//1
    printf("%d\n",i.get_bit(1));//0
    printf("%d\n",i.get_bit(2));//1
    printf("%d\n",i.get_bit(3));//1
    printf("%d\n",i.get_bit(4));//0
    printf("%d\n",i.get_bit(5));//1


    cout << "\nAddition\n";
    i = 18213;
    j = 23984;
    k = i + j;
    x = k.convert_to<uint16_t>();
    printf("%d\n",x); //42,197

    cout << "\nAddition\n";
    i = 0;
    i += 198;
    x = i.convert_to<uint16_t>();
    printf("%d\n",x); //198

    cout << "\nOverflow Addition\n";
    myuint<4> t(8);
    t += 6846854554;
    x = t.convert_to<uint16_t>();
    printf("%d\n",x); //Keeps overflowing to the correct value. 2

    cout << "\nSutraction\n";
    i = 50;
    i -= 18;
    x = i.convert_to<uint16_t>();
    printf("%d\n",x); //32

    cout << "\nUnderfow Subtraction\n";
    i = 50;
    i -= 51;
    x = i.convert_to<uint16_t>();
    printf("%d\n",x); //Overflows to pow(2,128)-1. Gets truncated to 65,535 because of uint16_t conversion

    cout << "\nSubtraction\n";
    i = 20;
    i -= 0;
    x = i.convert_to<uint16_t>();
    printf("%d\n",x);//20
    
    cout << "\nPost-fix and Pre-fix increment\n";
    i = 0;
    i++;
    ++i;
    x = i.convert_to<uint16_t>();
    printf("%d\n",x);//2

    cout << "\nPost-fix and Pre-fix decerement\n";
    x = (i--).convert_to<uint16_t>();
    printf("%d\n",x); //2
    
    x = i.convert_to<uint16_t>();
    printf("%d\n",x); //1

    cout << "\nMultiplication\n";
    i = 10;
    j = 20;
    k = i*j;
    x = k.convert_to<uint16_t>();
    printf("%d\n",x); //200



    cout << "\nDivision\n";
    i = 100;
    j = 10;
    k = i/ j;
    x = k.convert_to<uint16_t>();
    printf("%d\n",x); //10

    cout << "\nDivision and Multiplcation cancelling each other out\n";
    i = 98;
    k = 2;
    myuint p = (((((i/k)*k)/k) << 10) >> 10); //98/2 = 49
    x = p.convert_to<uint16_t>();
    printf("%d\n",x); //10

    cout << "\nModulo Operator\n";
    i = 101;
    if (i % 2) cout << "Odd" << '\n';
    else       cout << "Even" << '\n';


    cout << "\nFinding the multiples of 3\n";
    for (myuint i = 0; i <  20; i++) {
        cout << i.convert_to<uint16_t>() << (i%3? " Is Not ":" Is ") << "Dividible by 3\n";
    }

    i = 110;
    j = (i >> 0) & 1;
    x = j.convert_to<uint16_t>();
    printf("%d\n",x); 
    
    j = i.get_bit(0);
    x = j.convert_to<uint16_t>();
    printf("%d\n",x); //10


    return 0;
}