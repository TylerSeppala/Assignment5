//Tyler Seppala
//2297817
//seppala@chapman.edu
//CPSC 350-02
//Assignment 5 (Database)

//Implementation of program class, which utilizes user input to manipulate student and faculty tables.

#include <iostream>
#include "program.h"

Program::Program()
{
  studentTable = new GenTree<Student>;
  facultyTable = new GenTree<Faculty>;
  studentSaves = new GenStack<GenTree<Student>*>;
  facultySaves = new GenStack<GenTree<Faculty>*>;
  loadTables();
  saveState();
  userIn();
}

void Program::loadTables()//method too load save files into trees
{
  string line;//holds current line from file
  int idNum;//holds id number of current member
  string fullName;//holds name of current member
  string personLevel;//holds level of current member
  string studentMajor;//holds major of current student
  string departmentName;//holds department of current staff member
  double studentGpa;//holds gpa of current student
  int advisorId;//holds id of a student's advisor

  ifstream read_faculty (facTable);//for reading from faculty save file

  if (read_faculty.is_open())
  {
    while (getline(read_faculty,line))//reads through each line of faculty file creating faculty objects and adding them to the tree
    {
      idNum = stoi (line,nullptr,0);
      getline(read_faculty,line);
      getline(read_faculty,line);
      fullName = line.substr(6);
      getline(read_faculty,line);
      personLevel = line.substr(7);
      getline(read_faculty,line);
      departmentName = line.substr(12);
      Faculty *faculty = new Faculty(idNum, fullName, personLevel, departmentName);
      facultyTable->insert(idNum, faculty);
      getline(read_faculty,line);
    }
  }

  ifstream read_students (studTable);//for reading from student save file

  if (read_students.is_open())
  {
    while (getline(read_students,line))//reads through each line of student file creating student objects and adding them to the tree
    {
      idNum = stoi (line,nullptr,0);
      getline(read_students,line);
      getline(read_students,line);
      fullName = line.substr(6);
      getline(read_students,line);
      personLevel = line.substr(7);
      getline(read_students,line);
      studentMajor = line.substr(7);
      getline(read_students,line);
      studentGpa = stod (line.substr(5));
      getline(read_students,line);
      advisorId = stoi (line.substr(12),nullptr,0);
      Student *student = new Student(idNum, fullName, personLevel, studentMajor, studentGpa, advisorId);
      facultyTable->getValue(advisorId)->addAdvisee(idNum, student);
      studentTable->insert(idNum, student);
      getline(read_students,line);
    }
  }
}

