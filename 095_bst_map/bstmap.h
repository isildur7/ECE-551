#ifndef __BSTMAP_H__
#define __BSTMAP_H__
#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include "map.h"

template<typename K, typename V>
class BstMap : public Map<K, V>
{
  class Node
  {
   public:
    K key;
    V val;
    Node * left;
    Node * right;
    Node * parent;
    Node() : left(NULL), right(NULL), parent(NULL) {}
    Node(K key, V val) : key(key), val(val), left(NULL), right(NULL), parent(NULL) {}
    Node(K key, V val, Node * ptr) : key(key), val(val), left(NULL), right(NULL), parent(ptr) {}
    ~Node() {}
  };
  int size;
  Node * root;

  Node * add(const K & key, const V & value, Node * ptr, Node * papa) {
    if (ptr == NULL) {
      ptr = new Node(key, value, papa);
    }
    else if (ptr->key > key) {
      ptr->right = add(key, value, ptr->right, ptr);
    }
    else if (ptr->key < key) {
      ptr->left = add(key, value, ptr->left, ptr);
    }
    else {
      ptr->val = value;
    }
    return ptr;
  }

  void printTree(Node * ptr) {
    if (ptr->left != NULL) {
      printTree(ptr->left);
    }
    std::cout << ptr->key << "::" << ptr->val << " ";
    if (ptr->right != NULL) {
      printTree(ptr->right);
    }
  }

  void deleteMap(Node * ptr) {
    if (ptr != NULL) {
      if (ptr->left != NULL) {
        deleteMap(ptr->left);
      }
      if (ptr->right != NULL) {
        deleteMap(ptr->right);
      }
      delete ptr;
    }
  }

 public:
  BstMap() : size(0), root(NULL){};

  virtual void add(const K & key, const V & value) { root = add(key, value, root, NULL); }

  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    Node * curr = root;
    while (curr != NULL) {
      if (key == curr->key) {
        return curr->val;
      }
      else if (key < curr->key) {
        curr = curr->right;
      }
      else {
        curr = curr->left;
      }
    }
    throw std::invalid_argument("key does not exist");
  }
  //Remove
  Node * maxleft(Node * curr) {
    while (curr->right != NULL) {
      curr = curr->right;
    }
    return curr;
  }

  virtual void remove(const K & key) { root = remove(root, key); }

  Node * remove(Node * current, const K & key) {
    if (current == NULL) {
      return current;
    }
    if (key < current->key) {
      current->left = remove(current->left, key);
    }
    else if (key > current->key) {
      current->right = remove(current->right, key);
    }
    else {
      if (current->left == NULL && current->right == NULL) {
        delete current;
        current = NULL;
      }
      else if (current->left == NULL) {
        Node * temp = current;
        current = current->right;
        delete temp;
      }
      else if (current->right == NULL) {
        Node * temp = current;
        current = current->left;
        delete temp;
      }
      else {
        Node * temp = maxleft(current->left);
        current->key = temp->key;
        current->val = temp->val;
        current->left = remove(current->left, temp->key);
      }
    }
    return current;
  }

  ~BstMap() { deleteMap(root); }

  void printTree() {
    printTree(root);
    std::cout << "\n";
  }
};

#endif
