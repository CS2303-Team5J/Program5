#ifndef STACK_H
#define STACK_H
#include <vector>
#include <cassert>
#include <iostream>

namespace EIN_JRW_Prog5
{
    template<class T> class Stack
    {
        public:
        Stack();
        void push(T data);
        T previewPop();
        T pop();
        int getSize();
        void printData();

        private:
        std::vector<T> stackData;
        int sizeOf;
    };


    template<class T>
    Stack<T>::Stack()
    {
        this->stackData = std::vector<T>();
        sizeOf = 0;
    }

    template<class T>
    void Stack<T>::push(T data)
    {
        this->stackData.push_back(data);
        sizeOf++;
    }

    template<class T>
    T Stack<T>::previewPop()
    {
        assert(sizeOf!=0);
        T dataPopped = stackData.front();
        return dataPopped;
    }

    template<class T>
    T Stack<T>::pop()
    {
        assert(sizeOf!=0);
        T dataPopped = stackData.front(); // Get the top of the stack
        stackData.erase(stackData.begin()); // Take it out
        sizeOf--;
        return dataPopped;
    }

    template<class T>
    int Stack<T>::getSize()
    {
        return sizeOf;
    }

    template<class T>
    void Stack<T>::printData()
    {
        for(size_t x = 0; x < stackData.size(); x++)
        {
            std::cout << stackData.at(x) << std::endl;
        }
    }
}
//#include "stack.template"
#endif
