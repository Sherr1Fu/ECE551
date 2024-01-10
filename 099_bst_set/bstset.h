#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <stdexcept>

#include "set.h"
template<typename T>
class BstSet : public Set<T> {
 private:
  class Node {
   public:
    T key;
    Node * left;
    Node * right;
    Node() : key(0), left(NULL), right(NULL){};
    Node(const T & k) : key(k), left(NULL), right(NULL){};
  };
  Node * root;
  void addhelper(Node *& current, const T & key) {
    if (current == NULL) {
      current = new Node(key);
    }
    else if (key < current->key) {
      addhelper(current->left, key);
    }
    else if (key > current->key) {
      addhelper(current->right, key);
    }
    else {
      return;
    }
  }
  bool containshelper(const Node * current, const T & key) const {
    //std::cout << current->key << std::endl;
    if (current == NULL) {
      return false;
    }

    if (key == current->key) {
      return true;
    }
    else if (key < current->key) {
      return containshelper(current->left, key);
    }
    else {
      return containshelper(current->right, key);
    }
  }
  void removehelper(Node *& current, const T & key) {
    if (current == NULL) {
      return;
    }
    if (key < current->key) {
      return removehelper(current->left, key);
    }
    else if (key > current->key) {
      return removehelper(current->right, key);
    }
    else {
      if (current->left == NULL) {
        Node * ptr = current;
        current = current->right;
        delete ptr;
      }
      else if (current->right == NULL) {
        Node * ptr = current;
        current = current->left;
        delete ptr;
      }
      else {
        Node * ptr = current->right;
        while (ptr->left != NULL) {
          ptr = ptr->left;
        }
        current->key = ptr->key;
        //current->value = ptr->value;
        removehelper(current->right, ptr->key);
      }
    }
  }
  void copyhelper(Node *& des, const Node * rhs) {
    if (rhs == NULL) {
      des = NULL;
    }
    else {
      des = new Node(rhs->key);
      copyhelper(des->left, rhs->left);
      copyhelper(des->right, rhs->right);
    }
  }
  void clearhelper(Node *& current) {
    if (current != NULL) {
      clearhelper(current->left);
      clearhelper(current->right);
      delete current;
    }
  }

 public:
  BstSet() : root(NULL){};
  BstSet(const BstSet & rhs) : root(NULL) { copyhelper(root, rhs.root); };
  BstSet & operator=(const BstSet & rhs) {
    if (this != &rhs) {
      clearhelper(root);
      root = NULL;
      copyhelper(root, rhs.root);
    }
    return *this;
  };
  virtual ~BstSet() { clearhelper(root); };
  virtual void add(const T & key) { addhelper(root, key); };
  virtual bool contains(const T & key) const { return containshelper(root, key); }
  virtual void remove(const T & key) { removehelper(root, key); };
};
