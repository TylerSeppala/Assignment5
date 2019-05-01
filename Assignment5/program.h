//Tyler Seppala
//2297817
//seppala@chapman.edu
//CPSC 350-02
//Assignment 5 (Database)

//Header to program class, where student and faculty trees are stored

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "Faculty.h"
#include "GenStack.h"

using namespace std;

class Program
{
public:
  Program();

  void loadTables();
  void userIn();
  void printStudents();
  void printFaculty();
  void addStudent(string fullName, string personLevel, string studentMajor, double studentGpa, int advisor);
  void removeStudent(int id);
  void addFaculty(string fullName, string personLevel, string departmentName);
  void removeFaculty(int id);
  void writeFiles();
  void saveState();
  void rollBack();
  int saveInt(int input);

  const string facTable = "facultyTable";//name of faculty save file
  const string studTable = "studentTable";//name of student save file
  bool restart = true;//used to determine whether the program will continue to loop
  string endChoice;//user determines whether they want to continue
  GenTree<Student> *studentTable;//stores all students
  GenTree<Faculty> *facultyTable;//stores all faculty members
  GenStack<GenTree<Student>*> *studentSaves;//stores each save state of student table
  GenStack<GenTree<Faculty>*> *facultySaves;//stores each save state of faculty table 
};
