#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H
#include <iostream>
#include "DoubleLinkedNode.h"
using namespace std;
template <typename E>
class DoubleLinkedList
{
  public:
    DoubleLinkedList();
    ~DoubleLinkedList();

    bool isEmpty() const;
    const E& getFront();
    DoubleLinkedNode<E> * getFrontNode() const{return front;};
    DoubleLinkedNode<E> * getBackNode() const{return back;};


    const E& getBack();
    void insertPos(const E& e, int pos);//help
    void insertFront(const E& e);
    const E& removeFront();

    void insertAfter(DoubleLinkedNode<E>* node, const int num);
    void insertBefore(DoubleLinkedNode<E>* node, const int num);
    void insertBack(const E& e);
    const E& removeBack();

    const E& returnData(int pos) const;
    bool deletePos(int pos);

    //DoubleLinkedNode *removeNode(int key);//help


    int find(const E& e) const;

    unsigned int getSize() const;
    void printList();


  private:
    DoubleLinkedNode<E> *front = NULL;
    DoubleLinkedNode<E> *back = NULL;

    unsigned int size;

};
template<typename E> DoubleLinkedList<E>::DoubleLinkedList()
{
  front = NULL;
  back = NULL;
  size = 0;

}
template<typename E> DoubleLinkedList<E>::~DoubleLinkedList()
{
  while(front != NULL)
  {
    DoubleLinkedNode<E>* next = front->next;
    delete front;
    front = next;
  }
  front = NULL;
}

template<typename E> bool DoubleLinkedList<E>::isEmpty() const
{
  //return(front == NULL && back ==NULL);
  if(front == NULL)
  {
    return true;
  }
  return false;
}

template<typename E> const E& DoubleLinkedList<E>::getFront()
{
  if(front != NULL)
  {
    return front->data;
  }
  else
  {
    throw std::logic_error("Error: No Front to retrieve.");
  }
}

template<typename E> const E& DoubleLinkedList<E>::getBack()
{
  if(back != NULL)
  {
    return back->data;
  }
  else
  {
    throw std::logic_error("Error: No Back to retrieve.");
  }
}

template<typename E> void DoubleLinkedList<E>::insertAfter(DoubleLinkedNode<E>* node, const int num)
{
  if(node)//if node is not null
  {
    if(node->next)
    {
      DoubleLinkedNode<E> *newNode = new DoubleLinkedNode<E>(num, node, node->next);
      node->next->prev=newNode;
      node->next=newNode;
    }
    else
    {
      DoubleLinkedNode<E> *newNode = new DoubleLinkedNode<E>(num, node);
      node->next=newNode;
      back=newNode;
    }
  }
}
template<typename E> void DoubleLinkedList<E>::insertBefore(DoubleLinkedNode<E>* node, const int num)
{
  if(node)//if node is not null
  {
    if(node->prev)
    {


      DoubleLinkedNode<E> *newNode = new DoubleLinkedNode<E>(num, node->prev, node);
      node->prev->next=newNode;
      node->prev=newNode;
    }
    else
    {


      DoubleLinkedNode<E> *newNode = new DoubleLinkedNode<E>(num, NULL, node);
      node->prev=newNode;
      front=newNode;
    }
  }
}


template<typename E> void DoubleLinkedList<E>::insertPos(const E& e, int pos)
{
  if(front == NULL || pos == 0)//if there are no nodes or insert at pos 0
  {
    this->insertFront(e);
  }
  else if(pos >= size)
  {
    this->insertBack(e);
  }
  else
  {
    int idx = 0;
    DoubleLinkedNode<E> *prev = front;
    DoubleLinkedNode<E> *curr = front;
    DoubleLinkedNode<E> *newNode = new DoubleLinkedNode<E>(e);

    while(idx != pos)
    {
      prev = curr;
      curr = curr->next;
      ++idx;
    }
    //when it finds the position
    //add logic to verify value was found

    newNode->prev = prev;
    prev->next = newNode;

    newNode->next = curr;
    curr->prev = newNode;

    size++;

  }

}

template<typename E> void DoubleLinkedList<E>::insertFront(const E& e)
{
  DoubleLinkedNode<E> *node = new DoubleLinkedNode<E>(e);
  if(size == 0)
  {
    back = node;


  }
  else
  {
    front->prev = node;//front points to new
    node->next = front;//points to old front
  }
  front = node;
  size++;
}

