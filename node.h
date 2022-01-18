#ifndef NODE_H
#define NODE_H

template <typename T>
struct Node {
    T data;
    Node<T>* next;
    Node<T>* prev;

    Node(){ 
        // TODO
    }

    Node(T value){
        // TODO
    }

    void killSelf(){
        // TODO      
    }    
};

#endif