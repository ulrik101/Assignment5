#include <iostream>
//#include <experimental/random>
#include <sstream>
#include <string>
#include "StudentObject.h"
#include "FacultyObject.h"
#include "DoubleLinkedList.h"
#include "database.h"
#include "SnapShotManager.h"


#include "BST.h"
#include "Csv.h"
using namespace std;


database::database()
{

}
database::~database()
{
    delete masterStudent;
    delete masterFaculty;
}

int database::run()
{
    //generateData(10);
    setupSnapshot();
    loadDatabases();

    takeSnapshot(false);
    takeSnapshot(true);
    while (true)
    {
        printMenu();
        int choice = intInput("Enter a digit from the above choices: ");

        if (choice == 16)
        {
            return EXIT_SUCCESS;
        }
        commandBuilder(choice);
        switch (choice)
        {
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
            takeSnapshot(false);
            takeSnapshot(true);
            break;
        default:
            break;
        }
    }
}


bool database::isValidId(bool isStudent, int id)
{
    if (isStudent)
    {
        return !masterStudent->contains(id);
    }
    else
    {
        return !masterFaculty->contains(id);
    }
}

void database::loadDatabases()
{
    //load from facultyTable and studentTable files and set them to the objects
    loadData(false, "facultyTable.csv");

    loadData(true, "studentTable.csv");
}

int database::generateID(bool generateStudent)
{
    while (true)
    {
        int id = random(100000, 999999);

        if (generateStudent)//generate student ID
        {
            std::cout << "id to test: " << id << std::endl;
            std::cout << "contains: " << masterStudent->contains(id) << std::endl;

            if (!masterStudent->contains(id))
            {

                return id;
            }
        }
        else//generate faculty ID
        {
            id += 11000000;
            if (!masterFaculty->contains(id))
            {
                return id;
            }
        }
    }
}
int database::random(int min, int max)
{
    static int seed = 36;
    int number = ((seed * 3621) % max) + min;
    seed += 1;
    return number;
}
void database::generateData(int facultyNum)
{
    std::string firstNameList[10] = { "HereComes","MyMan","BabyFace","FlatFoot","Big","Lil","BaggyPants","Crazy","Thuggin","Carol" };
    std::string lastNameList[10] = { "DatBoi","Memeo","Linstead","Bojack","Rick","Morty","Siri","Adolf","Stalin","Mao" };
    std::string studentLevelList[5] = { "Freshman","Sophomore","Junior","Senior","Graduate" };
    std::string facultyLevelList[5] = { "Lecturer","Assistant Prof.","Associate Prof.","Prof.","Tenured Prof." };
    std::string fieldList[5] = { "DA","CPSC","Criminal Justice","Engineering","Chemistry" };


    for (int i = 1; i < facultyNum; i++)
    {
        int facultyId = generateID(false);
        std::string facultyName = ((firstNameList[random(0, 9)]) + " " + lastNameList[random(0, 9)]);
        std::string facultyLevel = facultyLevelList[random(0, 4)];
        std::string facultyField = fieldList[random(0, 4)];

        FacultyObject *facultyMember = new FacultyObject(facultyId, facultyName, facultyLevel, facultyField);//create new faculty object

        for (int x = 1; x <= 4; x++)//assign four students
        {

            int studentID = generateID(true);
            std::string studentName = ((firstNameList[(0, 9)]) + " " + lastNameList[random(0, 9)]);
            std::string studentLevel = studentLevelList[random(0, 4)];
            std::string studentField = fieldList[random(0, 4)];
            float studentGpa = ((float)random(0, 400)) / 100;

            StudentObject *student = new StudentObject(studentID, studentName, studentLevel, studentField, facultyId, studentGpa);

            facultyMember->addAdvisee(studentID);
            masterStudent->insert((student->getId()), student);
            student->print();

        }
        //add faculty to database
        masterFaculty->insert((facultyMember->getId()), facultyMember);
    }
}
void database::loadData(bool loadStudentTable, std::string fileName)
{
    std::cout << fileName << endl;
    ifstream file(fileName);
    if(file.is_open())
    {
        while(!file.eof())
        {
            std::string local_string;
            std::getline(file, local_string);
            //std::cout << local_string << endl;
            //file >> local_string;
            if(local_string != "")
            {
                personFromString(loadStudentTable, local_string);
            }
            else
            {

                break;
            }
        }
    }
    file.close();
}

void database::commitData(bool writeStudentTable, std::string fileName)
{
    if (writeStudentTable)
    {
        masterStudent->treeToCsv("studentTable.csv", masterStudent->getRoot());
    }
    else
    {
        masterFaculty->treeToCsv("facultyTable.csv", masterFaculty->getRoot());
    }
}

