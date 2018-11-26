#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H
#include <iostream>
#include "RBNode.h"
#include "BST.h"
using namespace std;
template <typename E, typename V>
class RedBlackTree : public BST <E,V>
{
  public:
    RedBlackTree();
    virtual ~RedBlackTree();
        bool isEmpty();
    void insert(const E& key, const V& data);
    void colorFix(RBNode<E, V> *node);
    void colorCheck(RBNode<E, V> *node);
    void rotateLeft(RBNode<E, V> *node);
    void rotateRight(RBNode<E, V> *node);
    void printTree();//interative
    void recPrint(RBNode<E, V> *node); //in-order traversal

    /*bool contains(const E& key);
    bool deleteNode(const E& key);//must have


    bool deleteRec(const E& k);


    RBNode<E, V>* getNode(const E& key);

    RBNode<E, V>* getSuccessor(RBNode<E, V> *d);


    void recPrint(RBNode<E, V> *node); //in-order traversal    */
    void devTest();

  private:
    RBNode<E, V> *root;
};

template<typename E, typename V> RedBlackTree<E, V>::RedBlackTree()
{
  root = NULL;
}

template<typename E, typename V> RedBlackTree<E, V>::~RedBlackTree()
{
  //iterate and delete
}
template<typename E, typename V> bool RedBlackTree<E, V>::isEmpty()
{
  return root==NULL;
}
template<typename E, typename V> void RedBlackTree<E, V>::insert(const E& key, const V& data)
{
  //check if duplicate exists
  RBNode<E, V> *node = new RBNode<E, V>(key, data);//node we are inserting
  //check if empty
    //set root to node
  //else
  std::cout << "Key: " << node->key << std::endl;

  if(isEmpty())
  {
    root = node;
  }
  else
  {
    RBNode<E, V> *parent = NULL;
    RBNode<E, V> *current = root;

    while(true)
    {

      parent = current;

      if(node->key < current->key)
      {
        current = current->left;
        if(current == NULL)
        {
          break;
        }
      }
      else
      {
        current = current->right;
        if(current == NULL)
        {
          break;
        }
      }
    }

    //found insertion point
    node->parent = parent;//setting parent
    if(parent == NULL)
    {

      root = node;
    }
    else if(node->key < parent->key)
    {
      parent->left = node;
    }
    else
    {
      parent->right = node;
    }

    node->left = NULL;
    node->right = NULL;
    node->isRed = true;
    colorFix(node);
    std::cout << "Inserted Correctly: "<< std::endl<< std::endl;

  }

}
template<typename E, typename V> void RedBlackTree<E, V>::colorFix(RBNode<E, V> *node)
{

  //RBNode<E, V> *parent = node->parent;
  //RBNode<E, V> *grandparent = parent->parent;
  RBNode<E, V> *uncle = NULL;

  while(node->parent->isRed)
  {
    if(node->parent == node->parent->parent->left)
    {
      uncle = node->parent->parent->right;
      bool uncleExists = false;//This is a workaround so that we can check uncle's color IF it exists, because it not existing implies it is a null.
      if(uncle != NULL)
      {
        if(uncle->isRed)
        {
          std::cout << "Uncle Exists: "  << std::endl;

          uncleExists = true;
        }
      }
      if(uncleExists)
      {

        node->parent->isRed = false;
        uncle->isRed = false;
        node->parent->parent->isRed = true;
        node = node->parent->parent;
        std::cout << "Shit Exists: "  << std::endl;
        break;
      }
      else if(node == node->parent->right)
      {
        node = node->parent;
        std::cout << "Rotating Left on: " << node->key << std::endl;

        rotateLeft(node);
      }
      else
      {
        node->parent->isRed = false;
        node->parent->parent->isRed = true;
        std::cout << "Rotating right on: " << node->parent->parent->key << std::endl;
        rotateRight(node->parent->parent);
      }

    }
    else
    {
      uncle = node->parent->parent->left;
      bool uncleExists = false;//This is a workaround so that we can check uncle's color IF it exists, because it not existing implies it is a null.
      if(uncle != NULL)
      {
        if(uncle->isRed)
        {
          std::cout << "Gay Uncle Exists: "  << std::endl;

          uncleExists = true;
        }
      }
      if(uncleExists)
      {

        node->parent->isRed = false;
        uncle->isRed = false;
        node->parent->parent->isRed = true;
        node = node->parent->parent;
        colorCheck(node);

        break;
      }
      else if(node == node->parent->left)
      {
        node = node->parent;
        std::cout << "Rotating Left on: " << node->key << std::endl;

        rotateRight(node);
      }
      else
      {
        node->parent->isRed = false;
        node->parent->parent->isRed = true;
        std::cout << "Rotating Right and gay on: " << node->parent->parent->key << std::endl;

        rotateLeft(node->parent->parent);
      }
    }
  }
  root->isRed = false;
}

