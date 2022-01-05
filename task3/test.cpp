#include <iostream>
#include <cstdio>
#include "myuint.hpp"

using namespace std;

int main() {
    myuint<128>  i(10);
    myuint<2048> j(20);
    myuint<16>   k(20);

    assert(i == 10);
    assert(i != 11);
    assert(j == 20);
    assert(j >= 20);
    assert(i <= 20);
    assert(i >= 5);
    assert(i <= 20);
    assert(j >= i);
    assert(j >= k);
    assert(k >= j);

    assert((i|0) == i);
    assert((i|1) == i+1);
    assert((j|1) == 21);
    assert((k|10) == 30);
    assert((i|j|k) == 30);

    assert((k&1) == 0);
    assert((i&i) == i);
    assert((i&j) == 0);
    assert((i&j&k) == 0);
    assert((i&255) == i);

    assert((~j) == ((j-j-1-j)));
    assert((~k) == 65515);

    assert((i^j) == 30);
    /*Because j has more space than i, the trailing empty bytes in i will XOR
    with the trailing empty bytes in j, making them full (255) bytes*/
    assert((j^i) != 30); 

    assert((i+2093) == 2103);
    assert((i+j+k) == 50);
    assert((k+65535) == (k-1));

    assert((i-8) == 2);
    assert(((j-i)+10) == k);
    assert((i+i-i+i-i+i-i) == i);

    assert((i << 3) == 80);
    assert((j << 1) == 40);
    assert((k << 2) == 80);
    assert((((k << k) >> k) +k) == (k+k-k));

    assert((i*j*k) == 4000);
    assert((i*827) == 8270);
    assert((j*k) == (i*2*j));

    assert((j/i) == 2);
    assert((j/5) == 4);
    assert((k/4) == ((j/5)+1));

    assert((i%2) == 0);
    assert(((i+1)%2) == 1);
    assert((j%k) == 0);
    assert(((j+i)%j) == i);

    myuint<1024> a(5);
    myuint<2048> b = (a << 1000) + 23;
    assert(b.convert_to<int>() == 23); 
    
    cout << "All Unit Tests succeeded\n";


}