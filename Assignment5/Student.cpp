//Tyler Seppala
//2297817
//seppala@chapman.edu
//CPSC 350-02
//Assignment 5 (Database)

//Implementation of student class, which allows student info to be manipulated 

#include <iostream>
#include <string>
#include "Student.h"

using namespace std;

Student::Student()//default constructor
{
  id = 0;
  name = "";
  level = "";
  major = "";
  gpa = 0;
  advisorId = 0;
}

Student::Student(int idNum, string fullName, string personLevel, string studentMajor, double studentGpa, int advisor)//constructor for a known student
{
  id = idNum;
  name = fullName;
  level = personLevel;
  major = studentMajor;
  gpa = studentGpa;
  advisorId = advisor;
}

void Student::printStudent()//prints all of student's info to console
{
  cout << id << endl;
  cout << "----------------" << endl;
  cout << "Name: " << name << endl;
  cout << "Level: " << level << endl;
  cout << "Major: " << major << endl;
  cout << "GPA: " << gpa << endl;
  cout << "Advisor ID: " << advisorId << endl;
  cout << endl;
}

string Student::toString()//returns string containing all of student's info
{
  return (to_string(id) + "\n----------------" + "\nName: " + name + "\nLevel: " + level + "\nMajor: " + major + "\nGPA: " + to_string(gpa) + "\nAdvisor ID: " + to_string(advisorId) + "\n\n");
}
