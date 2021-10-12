/* Classe ArrayDeque */

#ifndef ARRAYDEQUE_H
#define ARRAYDEQUE_H

#include <vector>

class ArrayDeque{
public:
    ArrayDeque(const int);
    void enqueueBack(const int key);
    void dequeueFront();
    bool isFull();
    bool isEmpty();
    void print();
    const int getFront();
    void enqueueFront(const int);
    void dequeueBack();
    const int getBack();
private:
    int _max_size;
    int _size;
    std::vector<int> _data;
    // Atributs creats per fer un array circular:
    int front;
    int rear;
};

#endif /* ARRAYDEQUE_H */

