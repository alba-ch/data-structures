/* Classe principal */

#include <cstdlib>
#include "BinarySearchTree.h"
using namespace std;
#include <iostream>

int main(int argc, char** argv) {
    BinarySearchTree<int,int> tree1;
    int testKeys[] = {2, 0, 8, 45, 76, 5, 3, 40};
    int testValues[] = {5, 5, 1, 88, 99, 12, 9, 11}; 
    for(int i=0; i<8;i++){
        tree1.add(testKeys[i],testValues[i]);
    }     
    cout<<"Preorder = ";
    tree1.showKeysPreorder();
    cout<<"\nInorder = ";
    tree1.showKeysInorder();
    cout<<"\nPostorder = ";
    tree1.showKeysPostorder();
    cout<<"\n";
    
    BinarySearchTree<int,int> tree2(tree1);
    
    if(tree1.equals(tree2)==1) cout<<"Cert"<<endl;
    else cout<<"Fals"<<endl;
    
    tree1.add(1,10);
    
    if(tree1.equals(tree2)==1) cout<<"Cert"<<endl;
    else cout<<"Fals"<<endl;
            
    return 0;
}