void Program::userIn()//for dealing with user input
{
  string choiceStr;
  int choice;
  int id;
  string fullName;
  string personLevel;
  string studentMajor;
  string departmentName;
  double studentGpa;
  int advisorId;
  Student *student;//used to edit data of current student
  Faculty *advisor;//used to edit data of current student's advisor
  //Display list of options for user to choose from
  while (restart)
  {
    cout << endl;
    cout << "Welcome. Please select from the following options:" << endl;
    cout << "--------------------------------------------------------" << endl;
    cout << " 1 - Print all students and their information (sorted by ascending id #)" << endl;
    cout << " 2 - Print all faculty and their information (sorted by ascending id #)" << endl;
    cout << " 3 - Find and display student information given the students id" << endl;
    cout << " 4 - Find and display faculty information given the faculty id" << endl;
    cout << " 5 - Given a student’s id, print the name and info of their faculty advisor" << endl;
    cout << " 6 - Given a faculty id, print ALL the names and info of his/her advisees" << endl;
    cout << " 7 - Add a new student" << endl;
    cout << " 8 - Delete a student given the id" << endl;
    cout << " 9 - Add a new faculty member" << endl;
    cout << " 10 - Delete a faculty member given the id" << endl;
    cout << " 11 - Change a student’s advisor given the student id and the new faculty id" << endl;
    cout << " 12 - Remove an advisee from a faculty member given the ids" << endl;
    cout << " 13 - Rollback" << endl;
    cout << " 14 - Exit" << endl;
    cout << endl;
    choice = saveInt(choice);

    switch (choice)//Carries out methods based on user's choice from above list
    {
      case 1://print all students
        cout << endl;
        cout << studentTable->treeString() << endl;
        break;
      case 2://print all faculty
        cout << endl;
        cout << facultyTable->treeString() << endl;
        break;
      case 3://print specific student
        cout << "Please enter the student's ID number: " << endl;
        id = saveInt(id);
        cout << endl;
        if (studentTable->contains(id))
          (studentTable->getValue(id))->printStudent();
        else
          cout << "Invalid input." << endl;
        break;
      case 4://print speecific faculty member
        cout << "Please enter the faculty member's ID number: " << endl;
        id = saveInt(id);
        cout << endl;
        if (facultyTable->contains(id))
          facultyTable->getValue(id)->printFacMember();
        else
          cout << "Invalid input." << endl;
        break;
      case 5://print student's advisor info
        cout << "Please enter the student's ID number: " << endl;
        id = saveInt(id);
        cout << endl;
        if (studentTable->contains(id))
        {
          cout << "Advisor Info: " << endl;
          cout << endl;
          facultyTable->getValue((studentTable->getValue(id))->advisorId)->printFacMember();
        }
        else
          cout << "Invalid input." << endl;
        break;
      case 6://print advisor's advisees
        cout << "Please enter the faculty member's ID number: " << endl;
        id = saveInt(id);
        cout << endl;
        cout << "Advisee info: " << endl;
        if (facultyTable->contains(id))
          facultyTable->getValue(id)->printAdvisees();
        else
          cout << "Invalid input." << endl;
        break;
      case 7://add student
        saveState();
        cout << "Please enter the student's full name: " << endl;
        cin.ignore();
        getline(cin, fullName);
        cout << "Please enter the student's level: " << endl;
        cin >> personLevel;
        cout << "Please enter the student's major: " << endl;
        cin.ignore();
        getline(cin, studentMajor);
        cout << "Please enter the student's GPA: " << endl;
        cin >> studentGpa;
        cout << "Please enter the ID number of the student's advisor: " << endl;
        cin >> advisorId;
        addStudent(fullName, personLevel, studentMajor, studentGpa, advisorId);
        writeFiles();
        break;
      case 8://remove student
        saveState();
        cout << "Please enter the student's ID number: " << endl;
        id = saveInt(id);
        removeStudent(id);
        writeFiles();
        break;
      case 9://add faculty member
        saveState();
        cout << "Please enter the faculty member's full name: " << endl;
        cin.ignore();
        getline(cin, fullName);
        cout << "Please enter the faculty member's level: " << endl;
        getline(cin, personLevel);
        cout << "Please enter the faculty member's department: " << endl;
        getline(cin, departmentName);
        addFaculty(fullName, personLevel, departmentName);
        writeFiles();
        break;
      case 10://remove faculty member
        saveState();
        cout << "Please enter the faculty member's ID number: " << endl;
        id = saveInt(id);
        removeFaculty(id);
        writeFiles();
        break;
      case 11://change student's advisor
        saveState();
        int newAdvisId;
        cout << "Please enter the student's ID number: " << endl;
        id = saveInt(id);
        if (studentTable->contains(id))
        {
          cout << "Please enter the ID number of the student's new advisor: " << endl;
          cin >> newAdvisId;
          if (facultyTable->contains(newAdvisId))
          {
            student = studentTable->getValue(id);
            advisor = facultyTable->getValue(student->advisorId);
            student->advisorId = newAdvisId;
            advisor->removeAdvisee(id);
            advisor = facultyTable->getValue(newAdvisId);
            advisor->addAdvisee(id, student);
            cout << "Advisor updated." << endl;
            writeFiles();
          }
          else
            cout << "Invalid Input." << endl;
        }
        else
          cout << "Invalid Input." << endl;
        break;
      case 12://removes advisee from faculty member
        saveState();
        cout << "Please enter the advisor's ID number: " << endl;
        advisorId = saveInt(advisorId);
        if (facultyTable->contains(advisorId))
        {
          cout << "Please enter the ID number of the advisee to be removed: " << endl;
          id = saveInt(id);
          if (facultyTable->getValue(advisorId)->advisees->contains(id))
          {
            facultyTable->getValue(advisorId)->removeAdvisee(id);
            student = studentTable->getValue(id);
            student->advisorId = 0;
            cout << "Advisee removed." << endl;
            cout << endl;
            cout << "Please enter the ID of the student's new advisor: " << endl;
            advisorId = saveInt(advisorId);
            if (facultyTable->contains(advisorId))
            {
              student->advisorId = advisorId;
              facultyTable->getValue(advisorId)->addAdvisee(id, student);
              writeFiles();
            }
          }
          else
            cout << "Invalid input." << endl;
        }
        else
          cout << "Invalid input." << endl;
        break;
      case 13://returns to previous save state
        rollBack();
        break;
      case 14://exit
        cout << "Goodbye." << endl;
        writeFiles();
        exit(EXIT_FAILURE);
      default://incorrect input
        cout << "Invalid input. Please try again." << endl;
        break;
    }
    cout << endl;
    endChoice = "n";
    cout << "Continue?" << endl;
    cin >> endChoice;
    if (endChoice == "y")
      restart = true;
    else//ends program if user does not want to continue
    {
      restart = false;
      writeFiles();
      cout << "Goodbye." << endl;
    }
  }
}

