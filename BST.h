#ifndef BST_H
#define BST_H
#include <iostream>
#include "TreeNode.h"
#include <functional>
#include <fstream>
//#include "DoubleLinkedList.h"
using namespace std;
template <typename E, typename V>
class BST
{
  public:
    /// \brief Constructor
    /// \param fnc delete function used to delete the data stored within the BST defaults to do nothing.
    ///   this should be set if the stored data is a pointer type
    ///
    BST(std::function<void(V)>fnc = [](V data)->void{});
    virtual ~BST();
    /// \brief Insert a value into the BST. Data/node will be sorted depending on the given value.
    /// \param value Numerical value used to sort the Node.
    /// \param data Data that is to be sorted and stored within the BST.
    void insert(const E& value, const V& data);

    /// \brief Checks to see if the given value/key is found within the BST.
    /// \return Returns a bool.
    /// \param value Identifying Key that prepresents the data.
    bool contains(const E& value);

    /// \brief finds and deletes the node with the given Key value
    /// \return Returns a bool.
    /// \param k Key value used to find and delete the desired Node.
    bool deleteNode(const E& k);


    /// \brief Checks to see if the tree is empty.
    /// \return Returns a bool.
    bool isEmpty();

    /// \brief Finds and returns a TreeNode given a Key Value.
    /// \param value Key value used to locate the desired node within the BST.
    /// \return Returns a TreeNode
    TreeNode<E, V>* getNode(const E& value);

    /// \brief Finds and returns the root TreeNode of the BST
    /// \return Returns a TreeNode<E, V>
    TreeNode<E, V>* getRoot();



    /// \brief Finds the successor to the given node.
    /// \return Returns a TreeNode<E, V>
    /// \param d TreeNode<E,V> To find the successor of.
    TreeNode<E, V>* getSuccessor(TreeNode<E, V> *d);

    /// \brief Prints the Tree
    /// \return void
    void printTree(bool ascending);//interative
    void printTreeData(bool ascending);//interative


    void treeToCsv(std::string fileName, TreeNode<E, V> *node);
    void recDelete(TreeNode<E, V> *node);


  private:
    /// \brief Recursively prints out the tree from the given TreeNode in Ascending Order
    /// \return void
    /// \param node TreeNode<E,V> to start from
    void recPrint(TreeNode<E, V> *node); //in-order traversal

    /// \brief Recursively prints out the tree from the given TreeNode in Descending Order
    /// \return
    /// \param node TreeNode<E,V> to start from
    void recPrintReverse(TreeNode<E, V> *node); //in-order traversal


    void recPrintData(TreeNode<E, V> *node); //in-order traversal
    void recPrintDataReverse(TreeNode<E, V> *node); //in-order traversal


    /// \brief
    /// \return
    /// \param
    std::function<void(V)>deleteData;

    /// \brief Recursively Deletes the entire tree from the given node
    /// \return void
    /// \param node TreeNode<E,V> to start from


    /*
    void createList(TreeNode<E, V> *node = root);
    void deleteList();*/
    TreeNode<E, V> *root;
    //DoubleLinkedList<V> list;
};

template<typename E, typename V> BST<E, V>::BST(std::function<void(V)>fnc)
{
  deleteData = fnc;
  root = NULL;
}

template<typename E, typename V> BST<E, V>::~BST()
{
  //iterate and delete
  recDelete(root);
}
template<typename E, typename V> void BST<E, V>::recDelete(TreeNode<E, V> *node)
{
  if(node->left)
  {
    recDelete(node->left);
  }
  if(node->right)
  {
    recDelete(node->right);
  }
  //deleteData(node->data);//if deleteData is unset, this will do nothing.
  delete node->data;
  node->data = NULL;
  delete node;
}

template<typename E, typename V> void BST<E, V>::printTree(bool ascending)
{
  if(ascending)
  {
    recPrint(root);
  }
  else
  {
    recPrintReverse(root);
  }
}




template <typename E, typename V>
void BST<E, V>::treeToCsv(std::string fileName, TreeNode<E, V> *node)
{
    if(node == root)
    {

        std::ofstream resetFile;
        resetFile.open(fileName, std::ofstream::out | std::ofstream::trunc);
        resetFile.close();
    }
    if (node == NULL)
    {
        return;
    }
    treeToCsv(fileName,node->left);
    std::ofstream openFile;
    openFile.open(fileName, ios::out | ios::app );
    openFile << (node->data->toString() + "\n");
    openFile.flush();
    openFile.close();
    treeToCsv(fileName,node->right);
}

template<typename E, typename V> void BST<E, V>::printTreeData(bool ascending)
{
    if (ascending)
    {
        recPrintData(root);
    }
    else
    {
        recPrintDataReverse(root);
    }
}


template<typename E, typename V> void BST<E, V>::recPrint(TreeNode<E, V> *node)
{
    if(node == NULL)
    {
      return;
    }
    recPrint(node->left);
    //std::cout << "Node left of "<< node->key <<" is "<< node->left->key << std::endl;

    cout << node->key << endl;
    recPrint(node->right);
    //std::cout << "Node right of "<< node->key <<" is "<< node->right->key << std::endl;

}
template<typename E, typename V> void BST<E, V>::recPrintReverse(TreeNode<E, V> *node)
{
    if(node == NULL)
    {
      return;
    }
    recPrintReverse(node->right);

    cout << node->key << endl;
    recPrintReverse(node->left);

}



