#ifndef STUDENTOBJECT_H
#define STUDENTOBJECT_H
#include <iostream>
#include "PersonObject.h"
using namespace std;
class StudentObject : public PersonObject
{
  public:
    StudentObject(int newId = -1, std::string newName = "undefined", std::string academicLevel = "undefined", std::string academicField = "undefined", int newAdviserId = -1, float newGpa = 0.0);
    //StudentObject(std::string stringObject);
    ~StudentObject();


    const int& getAdviserId() const {return adviserId;}
    void setAdviserId(const int& newAdviserId){adviserId=newAdviserId;}

    const float& getGpa() const {return gpa;}
    void setGpa(const float& newGpa){gpa=newGpa;}

    std::string toString();
    void print();


  private:
    void setField(int spot, std::string value);
    int adviserId;
    float gpa;
};

#endif
