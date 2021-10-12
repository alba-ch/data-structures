/* Classe LinkedDeque */

#include <iostream>
using namespace std;

#ifndef LINKEDDEQUE_H
#define LINKEDDEQUE_H
#include "DoubleNode.h"
template <class E>

class LinkedDeque{
public: 
    LinkedDeque();
    virtual ~LinkedDeque(); // elimina tots els elements de la cua i la deixa buida. 
    LinkedDeque(const LinkedDeque<E>& q); // constructor còpia
    
    void enqueueFront(E& f);
    void enqueueBack(E& f);
    void dequeueFront();
    void dequeueBack();

    bool isEmpty(); // retorna true si la LinkedDeque està buida, false en cas contrari.
    void print(); // imprimeix per consola tots els elements de la LinkedDeque.
    
    const E& getFront();
    const E& getBack();
    
    int size();

private:
    int _size;
    DoubleNode<E>* _front;
    DoubleNode<E>* _rear;

};

// Implementació dels mètodes de LinkedDeque (amb template)

template <class E>
LinkedDeque<E>::LinkedDeque(){
    _front = nullptr; // _rear i _front són punters, els inicialitzem com nullptr.
    _rear = nullptr;
    _size = 0;
}


template <class E>
LinkedDeque<E>::~LinkedDeque(){ // Elimina tots els elements de la cua i la deixa buida.
    DoubleNode<E> *i = _front; // Utilitzem dos auxiliars, 'i' i 'temp', 'i' per recórrer els nodes
    DoubleNode<E> *temp;       // i 'temp' anar-los eliminant.
    while(i != nullptr){
        temp = i;
        i = i->getNext();
        cout<<"He eliminat: "<<temp->getElement()<<" ";
        delete temp;
    }
}  

template <class E>
LinkedDeque<E>::LinkedDeque(const LinkedDeque<E>& q){
    if(_front == nullptr){ // Si el LinkedDeque esta buit, la còpia també.
        q._front = q._rear = nullptr;
    }else{
        DoubleNode<E> *i = new DoubleNode<E>;
        i = _front;
        while(i->getNext()!= nullptr){
            i = i->setNext(i);
            q.enqueueBack(i->getElement()); // Fem una còpia de cada element a la nova llista.
        }
    }
}

template <class E>
void LinkedDeque<E>::enqueueFront(E& f){
    DoubleNode<E> *n = new DoubleNode<E>(f); // Creem el node al heap.
    if(isEmpty()){ // Si està buida el nou punter serà tant el rear com el front.
        _rear = n;
        _front = n;
    }else{
        n->setNext(_front); // Canviem el next del node, aquest apuntarà al _front actual.
        _front->setPrevious(n); // Després canviem el prev del _front, que fins ara era nullptr, per que apunti al nou node.
        _front = n; // Fem que el node sigui el nou front.
    }
    _size++; // Incrementa el tamany de la cua.
}

template <class E>
void LinkedDeque<E>::enqueueBack(E& f){
    DoubleNode<E> *n = new DoubleNode<E>(f);
    if(isEmpty()){ // Si està buida el nou punter serà tant el rear com el front.
        _rear = n; 
        _front = n;
    }else{
        n->setPrevious(_rear); // El prev del nou punter apuntarà al que fins ara era el _rear.
        _rear->setNext(n); // Canviem el next del que fins ara era _rear perquè apunti al nou node.
        _rear = n; // _rear serà ara el node que hem creat.
    }
    _size++; // Incrementa el tamany de la cua.
}

template <class E>
void LinkedDeque<E>::dequeueFront(){ 
    if(isEmpty()){
        throw invalid_argument("No hi ha elements a la llista"); // EXCEPCIÓ
    }else{
        DoubleNode<E> *aux = _front; // Creem un node auxiliar per eliminar correctament el node, que es troba al heap.
        _front = aux->getNext(); // Fem _front al node següent del que anem a eliminar.
        delete aux; // Eliminem el node
        _size--; // Disminueix el size
    }
}

template <class E>
void LinkedDeque<E>::dequeueBack(){ // El mateix que dequeFront però fent rear al previous del actual rear.
    if(isEmpty()){
        throw invalid_argument("No hi ha elements a la llista"); // EXCEPCIÓ
    }else{
        DoubleNode<E> *aux = _rear;
        _rear = aux->getPrevious();
        _rear->setNext(nullptr);
        delete aux;
        _size--;
    }
}

template <class E>
bool LinkedDeque<E>::isEmpty(){
    return (_front == nullptr); // retorna true si la LinkedDeque està buida, false en cas contrari.
} 

template <class E>
void LinkedDeque<E>::print(){  
    if(isEmpty()){
       throw invalid_argument("[] (L’estructura està buida)"); // EXCEPCIÓ
    }else{
        cout<<"["<<_front->getElement();
        DoubleNode<E> *i = _front->getNext();
        while(i != nullptr){ // Mentre el _next del node sigui diferent a nullptr (fins que arribi al _rear).     
            cout<<", "<<i->getElement(); 
            i = i->getNext();
        }
        cout<<"]\n"<<endl;
    }
} 

template <class E>
const E& LinkedDeque<E>::getFront(){
    if(isEmpty()){
        throw invalid_argument("No hi ha elements a la llista"); // EXCEPCIÓ
    }
    return _front->getElement();
}

template <class E>
const E& LinkedDeque<E>::getBack(){
    if(isEmpty()){
        throw invalid_argument("No hi ha elements a la llista"); // EXCEPCIÓ
    }
    return _rear->getElement();
}

template <class E>
int LinkedDeque<E>::size(){
    return _size;
}

#endif /* ARRAYDEQUE_H */