template<typename E, typename V> void BST<E, V>::recPrintData(TreeNode<E, V> *node)
{
    if (node == NULL)
    {
        return;
    }
    recPrintData(node->left);
    node->data->print();
    //cout <<  << endl;
    recPrintData(node->right);

}
template<typename E, typename V> void BST<E, V>::recPrintDataReverse(TreeNode<E, V> *node)
{
    if (node == NULL)
    {
        return;
    }
    recPrintDataReverse(node->right);
    node->data->print();
    //cout << node->data->print() << endl;
    recPrintDataReverse(node->left);

}






template<typename E, typename V> bool BST<E, V>::isEmpty()
{
  return root==NULL;
}


template<typename E, typename V> void BST<E, V>::insert(const E& value, const V& data)
{

  //check if duplicate exists, if duplicates are not allowed
  TreeNode<E, V> *node = new TreeNode<E, V>(value,data);
  if(isEmpty())
  {
    root = node;
  }
  else//not an empty tree
  {

    TreeNode<E, V> * current = root;
    TreeNode<E, V> *parent;//empty node

    while(true)
    {
      parent = current;
      if(value < current->key)//we go left
      {

        current = current->left;
        if(current == NULL)//found insertion point
        {
          //parent->key = node->key;

          parent->left = node;


          break;
        }
      }
      else//go right
      {

        current = current->right;
        if(current == NULL)//found insertion point
        {
          //parent->key = node->key;
          parent->right = node;

          break;
        }
      }
    }
  }
}

template<typename E, typename V> bool BST<E, V>::contains(const E& value)//search method
{
  TreeNode<E, V> *current = root;



  while(current!=NULL && current ->key != value)
  {

    if(value < current->key)
    {
      current = current->left;
    }
    else
    {
      current = current->right;
    }
  }


  return current != NULL;
}
template<typename E, typename V> TreeNode<E, V>* BST<E, V>::getNode(const E& value)
{

  TreeNode<E, V> *current = root;
  while(current ->key != value)
  {

    if(current == NULL)
    {
      return NULL;
    }
    if(value < current->key)
    {
      current = current->left;
    }
    else
    {
      current = current->right;
    }
  }
  return current;
}
template<typename E, typename V> TreeNode<E, V>* BST<E, V>::getRoot()
{
  return root;
}
template<typename E, typename V> bool BST<E, V>::deleteNode(const E& k)
{
  //std::cout << "Fired, searching for "<< k << std::endl;
  //check if contains
  if(!contains(k))
  {
    //std::cout << "Does Not Contain:" << std::endl;
    return false;
  }
  else//find node and attempt to delete
  {
    //std::cout << "Does Contain:" << std::endl;
    TreeNode<E, V> *parent = root;
    TreeNode<E, V> *current = root;
    bool isLeft = true;

    while(current->key != k)
    {
      parent = current;
      //std::cout << "Current spot is now " << current->key << std::endl;

      if(k < current->key)
      {
        //std::cout << "Traveling Left to " << current->left->key << std::endl;
        isLeft = true;
        current = current->left;
      }
      else // go right
      {
        //std::cout << "Traveling Right to "<< current->right->key << std::endl;

        isLeft = false;
        current = current->right;
      }
      if(current == NULL)
      {
        //std::cout << "Return False:" << std::endl;
        return false;
      }
    }
    //found the node to be deleted
    //std::cout << "Found Node:"<< std::endl;

    //node has no children, leaf node
    if(current->left == NULL && current->right == NULL)
    {
      if(current == root)
      {
        root = NULL;
      }
      else if (isLeft)
      {
        parent->left = NULL;
      }
      else
      {
        parent->right = NULL;
      }
    }

    //check if the node has only one child
    else if(current->right == NULL)//no right child means it must be a left node
    {
      if(current == root)
      {
        root = current->left;
      }
      else if(isLeft)
      {
        parent->left = current->left;
      }
      else//right child
      {
        parent->right = current->left;
      }
    }
    else if(current->left == NULL)//no left child, opposite of above
    {
      if(current == root)
      {
        root = current->right;
      }
      else if(isLeft)
      {
        parent->left = current->right;
      }
      else//right child
      {
        parent->right = current->right;
      }
    }
    else//node has two children.
    {

      TreeNode<E, V> *successor = getSuccessor(current);

      //current = successor;
      //successor = NULL;



      if(current == root)
      {
        root = successor;
        successor->left = current->left;
        successor = NULL;
        current = NULL;

      }
      else if(isLeft)
      {

        parent->left = successor;
        //parent->left->left = current->left;

        successor->left = current->left;
        successor = NULL;
        current = NULL;

      }
      else
      {
        parent->right = successor;
        successor->left = current->left;
        successor = NULL;
        current = NULL;
      }



    }
    return true;
  }
}

//d is the node we are deleting
template<typename E, typename V> TreeNode<E, V>* BST<E, V>::getSuccessor(TreeNode<E, V> *d)
{
  TreeNode<E, V> *successor_parent = d; //successor_parent
  TreeNode<E, V> *successor = d; // should one right, all the way left
  TreeNode<E, V> *current = d->right;
  while(current != NULL)
  {
    successor_parent = successor;
    successor = current;
    current = current->left;

  }
  if(successor != d->right)//descending of right child
  {
    successor_parent->left = successor->right;
    successor->right = d->right;

  }

  return successor;
}




#endif
