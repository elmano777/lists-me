#ifndef DOUBLY_H
#define DOUBLY_H
#include <iostream>
#include "list.h"

// TODO: Implement all methods
template <typename T>
class DoubleList : public List<T> {
    private:
        Node<T>* head;
        Node<T>* tail;
        int nodes;
    public:
        DoublyList() : List<T>() {}

        ~DoublyList(){ 
         	// TODO            
        }
        
};
#endif