#ifndef STACK_H
#define STACK_H

namespace EIN_JRW_Prog5
{

  template < typename T>
class Stack
    {
    public:
      explicit Stack(int = 10); //default constructor (Stack size 10)
      ~Stack() //destructor
      {
	delete [] stackPtr; //deallocate internal space for Stack
      }
      bool push(const T &); //push an element onto the Stack
      bool pop(T &); //pop an element off the Stack
      inline  bool isEmpty() const //determine whether Stack is empty
      {
	return top == -1;
      } 
      inline  bool isFull() const //determine whether Stack is full
      {
	return top == size -1; 
      }
    private:
      int size; //# of elements in the Stack
      int top; //location of the top element (-1 means empty)
      T* stackPtr; // pointer to internal representation of the Stack
    };

#endif
