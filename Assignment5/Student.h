//Tyler Seppala
//2297817
//seppala@chapman.edu
//CPSC 350-02
//Assignment 5 (Database)

//Header to student class, which stores all the info for each student 

#include <iostream>
#include "Person.h"

using namespace std;

class Student : public Person
{
public:
  Student();
  Student(int idNum, string fullName, string personLevel, string studentMajor, double studentGpa, int advisor);

  void addToAdvisor(int advisor);
  void printAdvisorInfo();
  void changeAdvisor(int newAdvisor);
  void printStudent();
  string toString();

  string major;
  double gpa;
  int advisorId;
};
