//---------------------------------------------------------------------
//Filename:	BST.hpp
//Author:	Jimmy Li
//PID:		A96026254
//Date:		10/19/2013
//Rev-Date:	10/21/2013
//Description:	Contains the properties of a binary search tree 
//		data structure.
//---------------------------------------------------------------------
#ifndef BST_HPP
#define BST_HPP
#include "BSTNode.hpp"
#include "BSTIterator.hpp"
#include <iostream>

template<typename Data>
class BST {

protected:

  /** Pointer to the root of this BST, or 0 if the BST is empty */
  BSTNode<Data>* root;

  /** Number of Data items stored in this BST. */
  unsigned int isize;

public:

  /** define iterator as an aliased typename for BSTIterator<Data>. */
  typedef BSTIterator<Data> iterator;

  /** Default constructor.
      Initialize an empty BST.
   */
  BST() : root(0), isize(0) {  }


  /** Default destructor.
      Delete every node in this BST.
   */ // TODO
  virtual ~BST() {
    deleteAll(root);
    isize = 0;
  }

  /** Given a reference to a Data item, insert a copy of it in this BST.
   *  Return  true if the item was added to this BST
   *  as a result of this call to insert,
   *  false if an item equal to this one was already in this BST.
   *  Note: This function should use only the '<' operator when comparing
   *  Data items.
   */ // TODO
  virtual bool insert(const Data& item) {
    BSTNode<Data>* currNode = root, *prevNode = 0;
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
    if(root == 0) {
      root = new BSTNode<Data>(item);
      isize++;
      return true;
    }
    //Inserts node as right child if larger
    else if (prevNode->data < item) {
      prevNode->right = new BSTNode<Data>(item);
      prevNode->right->parent = prevNode;
      isize++;
      return true;
    }
    //Inserts node as left child if smaller
    else {
      prevNode->left= new BSTNode<Data>(item);
      prevNode->left->parent = prevNode;
      isize++;
      return true;
    }
  }


  /** Find a Data item in the BST.
   *  Return an iterator pointing to the item, or pointing past
   *  the last node in the BST if not found.
   *  Note: This function should use only the '<' operator when comparing
   *  Data items.
   */
  // TODO
  iterator find(const Data& item) const {
    BSTNode<Data>* tempNode = root;
    //Iterates through left and right children until match is found and
    //returns iterator of the matched node
    while(tempNode!= 0) { 
      if(item < tempNode->data) {
        tempNode = tempNode->left;
      }
      else if(tempNode->data < item) {
        tempNode = tempNode->right;
      }
      else {
        return typename BST<Data>::iterator(tempNode);
      }
    }
    //Return last node if no match
    return typename BST<Data>::iterator(0);
  }

  
  /** Return the number of items currently in the BST.
   */ // TODO
  unsigned int size() const {
    return isize;
  }

  /** Return true if the BST is empty, else false.
   */ // TODO
  bool empty() const {
    if(root == 0) {
      return true;
    }
    else {
      return false;
    }
  }

  /** Return an iterator pointing to the first item in the BST.
   */ // TODO
  iterator begin() const {
    return typename BST<Data>::iterator(first(root));  
  }

  /** Return an iterator pointing past the last item in the BST.
   */
  iterator end() const {
    return typename BST<Data>::iterator(0);
  }

  /** Perform an inorder traversal of this BST.
   */
  void inorder() const {
    inorder(root);
  }


private:

  /** Recursive inorder traversal 'helper' function */
  void inorder(BSTNode<Data>* n) const {
    if(n==0) return;
    inorder(n->left);
    std::cout << *n << std::endl;
    inorder(n->right);
  }

  static BSTNode<Data>* first(BSTNode<Data>* root) {
    if(root == 0) return 0;
    while(root->left != 0) root = root->left;
    return root;
  }

  // do a postorder traversal, deleting nodes
  static void deleteAll(BSTNode<Data>* n) {
    if (0 == n) return;
    deleteAll(n->left);
    deleteAll(n->right);
    delete n;
  }


 };


#endif //BST_HPP:
