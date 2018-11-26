#ifndef CSV_H
#define CSV_H
#include <iostream>
#include <fstream>

class Csv
{
  public:
    Csv(std::string fileName);
    ~Csv();
    void stringToCsv(std::string inputString);

  private:
    std::ofstream openFile;
    std::string fileName = "";
};

Csv::Csv(std::string newFileName)
{
  fileName = newFileName;
  openFile.open(fileName);
}



Csv::~Csv()
{
  openFile.flush();
  openFile.close();
}



void Csv::stringToCsv(std::string inputString)
{
  openFile << (inputString + "\n");
}
#endif