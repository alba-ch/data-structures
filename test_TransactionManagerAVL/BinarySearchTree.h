/* Classe BinarySearchTree */

/*/ COST COMPUTACIONAL:
 * BinarySearchTree: O(1)
 * BinarySearchTree (constructor còpia): O(n)
 * ~BinarySearchTree (destructor): O(n)
 * isEmpty: O(1)
 * height: O(n) en el pitjor cas
 * size: O(1)
 * sizeAux: O(n) en el pitjor cas
 * add: O(1)
 * addAux: O(n) en el pitjor cas
 * showKeysPreorder: O(n) en el pitjor cas
 * showKeysInorder: O(n) en el pitjor cas
 * showKeysPostorder: O(n) en el pitjor cas
 * equals: O(1)
 * equalsAux: O(n) en el pitjor cas
 * has: O(1)
 * hasAux: O(n) en el pitjor cas
 * valuesOf: O(n) en el pitjor cas
 * getLeafs: O(1)
 * getLeafsAux: O(n) en el pitjor cas
 * findAux: O(n) en el pitjor cas 
/*/

#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

#include "BinaryTreeNode.h"

template <class K, class V>
class BinarySearchTree{
public:
    BinarySearchTree(); // Constructor
    BinarySearchTree(const BinarySearchTree<K, V>& orig); // Constructor còpia
    virtual ~BinarySearchTree(); // Destructor

    /* Informació sobre l'arbre */
    bool isEmpty() const;
    int height() const;
    int size() const;
    int sizeAux(BinaryTreeNode<K,V>* n) const;
    
    /* Afegir un element */
    BinaryTreeNode<K,V>* add(const K& k, const V& value);
    virtual BinaryTreeNode<K,V>* addAux(const K& k, const V& value, BinaryTreeNode<K,V>* t, BinaryTreeNode<K,V>* temp = nullptr); // Mètode propi

    /* Imprimir elements */
    void showKeysPreorder(const BinaryTreeNode<K,V>* n = nullptr) const;
    void showKeysInorder(const BinaryTreeNode<K,V>* n = nullptr) const;
    void showKeysPostorder(const BinaryTreeNode<K,V>* n = nullptr) const;

    /* Informació sobre el contingut */
    bool equals(const BinarySearchTree<K, V>& other) const;
    bool equalsAux(const BinaryTreeNode<K, V>* other, const BinaryTreeNode<K,V>* n) const; // Mètode propi
    bool has(const K& k) const;
    bool hasAux(BinaryTreeNode<K,V>* n,const K& k) const; // Mètode propi
    const vector<V>& valuesOf(const K& k) const;
    const vector<BinaryTreeNode<K, V>*> getLeafs() const;
    void getLeafsAux(BinaryTreeNode<K, V>* n, vector<BinaryTreeNode<K, V>*>& v) const; // Mètode propi
    
    BinaryTreeNode<K,V>* findAux(BinaryTreeNode<K, V>* n, const K& k) const; // Mètode propi
    
protected:
    BinaryTreeNode<K,V>* p_root; // Punter al node root de l'arbre
    BinaryTreeNode<K,V>* find(const K& k) const; // Troba un node donat el seu key
};

#endif /* BINARYSEARCHTREE_H */

/*Construeix l’arbre buit.*/
template <class K, class V>
BinarySearchTree<K,V>::BinarySearchTree(){
    cout<<"Arbre binari creat"<<endl;
    p_root = nullptr;
}

/*Construeix una còpia de l'arbre partir del node original rebut per paràmetre*/
template <class K, class V>
BinarySearchTree<K,V>::BinarySearchTree(const BinarySearchTree<K, V>& orig){
    // Copia el root de orig, que ja conté els enllaços als nodes que formen l'arbre.
    this->p_root = new BinaryTreeNode<K,V>(*orig.p_root); 
    cout<<"Arbre binari copiat"<<endl;
}

/*Destrueix els nodes de l’arbre binari, començant pel root. */
template <class K, class V>
BinarySearchTree<K,V>::~BinarySearchTree(){ 
    cout<<"Destruint arbre binari"<<endl;
    if(p_root){
        delete p_root; // Eliminem el root, que crida al destructor del node i els elimina tots succesivament.
    }
}

/*Retorna cert si l’arbre binari està buit, fals en cas contrari */
template <class K, class V>
bool BinarySearchTree<K,V>::isEmpty() const{
    return (p_root==nullptr); // L'arbre està buit si no té root.
}

/*Retorna el nombre de nodes que hi ha l’arbre binari. Aquesta funció recorre els nodes
per calcular quants nodes té l’arbre binari.*/
template <class K, class V>
int BinarySearchTree<K,V>::size() const{
    return sizeAux(p_root);
}

template <class K, class V>
int BinarySearchTree<K,V>::sizeAux(BinaryTreeNode<K,V>* n) const{
    if (n == nullptr) return 0; // Si p_root és zero, no hi ha cap node a l'arbre, per tant size és 0.
    else { 
        // Retorna la suma del size de la branca esquerra i de la dreta sumant 1 recursivament.
        return(size(n->getLeft()) + size(n->getRight()) + 1);  
    }
}

