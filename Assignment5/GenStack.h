//Tyler Seppala
//2297817
//seppala@chapman.edu
//CPSC 350-02
//Assignment 5 (Database)

//Template class and implementation for a generic stack

#include <iostream>

using namespace std;

template <class X>
class GenStack
{
  public:
    GenStack();//constructor
    GenStack(int maxSize);//overload constructor
    ~GenStack();//destructor

    void push(X d);
    X pop();
    X peek();//AKA top()

    int size();
    bool isFull();
    bool isEmpty();

    int maxSize;
    int top;

    X *myArray;
};

template <class X>
GenStack<X>::GenStack()//default constructor
{
  myArray = new X[128];
  maxSize = 128;
  top = -1;
}

template <class X>
GenStack<X>::GenStack(int size)//constructor
{
	myArray = new X[size];
	maxSize = size;
	top = -1;
}

template <class X>
GenStack<X>::~GenStack()//destructor
{
  delete []myArray;
}

template <class X>
void GenStack<X>::push(X d)
{
	if (isFull())
	{
		cout << "Stack Full\nProgram Terminated\n";
		exit(EXIT_FAILURE);
	}

	//cout << "Inserting " << d << endl;
	myArray[++top] = d;
}

template <class X>
int GenStack<X>::size()
{
	return (top + 1);
}

template <class X>
X GenStack<X>::pop()
{
	if (isEmpty())
	{
		cout << "Stack Empty\nProgram Terminated\n";
		exit(EXIT_FAILURE);
	}

	//cout << "Removing " << peek() << endl;

	return myArray[top--];
}

template <class X>
X GenStack<X>::peek()
{
  /////I included error checking here but commented it out because i found
  /////it easiest to catch the error produced in this function in this project
  /*
	if (!isEmpty())
  {
		return myArray[top];
  }
	else
  {
    cout << "Stack Empty\nProgram Terminated\n";
		exit(EXIT_FAILURE);
  }
  */
  return myArray[top];
}

template <class X>
bool GenStack<X>::isEmpty()
{
	return (top == -1);
}

template <class X>
bool GenStack<X>::isFull()
{
	return (top == maxSize - 1);
}
