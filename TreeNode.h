#ifndef TREENODE_H
#define TREENODE_H
#include <iostream>
using namespace std;
template <typename E, typename V>
class TreeNode
{
  public:
    TreeNode();
    /// \brief Construct a new node with the given key and data.
    /// \param newKey Key is the data that the node will be sorted by.

    TreeNode(const E& newKey, const V& newData, TreeNode* _left = NULL,  TreeNode* _right = NULL);
    virtual ~TreeNode();
    /// \brief The number or data used to sort the Node within the database.
    E key;
    V data;
    //Object key;
    TreeNode *left;
    TreeNode *right;

    inline bool operator==(const TreeNode &right ){return this->key == right.key;}//https://en.cppreference.com/w/cpp/language/operators
    inline bool operator!=(const TreeNode &right ){return this->key != right.key;}
    inline bool operator<(const TreeNode &right ){return this->key < right.key;}
    inline bool operator>(const TreeNode &right ){return this->key > right.key;}
    inline bool operator<=(const TreeNode &right ){return this->key <= right.key;}
    inline bool operator>=(const TreeNode &right ){return this->key >= right.key;}

};

template<typename E, typename V> TreeNode<E, V>::TreeNode()
{
  left = NULL;//nullptr
  right = NULL;
}

template<typename E, typename V> TreeNode<E, V>::TreeNode(const E& newKey, const V& newData, TreeNode* _left,  TreeNode* _right)
{
  left = _left;
  right = _right;
  key = newKey;
  data = newData;
}

template<typename E, typename V> TreeNode<E, V>::~TreeNode()
{
  left = NULL;
  right = NULL;
}
#endif
