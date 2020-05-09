// mac937@nyu.edu
// hw question 1

#include <iostream>
#include <ctime>
#include "avl.h"

using namespace std;

int main(){

    AVL<int> b;
    srand(time(NULL));
    for (int i = 0; i < 25; i++){
        int val = rand() % 1000;
        b.insert(val);
    }
    b.printLevelOrder(cout);
}
