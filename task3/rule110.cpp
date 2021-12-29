#include <iostream>
#include <cstdio>
#include <unistd.h>
#include "myuint.hpp"

/*This is a program to further demonstrate the myuint class. With this program we can finally
conclude that C++ is actually turing complete. Wow.*/

#define BOARD_CAP 70
using namespace std;

myuint<8> board[BOARD_CAP]{0};

int main(void) {

    //Initial seed
    board[BOARD_CAP-1] = 1;
    myuint _110 = 110;

    for (myuint i = 0; i < BOARD_CAP; i++) {
        //Display board
        for (myuint j = 0; j < BOARD_CAP; j++)
            cout << " #"[board[j.convert_to<uint8_t>()].convert_to<uint8_t>()];
        cout << '\n';

        //Update Board
        myuint pattern = (board[0]<<1) | board[1];

        for (myuint j = 1; j < BOARD_CAP-1; j++) {
            pattern = ((pattern << 1) & 7) | board[(j+1).convert_to<uint8_t>()]; //Add next bit to the front
            board[j.convert_to<uint8_t>()] = (_110 >> pattern) & 1; //Get pattern'th least significant bit
        }

    }

    return 0;
}