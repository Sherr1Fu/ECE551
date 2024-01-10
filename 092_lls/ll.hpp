#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <cstdlib>
#include <exception>

//YOUR CODE GOES HERE
class Tester;

template<typename T>
class LinkedList {
 public:
  class Node {
   public:
    T data;
    Node * next;
    Node * prev;
    Node() : data(T()), next(NULL), prev(NULL){};
    Node(T d, Node * n, Node * p) : data(d), next(n), prev(p){};
  };
  Node * head;
  Node * tail;

 public:
  LinkedList() : head(NULL), tail(NULL){};
  LinkedList(const LinkedList & rhs);
  LinkedList & operator=(const LinkedList & rhs);
  ~LinkedList();
  void addFront(const T & item);
  void addBack(const T & item);
  bool remove(const T & item);
  T & operator[](int index);
  const T & operator[](int index) const;
  int find(const T & item);
  int getSize() const;
  friend class Tester;
};

template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T> & rhs) : head(NULL), tail(NULL) {
  Node * ptr = rhs.head;
  while (ptr != NULL) {
    addBack(ptr->data);
    ptr = ptr->next;
  }
}
template<typename T>
LinkedList<T> & LinkedList<T>::operator=(const LinkedList<T> & rhs) {
  if (this != &rhs) {
    LinkedList<T> temp(rhs);
    Node * ptr = head;
    head = temp.head;
    temp.head = ptr;
    ptr = tail;
    tail = temp.tail;
    temp.tail = ptr;
    //std::swap(head, temp.head);
    //std::swap(tail, temp.tail);
  }
  /*  if (this != rhs) {
    while (head != NULL) {
      Node * ptr = head;
      head = head->next;
      delete ptr;
    }
    tail = NULL;
    Node * ptr = rhs.head;
    while (ptr != NULL) {
      addBack(ptr->data);
      ptr = ptr->next;
    }
    }*/
  return *this;
}
template<typename T>
LinkedList<T>::~LinkedList() {
  while (head != NULL) {
    Node * ptr = head;
    head = head->next;
    delete ptr;
  }
}
template<typename T>
void LinkedList<T>::addFront(const T & item) {
  Node * p = new Node(item, head, NULL);
  if (head == NULL) {
    tail = p;
  }
  else {
    head->prev = p;
  }
  head = p;
}
template<typename T>
void LinkedList<T>::addBack(const T & item) {
  Node * p = new Node(item, NULL, tail);
  if (tail == NULL) {
    head = p;
  }
  else {
    tail->next = p;
  }
  tail = p;
}
template<typename T>
bool LinkedList<T>::remove(const T & item) {
  Node * ptr = head;
  while (ptr != NULL) {
    if (ptr->data == item) {
      if (ptr->prev == NULL) {
        head = head->next;
        if (head == NULL) {
          tail = NULL;
        }
        else {
          head->prev = NULL;
        }
        delete ptr;
        return true;
      }
      if (ptr->next == NULL) {
        tail = tail->prev;
        tail->next = NULL;
        delete ptr;
        return true;
      }
      ptr->prev->next = ptr->next;
      ptr->next->prev = ptr->prev;
      delete ptr;
      return true;
    }
    ptr = ptr->next;
  }
  return false;
}
template<typename T>
T & LinkedList<T>::operator[](int index) {
  assert(index >= 0);
  Node * ptr = head;
  int i = 0;
  while (ptr != NULL) {
    if (i == index) {
      return ptr->data;
    }
    i++;
    ptr = ptr->next;
  }
  assert(false && "Index out of bounds");
}
template<typename T>
const T & LinkedList<T>::operator[](int index) const {
  assert(index >= 0);
  Node * ptr = head;
  int i = 0;
  while (ptr != NULL) {
    if (i == index) {
      return ptr->data;
    }
    i++;
    ptr = ptr->next;
  }
  assert(false && "Index out of bounds");
}
template<typename T>
int LinkedList<T>::find(const T & item) {
  Node * ptr = head;
  int i = 0;
  while (ptr != NULL) {
    if (ptr->data == item) {
      return i;
    }
    i++;
    ptr = ptr->next;
  }
  return -1;
}
template<typename T>
int LinkedList<T>::getSize() const {
  Node * ptr = head;
  int i = 0;
  while (ptr != NULL) {
    i++;
    ptr = ptr->next;
  }
  return i;
}
#endif
