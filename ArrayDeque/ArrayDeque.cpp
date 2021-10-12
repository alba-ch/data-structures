// Implementació dels mètodes de ArrayDeque

#include "ArrayDeque.h"
#include <iostream>
using namespace std;

ArrayDeque::ArrayDeque(const int _max_size) {
    this->_max_size = _max_size;
    this->_size = 0;
    front = 0;
    rear = -1;
    _data = {0};
}

void ArrayDeque::enqueueBack(const int key){
    if (isFull()) {
        throw invalid_argument("L’estructura està plena");
    }else{
    // Comprovem que rear no passa la mida de la cua, en aquest cas torna al principi.
        rear = (rear + 1) % _max_size;
    // Incrementem la mida de la cua.
        _size++;
    // Afegim el nou rear.
        _data[rear] = key;
        cout<<"Element "<<key<<" agregat\n"<<endl;
    }
}

void ArrayDeque::enqueueFront(const int key){
    if (isFull()){
        throw invalid_argument("L’estructura està plena");
    }else{
        // Comprovem que rear no passa la mida de la cua, en aquest cas torna al principi.
        front = (front - 1) % _max_size;  
        // Incrementem la mida de la cua.
        _size++;
        // Afegim el nou front.
        _data[front] = key; 
        cout<<"Element "<<key<<" agregat\n"<<endl;
        
    }
}

void ArrayDeque::print(){
    if(isEmpty()){
        throw invalid_argument("[] (L’estructura està buida)");
    }else{
        cout<<"["<<_data[front];
        // Imprimim des del front fins el rear, ambdós inclosos.
        for (int i = (front+1); i < (rear+1); i++){ // Comencem amb front+1 perquè ja em imprés el primer element.
            cout <<","<< _data[i];
        }   
        cout<<"]\n"<<endl;
    }
}

void ArrayDeque::dequeueBack(){
    if (isEmpty()){
        throw invalid_argument("L’estructura està buida");
    }else{
        cout<<"Element "<<_data[rear]<<" eliminat.\n"<<endl;
        // Comprovem que rear no passa la mida de la cua, en aquest cas torna al principi.
        rear = (rear - 1) % _max_size; 
        // Disminuim la mida de la cua.
        _size--;
    }
}

void ArrayDeque::dequeueFront(){
    if (isEmpty()){
        throw invalid_argument("L’estructura està buida");
    }else{
        cout<<"Element "<<_data[front]<<" eliminat.\n"<<endl;
        // Comprovem que rear no passa la mida de la cua, en aquest cas torna al principi.
        front = (front + 1) % _max_size;  
        // Disminuim la mida de la cua.
        _size--;
    }  
}

bool ArrayDeque::isEmpty(){
    return (_size == 0);
}

bool ArrayDeque::isFull(){
    return (_size == _max_size);
}

const int ArrayDeque::getBack(){
    if(isEmpty()){
        throw invalid_argument("No hi ha cap valor.");
    }
    return _data[rear];
}

const int ArrayDeque::getFront(){
    if (isEmpty()){
        throw invalid_argument("No hi ha cap valor.");
    }
    return _data[front];
}