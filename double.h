#ifndef DOUBLY_H
#define DOUBLY_H
#include "list.h"
#include <iostream>

template <typename T> class DoubleList : public List<T> {
private:
  struct Node {
    T data;
    Node *next;
    Node *prev;

    Node() {
      next = nullptr;
      prev = nullptr;
    }

    Node(T value) {
      data = value;
      next = nullptr;
      prev = nullptr;
    }

    void killSelf() {
      if (next) {
        next->killSelf();
      }
      delete this;
    }
  };

private:
  Node *head;
  Node *tail;
  int nodes;

public:
  DoubleList() : List<T>() {
    head = nullptr;
    tail = nullptr;
    nodes = 0;
  }

  ~DoubleList() {
    if (head) {
      head->killSelf();
    }
  }

  T front() {
    if (is_empty()) {
      throw std::out_of_range("List is empty");
    }
    return head->data;
  }

  T back() {
    if (is_empty()) {
      throw std::out_of_range("List is empty");
    }
    return tail->data;
  }

  void push_front(T data) {
    Node *newNode = new Node(data);

    if (is_empty()) {
      head = newNode;
      tail = newNode;
    } else {
      newNode->next = head;
      head->prev = newNode;
      head = newNode;
    }
    nodes++;
  }

  void push_back(T data) {
    Node *newNode = new Node(data);

    if (is_empty()) {
      head = newNode;
      tail = newNode;
    } else {
      tail->next = newNode;
      newNode->prev = tail;
      tail = newNode;
    }
    nodes++;
  }

  T pop_front() {
    if (is_empty()) {
      throw std::out_of_range("List is empty");
    }

    T data = head->data;

    if (head == tail) {
      delete head;
      head = nullptr;
      tail = nullptr;
    } else {
      Node *temp = head;
      head = head->next;
      head->prev = nullptr;
      delete temp;
    }
    nodes--;
    return data;
  }

  T pop_back() {
    if (is_empty()) {
      throw std::out_of_range("List is empty");
    }

    T data = tail->data;

    if (head == tail) {
      delete tail;
      head = nullptr;
      tail = nullptr;
    } else {
      Node *temp = tail;
      tail = tail->prev;
      tail->next = nullptr;
      delete temp;
    }
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

    Node *newNode = new Node(data);

    Node *temp;
    if (pos <= nodes / 2) {
      temp = head;
      for (int i = 0; i < pos; i++) {
        temp = temp->next;
      }
    } else {
      temp = tail;
      for (int i = nodes - 1; i >= pos; i--) {
        temp = temp->prev;
      }
    }

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

    Node *temp;
    if (pos <= nodes / 2) {
      temp = head;
      for (int i = 0; i < pos; i++) {
        temp = temp->next;
      }
    } else {
      temp = tail;
      for (int i = nodes - 1; i > pos; i--) {
        temp = temp->prev;
      }
    }

    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    delete temp;

    nodes--;
    return true;
  }

  T &operator[](int pos) {
    if (pos < 0 || pos >= nodes) {
      throw std::out_of_range("Index out of range");
    }

    Node *temp;
    if (pos <= nodes / 2) {
      temp = head;
      for (int i = 0; i < pos; i++) {
        temp = temp->next;
      }
    } else {
      temp = tail;
      for (int i = nodes - 1; i > pos; i--) {
        temp = temp->prev;
      }
    }

    return temp->data;
  }

  bool is_empty() { return head == nullptr; }

  int size() { return nodes; }

  void clear() {
    if (head) {
      head->killSelf();
      head = nullptr;
      tail = nullptr;
      nodes = 0;
    }
  }

  void sort() {
    if (is_empty() || size() == 1) {
      return;
    }

    bool swapped;
    Node *current;
    Node *last = nullptr;

    do {
      swapped = false;
      current = head;

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

    Node *current = head;
    while (current->next != nullptr) {
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

    Node *current = head;
    Node *temp = nullptr;

    tail = head;

    while (current != nullptr) {
      temp = current->prev;
      current->prev = current->next;
      current->next = temp;
      current = current->prev;
    }

    head = temp->prev;
  }

  std::string name() { return "DoubleList"; }
};
#endif
