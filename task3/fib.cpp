#include <iostream>
#include <cstdio>
#include <unistd.h>
#include "myuint.hpp"

/*This is a program to further demonstrate the myuint class. It prints out the fibonacci numbers
using only the myuint class.*/

using namespace std;

int main() {

    myuint a=0,b=1,c=0;
    while (1) {
        c = a;
        a = b;
        b += c;
        printf("%lu\n",a.convert_to<uint64_t>());
        sleep(1);
    }

    return 0;
}