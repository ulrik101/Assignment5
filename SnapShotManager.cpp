#include <iostream>
#include <fstream>
#include "SnapShotManager.h"
#include "stdio.h"

using namespace std;

void setupSnapshot()//must be used at start
{
  for(int i = 1; i <= 10;i++)
  {
    createFile(true,i);
    createFile(false,i);
  }
}


void createFile(bool isStudent, int num)
{
  std::string fileName;
  if(isStudent)
  {
    fileName = "StudentHistory_";
  }
  else
  {
    fileName = "FacultyHistory_";
  }
  fileName+= to_string(num);
  fileName+=".csv";
  std::ofstream file(fileName);
  file.close();
}
void renameFile(std::string oldName, std::string newName)//internal use
{
  const char * temp1 = oldName.c_str();
  const char * temp2 = newName.c_str();
  rename(temp1,temp2);
  //std::cout<<temp1<<" To "<<temp2<<endl;
}//internal use

void prepareSnapShot(bool isStudent)
{
  std::string fileName;

  if(isStudent)
  {
    fileName = "StudentHistory_";
  }
  else
  {
    fileName = "FacultyHistory_";
  }

  remove((fileName + "10.csv").c_str());//removing end of history

  for(int i = 10; i > 1;i--)//renaming files 1-9 to be 2-10
  {
    int temp = i-1;
    std::string oldFileName = (fileName + to_string(temp) + ".csv");
    std::string newFileName = (fileName + to_string(i) + ".csv");
    renameFile(oldFileName,newFileName);
  }
  createFile(isStudent,1);
}
void deleteSnapshot(bool isStudent)
{
  std::string fileName;

  if(isStudent)
  {
    fileName = "StudentHistory_";
  }
  else
  {
    fileName = "FacultyHistory_";
  }

  remove((fileName + "1.csv").c_str());//removing end of history

  for(int i = 2; i <= 10;i++)//renaming files 1-9 to be 2-10
  {
    int temp = i-1;
    std::string oldFileName = (fileName + to_string(i) + ".csv");
    std::string newFileName = (fileName + to_string(temp) + ".csv");
    renameFile(oldFileName,newFileName);
  }
  createFile(isStudent,10);



}
