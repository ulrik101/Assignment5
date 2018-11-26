#include "BST.h"
#include "StudentObject.h"
#include "FacultyObject.h"
#ifndef DATABASE_H
#define DATABASE_H
using namespace std;

class database
{
public:
    database();
    ~database();
    int run();


    void loadDatabases();
    int generateID(bool generateStudent);
    void generateData(int facultyNum);
    bool isValidId(bool isStudent, int id);
    void loadData(bool loadStudentTable, std::string fileName);
    void commitData(bool writeStudentTable, std::string fileName);
    void printAllInfo(bool printStudents, bool printAscending) const;
    void printInfo(bool printStudent, int idNum) const;
    void printRelationship(bool adviseeToAdviser, int id) const;
    void addStudent(int studentId, 
                    std::string personName,
                    std::string level, std::string field, int facultyId,
                    float gpa) const;

    void deleteStudent(int id);

    void addFaculty(int facultyId, std::string personName, std::string level, std::string field);
    void deleteFaculty(int facultyId);
    void changeAdvisor(int studentId, int facultyId);
    void removeAdvisee(int facultyId, int studentId);
    void takeSnapshot(bool studentDatabase);
    void rollback();



    int random(int min, int max);


    //menu stuff
    static void printMenu();
    int intInput(std::string prompt);
    void commandBuilder(int command);
    int getNewIdInput(bool isStudent, std::string prompt);
    float gpaInput(std::string prompt);


    int getValidIdInput(bool isStudent, std::string prompt);
    std::string getString(std::string prompt);

private:
    void personFromString(bool isStudent, std::string info);
    void facultyFromString(std::string info);

    BST<int, StudentObject*>* masterStudent = new BST<int, StudentObject*>([](StudentObject* data)-> void
    {
        delete data;
    }); //telling the BST how to delete its data.
    BST<int, FacultyObject*>* masterFaculty = new BST<int, FacultyObject*>([](FacultyObject* data)-> void
    {
        delete data;
    });
};
#endif
