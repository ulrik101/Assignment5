#include <string>
#include "PersonObject.h"
PersonObject::PersonObject(int newId, std::string newName, std::string newLevel, std::string newField)
{
  id = newId;
  personName = newName;
  academicLevel = newLevel;
  academicField = newField;
}
PersonObject::~PersonObject()
{

}
std::string PersonObject::toString()
{
  std::string stringObject;
  stringObject+=to_string(id);
  stringObject+=",";
  stringObject+=personName;
  stringObject+=",";
  stringObject+=academicLevel;
  stringObject+=",";
  stringObject+=academicField;
  stringObject+=",";
  return stringObject;
}
void PersonObject::print()
{
  std::cout << "ID: " << id << std::endl;
  std::cout << "     Name: " << personName.c_str() << std::endl;
  std::cout << "     Level: " << academicLevel.c_str() << std::endl;
  std::cout << "     Field: " << academicField.c_str() << std::endl;

}
