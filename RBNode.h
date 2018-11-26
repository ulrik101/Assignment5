#ifndef RBNODE_H
#define RBNODE_H
#include <iostream>
#include "TreeNode.h"
using namespace std;
template <typename E, typename V>
class RBNode : public TreeNode <E,V>
{
  public:
    RBNode();
    RBNode(const E& newKey, const V& newData, RBNode* _left = NULL,  RBNode* _right = NULL);
    virtual ~RBNode();

    /// \Brief whether or not the not is a red or black node.
    bool isRed;
    RBNode *left;
    RBNode *right;
    RBNode *parent;
};

template<typename E, typename V> RBNode<E, V>::RBNode()
{
  left = NULL;//nullptr
  right = NULL;
}

template<typename E, typename V> RBNode<E, V>::RBNode(const E& newKey, const V& newData, RBNode* _left,  RBNode* _right)
{
  left = _left;
  right = _right;
  this->key = newKey;
  this->data = newData;
}

template<typename E, typename V> RBNode<E, V>::~RBNode()
{
  left = NULL;
  right = NULL;
  parent = NULL;
}
#endif