/*Retorna un enter amb l’alçada de l’arbre binari de cerca, és a dir, l'alçada del root.
Aquesta funció s’ha d’implementar de forma RECURSIVA*/
template <class K, class V>
int BinarySearchTree<K,V>::height() const{
    if (isEmpty()){
        throw invalid_argument("Arbre binari buit.");
    }
    return p_root->height(); // Cridem el mètode height de p_root, que calcularà el height de tot l'arbre.
}

/*Afegeix un nou node a l’arbre binari de cerca*/
template <class K, class V>
BinaryTreeNode<K,V>* BinarySearchTree<K,V>::add(const K& k, const V& value){
    p_root = addAux(k,value,this->p_root); 
    return p_root;
}

template <class K, class V>
BinaryTreeNode<K,V>* BinarySearchTree<K,V>::addAux(const K& k, const V& value, BinaryTreeNode<K,V>* t, BinaryTreeNode<K,V>* temp){
    if (t == nullptr){ 
        t = new BinaryTreeNode<K,V>(k); // Creem un nou node amb la key rebuda per paràmetre.
        t->addValue(value); // Afegim els values al node.
        t->setParent(temp); // Fem pare del nou node el node anterior a nullptr, guardat a temp.
        cout<<"Inserta a l’arbre element "<<k<<endl;
        return t; // Retornem el nou node.
    }
    temp = t; // Guardem el node actual en temp, per poder assignar-ho després com a pare si resulta ser el següent node nullptr.
    if (k < t->getKey()) { // Si la key del nou node és menor a la key del node actual, anem a l'esquerra.
        t->setLeft(addAux(k,value,t->getLeft(),temp)); // En aquest cas, el node esquerre serà el nou node.
    }else{ // Si la key del nou node és major, anem a la dreta.
        t->setRight(addAux(k,value,t->getRight(),temp)); // En aquest cas, el node dret serà el nou node.
    }
    return t; // Retornem el node amb tots els enllaços.
}

/*Retorna cert si l’arbre binari de cerca té l'element indexat amb una certa clau, fals en
cas contrari. Aquesta funció s’ha d’implementar de forma RECURSIVA*/
template <class K, class V>
bool BinarySearchTree<K,V>::has(const K& k) const{
    return hasAux(p_root,k); // L'arbre conté el node si el troba a l'arbre.
}

template <class K, class V>
bool BinarySearchTree<K,V>::hasAux(BinaryTreeNode<K,V>* n,const K& k) const{
    // Si arribem a nullptr sense haver trobat el node, retornem fals.
    if(n == nullptr){ 
        return false;
    }
    // Si el key del node és igual a la key del node a trobar, l'hem trobat, retornem true.
    if(n->getKey()==k){ 
        return true;
    }
    // Fem una cerca recursiva entre els nodes des de p_root.
    if(k<n->getKey()){
        return hasAux(n->getLeft(),k);
    }else{
        return hasAux(n->getRight(),k);
    }    
}

/*Retorna el vector de valors (atribut values) d'un node de l'arbre amb una certa key
passada per paràmetre*/
template <class K, class V>
const vector<V>& BinarySearchTree<K,V>::valuesOf(const K& k) const{
    if(find(p_root,k)==nullptr){ // Si no troba el node, llença excepció.
        throw new invalid_argument(k + "no existeix.");
    }
    return find(p_root,k)->getValues(); // Trobem el node amb find i retornem els seus values.
}

/*Mostra per consola les claus i el contingut de les claus dels nodes seguint un
recorregut en preordre*/
template <class K, class V>
void BinarySearchTree<K,V>::showKeysPreorder(const BinaryTreeNode<K,V>* n) const{ 
    if(isEmpty())
        throw invalid_argument("L'arbre està buit.");
    if (n == nullptr){
        cout<<"{";
        showKeysPreorder(p_root);
        cout<<"}";
    }else{
        // Preorder -> root, left, right
        if(n == p_root) cout <<n->getKey(); // Si n és el primer element, no imprimim ','. 
        else cout <<","<< n->getKey(); // Si no és el primer element, imprimim la coma i el key.
        
        if (n->getLeft() != nullptr){ // Mentre hi hagi elements a l'esquerra
            showKeysPreorder(n->getLeft()); // Fem un recorregut recursiu imprimint cada element
        }
        if (n->getRight() != nullptr){ // Mentre hi hagi elements a la dreta
            showKeysPreorder(n->getRight()); // Fem un recurregut recursiu imprimint cada element
        }
    }
}

