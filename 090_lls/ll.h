#ifndef _LL_H_
#define _LL_H_
#include <assert.h>

#include <cstdlib>
#include <exception>
#include <iostream>

//YOUR CODE GOES HERE
template<typename T>
class LinkedList
{
 private:
  class Node
  {
   public:
    T data;
    Node * prev;
    Node * next;
    Node() : prev(NULL), next(NULL) {}
    Node(T data, Node * prev, Node * next) : data(data), prev(prev), next(next) {}
    Node(T data) : data(data), prev(NULL), next(NULL) {}
  };
  Node * head;
  Node * tail;
  int size;

 public:
  LinkedList() : head(NULL), tail(NULL), size(0) {}

  LinkedList(const LinkedList<T> & rhs) : head(NULL), tail(NULL), size(0) {
    if (rhs.head != NULL) {
      Node * rCurr = rhs.head;
      head = new Node(rCurr->data);
      Node * lCurr = head;
      size++;
      while (rCurr->next != NULL) {
        lCurr->next = new Node(rCurr->next->data);
        lCurr->next->prev = lCurr;
        lCurr = lCurr->next;
        rCurr = rCurr->next;
        size++;
      }
      tail = lCurr;
    }
    else {
    }
  }

  LinkedList & operator=(const LinkedList<T> & rhs) {
    if (this != &rhs) {
      LinkedList<T> temp(rhs);

      Node * now = tail;
      while (now != NULL) {
        Node * next = now->prev;
        delete now;
        now = next;
      }

      head = temp.head;
      tail = temp.tail;
      size = temp.size;

      temp.head = NULL;
      temp.tail = NULL;
    }
    return *this;
  }

  T & operator[](int index) {
    if (index >= 0 && index < size) {
      Node * curr = head;
      for (int i = 0; i < index; i++) {
        curr = curr->next;
      }
      return curr->data;
    }
    else {
      throw std::out_of_range("Out of Bounds");
    }
  }

  const T & operator[](int index) const {
    if (index >= 0 && index < size) {
      Node * curr = head;
      for (int i = 0; i < index; i++) {
        curr = curr->next;
      }
      return curr->data;
    }
    else {
      throw std::out_of_range("Out of Bounds");
    }
  }

  int find(const T & item) {
    for (int i = 0; i < size; i++) {
      if ((*this)[i] == item) {
        return i;
      }
    }
    return -1;
  }

  void addFront(const T & item) {
    Node * newHead = new Node(item);
    if (size == 0) {
      head = newHead;
      tail = head;
    }
    else {
      newHead->next = head;
      head->prev = newHead;
      head = newHead;
    }
    size++;
  }

  void addBack(const T & item) {
    Node * newTail = new Node(item);
    if (size == 0) {
      tail = newTail;
      head = tail;
    }
    else {
      newTail->prev = tail;
      tail->next = newTail;
      tail = newTail;
    }
    size++;
  }

  bool remove(const T & item) {
    int index = find(item);
    if (index != -1) {
      Node * curr = head;
      for (int i = 0; i < index; i++) {
        curr = curr->next;
      }
      if (curr->next != NULL) {
        curr->next->prev = curr->prev;
      }
      else {
        tail = curr->prev;
      }
      if (curr->prev != NULL) {
        curr->prev->next = curr->next;
      }
      else {
        head = curr->next;
      }
      delete curr;
      --size;

      return true;
    }
    else {
      return false;
    }
  }

  int getSize() const { return size; }

  void printList() {
    if (head == NULL) {
      std::cout << "[ "
                << " ]" << std::endl;
    }
    else {
      Node * curr = head;
      std::cout << "[ ";
      while (curr != NULL) {
        std::cout << curr->data << " ";
        curr = curr->next;
      }
      std::cout << "]" << std::endl;
      std::cout << "head: " << head->data;
      std::cout << " tail: " << tail->data << std::endl;
    }
  }

  ~LinkedList() {
    Node * now = tail;
    while (now != NULL) {
      Node * next = now->prev;
      delete now;
      now = next;
    }
  }
};
#endif
