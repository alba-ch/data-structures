/* Especificació de AVLTree */

/*/ COST COMPUTACIONAL:
 * AVLTree: O(1)
 * AVLTree(constructor còpia): O(n)
 * ~AVLTree (destructor): O(n)
 * addAux: O(n) en el pitjor cas
 * rotacioDreta: O(n) en el pitjor cas
 * rotacioEsquerra: O(n) en el pitjor cas
 * rotacioEsquerraDreta: O(n) en el pitjor cas
 * rotacioDretaEsquerra: O(n) en el pitjor cas
 * findBalance: O(n) en el pitjor cas
 * balanceAVL: O(n) en el pitjor cas
/*/

/*/ SIMILITUDS I DIFERÈNCIES AMB BinarySearchTree /*/ 
/*
 * Per balancejar l'arbre BST, haurem de modificar el mètode addAux per inserir elements. 
 * Balancejarem l'arbre cridant a un mètode, < balanceAVL >, que calcularà el balanç del 
 * node a l'arbre (amb un mètode < findBalance >), i en cas que aquest sigui <-1 o >1 
 * haurem de fer una rotació d'un d'aquests tipus:
    - Rotació cap a l'Esquerra < rotacioEsquerra >
    - Rotació cap a la Dreta < rotacioDreta >
    - Rotació Esquerra Dreta < rotacioEsquerraDreta >
    - Rotacio Dreta Esquerra < rotacioDretaEsquerra > 
 */ 

/*/ OBSERVACIONS /*/
/* 
 * Per poder redefinir el mètode addAux, original de la classe mare BinarySearchTree, a la espicificació d'aquest mètode ho he canviat a 'virtual'.
 * D'aquesta manera dono prioritat a la classe filla i m'estalvio haver de implementar un nou mètode encarregat de cridar addAux filla.
 * 
 */

#include<iostream>
#ifndef AVLTREE_H
#define AVLTREE_H
using namespace std;

#include "BinarySearchTree.h"

template <class K, class V>
class AVLTree : public BinarySearchTree<K,V> {
public:
    AVLTree();
    AVLTree(const AVLTree& orig);
    virtual ~AVLTree();
    
    BinaryTreeNode<K,V>* addAux(const K& k, const V& value, BinaryTreeNode<K,V>* t, BinaryTreeNode<K,V>* temp = nullptr) override;
    
    BinaryTreeNode<K,V>* rotacioDreta(BinaryTreeNode<K,V>* parent);
    BinaryTreeNode<K,V>* rotacioEsquerra(BinaryTreeNode<K,V>* parent);
    BinaryTreeNode<K,V>* rotacioEsquerraDreta(BinaryTreeNode<K,V>* parent);
    BinaryTreeNode<K,V>* rotacioDretaEsquerra(BinaryTreeNode<K,V>* parent);
    
    int findBalance(BinaryTreeNode<K,V>* n) const; // Retorna el balanç d'un node
    BinaryTreeNode<K,V>* balanceAVL(BinaryTreeNode<K,V>* n); // Balanceja l'arbre
    
private:
};

#endif /* AVLTREE_H */

/*Construeix l’arbre buit. */
template <class K, class V>
AVLTree<K,V>::AVLTree(){
    cout<<"Arbre binari creat"<<endl;    
}

/* Constructor còpia. */
template <class K, class V>
AVLTree<K,V>::AVLTree(const AVLTree& orig):BinarySearchTree<K,V>(orig){
    cout<<"Còpia del arbre binari creada"<<endl; 
}

/* Destrueix els nodes de l’arbre binari. */
template <class K, class V>
AVLTree<K,V>::~AVLTree(){ 
    cout<<"Destruint arbre binari AVL"<<endl;   
}

/* MÈTODES DE ROTACIONS */

/* Fa una rotació a la dreta. */
template <class K, class V>
BinaryTreeNode<K,V>* AVLTree<K,V>::rotacioDreta(BinaryTreeNode<K,V>* parent){
    BinaryTreeNode<K,V>* temp = parent->getRight(); // Creem un node auxiliar per fer els enllaços.
    parent->setRight(temp->getLeft()); //  El fill dret del node passa a ser el fill esquerra de temp (fill esquerra del fill dret).
    temp->setLeft(parent); // El fill esquerra de temp passa a ser el node pare.
    return temp; // Retornem el node.
}

