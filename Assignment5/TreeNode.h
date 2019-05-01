//Tyler Seppala
//2297817
//seppala@chapman.edu
//CPSC 350-02
//Assignment 5 (Database)

//Template for treenode class, used by BST

#include <iostream>

using namespace std;

template <class X>
class TreeNode
{
public:
  TreeNode();
  TreeNode(int key);
  TreeNode(int key, X *data);
  virtual ~TreeNode(); //find out why its virtual

  int key;
  X *data;//used to store non-int data types 
  TreeNode<X> *left;
  TreeNode<X> *right;
};

template <class X>
TreeNode<X>::TreeNode()
{
  left = NULL;
  right = NULL;
}

template <class X>
TreeNode<X>::TreeNode(int k)
{
  left = NULL;
  right = NULL;
  key = k;
}

template <class X>
TreeNode<X>::TreeNode(int k, X *dat)
{
  left = NULL;
  right = NULL;
  key = k;
  data = dat;
}

template <class X>
TreeNode<X>::~TreeNode()
{
  if (left)
    delete left;
  if (right)
    delete right;
}