template<typename E, typename V> void RedBlackTree<E, V>::colorCheck(RBNode<E, V> *node)
{
  std::cout << "Node: " <<node->key<< std::endl;


  if(node->parent != NULL)
  {
    std::cout << "Gay: " << std::endl;
    if((node->parent->isRed) && (node->isRed))
    {
      std::cout << "Super Gay: " << std::endl;


      if((node->parent->parent != NULL) && (node->parent->parent->left->isRed))
      {
        std::cout << "John Cena: " << node->key<< std::endl;

      }
      else
      {

        rotateLeft(node->parent);
        std::cout << "is Now: " << node->key<< std::endl;
      }

    }
    if((node->isRed) && (node->left->isRed))
    {
      std::cout << "Triggered Left: " << node->key<< std::endl;

      rotateRight(node->parent);
      node->isRed=false;
      node->right->isRed=true;
    }
    else if((node->isRed) && (node->right->isRed))
    {
      std::cout << "Triggered Right: " << node->key<< std::endl;

    }

  }

}


template<typename E, typename V> void RedBlackTree<E, V>::rotateLeft(RBNode<E, V> *node)
{
  RBNode<E, V> *otherNode = node->right;
  node->right = otherNode->left;

  if(otherNode->left != NULL)
  {
    otherNode->left->parent = node;
  }

  otherNode->parent = node->parent;

  if(node->parent == NULL)
  {
    root = otherNode;
  }

  else if(node == node->parent->left)
  {
    node->parent->left = otherNode;
  }

  else
  {
    node->parent->right = otherNode;
  }

  otherNode->left = node;
  node->parent = otherNode;

}

template<typename E, typename V> void RedBlackTree<E, V>::rotateRight(RBNode<E, V> *node)
{

  RBNode<E, V> *otherNode = node->left;

  node->left = otherNode->right;

  if(otherNode->right != NULL)
  {
    otherNode->right->parent = node;
  }

  otherNode->parent = node->parent;

  if(node->parent == NULL)
  {
    root = otherNode;
  }

  else if(node == node->parent->right)
  {
    node->parent->right = otherNode;
  }

  else
  {
    node->parent->left = otherNode;
  }

  otherNode->right = node;
  node->parent = otherNode;

}

template<typename E, typename V> void RedBlackTree<E, V>::printTree()
{
  recPrint(root);
}

template<typename E, typename V> void RedBlackTree<E, V>::recPrint(RBNode<E, V> *node)
{
  //std::cout << "Shit "<< std::endl<< std::endl;

    if(node == NULL)
    {
      return;
    }
    recPrint(node->left);
    //std::cout << "Node left of "<< node->key <<" is "<< node->left->key << std::endl;

    //cout << node->key << endl;
    cout << "Node: " <<node->key<<" Color: "<<node->isRed << endl;

    recPrint(node->right);
    //std::cout << "Node right of "<< node->key <<" is "<< node->right->key << std::endl;

}




template<typename E, typename V> void RedBlackTree<E, V>::devTest()
{
  std::cout << "Root: "<< root->key  << std::endl;
  std::cout << "Root Left: "<< root->left->key  << std::endl;
  std::cout << "Root Left Right : "<< root->left->right->key  << std::endl;
  std::cout << "Root Right: "<< root->right->key  << std::endl;
  std::cout << "Root Right Left: "<< root->right->left->key  << std::endl;

  //std::cout << "root right left left right: "<< root->right->left->left->right->right->key  << std::endl;
  //std::cout << "root right left right: "<< root->right->left->right->key  << std::endl;



}



#endif
