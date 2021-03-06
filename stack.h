#ifndef STACK_H
#define STACK_H
#include <vector>
#include <cassert>
#include <iostream>

namespace EIN_JRW_Prog5
{
    // Implementation of a stack based on a vector
    template<class T> class Queue
    {
        public:
            Queue();
                // Add data to the stack
            void push(T data);
                // Preview the next pop
            T previewPop();
                // Pop the stack
            T pop();
            int getSize();
                // Print the stack
            void printData();

        private:
            std::vector<T> stackData;
            int sizeOf;
    };


    template<class T>
    Queue<T>::Queue()
    {
        this->stackData = std::vector<T>();
        sizeOf = 0;
    }

    template<class T>
    void Queue<T>::push(T data)
    {
        this->stackData.push_back(data); // Add to the end
        sizeOf++;
    }

    template<class T>
    T Queue<T>::previewPop()
    {
        assert(sizeOf!=0);
        T dataPopped = stackData.front(); // Take off the end
        return dataPopped;
    }

    template<class T>
    T Queue<T>::pop()
    {
        assert(sizeOf!=0);
        T dataPopped = stackData.front(); // Get the top of the stack
        stackData.erase(stackData.begin()); // Take it out
        sizeOf--;
        return dataPopped;
    }

    template<class T>
    int Queue<T>::getSize()
    {
        return sizeOf;
    }

    template<class T>
    void Queue<T>::printData()
    {
        for(size_t x = 0; x < stackData.size(); x++)
        {
            std::cout << stackData.at(x) << std::endl;
        }
    }
}
//#include "stack.template"
#endif
