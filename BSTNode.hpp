/*
Name: Jimmy Li
PID: A960626254
Assignment 1
CSE100
*/

#ifndef BSTNODE_HPP
#define BSTNODE_HPP
#include <iostream>
#include <iomanip>

template<typename Data>
class BSTNode {

public:

  /** Constructor.  Initialize a BSTNode with the given Data item,
   *  no parent, and no children.
   */
  BSTNode(const Data & d) : data(d) {
    left = right = parent = 0;
  }

  BSTNode<Data>* left;
  BSTNode<Data>* right;
  BSTNode<Data>* parent;
  Data const data;   // the const Data in this node.

  /** Return the successor of this BSTNode in a BST, or 0 if none.
   ** PRECONDITION: this BSTNode is a node in a BST.
   ** POSTCONDITION:  the BST is unchanged.
   ** RETURNS: the BSTNode that is the successor of this BSTNode,
   ** or 0 if there is none.
   */ // TODO
  BSTNode<Data>* successor() {
    if(this == 0) {
      return 0;
    }
    //For nodes without right child, look to parent to find successor
    else if(right == 0) {
      return parentRecurse(parent);
    }
    //For all other nodes, look right and recurse left for successor
    else {
      return childRecurse(right);
    }     
  }

private:
  //Recurse through parent until successor is found
  BSTNode<Data>* parentRecurse(BSTNode<Data>* node) {
    if(node == 0) {
      return 0;
    }
    else if(node->data < data) {
      return parentRecurse(node->parent);
    }
    else {
      return node;
    }
  }
  //Recurses through left node until successor is found
  BSTNode<Data>* childRecurse(BSTNode<Data>* node) {
    if(node->left == 0) {
      return node;
    }
    else {
      return childRecurse(node->left);
    }
  }
}; 

/** Overload operator<< to print a BSTNode's fields to an ostream. */
template <typename Data>
std::ostream & operator<<(std::ostream& stm, const BSTNode<Data> & n) {
  stm << '[';
  stm << std::setw(10) << &n;                 // address of the BSTNode
  stm << "; p:" << std::setw(10) << n.parent; // address of its parent
  stm << "; l:" << std::setw(10) << n.left;   // address of its left child
  stm << "; r:" << std::setw(10) << n.right;  // address of its right child
  stm << "; d:" << n.data;                    // its data field
  stm << ']';
  return stm;
}

#endif // BSTNODE_HPP
