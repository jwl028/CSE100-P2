//---------------------------------------------------------------------
//Filename:	RST.hpp
//Author:	Jimmy Li
//PID:		A96026254
//Date:		10/19/2013
//Rev-Date:	10/21/2013
//Description:	Contains the properties of a randomized search tree 
//		data structure.
//---------------------------------------------------------------------

#ifndef RST_HPP
#define RST_HPP
#include "BST.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

template <typename Data>
class RST : public BST<Data> {

public:

  //---------------------------------------------------------------------
  //insert()
  //
  //Input: const Data& item
  //Output: boolean
  //Description: Inserts a node with the inputted data into the RST.
  //---------------------------------------------------------------------

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
      //std::cout << "Inst Root" << std::endl;
      //Random seed for random priorities each run
      srand(time(NULL));
      BST<Data>::root->info = rand();
      //std::cout << item << std::endl;
      //std::cout << BST<Data>::root->info << std::endl;
      BST<Data>::isize++;
      return true;
    }
    //Inserts node as right child if larger
    else if (prevNode->data < item) {
      prevNode->right = new BSTNode<Data>(item);
      //std::cout << "Inst Right" << std::endl;
      //std::cout << item << std::endl;
      prevNode->right->parent = prevNode;
      prevNode->right->info = rand();
      //std::cout << prevNode->right->info << std::endl;
      //If priority of right child is higher than node, rotate left
      if(prevNode->right->info > prevNode->info) {
        rotateLeft(prevNode);
      }
      BST<Data>::isize++;
      return true;
    }
    //Inserts node as left child if smaller
    else {
      prevNode->left = new BSTNode<Data>(item);
      //std::cout << "Inst Left" << std::endl;
      //std::cout << item << std::endl;
      prevNode->left->parent = prevNode;
      prevNode->left->info = rand();
      //std::cout << rand() << std::endl;
      //If priority of left child is higher than node, rotate right
      if(prevNode->left->info > prevNode->info) {
        rotateRight(prevNode);
      }
      BST<Data>::isize++;
      return true;
    }
  }
  
  //---------------------------------------------------------------------
  //rotateLeft()
  //
  //Input: BSTNode<Data>* node 
  //Output: None 
  //Description: Recursively performs AVL left rotation on node if right 
  //             child's priority is less than the node's priority. Calls
  //             rotateRight if right child's priority is greater.
  //---------------------------------------------------------------------

  void rotateLeft(BSTNode<Data>* node) {
 // std::cout << "Left" << std::endl;
    //Rotate left if right child has higher priority
    if(node->right->info > node->info) {
      node->right->parent = node->parent;
      node->parent = node->right;
      node->right = node->parent->left;
      node->parent->left = node;
      if(node->right !=0) {
        node->right->parent = node;
      }
      if(node->parent->parent != 0 ){
        //If node is right child, check if left rotation is needed
        if(node->parent->parent->data < node->data) {
          node->parent->parent->right = node->parent;
          rotateLeft(node->parent->parent);
        }
        else {
        //If node is left child, check if right rotation is needed
          node->parent->parent->left = node->parent;
          rotateRight(node->parent->parent);
        }
      }
      else {
        BST<Data>::root = node->parent;
      }
    }
  }

  //---------------------------------------------------------------------
  //rotateRight()
  //
  //Input: BSTNode<Data>* node 
  //Output: None 
  //Description: Recursively performs AVL right rotation on node if left 
  //             child's priority is less than the node's priority. Calls
  //             rotateRight if right child's priority is greater.
  //---------------------------------------------------------------------

  void rotateRight(BSTNode<Data>* node) {
  //std::cout << "Right" << std::endl;
    //Rotate right if left child has higher priority
    if(node->left->info > node->info) {
      node->left->parent = node->parent;
      node->parent = node->left;
      node->left = node->parent->right;
      node->parent->right = node;
      if(node->left !=0) {
        node->left->parent = node;
      }
      if(node->parent->parent !=0){
        //If node is right child, check if left rotation is needed
        if(node->parent->parent->data < node->data) {
          node->parent->parent->right= node->parent;
          rotateLeft(node->parent->parent);
        }
        else {
        //If node is left child, check if right rotation is needed
          node->parent->parent->left= node->parent;
          rotateRight(node->parent->parent);
        } 
      }
      else {
        BST<Data>::root = node->parent;
      }
    }
  }

};
#endif //RST_HPP
