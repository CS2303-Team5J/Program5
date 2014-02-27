#ifndef "Stack.h"
#include 'Stack.h"

namespcae EIN_JRW_Prog5
{
  template< typename T > //constructor template
  Stack< T >::Stack(int s)
  :size(s > 0 ? s : 10), //validate size
  top(-1), //Stack initially empty
  stackPtr(new T[ size ]) //allocate memory for elements
    {
//empty body
    }

    template< typename T> //push element onto stack, if successful, return true; otherwise, return false
     bool Stack< T>::push(const T &pushValue) 
      {
	if(! isFull())
	  {
	    stackPtr[ ++top] = pushValue; //place item on Stack
	    return true; //push successful
	  }
	return false; //push unsuccessful
      }
template< typename T>
  bool Stack<T >::pop(T &popValue) //pop element off Stack, if successful, return true; otherwise, return false
  {
    if( !isEmpty())
      {
	popValue = stackPtr[ top--]; //remove item from Stack
	return true; //pop successful
      }
    return false; //pop unsuccessful
  }

#endif