void Program::addStudent(string fullName, string personLevel, string studentMajor, double studentGpa, int advisor)
{
  int idNum = 0;
  do//selects a new id number for new student
  {
    srand(time(0));
    idNum = rand() % 200000 + 100000;
  } while (facultyTable->contains(idNum));

  if (facultyTable->contains(advisor))//determines if advisor number input is correct
  {
    Student *student = new Student(idNum, fullName, personLevel, studentMajor, studentGpa, advisor);//new student created and added to propper tables
    facultyTable->getValue(advisor)->addAdvisee(idNum, student);
    studentTable->insert(idNum, student);
    cout << "Student added. " << endl;
    cout << endl;
  }
  else
  {
    cout << "Invalid input. " << endl;
    restart = true;
  }
}

void Program::removeStudent(int id)
{
  Student *student = new Student();//to edit info of current student
  if (studentTable->contains(id))
  {
    student = studentTable->getValue(id);
    studentTable->deleteNode(id);//removes student from student table
    (facultyTable->getValue(student->advisorId))->removeAdvisee(id);//removes student from advisor
    delete student;
    cout << "Student removed. " << endl;
    cout << endl;
  }
  else
  {
    cout << "Invalid input. " << endl;
    restart = true;
  }
}

void Program::addFaculty(string fullName, string personLevel, string departmentName)
{
  int idNum = 0;
  do//selects new id number for new faculty member
  {
    srand(time(0));
    idNum = rand() % 200000 + 100000;
  } while (facultyTable->contains(idNum));

  Faculty *faculty = new Faculty(idNum, fullName, personLevel, departmentName);//creates new faculty member
  facultyTable->insert(idNum, faculty);//inserts to faculty tree
  cout << "Faculty member added. " << endl;
  cout << endl;
}

void Program::removeFaculty(int id)
{
  if (facultyTable->contains(id))//checks if faculty member exists
  {
    facultyTable->deleteNode(id);//removes faculty member from table
    cout << "Faculty member removed. " << endl;
    cout << endl;
  }
  else
  {
    cout << "Invalid input. " << endl;
    restart = true;
    //return;
  }
}

void Program::writeFiles()
{
  ofstream writeFac(facTable);
  facultyTable->treeToFile(writeFac);//writes faculty tree to save file
  ofstream writeStud(studTable);
  studentTable->treeToFile(writeStud);//writes student tree to save file

  cout << endl;
  cout << "Saved" << endl;
}

void Program::saveState()
{//memory allocated for tree copies
  GenTree<Faculty> *facultyCopy;
  GenTree<Student> *studentCopy;
  facultyCopy = new GenTree<Faculty>(facultyTable->clone());//trees copied
  studentCopy = new GenTree<Student>(studentTable->clone());
  facultySaves->push(facultyCopy);//tree copies pushed to corresponding stacks for rollback feature
  studentSaves->push(studentCopy);
}

void Program::rollBack()
{
  if (!facultySaves->isEmpty())//ensures stack isn't empty
  {
    facultyTable = facultySaves->pop();//most recent tree copies popped from stacks to replace current tree
    studentTable = studentSaves->pop();
    cout << endl;
    cout << "Previous state restored." << endl;
  }
  else
  {
    cout << "No prior saves stored." << endl;
  }
}

int Program::saveInt(int input)
{
  while (!(cin >> input))//checks if cin is of correct type
  {
    cin.clear();//clears bad input flag 
    cin.ignore(10000, '\n'); //discard input
    cout << "Invalid input. Please try again.\n";
  }
  return input;
}