/*Mostra per consola les claus i el contingut les claus dels nodes seguint un recorregut
en inordre*/
template <class K, class V>
void BinarySearchTree<K,V>::showKeysInorder(const BinaryTreeNode<K,V>* n) const{
    if(isEmpty()){
        throw invalid_argument("L'arbre està buit.");
    }
    if (n == nullptr){
        cout<<"{";
        showKeysInorder(p_root);
        cout<<"}";
    }else{
        // Inorder -> left, root, right
        if (n->getLeft() != nullptr){ // Mentre hi hagi elements a l'esquerra
            showKeysInorder(n->getLeft()); // Fem un recorregut recursiu imprimint cada element
        }
        cout<<","<<n->getKey(); // Imprimim el key del node actual
        if (n->getRight() != nullptr){ // Mentre hi hagi elements a la dreta
            showKeysInorder(n->getRight()); // Fem un recorregut recursiu imprimint cada element
        }
    }
}
/*Mostra per consola les claus i el contingut les claus dels nodes seguint un recorregut
en postordre*/
template <class K, class V>
void BinarySearchTree<K,V>::showKeysPostorder(const BinaryTreeNode<K,V>* n) const{ 
    if(isEmpty()){
        throw invalid_argument("L'arbre està buit.");
    }
    if (n == nullptr){
        cout<<"{";
        showKeysPostorder(p_root);
        cout<<"}";
    }else{
        // Postorder -> left, right, root
        if (n->getLeft() != nullptr){ // Mentre hi hagi elements a l'esquerra
            showKeysPostorder(n->getLeft()); // Fem un recorregut recursiu imprimint cada element
        }
        if (n->getRight() != nullptr){ // Mentre hi hagi elements a la dreta
            showKeysPostorder(n->getRight()); // Fem un recorregut recursiu imprimint cada element
        }
        if(n == p_root) cout<<n->getKey(); // Si el node és el root, no imprimim cap coma
        else cout<<n->getKey()<<","; // En cas contrari, imprimim el key i una coma.
    }
}
/*Retorna cert si l’arbre binari intern és igual a l’arbre binari que es passa per
paràmetre, fals en cas contrari. Dos arbres són iguals si tots els seus nodes ho són*/
template <class K, class V>
bool BinarySearchTree<K,V>::equals(const BinarySearchTree<K, V>& other) const{
    return equalsAux(other.p_root, p_root);
}

template <class K, class V>
bool BinarySearchTree<K,V>::equalsAux(const BinaryTreeNode<K, V>* other, const BinaryTreeNode<K, V>* n) const{
    if(other == nullptr && n == nullptr){ // Si tots dos roots són nullptr, els arbres són iguals, tots dos són buits.
        return true;
    }else if(other != nullptr && n != nullptr){
        if (n->operator ==(*other)){ // Si el node n (arbre original) és igual que el node de l'altre arbre, fem una crida recursiva 
            return equalsAux(other->getLeft(), n->getLeft()) && equalsAux(other->getRight(), n->getRight()); // Comprovem que els altres nodes també són iguals
        }
    }
    return false; // Si arribem aquí significa que els dos nodes no són els dos ni nullptr ni iguals, són diferents, retornem fals.
}

/*Retorna un vector amb tots els nodes fulla de l'arbre. Implementat de forma RECURSIVA.*/
template <class K, class V>
const vector<BinaryTreeNode<K, V>*> BinarySearchTree<K,V>::getLeafs() const{
    vector<BinaryTreeNode<K, V>*> nodes; // Creem un vector on guardar els nodes que són leaf.
    getLeafsAux(p_root,nodes);
    return nodes;
}

template <class K, class V>
void BinarySearchTree<K,V>::getLeafsAux(BinaryTreeNode<K, V>* n, vector<BinaryTreeNode<K, V>*>& v) const{
    if(n==nullptr) return;
    if(n->isLeaf()) v.push_back(n); // Si el node és fulla, l'afegeix al vector dels nodes leaf.
    else{
        getLeafs(n->getLeft(),v); // Cerquem per l'esquerra.
        getLeafs(n->getRight(),v); // Cerquem per la dreta.
    }
}

/*Troba un element (indexat per la clau) de l’arbre binari de cerca i retorna el node si
el troba, en cas contrari retorna nullptr. Aquesta funció s’ha d’implementar de
forma ITERATIVA.*/
template <class K, class V>
BinaryTreeNode<K,V>* BinarySearchTree<K,V>::find(const K& k) const{    
    if(isEmpty()){
        throw invalid_argument ("Arbre binari buit.\n");
    }
    bool trobat = false;
    BinaryTreeNode<K, V>* temp = p_root; // Creem el node temporal 'temp' que comença pel root per iterar pels nodes de l'arbre.
    while(temp != nullptr && !trobat){
        if (k < temp->getKey()){ // Si el key del node és menor al de l'actual, cerquem per l'esquerra.
            temp = temp->getLeft();
        }else if(k > temp->getKey()){ // Si el key del node és major al de l'actual, cerquem per la dreta.
            temp = temp->getRight();
        }else{ // Si el key del node és igual al de l'actual, el node existeix a l'arbre, trobat = true.
            trobat = true;
        }
    }
    return temp; // Retornem el node trobat.
}