//Tyler Seppala
//2297817
//seppala@chapman.edu
//CPSC 350-02
//Assignment 5 (Database)

//Header to faculty class, which stores information for each faculty member

#include <iostream>
#include <string>
#include "Student.h"
#include "GenTree.h"

using namespace std;

class Faculty : public Person
{
public:
  Faculty();
  Faculty(int idNum, string fullName, string personLevel, string departmentName);
  ~Faculty();

  void addAdvisee(int studentId, Student *student);
  void removeAdvisee(int studentId);
  void printFacMember();
  void printAdvisees();
  string toString();

  string department;//Holds faculty member's department
  GenTree<Student> *advisees;//Tree of faculty member's advisees 
};
