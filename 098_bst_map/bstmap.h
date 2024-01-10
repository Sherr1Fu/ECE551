#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <stdexcept>

#include "map.h"
template<typename K, typename V>
class BstMap : public Map<K, V> {
 private:
  class Node {
   public:
    K key;
    V value;
    Node * left;
    Node * right;
    Node() : key(0), value(0), left(NULL), right(NULL){};
    Node(const K & k, const V & v) : key(k), value(v), left(NULL), right(NULL){};
  };
  Node * root;
  void addhelper(Node *& current, const K & key, const V & value) {
    if (current == NULL) {
      current = new Node(key, value);
    }
    else if (key < current->key) {
      addhelper(current->left, key, value);
    }
    else if (key > current->key) {
      addhelper(current->right, key, value);
    }
    else {
      current->value = value;
    }
  }
  const V & lookuphelper(const Node * current, const K & key) const {
    //std::cout << current->key << std::endl;
    if (current == NULL) {
      throw std::invalid_argument("Key is not found");
    }

    if (key == current->key) {
      return current->value;
    }
    else if (key < current->key) {
      return lookuphelper(current->left, key);
    }
    else {
      return lookuphelper(current->right, key);
    }
  }
  void removehelper(Node *& current, const K & key) {
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
        current->value = ptr->value;
        removehelper(current->right, ptr->key);
      }
    }
  }
  void copyhelper(Node *& des, const Node * rhs) {
    if (rhs == NULL) {
      des = NULL;
    }
    else {
      des = new Node(rhs->key, rhs->value);
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
  BstMap() : root(NULL){};
  BstMap(const BstMap & rhs) : root(NULL) { copyhelper(root, rhs.root); };
  BstMap & operator=(const BstMap & rhs) {
    if (this != &rhs) {
      clearhelper(root);
      root = NULL;
      copyhelper(root, rhs.root);
    }
    return *this;
  };
  virtual ~BstMap() { clearhelper(root); };
  virtual void add(const K & key, const V & value) { addhelper(root, key, value); };
  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    return lookuphelper(root, key);
  };
  virtual void remove(const K & key) { removehelper(root, key); };
};