/* Fa una rotació a l'esquerra. */
template <class K, class V>
BinaryTreeNode<K,V>* AVLTree<K,V>::rotacioEsquerra(BinaryTreeNode<K,V>* parent){
    BinaryTreeNode<K,V>* temp = parent->getLeft(); // Node auxiliar per fer enllaços.
    parent->setLeft(temp->getRight()); // El fill esquerra del node pare passa a ser el fill dret del seu fill esquerra.
    temp->setRight(parent); // El fill esquerra del fill dret de l node pare passa a ser el pare.
    return temp; // Retornem el node.
}

/* Fa una rotació Esquerra-Dreta. */
template <class K, class V>
BinaryTreeNode<K,V>* AVLTree<K,V>::rotacioEsquerraDreta(BinaryTreeNode<K,V>* parent){
    BinaryTreeNode<K,V>* temp = parent->getLeft(); // Node auxiliar per fer enllaços.
    parent->setLeft(rotacioDreta(temp)); // El fill esquerra del node pare serà la rotació cap a la dreta del fill esquerra.
    return rotacioEsquerra(parent); // Llavors retornem el node amb una rotació a l'esquerra.
}

/* Fa una rotació Dreta-Esquerra */
template <class K, class V>
BinaryTreeNode<K,V>* AVLTree<K,V>::rotacioDretaEsquerra(BinaryTreeNode<K,V>* parent){
    BinaryTreeNode<K,V>* temp = parent->getRight(); // Node auxiliar per fer enllaços.
    parent->setRight(rotacioEsquerra(temp)); // El fill dret del node pare serà la rotació cap a l'esquerra del fill dret.
    return rotacioDreta(parent); // Retornem el node amb la rotació a la dreta.
}

/* Troba el balanç d'un node. */
template <class K, class V>
int AVLTree<K,V>::findBalance(BinaryTreeNode<K,V>* n) const{
    if(n==nullptr) return 0; // Si no hi ha node, el balanç serà 0.
    // Per trobar el balanç fem la diferència entre el height del fill esquerra i fill dret del node.
    int balanceNode = ((n->getLeft())->height())-((n->getRight())->height()) ; 
    return balanceNode;
}

/* Balanceja l'arbre. */
template <class K, class V>
BinaryTreeNode<K,V>* AVLTree<K,V>::balanceAVL(BinaryTreeNode<K,V>* temp){
    int balance = findBalance(temp); // Trobem el balanç del node.
    // Si el balanç és <-1 o >1, balancegem l'arbre.
    if (balance > 1){ 
        // Comprovem on hi ha desbalanceig i fem rotacions.
        if (findBalance(temp->getLeft()) > 0){ 
            temp = rotacioEsquerra(temp);
        }else{
            temp = rotacioEsquerraDreta(temp);
        }
    }else if (balance < -1){
        // Comprovem on hi ha desbalanceig i fem rotacions.
        if (findBalance(temp->getRight()) > 0){
            temp = rotacioDretaEsquerra(temp);
        }else{
            temp = rotacioDreta(temp);
        }
    }
    return temp; // Retornem el node amb tot balancejat.
}

/* Afegeix un node a l'arbre balancejat. */
template <class K, class V>
BinaryTreeNode<K,V>* AVLTree<K,V>::addAux (const K& k, const V& value, BinaryTreeNode<K,V>* t, BinaryTreeNode<K,V>* temp){
    if (t == nullptr){ 
        t = new BinaryTreeNode<K,V>(k); // Creem un nou node amb la key rebuda per paràmetre.
        t->addValue(value); // Afegim els values al node.
        t->setParent(temp); // Fem pare del nou node el node anterior a nullptr, guardat a temp.
        cout<<"Inserta a l’arbre element "<<k<<endl;
        return t; // Retornem el nou node.
    }else{
        temp = t; // Guardem el node actual en temp, per poder assignar-ho després com a pare si resulta ser el següent node nullptr.
        if (k < t->getKey()) { // Si la key del nou node és menor a la key del node actual, anem a l'esquerra.
            t->setLeft(addAux(k,value,t->getLeft(),temp)); // En aquest cas, el node esquerre serà el nou node.
            t = balanceAVL(t); // < Balancegem l'arbre.
        }else{ // Si la key del nou node és major, anem a la dreta.
            t->setRight(addAux(k,value,t->getRight(),temp)); // En aquest cas, el node dret serà el nou node.
            t = balanceAVL(t); // < Balancegem l'arbre.
        }   
    }
    return t; // Retornem el node amb tots els enllaços.
}