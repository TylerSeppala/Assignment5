//Tyler Seppala
//2297817
//seppala@chapman.edu
//CPSC 350-02
//Assignment 5 (Database)

//Template class for a binary search tree

#include<iostream>
#include<fstream>
#include "TreeNode.h"

using namespace std;

template<class X>
class GenTree
{
public:
  GenTree();
  GenTree(TreeNode<X>* r);
  ~GenTree();
  void insert(int value);
  void insert(int value, X *data);
  bool contains(int value);
  X *getValue(int value);
  bool deleteNode(int value);
  TreeNode<X>* getSuccessor(TreeNode<X>* d);
  TreeNode<X>* clone();
  bool deleteRec();

  TreeNode<X>* getMin();
  TreeNode<X>* getMax();
  bool isEmpty();
  void printTree();
  void recPrint(TreeNode<X> *node);
  void recBuildString(TreeNode<X> *node);
  void treeToFile(ofstream& file);
  string treeString();

private:
  string tree;
  void treeToFile(TreeNode<X>* node, ofstream& file);
  TreeNode<X>* clone(TreeNode<X>* node);
  TreeNode<X> *root;
};

template <class X>
GenTree<X>::GenTree()
{
  root = NULL;
}

template <class X>
GenTree<X>::GenTree(TreeNode<X>* r)
{
  root = r;
}

template <class X>
GenTree<X>::~GenTree()
{
  if (root)
    delete root;
}

template <class X>
void GenTree<X>::printTree()
{
  recPrint(root);
}

template <class X>
void GenTree<X>::recPrint(TreeNode<X> *node)
{
  if (node == NULL)
    return;

  recPrint(node->left);
  cout << node->key << endl;
  recPrint(node->right);
}

template <class X>
void GenTree<X>::recBuildString(TreeNode<X> *node)
{
  if (node == NULL)
    return;

  recBuildString(node->left);
  tree += node->data->toString();
  recBuildString(node->right);
}

template <class X>
string GenTree<X>::treeString()
{
  tree = "";
  recBuildString(root);
  return tree;
}

template <class X>
bool GenTree<X>::isEmpty()
{
  return (root == NULL);
}

template <class X>
void GenTree<X>::insert(int value, X *data)
{
  //check if value exists, if not continue
  TreeNode<X> *node = new TreeNode<X>(value, data);

  if (isEmpty())
  {
    root = node;
  }
  else
  {
    TreeNode<X> *current = root;
    TreeNode<X> *parent;

    while (true)
    {
      parent = current;
      if (value < current->key)
      {
        current = current->left;
        if (current == NULL)
        {
          parent->left = node;
          break;
        }
      }
      else
      {
        current = current->right;
        if (current == NULL)
        {
          parent->right = node;
          break;
        }
      }
    }
  }
}

template <class X>
bool GenTree<X>::contains(int value)
{
  if (isEmpty())
  {
    return false;
  }
  else
  {
    TreeNode<X> *current = root;

    while (current->key != value)
    {
      if (value < current->key)
      {
        current = current->left;
      }
      else
      {
        current = current->right;
      }
      if (current == NULL)
      {
        return false;
      }
    }
    return true;
  }
}

template <class X>
X *GenTree<X>::getValue(int value)//used to return the object stored at the given key
{
  if (isEmpty())
  {
    return NULL;
  }
  else
  {
    TreeNode<X> *current = root;

    while (current->key != value)
    {
      if (value < current->key)
      {
        current = current->left;
      }
      else
      {
        current = current->right;
      }
      if (current == NULL)
      {
        return NULL;
      }
    }
    return current->data;
  }
}

template <class X>
bool GenTree<X>::deleteNode(int value)
{
  if (isEmpty())
    return false;

  //check if key/value exists in tree

  TreeNode<X> *current = root;
  TreeNode<X> *parent = root;
  bool isLeft = true;

  //now lets iterate and update our pointers
  while (current->key != value)
  {
    parent = current;

    if (value < current->key)
    {
      isLeft = true;
      current = current->left;
    }
    else
    {
      isLeft = false;
      current = current->right;
    }

    if (current == NULL)
      return false;
  }
  //now we are at the node to be deleted
  if (current->left == NULL && current->right == NULL)//external node
  {
    if (current == root)
      root = NULL;
    else if (isLeft)
    {
      parent->left = NULL;
    }
    else
    {
      parent->right = NULL;
    }
  }
  //check if node to be deleted has one child
  else if (current->right == NULL)
  {
    if (current == root)
      root = current->left;
    else if (isLeft)
    {
      parent->left = current->left;
    }
    else
    {
      parent->right = current->left;
    }
  }
  else if (current->left == NULL)
  {
    if (current == root)
      root = current->right;
    else if (isLeft)
    {
      parent->left = current->right;
    }
    else
    {
      parent->right = current->right;
    }
  }
  else //node has 2 children
  {
    TreeNode<X> *successor = getSuccessor(current);

    if (current == root)
      root = successor;
    else if (isLeft)
      parent->left = successor;
    else
      parent->right = successor;

    successor->left = current->left;
  }
  return true;
}

template <class X>
TreeNode<X>* GenTree<X>::getSuccessor(TreeNode<X> *d)
{
  TreeNode<X> *sp = d;//successor's parent
  TreeNode<X> *successor = d;
  TreeNode<X> *current = d->right;

  while (current != NULL)
  {
    sp = successor;
    successor = current;
    current = current->left;
  }

  //check if successor is a descendant of right child
  if (successor != d->right)
  {
    sp->left = successor->right;
    successor->right = d->right;
  }
  return successor;
}

template<class X>
void GenTree<X>::treeToFile(TreeNode<X>* node, ofstream& file)//used to store tree in a file
{
    if (node == NULL)
    {
      file << "";
      return;
    }

    file << node->data->toString();
    treeToFile(node->left, file);
    treeToFile(node->right, file);
}

template<class X>
void GenTree<X>::treeToFile(ofstream & file)//used to store tree in file starting from root
{
    treeToFile(root, file);
    file.close();
}

template<class X>
TreeNode<X>* GenTree<X>::clone(TreeNode<X>* node)//used to make copy of the tree
{
  if (node == NULL )
    return node;

  //create new node and make it a copy of node pointed by root
  TreeNode<X> *temp = (TreeNode<X> *)malloc(sizeof(TreeNode<Student>)) ;
  temp->key = node->key;
  temp->data = node-> data;    //copying data
  temp->left = clone(node -> left);    //cloning left child
  temp->right = clone(node -> right);  //cloning right child
  return temp;
}

template<class X>
TreeNode<X>* GenTree<X>::clone()//used to clone tree from root
{
  clone(root);
}
