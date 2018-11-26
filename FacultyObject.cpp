#include "FacultyObject.h"
#include <string>

FacultyObject::FacultyObject(int newId, std::string newName, std::string newLevel, std::string newField)
{
  id = newId;
  personName = newName;
  academicLevel = newLevel;
  academicField = newField;
}
FacultyObject::~FacultyObject()
{
}

std::string FacultyObject::toString()
{
  std::string stringObject = PersonObject::toString();
  for(int i = 0; i < adviseeList.getSize(); i++)
  {
    stringObject+= (to_string(adviseeList.returnData(i)) + ",");
  }
  return stringObject;
}
void FacultyObject::print()
{
  PersonObject::print();
  std::cout << "     Advisees: (" << adviseeList.getSize() << ")" << std::endl;


  for(int i = 0; i < adviseeList.getSize(); i++)
  {
    std::cout << "        "<<adviseeList.returnData(i)<< std::endl;
  }
}

bool FacultyObject::hasAdvisees() const
{
    return !adviseeList.isEmpty();
}


void FacultyObject::printAdvisees()
{
  std::cout <<id<<"/"<<personName.c_str() <<"'s Advisees: ("<< adviseeList.getSize() <<")" << std::endl;

  for(int i = 0; i < adviseeList.getSize(); i++)
  {
    std::cout << "   "<<adviseeList.returnData(i)<< std::endl;

  }
}
const DoubleLinkedList<int>* FacultyObject::returnAdvisees() const
{
  return &adviseeList;
}

void FacultyObject::addAdvisee(int id)
{
  adviseeList.insertFront(id);
}


void FacultyObject::removeAdvisee(int id)
{
  //DoubleLinkedNode<int> *node = adviseeList->find(id);
  int pos = adviseeList.find(id);
  //std::cout << "pos: " << pos << endl;
  adviseeList.deletePos(pos);


}