void database::printAllInfo(bool printStudents, bool printAscending) const
{
    if (printStudents)//print student list
    {
        if (printAscending)//print in ascending
        {

            masterStudent->printTreeData(true);
        }
        else//print in descending
        {
            masterStudent->printTreeData(false);
        }
    }
    else//print faculty list
    {
        if (printAscending)//print in ascending
        {
            masterFaculty->printTreeData(true);
        }
        else//print in descending
        {
            masterFaculty->printTreeData(false);
        }
    }
}
void database::printInfo(bool printStudent, int idNum) const
{
    if (printStudent)//print student info
    {
        masterStudent->getNode(idNum)->data->print();
        //student.print();
    }
    else//print faculty info
    {
        masterFaculty->getNode(idNum)->data->print();
        //faculty.print();
    }
}
void database::printRelationship(bool adviseeToAdviser, int id) const
{
    if (adviseeToAdviser)//print the advisees' adviser
    {
        //StudentObject student = masterStudent->getNode(id)->data;
        std::cout << id << "/" << masterStudent->getNode(id)->data->getName() << "'s Adviser: " << endl;
        masterFaculty->getNode(masterStudent->getNode(id)->data->getAdviserId())->data->print();
        //faculty.print();

    }
    else//print the adviser's advisees
    {
        std::cout << "Print advisees" << endl;

        std::string factulyToString = masterFaculty->getNode(id)->data->toString();
        std::cout << factulyToString << endl;

        
        int otherId;

        std::string editableString = factulyToString;

        std::string csvSeperator = ",";
        std::string substring;
        int position = 0;
        int counter = 0;

        while ((position = editableString.find(csvSeperator)) != std::string::npos)
        {
            counter++;
            substring = editableString.substr(0, position);
            stringstream stream(substring);


            if (counter > 4)
            {
                stream >> otherId;
                std::cout << otherId << endl;

                printInfo(true,otherId);
            }

            editableString.erase(0, position + csvSeperator.length());
        }
    }
}
void database::addStudent(int studentId, std::string personName, std::string level, std::string field, int facultyId, float gpa) const
{
    StudentObject *student = new StudentObject(studentId, personName, level, field, facultyId, gpa);

    FacultyObject *facultyMember(masterFaculty->getNode(facultyId)->data);
    facultyMember->addAdvisee(studentId);
    //facultyMember->removeAdvisee(studentId);
    //masterFaculty->getNode(facultyId)->data->addAdvisee(studentId);//This is the issue right here.

    masterStudent->insert(studentId, student);

    student->print();
}



void database::deleteStudent(int id)
{
    const int adviserId = masterStudent->getNode(id)->data->getAdviserId();

    masterFaculty->getNode(adviserId)->data->removeAdvisee(id);

    masterStudent->getNode(id)->data->setAdviserId(-1);

    masterStudent->deleteNode(id);
}


void database::addFaculty(int facultyId, std::string personName, std::string level, std::string field)
{
    FacultyObject *facultyMember = new FacultyObject(facultyId, personName, level, field);//create new faculty object
    masterFaculty->insert(facultyId, facultyMember);
}
void database::deleteFaculty(int facultyId)
{

    if(masterFaculty->getNode(facultyId)->data->hasAdvisees())
    {
        std::cout << "Can not not delete faculty member. Faculty Member has Advisees. " << endl;
    }
    else
    {
        std::cout << "Deleted Faculty Member. " << endl;

        masterFaculty->deleteNode(facultyId);
    }
}
void database::changeAdvisor(int studentId, int facultyId)
{

    masterFaculty->getNode(masterStudent->getNode(studentId)->data->getAdviserId())->data->removeAdvisee(studentId);
    masterStudent->getNode(studentId)->data->setAdviserId(facultyId);
    //masterFaculty->getNode(facultyId)->data->removeAdvisee(studentId);
    masterFaculty->getNode(facultyId)->data->addAdvisee(studentId);
}

void database::removeAdvisee(int facultyId, int studentId)
{
    //masterFaculty->getNode(facultyId)->data->print();

    //FacultyObject fMember = masterFaculty->getNode(facultyId)->data;

    masterFaculty->getNode(facultyId)->data->removeAdvisee(studentId);
}

void database::takeSnapshot(bool studentDatabase)
{
    std::string fileName = "studentTable.csv";
    if (!studentDatabase)
    {
        fileName = "facultyTable.csv";
    }
    std::string newFileName = "StudentHistory_1.csv";
    if (!studentDatabase)
    {
        newFileName = "FacultyHistory_1.csv";
    }


    //move snapshots over
    prepareSnapShot(studentDatabase);

    //commit to table
    commitData(studentDatabase, fileName);

    //take current table, rename it to snapshot one.
    renameFile(fileName, newFileName);

    //commit to table again
    commitData(studentDatabase, fileName);
    
}

