/* Classe BinaryTreeNode */

/*/ COST COMPUTACIONAL:
 * BinaryTreeNode: O(1)
 * BinaryTreeNode (constructor còpia): O(n)
 * ~BinaryTreeNode (destructor): O(n)
 * setKey: O(1)
 * setValues: O(1)
 * setLeft: O(1)
 * setRight: O(1)
 * setParent: O(1)
 * getKey: O(1)
 * getValues: O(1)
 * getParent: O(1)
 * getLeft: O(1)
 * getRight: O(1)
 * isRoot: O(1)
 * hasLeft: O(1)
 * hasRight: O(1)
 * isLeaf: O(1)
 * addValue: O(1)
 * depth: O(n) en el pitjor cas
 * height: O(n) en el pitjor cas
 * operator==: O(1)
/*/

#ifndef BINARYTREENODE_H
#define BINARYTREENODE_H
#include <valarray>
#include <vector>
#include <stdexcept>
#include <iostream>
using namespace std;

template <class K, class V>
class BinaryTreeNode{
public:
    BinaryTreeNode(const K& key); // Constructor
    BinaryTreeNode(const BinaryTreeNode<K,V>& orig); // Constructor còpia
    virtual ~BinaryTreeNode(); // Destructor

    /* Modificadors */
    void setKey(K k); 
    void setValues(vector<V> v); 
    void setLeft(BinaryTreeNode<K,V>* n);
    void setRight(BinaryTreeNode<K,V>* n);
    void setParent(BinaryTreeNode<K,V>* n);
    
    /* Consultors */
    const K& getKey() const;
    const vector<V>& getValues() const;
    BinaryTreeNode<K,V>* getParent() const;
    BinaryTreeNode<K,V>* getLeft() const;
    BinaryTreeNode<K,V>* getRight() const;
  
    /* Operacions */
    bool isRoot() const; // True si el node és root, false cas contrari.
    bool hasLeft() const; // True si el node té fill esquerra, false cas contrari.
    bool hasRight() const; // True si el node és fill dret, false cas contrari.
    bool isLeaf() const; // True si el node és leaf, false cas contrari.
    void addValue(const V& v); // Afegeix un objecte al vector values.
    int depth() const; // Calcula el depth de l'arbre.
    int height() const; // Calcula l'altura de l'arbre.
    bool operator==(const BinaryTreeNode<K,V>& node) const; // Compara dos nodes i determina si són iguals - true.
 
 private:
    K key; // Key del node - <string Data>
    vector<V> values; // Objectes adjacents al node - <objectes Transaction>
    BinaryTreeNode<K,V>* parent; // Punter al pare del node
    BinaryTreeNode<K,V>* left; // Punter al node esquerra del node
    BinaryTreeNode<K,V>* right; // Punter al node dreta del node
};

#endif /* BINARYTREENODE_H */

/* Construeix un nou node de l’arbre binari, passant com a paràmetre una clau */
template <class K, class V>
BinaryTreeNode<K,V>::BinaryTreeNode(const K& key){
    this->key = key;
    this->parent = nullptr;
    this->left = nullptr;
    this->right = nullptr;
}

/* Construeix una còpia del node partir del node original rebut per paràmetre */
template <class K, class V>
BinaryTreeNode<K,V>::BinaryTreeNode(const BinaryTreeNode<K,V>& orig):BinaryTreeNode(orig.key){ 
    this->values = orig.values; // Copiem el vector values
    if(orig.left != nullptr){ // Si l'arbre orig té fill esquerra, fem una còpia.
        this->left = new BinaryTreeNode<K,V>(*orig.left);
        this->left->setParent(this); // Assignem al node actual pare del fill.
    }
    if(orig.right != nullptr){ // Si l'arbre orig té fill dret, fem una còpia.
        this->right = new BinaryTreeNode<K,V>(*orig.right);
        this->right->setParent(this); // Assignem al node actual pare del fill.
    }
}

/* Destrueix els nodes fills.*/
template <class K, class V>
BinaryTreeNode<K,V>::~BinaryTreeNode(){
    cout << "Eliminant BinaryTreeNode " << this->key << "\n";
    delete left; // Destruïm el node esquerra, cridarà al seu destructor i destruirà els fills de manera succesiva.
    delete right; // Destruïm el node dret i tots els fills.
}

 /* --------- Operacions --------- */