template<typename E> const E& DoubleLinkedList<E>::removeFront()
{
  DoubleLinkedNode<E> *temp = front;
  if(front->next == NULL)//only node in list check
  {
    back = NULL;
  }
  else
  {
    front->next->prev = NULL;
  }
  front=front->next;
  temp->next=NULL;
  const E& val = temp->data;

  delete temp;
  size--;

  return val;
}

template<typename E> void DoubleLinkedList<E>::insertBack(const E& e)
{
  ++size;
  DoubleLinkedNode<E> *node = new DoubleLinkedNode<E>(e);

  if(front == NULL)
  {
    front = node;
  }
  else
  {
    back->next = node;//back points to new
    node->prev = back;//points to old back
  }
  back = node;
}


template<typename E> const E& DoubleLinkedList<E>::removeBack()
{

  DoubleLinkedNode<E> *temp = back;
  const E& val = temp->data;
  if(back != NULL)//if there is a node
  {
    if(back != front)//if back and front are different nodes
    {
      back=back->prev;
      temp->prev=NULL;
      back->next=NULL;
    }
    else//back and front are the same
    {
      temp->next = NULL;
      temp->prev = NULL;
      back = NULL;
      front = NULL;
    }
  }
  else//throw error as there are no nodes
  {
    throw std::logic_error("Error: No Back to remove.");
  }
  delete temp;
  size--;
  return val;
}

template<typename E> const E& DoubleLinkedList<E>::returnData(int pos) const
{
  int idx = 0;
  DoubleLinkedNode<E> *prev = front;
  DoubleLinkedNode<E> *curr = front;
  while(idx != pos)
  {
    prev = curr;
    curr = curr->next;
    ++idx;
  }
  const E& d = curr->data;
  return d;
}


template<typename E> bool DoubleLinkedList<E>::deletePos(int pos)
{
  if(pos >= 0)
  {
    int idx = 0;
    //DoubleLinkedNode<E> *prev = front;
    DoubleLinkedNode<E> *curr = front;

    while(curr != NULL && idx != pos)
    {
      //prev = curr;

      curr = curr->next;

      ++idx;
    }
    if(curr != NULL)
    {

      //when it finds the position
      //add logic to verify value was found
      if(curr->prev)
      { 
        curr->prev->next = curr->next;
      }
      if (back == curr)
      {
          back = curr->prev;
      }
      if (front == curr)
      {
          front = curr->next;
      }
      //curr->next = NULL;

      size--;
      delete curr;
	  curr = NULL;
      return true;
    }

  }
  return false;

}
/*template<typename E> const E& DoubleLinkedList<E>::deletePos(int pos)
{
  if(pos >= 0)
  {
    int idx = 0;
    DoubleLinkedNode<E> *prev = front;
    DoubleLinkedNode<E> *curr = front;

    while(idx != pos)
    {
      prev = curr;

      curr = curr->next;

      ++idx;
    }
    //when it finds the position
    //add logic to verify value was found

    prev->next = curr->next;
    curr->next = NULL;
    const E& d = curr->data;
    size--;
    delete curr;

    return d;
  }
  else
  {
    return NULL;
  }
}*/

/*
DoubleLinkedNode *DoubleLinkedList::removeNode(int key)//wtf
{
  DoubleLinkedNode *current = front;
  while(current->data =! key)
  {
    current = current->next;
    if(current == NULL)
    {
      return NULL;
    }
    //we found the value that needs to be removed
    if(current == front)
    {
      front = current->next;
    }
    if(current == back)
    {
      back = current->prev;
    }
    else
    {
      current->prev->next = current->next;
      current->next->prev = current->prev;
    }


    current->next = NULL;
    current->prev = NULL;

    --size;
    return current;
  }

}*/


template<typename E> int DoubleLinkedList<E>::find(const E& e) const
{
  int idx = -1;
  DoubleLinkedNode<E> *curr = front;

  while(curr != NULL)
  {

    ++idx;
		//std::cout<<"idx: "<<idx<<"   data: "<< curr->data<<endl;
    if(curr->data == e)
    {
      break;
    }
    else//did not find it, continue searching
    {
      curr = curr->next;
    }
  }

  if(curr == NULL)
  {
    idx = -1;
  }
  return idx;
}

template<typename E> unsigned int DoubleLinkedList<E>::getSize() const
{
  return size;
}

template<typename E> void DoubleLinkedList<E>::printList()
{
  if(front != NULL)
  {
    DoubleLinkedNode<E> *curr = front;
    while(curr)
    {
      cout<<curr->data<< endl;
      curr = curr->next;
    }
  }
}
#endif
