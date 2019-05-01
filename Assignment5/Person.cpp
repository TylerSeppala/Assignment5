//Tyler Seppala
//2297817
//seppala@chapman.edu
//CPSC 350-02
//Assignment 5 (Database)

//Header to person class, which gives constructor to be overloaded by inheriting classes 

#include <iostream>
#include "Person.h"

using namespace std;

Person::Person()
{
  id = 0;
  name = "";
  level = "";
}

Person::Person(int idNum, string fullName, string personLevel)
{
  id = idNum;
  name = fullName;
  level = personLevel;
}