void database::rollback()
{
    //clear current table
    masterStudent->recDelete(masterStudent->getRoot());
    masterFaculty->recDelete(masterFaculty->getRoot());

    //take old snapshot and rename to table
    renameFile("FacultyHistory_1.csv", "facultyTable.csv");
    renameFile("StudentHistory_1.csv", "studentTable.csv");

    //rename rest
    deleteSnapshot(false);
    deleteSnapshot(true);

    //load table
    loadDatabases();



}





//menu stuff

void database::printMenu()
{
    int index = 1;
    std::cout << "==============================================================================" << std::endl;
    std::cout << index++ << ".\tPrint all students and their information (sorted by ascending id #)." << std::endl;
    std::cout << index++ << ".\tPrint all students and their information (sorted by descending id #)." << std::endl;
    std::cout << index++ << ".\tPrint all faculty and their information (sorted by ascending id #)." << std::endl;
    std::cout << index++ << ".\tPrint all faculty and their information (sorted by descending id #)." << std::endl;
    std::cout << index++ << ".\tFind and display student information given the students id." << std::endl;
    std::cout << index++ << ".\tFind and display faculty information given the faculty id." << std::endl;
    std::cout << index++ << ".\tGiven a student’s id, print the name and info of their faculty advisor." << std::endl;
    std::cout << index++ << ".\tGiven a faculty id, print ALL the names and info of his/her advisees." << std::endl;
    std::cout << index++ << ".\tAdd a new student." << std::endl;
    std::cout << index++ << ".\tDelete a student given the id." << std::endl;
    std::cout << index++ << ".\tAdd a new faculty member." << std::endl;
    std::cout << index++ << ".\tDelete a faculty member given the id." << std::endl;
    std::cout << index++ << ".\tChange a student’s advisor given the student id and the new faculty id." << std::endl;
    std::cout << index++ << ".\tRemove an advisee from a faculty member given the ids." << std::endl;
    std::cout << index++ << ".\tRollback." << std::endl;
    std::cout << index++ << ".\tExit." << std::endl;
    //std::cout << index++ << ".\tCheck for Memory Leaks." << std::endl << std::endl;

    std::cout << "==============================================================================" << std::endl;

}

void database::commandBuilder(int command)
{
    int studentId;
    int facultyId;
    std::string personName;
    std::string level;
    std::string field;
    float gpa;

    switch (command) {
    case 1:

        printAllInfo(true, true);
        break;
    case 2:
        printAllInfo(true, false);
        break;
    case 3:
        printAllInfo(false, true);
        break;
    case 4:
        printAllInfo(false, false);
        break;
    case 5:
        printInfo(true, getValidIdInput(true,"Enter Student ID: \n"));
        break;
    case 6:
        printInfo(false, getValidIdInput(false, "Enter Faculty Member ID: \n"));
        break;
    case 7:
        printRelationship(true, getValidIdInput(true, "Enter Student ID: \n"));
        break;
    case 8:
        printRelationship(false, getValidIdInput(false, "Enter Faculty ID: \n"));
        break;
    case 9://add new student
        studentId = getNewIdInput(true, "Enter New Student ID: \n");
        personName = getString("Enter First Name:\n");
        personName += " ";
        personName += getString("Enter Last Name:\n");

        level = getString("Enter Student Acedemic Level:\n");
        field = getString("Enter Student Acedemic Field:\n");
        facultyId = getValidIdInput(false, "Enter Faculty ID: \n");
        gpa = gpaInput("Enter Student GPA. Must be betweel 0 and 4;\n");
        addStudent(studentId, personName, level, field, facultyId, gpa);


        break;
    case 10:
        studentId = getValidIdInput(true, "Enter Student ID: \n");
        deleteStudent(studentId);
        break;
    case 11://add new faculty member
        facultyId = getNewIdInput(false, "Enter New Faculty ID: \n");
        personName = getString("Enter First Name:(No commas or new lines)\n");
        personName += " ";
        personName += getString("Enter Last Name:(No commas or new lines)\n");

        level = getString("Enter Faculty Acedemic Level:(No commas or new lines)\n");
        field = getString("Enter Faculty Acedemic Field:(No commas or new lines)\n");

        addFaculty(facultyId, personName, level, field);
        break;
    case 12:
        facultyId = getValidIdInput(false, "Enter Faculty ID: \n");

        deleteFaculty(facultyId);
        break;
    case 13:
        studentId = getValidIdInput(true, "Enter Student ID: \n");
        facultyId = getValidIdInput(false, "Enter New Faculty ID: \n");
        changeAdvisor(studentId,facultyId);
        break;
    case 14:

        studentId = getValidIdInput(true, "Enter Student ID: \n");
        facultyId = getValidIdInput(false, "Enter Faculty ID: \n");
        removeAdvisee(facultyId, studentId);
        break;
    case 15:
        std::cout << "This is the one feature that does not work fully. History is fully recorded within the csv files, but there are issues with loading it back. \n\n However, loading back into the program after doing a rollback works. To test this, uncomment line 475 from database.cpp (rollback(); \n\n\n I have spent three hours on this exact issue and have gotten nowhere.)" << endl;
        //rollback();
        break;
    //case 17:
        //std::cout << "There Aren't Any. I checked." << endl;

        //break;
    //case 20://Developer stuff
        //std::cout << "Secret Option Selected:" << endl;

        //addFaculty(666, "Moe Jr.", "Doctor", "BioChem");
        //addFaculty(3621, "Moey iff.", "Doctor", "Art");
        //addStudent(1, "David Ulriksen", "Junior", "DA", 666, 3.75);
        //addStudent(2, "Jamie Newbon", "Masters", "CPSC", 666, 4.99);
        //personFromString(false, "3,mr.memes,professor,MEMES,1337,123456789,");

        //personFromString(true,"3,IWannaDie,Freshman,NONE,3,2.0,");

        //commitData(true, "studentTable.csv");
        //commitData(false, "facultyTable.csv");
        //takeSnapshot(true);
        //takeSnapshot(false);

        break;
    default:
        std::cout << "That value was not recognized." << endl;
        break;



    }
}
int database::getNewIdInput(bool isStudent, std::string prompt)//get a new unique id
{
    while (true)
    {
        int id;
        id = intInput(prompt);
        if (isValidId(isStudent, id))
        {
            return id;
        }
        std::cout << "Id Taken. Try Again: " << endl;
    }
}



