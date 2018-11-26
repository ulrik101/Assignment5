#ifndef PERSONOBJECT_H
#define PERSONOBJECT_H
#include <iostream>
using namespace std;
class PersonObject
{
  public:
    PersonObject(int newId = -1, std::string newName = "undefined", std::string academicLevel = "undefined", std::string academicField = "undefined");
    ~PersonObject();


    const int& getId() const {return id;}
    void setId(const int& newId){id=newId;}

    const std::string& getName() const{return personName;}
    void setName(const std::string& newName){personName=newName;}

    const std::string& getAcademicLevel() const{return academicLevel;}
    void setAcademicLevel(const std::string& newAcademicLevel){academicLevel=newAcademicLevel;}

    const std::string& getAcademicField() const{return academicField;}
    void setAcademicField(const std::string& newAcademicField){academicField=newAcademicField;}

    std::string toString();
    void print();




    inline bool operator==(const PersonObject &right ) const {return (this->id==right.getId());}
    inline bool operator!=(const PersonObject &right ) const {return (this->id!=right.getId());}
    inline bool operator<(const PersonObject &right ) const {return (this->id<right.getId());}
    inline bool operator>(const PersonObject &right ) const {return (this->id>right.getId());}
    inline bool operator<=(const PersonObject &right ) const {return (this->id<=right.getId());}
    inline bool operator>=(const PersonObject &right ) const {return (this->id>=right.getId());}

  protected:
    int id;
    std::string personName;
    std::string academicLevel;
    std::string academicField;
};

#endif
