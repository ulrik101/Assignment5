#ifndef FACULTYOBJECT_H
#define FACULTYOBJECT_H
#include <iostream>
#include "PersonObject.h"
#include "DoubleLinkedList.h"

using namespace std;
class FacultyObject : public PersonObject
{
  public:
    FacultyObject(int newId = -1, std::string newName = "undefined", std::string newLevel = "undefined", std::string newField = "undefined");
    ~FacultyObject();

/*
    const int& getAdviserId() const {return adviserId;}
    void setAdviserId(const int& newAdviserId){adviserId=newAdviserId;}
    */

    std::string toString();
    void print();
    bool hasAdvisees() const;

    void printAdvisees();
    const DoubleLinkedList<int>* returnAdvisees() const;
    void addAdvisee(int id);
    void removeAdvisee(int id);


  //private:
    DoubleLinkedList<int> adviseeList;
};

#endif
