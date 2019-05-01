//Tyler Seppala
//2297817
//seppala@chapman.edu
//CPSC 350-02
//Assignment 5 (Database)

//Header to person class, which holds values common to students and faculty 

#include <iostream>

using namespace std;

class Person
{
public:
  Person();
  Person(int idNum, string fullName, string personLevel);

  int id;
  string name;
  string level;
};
