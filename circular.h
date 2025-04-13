#ifndef CIRCULAR_H
#define CIRCULAR_H
#include <iostream>
#include "list.h"

// TODO: Implement all methods
template <typename T>
class CircularList : public List<T> {
    private:
        struct Node {
            T data;
            Node* next;
            Node* prev;

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

    private:
        Node* head;//sentinel
        int nodes;

    public:
        CircularList() : List<T>() { }

        ~CircularList(){
           // TODO
        }

         T front(){
            throw ("sin definir");
        }

        T back(){
            throw ("sin definir");
        }

        void push_front(T data){
            throw ("sin definir");
        }

        void push_back(T data){
            throw ("sin definir");
        }

        T pop_front(){
            throw ("sin definir");
        }

        T pop_back(){
            throw ("sin definir");
        }

        T insert(T data, int pos){
            throw ("sin definir");
        }

        bool remove(int pos){
            throw ("sin definir");
        }

        T& operator[](int pos){
            throw ("sin definir");
        }

        bool is_empty(){
            throw ("sin definir");
        }

        int size(){
            throw ("sin definir");
        }

        void clear(){
            throw ("sin definir");
        }

        void sort(){
            throw ("sin definir");
        }

        bool is_sorted(){
            throw ("sin definir");
        }

        void reverse(){
            throw ("sin definir");
        }

        std::string name(){
            return "ForwardList";
        }
};

#endif
