#ifndef __SET_H__
#define __SET_H__
#include <cstdlib>
#include <iostream>
#include <stdexcept>

template<typename T>
class Set
{
 public:
  virtual void add(const T & key) = 0;
  virtual bool contains(const T & key) const = 0;
  virtual void remove(const T & key) = 0;
  virtual ~Set<T>() {}
};

template<typename K>
class BstSet : public Set<K>
{
  class Node
  {
   public:
    K key;
    Node * left;
    Node * right;
    Node() : left(NULL), right(NULL) {}
    Node(K key) : key(key), left(NULL), right(NULL) {}
    ~Node() {}
  };
  int size;
  Node * root;

  Node * add(const K & key, Node * ptr) {
    if (ptr == NULL) {
      ptr = new Node(key);
    }
    else if (ptr->key < key) {
      ptr->right = add(key, ptr->right);
    }
    else if (ptr->key > key) {
      ptr->left = add(key, ptr->left);
    }
    else {
      ptr->key = key;
    }
    return ptr;
  }

  void printTree(Node * ptr) {
    if (ptr->left != NULL) {
      printTree(ptr->left);
    }
    std::cout << ptr->key << " ";
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

  Node * copy(Node * ptr, Node * rhs) {
    if (rhs != NULL) {
      ptr = new Nxsxsode;
      ptr->key = rhs->key;
      ptr->val = rhs->val;
      ptr->left = copy(ptr->left, rhs->left);
      ptr->right = copy(ptr->left, rhs->right);
      return ptr;
    }
    return NULL;
  }

  Node * maxleft(Node * curr) {
    while (curr->right != NULL) {
      curr = curr->right;
    }
    return curr;
  }

 public:
  BstSet<K>() : size(0), root(NULL){};
  BstSet<K>(const BstSet<K> & rhs) : size(0), root(NULL) { root = copy(root, rhs.root); }

  BstSet<K> & operator=(const BstSet<K> & rhs) {
    BstSet<K> temp(rhs);
    deleteMap(root);
    root = NULL;
    std::swap(root, temp.root);
    return *this;
  }

  virtual void add(const K & key) { root = add(key, root); }

  bool contains(const K & key) const throw(std::invalid_argument) {
    Node * curr = root;
    while (curr != NULL) {
      if (key == curr->key) {
        return true;
      }
      else if (key > curr->key) {
        curr = curr->right;
      }
      else {
        curr = curr->left;
      }
    }
    return false;
  }

  virtual void remove(const K & key) { root = remove(root, key); }

  virtual ~BstSet() { deleteMap(root); }

  void printTree() {
    printTree(root);
    std::cout << "\n";
  }
};

#endif