/* Retorna cert si el node és el root de l'arbre binari de cerca, fals altrament */
template <class K, class V>
bool BinaryTreeNode<K,V>::isRoot() const{
    return (this->parent == nullptr);
}

/* Retorna cert si el node té un fill esquerre, fals altrament */
template <class K, class V>
bool BinaryTreeNode<K,V>::hasLeft() const{
    return (this->left != nullptr);
}

/* Retorna cert si el node té un fill dret, fals altrament */
template <class K, class V>
bool BinaryTreeNode<K,V>::hasRight() const{
    return (this->right != nullptr);
}

/* Retorna cert si el node és una fulla de l'arbre binari de cerca, fals altrament */
template <class K, class V>
bool BinaryTreeNode<K,V>::isLeaf() const{
    return (left == nullptr && right == nullptr); // Serà fulla si no té node esquerra ni dret.
}

/* Afegeix un valor a la llista de valors */
template <class K, class V>
void BinaryTreeNode<K,V>::addValue(const V& v){
    values.push_back(v);
}

/* Retorna la profunditat del node en l'arbre binari de cerca. Convindrem que el root té sempre
profunditat 0. Aquesta funció s’ha d’implementar de forma RECURSIVA */
template <class K, class V>
int BinaryTreeNode<K,V>::depth() const{
    if (isRoot()){ // Si el node és root, el depth és zero.
        return 0;
    }else{
        return 1 + parent->depth(); // Retornem 1 + el depth total, que es calcularà de manera recursiva.
    }
}

/* Retorna l'alçada del node en l'arbre de cerca binari. Convindrem que les fulles sempre tenen
alçada 1. Aquesta funció s’ha d’implementar de forma RECURSIVA */
template <class K, class V>
int BinaryTreeNode<K,V>::height() const{
    if (this == nullptr){ 
        return 0;
    }else{
        int rightHeight = right->height(); // Trobem el height per la dreta del node
        int leftHeight = left->height(); // Trobem el height per l'esquerra del node
        
        if(rightHeight<leftHeight){ // Retornem el major height + 1.
            return leftHeight+1;
        }else{
            return rightHeight+1;
        }
    }
}

/* (Sobrecarrega de l'operador d'igualtat) Retorna cert si dos nodes són iguals: tenen la mateixa clau
i els mateixos valors */
template <class K, class V>
bool BinaryTreeNode<K,V>::operator==(const BinaryTreeNode<K,V>& node) const{
    return (node.values == this->values && node.key == this->key);
}

 /* --------- Modificadors --------- */

template <class K, class V>
void BinaryTreeNode<K,V>::setKey(K k){
    this->key = k;
}

template <class K, class V>
void BinaryTreeNode<K,V>::setValues(vector<V> v){
    this->values = v;
}

template <class K, class V>
void BinaryTreeNode<K,V>::setLeft(BinaryTreeNode<K,V>* n){
    this->left = n;
}

template <class K, class V>
void BinaryTreeNode<K,V>::setRight(BinaryTreeNode<K,V>* n){
    this->right = n;
}

template <class K, class V>
void BinaryTreeNode<K,V>::setParent(BinaryTreeNode<K,V>* n){
    this->parent = n;
}
 
 /* --------- Consultors --------- */

/* Retorna la clau del node (atribut key) */
template <class K, class V>
const K& BinaryTreeNode<K,V>::getKey() const{
    return this->key;
}

/* Retorna el vector de valors (atribut values) */
template <class K, class V>
const vector<V>& BinaryTreeNode<K,V>::getValues() const{
    return this->values;
}

/* Retorna el pare del node (atribut parent) */
template <class K, class V>
BinaryTreeNode<K,V>* BinaryTreeNode<K,V>::getParent() const{
    return this->parent;
}

/* Retorna el node esquerre (atribut left) */
template <class K, class V>
BinaryTreeNode<K,V>* BinaryTreeNode<K,V>::getLeft() const{
    return this->left;
}

/* Retorna el node dret (atribut right) */
template <class K, class V>
BinaryTreeNode<K,V>* BinaryTreeNode<K,V>::getRight() const{
    return this->right;
}