int database::getValidIdInput(bool isStudent, std::string prompt)//for checking if there is already an id
{
    while (true)
    {
        int id;
        id = intInput(prompt);
        if (!isValidId(isStudent, id))
        {
            return id;
        }
        std::cout << "Invalid Id. Not Found. Try Again: " << endl;
    }
}

std::string database::getString(std::string prompt)
{
    std::cout << prompt << endl;
    std::string input = "";
    std::cin >> input;

    stringstream stream(input);

    stream >> input;

    return input;
}

void database::personFromString(bool isStudent,std::string info)
{
    int selfId;
    std::string personName;
    std::string level;
    std::string field;
    int otherId;
    float gpa;


    std::string editableString = info;

    std::string csvSeperator = ",";
    std::string substring;
    int position = 0;
    int counter = 0;

    while((position = editableString.find(csvSeperator)) != std::string::npos)
    {
        counter++;
        substring = editableString.substr(0, position);
            stringstream stream(substring);

            switch (counter)
            {
            case 1:

                stream >> selfId;
                break;
            case 2:
                personName = substring;
                break;
            case 3:
                level = substring;
                break;
            case 4:
                field = substring;
                break;
            case 5:
                if (isStudent)
                {
                    stream >> otherId;
                }
                break;
            case 6:
                if (isStudent)
                {
                    stream >> gpa;
                }
                break;
            }
            if (counter <= 4 || isStudent)
            {
                editableString.erase(0, position + csvSeperator.length());


            }
            if (counter == 6)
            {
                break;
            }


        

    }
    if (isStudent)
    {
        addStudent(selfId, personName, level, field, otherId, gpa);

    }
    else
    {
        addFaculty(selfId, personName, level, field);

        while ((position = editableString.find(csvSeperator)) != std::string::npos)
        {
            substring = editableString.substr(0, position);
            stringstream stream(substring);
            stream >> otherId;
            //std::cout << otherId << endl;
            masterFaculty->getNode(selfId)->data->addAdvisee(otherId);
            editableString.erase(0, position + csvSeperator.length());
        }
        //std::cout << endl << endl;

    }
}

void database::facultyFromString(std::string info)
{

}

int database::intInput(std::string prompt)
{
    while (true)
    {
        try
        {
            std::string numStr;
            std::cout << prompt << std::endl;

            std::cin >> numStr;

            stringstream stream(numStr);
            int num;
            stream >> num;

            if (num > 0 || num < 0)
            {
                return num;

            }
        }
        catch (const std::exception& e)
        {

        }
    }

}
float database::gpaInput(std::string prompt)
{
    while (true)
    {
        try
        {
            std::string numStr;
            std::cout << prompt << std::endl;

            std::cin >> numStr;

            stringstream stream(numStr);
            float num;
            stream >> num;

            if (num >= 0 && num <= 4)
            {
                return num;

            }
        }
        catch (const std::exception& e)
        {

        }
    }

}
