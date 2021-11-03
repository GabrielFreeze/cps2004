#include <iostream>
#include "dag.hpp"
using namespace std;

Dag<int, int> dag;

int main() {

    dag.x = 2;
    cout << dag.x << endl;    

    return 0;
}