#include "avl.h"
#include <iostream>

using namespace std;

int main(){

    Avl<int>* tree = new Avl<int>();
    
    tree->insert(9);
    tree->insert(10);
    tree->insert(8);
    tree->insert(7);
    tree->insert(14);
    tree->insert(12);



    tree->print();
    cout<<"\n";

    return 0;
}