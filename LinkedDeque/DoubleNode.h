/* Classe DoubleNode */

#ifndef DOUBLENODE_H
#define DOUBLENODE_H
template <class E>

class DoubleNode {
public:
    DoubleNode();
    DoubleNode(const E &e);
    virtual ~DoubleNode();
    const E& getElement() const;
    DoubleNode<E>* getNext() const;
    void setNext(DoubleNode<E>* n); 
    DoubleNode<E>* getPrevious() const;
    void setPrevious(DoubleNode<E>* n); 
    
private:
    E _element;
    DoubleNode<E>* _next;
    DoubleNode<E>* _prev;
};

// Implementació dels mètodes de DoubleNode (amb template)

template <class E>
DoubleNode<E>::DoubleNode() {
    this->_element = 0;
    this->_next = nullptr;
    this->_prev = nullptr;
}

template <class E>
DoubleNode<E>::~DoubleNode() {
}

template <class E>
DoubleNode<E>::DoubleNode(const E &e){
    this->_element = e;
    this->_next = nullptr;
    this->_prev = nullptr;
}

template <class E>
const E& DoubleNode<E>::getElement() const{
    return _element;
}

template <class E>
DoubleNode<E>* DoubleNode<E>::getNext() const{
    return _next;
    
}

template <class E>
void DoubleNode<E>::setNext(DoubleNode<E>* n){ 
    this->_next = n;
}

template <class E>
DoubleNode<E>* DoubleNode<E>::getPrevious() const{
    return _prev;
}

template <class E>
void DoubleNode<E>::setPrevious(DoubleNode<E>* n){
    this->_prev = n;
}

#endif /* DOUBLENODE_H */

