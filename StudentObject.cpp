#include "StudentObject.h"
#include <string>

StudentObject::StudentObject(int newId, std::string newName, std::string newLevel, std::string newField, int newAdviserId, float newGpa)
{
  id = newId;
  personName = newName;
  academicLevel = newLevel;
  academicField = newField;
  adviserId = newAdviserId;
  gpa = newGpa;
}
/*StudentObject::StudentObject(std::string stringObject)
{

  stringstream inquisition(stringObject);
  std::vector<string> theGreatSeperator;

  int questionCounter = 0;
  while(inquisition.good())
  {
    questionCounter++;
    string suspect;
    getline(inquisition, suspect, ',');
    setField(questionCounter, theGreaSeperator.push_back(suspect));
  }
}*/
StudentObject::~StudentObject()
{

}

void StudentObject::setField(int spot, std::string value)
{
  switch (spot) {
    case 0:
      break;
    case 1:
      break;
    case 2:
      break;
  }
}

std::string StudentObject::toString()
{
  std::string stringObject = PersonObject::toString();
  stringObject += to_string(adviserId);
  stringObject += ",";
  stringObject += to_string(gpa);
  stringObject += ",";
  return stringObject;
}

void StudentObject::print()
{
  PersonObject::print();
  std::cout << "     Adviser ID: " << adviserId << std::endl;
  std::cout << "     GPA: " << gpa << std::endl;
}
