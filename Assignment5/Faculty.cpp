//Tyler Seppala
//2297817
//seppala@chapman.edu
//CPSC 350-02
//Assignment 5 (Database)

//Implementation of faculty class, which allows each faculty member's data to be managed 

#include <iostream>
#include <string>
#include "Faculty.h"

using namespace std;

Faculty::Faculty(int idNum, string fullName, string personLevel, string departmentName)//constructor for a known student
{
  id = idNum;
  name = fullName;
  level = personLevel;
  department = departmentName;
  advisees = new GenTree<Student>();
}

Faculty::~Faculty()
{
  delete advisees;
}

void Faculty::addAdvisee(int studentId, Student *student)//inserts student into advisee tree
{
  advisees->insert(studentId, student);
}

void Faculty::removeAdvisee(int studentId)//removes student from advisee tree
{
  advisees->deleteNode(studentId);
}

void Faculty::printFacMember()//used to print faculty member's info
{
  cout << id << endl;
  cout << "----------------" << endl;
  cout << "Name: " << name << endl;
  cout << "Level: " << level << endl;
  cout << "Department: " << department << endl;
  cout << endl;
}

string Faculty::toString()//returns a string containing faculty member's info
{
  return (to_string(id) + "\n----------------" + "\nName: " + name + "\nLevel: " + level + "\nDepartment: " + department + "\n\n");
}

void Faculty::printAdvisees()
{
  cout << endl;
  cout << advisees->treeString() << endl;
}
