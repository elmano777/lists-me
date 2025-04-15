#ifndef FORWARD_H
#define FORWARD_H
#include "list.h"
#include <iostream>

template <typename T> class ForwardList : public List<T> {
private:
  struct Node {
    T data;
    Node *next;

    Node() { next = nullptr; }

    Node(T value) {
      data = value;
      next = nullptr;
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
  int nodes;

public:
  ForwardList() : List<T>() {}

  ~ForwardList() {
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

    Node *temp = head;
    while (temp->next != nullptr) {
      temp = temp->next;
    }
    return temp->data;
  }

  void push_front(T data) {
    Node *newNode = new Node(data);
    newNode->next = head;
    head = newNode;
    nodes++;
  }

  void push_back(T data) {
    Node *newNode = new Node(data);

    if (is_empty()) {
      head = newNode;
    } else {
      Node *temp = head;
      while (temp->next != nullptr) {
        temp = temp->next;
      }
      temp->next = newNode;
    }
    nodes++;
  }

  T pop_front() {
    if (is_empty()) {
      throw std::out_of_range("List is empty");
    }

    T data = head->data;
    Node *temp = head;
    head = head->next;
    delete temp;
    nodes--;
    return data;
  }

  T pop_back() {
    if (is_empty()) {
      throw std::out_of_range("List is empty");
    }

    if (head->next == nullptr) {
      T data = head->data;
      delete head;
      head = nullptr;
      nodes--;
      return data;
    }

    Node *temp = head;
    while (temp->next->next != nullptr) {
      temp = temp->next;
    }

    T data = temp->next->data;
    delete temp->next;
    temp->next = nullptr;
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

    Node *newNode = new Node(data);
    Node *temp = head;

    for (int i = 0; i < pos - 1; i++) {
      temp = temp->next;
    }

    newNode->next = temp->next;
    temp->next = newNode;
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

    Node *temp = head;
    for (int i = 0; i < pos - 1; i++) {
      temp = temp->next;
    }

    Node *toDelete = temp->next;
    temp->next = toDelete->next;
    delete toDelete;
    nodes--;
    return true;
  }

  T &operator[](int pos) {
    if (pos < 0 || pos >= nodes) {
      throw std::out_of_range("Index out of range");
    }

    Node *temp = head;
    for (int i = 0; i < pos; i++) {
      temp = temp->next;
    }

    return temp->data;
  }

  bool is_empty() { return head == nullptr; }

  int size() { return nodes; }

  void clear() {
    if (head) {
      head->killSelf();
      head = nullptr;
      nodes = 0;
    }
  }

  void sort() {
    if (is_empty() || size() == 1) {
      return;
    }

    bool swapped;
    for (int i = 0; i < nodes - 1; i++) {
      swapped = false;
      Node *current = head;
      Node *prev = nullptr;

      for (int j = 0; j < nodes - i - 1; j++) {
        if (current->data > current->next->data) {
          Node *temp = current->next;
          current->next = temp->next;
          temp->next = current;

          if (prev == nullptr) {
            head = temp;
          } else {
            prev->next = temp;
          }

          prev = temp;
          swapped = true;
        } else {
          prev = current;
          current = current->next;
        }
      }

      if (!swapped) {
        break;
      }
    }
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

    Node *prev = nullptr;
    Node *current = head;
    Node *next = nullptr;

    while (current != nullptr) {
      next = current->next;
      current->next = prev;
      prev = current;
      current = next;
    }

    head = prev;
  }

  std::string name() { return "ForwardList"; }
};

#endif
