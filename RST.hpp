#ifndef RST_HPP
#define RST_HPP
#include "BST.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

template <typename Data>
class RST : public BST<Data> {

public:

  virtual bool insert(const Data& item) {
    BSTNode<Data>* currNode = BST<Data>::root, *prevNode = 0;
    while(currNode !=0){
      prevNode = currNode;
      //Go to left child node if inserted node is smaller
      if(item < currNode->data) {
        currNode = currNode->left;
      }
      //Go to right child node if inserted node is larger 
      else if(currNode->data < item) {
        currNode = currNode->right;
      }
      //Prevents duplicate nodes
      else {
        return false;
      }
    }
    //Inserts node as root if empty
    if(BST<Data>::root == 0) {
      BST<Data>::root = new BSTNode<Data>(item);
    srand(time(NULL));
      BST<Data>::root->info = rand();
      BST<Data>::isize++;
      return true;
    }
    //Inserts node as right child if larger
    else if (prevNode->data < item) {
      prevNode->right = new BSTNode<Data>(item);
      prevNode->right->parent = prevNode;
      prevNode->right->info = rand();
      std::cout << prevNode->right->info << std::endl;
      if(prevNode->right->info > prevNode->info) {
        rotateLeft(prevNode);
      std::cout << "Inst" << std::endl;
      }
      BST<Data>::isize++;
      return true;
    }
    //Inserts node as left child if smaller
    else {
      prevNode->left = new BSTNode<Data>(item);
      prevNode->left->parent = prevNode;
      prevNode->left->info = rand();
      //std::cout << rand() << std::endl;
      if(prevNode->left->info > prevNode->info) {
        rotateRight(prevNode);
      }
      BST<Data>::isize++;
      return true;
    }
  }

  void rotateLeft(BSTNode<Data>* node) {
  std::cout << "Left" << std::endl;
  if(node->parent != 0) {
      BSTNode<Data>* nodeParent = node->parent;
      BSTNode<Data>* nodeRight= node->right;
    if(node->right->info > node->info) {
    //  BSTNode<Data>* nodeLeft= node->left;
      node->parent = nodeRight;
      node->parent->left = node;
      node->right = nodeRight->left;
      if(node->right !=0) {
        node->right->parent = node;
      }
      node->parent->parent = nodeParent;
      if(nodeParent->data < node->data) {
        node->parent->parent->right = node->parent;
      }
      else {
        node->parent->parent->left = node->parent;
      } 
    }
    else {
    }
    rotateLeft(nodeParent);
  }
  }

  void rotateRight(BSTNode<Data>* node) {
    if(node->parent !=0){
      BSTNode<Data>* nodeParent = node->parent;
      BSTNode<Data>* nodeLeft= node->left;
    if(node->left->info > node->info) {
     // BSTNode<Data>* nodeRight= node->right;
      node->parent = nodeLeft;
      node->parent->right = node;
      node->left = nodeLeft->right;
      if(node->left !=0) {
        node->left->parent = node;
      }
      node->parent->parent = nodeParent;
      if(nodeParent->data < node->data) {
        node->parent->parent->right = node->parent;
      }
      else {
        node->parent->parent->left = node->parent;
      } 
    }
    else {
    }
    rotateRight(nodeParent);
  }
  }

};
#endif //RST_HPP
