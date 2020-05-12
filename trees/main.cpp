// mac937@nyu.edu
// hw question 1

#include <iostream>
#include <ctime>
#include "redblack.h"

using namespace std;

int main(){

    RedBlackTree<int> b;
    srand(time(NULL));
    for (int i = 0; i < 25; i++){
        int val = rand() % 1000;
        b.insert(val);
    }
    b.printLevelOrder(cout);
}
