#ifndef CIRCULAR_H
#define CIRCULAR_H
#include <iostream>
#include "list.h"

template <typename T>
class CircularList : public List<T> {
    private:
        struct Node {
            T data;
            Node* next;
            Node* prev;

            Node() {
                next = this;
                prev = this;
            }

            Node(T value) {
                data = value;
                next = this;
                prev = this;
            }

            void killSelf() {
                if (next != this) {
                    next->killSelf();
                }
                delete this;
            }
        };

    private:
        Node* head;
        int nodes;

    public:
        CircularList() : List<T>() {
            head = new Node();
            nodes = 0;
        }

        ~CircularList() {
            if (head) {
                if (head->next != head) {
                    head->prev->next = nullptr;
                    head->next->killSelf();
                }
                delete head;
            }
        }

        T front() {
            if (is_empty()) {
                throw std::out_of_range("List is empty");
            }
            return head->next->data;
        }

        T back() {
            if (is_empty()) {
                throw std::out_of_range("List is empty");
            }
            return head->prev->data;
        }

        void push_front(T data) {
            Node* newNode = new Node(data);

            newNode->next = head->next;
            newNode->prev = head;
            head->next->prev = newNode;
            head->next = newNode;

            nodes++;
        }

        void push_back(T data) {
            Node* newNode = new Node(data);

            newNode->next = head;
            newNode->prev = head->prev;
            head->prev->next = newNode;
            head->prev = newNode;

            nodes++;
        }

        T pop_front() {
            if (is_empty()) {
                throw std::out_of_range("List is empty");
            }

            Node* temp = head->next;
            T data = temp->data;

            head->next = temp->next;
            temp->next->prev = head;
            delete temp;

            nodes--;
            return data;
        }

        T pop_back() {
            if (is_empty()) {
                throw std::out_of_range("List is empty");
            }

            Node* temp = head->prev;
            T data = temp->data;

            temp->prev->next = head;
            head->prev = temp->prev;
            delete temp;

            nodes--;
            return data;
        }

        bool insert(T data, int pos) {
            if (pos < 0 || pos > nodes) {
                return false;
            }

            if (pos == 0) {
                push_front(data);
                return true;
            }

            if (pos == nodes) {
                push_back(data);
                return true;
            }

            Node* temp = head->next;
            for (int i = 0; i < pos; i++) {
                temp = temp->next;
            }

            Node* newNode = new Node(data);
            newNode->next = temp;
            newNode->prev = temp->prev;
            temp->prev->next = newNode;
            temp->prev = newNode;

            nodes++;
            return true;
        }

        bool remove(int pos) {
            if (is_empty() || pos < 0 || pos >= nodes) {
                return false;
            }

            if (pos == 0) {
                pop_front();
                return true;
            }

            if (pos == nodes - 1) {
                pop_back();
                return true;
            }

            Node* temp = head->next;
            for (int i = 0; i < pos; i++) {
                temp = temp->next;
            }

            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            delete temp;

            nodes--;
            return true;
        }

        T& operator[](int pos) {
            if (pos < 0 || pos >= nodes) {
                throw std::out_of_range("Index out of range");
            }

            Node* temp = head->next;
            for (int i = 0; i < pos; i++) {
                temp = temp->next;
            }

            return temp->data;
        }

        bool is_empty() {
            return head->next == head;
        }

        int size() {
            return nodes;
        }

        void clear() {
            if (!is_empty()) {
                head->prev->next = nullptr;
                head->next->killSelf();

                head->next = head;
                head->prev = head;
                nodes = 0;
            }
        }

        void sort() {
            if (is_empty() || size() == 1) {
                return;
            }

            bool swapped;
            Node* current;
            Node* last = head;

            do {
                swapped = false;
                current = head->next;

                while (current->next != last) {
                    if (current->data > current->next->data) {
                        T temp = current->data;
                        current->data = current->next->data;
                        current->next->data = temp;
                        swapped = true;
                    }
                    current = current->next;
                }
                last = current;
            } while (swapped);
        }

        bool is_sorted() {
            if (is_empty() || size() == 1) {
                return true;
            }

            Node* current = head->next;
            while (current->next != head) {
                if (current->data > current->next->data) {
                    return false;
                }
                current = current->next;
            }

            return true;
        }

        void reverse() {
            if (is_empty() || size() == 1) {
                return;
            }

            Node* current = head;
            Node* temp;

            do {
                temp = current->next;
                current->next = current->prev;
                current->prev = temp;

                current = current->prev;
            } while (current != head);
        }

        std::string name() {
            return "CircularList";
        }
};

#endif
