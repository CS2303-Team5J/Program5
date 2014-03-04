
#ifndef STACK_H
#define STACK_H
#include <vector>
#include <cassert>
#include <iostream>

namespace EIN_JRW_Prog5
{
    // Author Jacob Watson (jrwatson@wpi.edu)
    // Implementation of a different queue for routing purposes
    template<class T> class Queue
    {
        public:
            Queue();
                // Add data to the queue
            void push(T data);
                // Preview the next pop
            T previewPop();
                // Pop the queue
            T pop();
            int getSize();
                // Print the queue
            void printData();

        private:
            std::vector<T> stackData;
            int sizeOf;
    };


    // Author Jacob Watson (jrwatson@wpi.edu)
    template<class T>
    Queue<T>::Queue()
    {
        this->stackData = std::vector<T>();
        sizeOf = 0;
    }

    // Author Jacob Watson (jrwatson@wpi.edu)
    template<class T>
    // Add something to the end of the queue
    void Queue<T>::push(T data)
    {
        this->stackData.push_back(data); // Add to the end
        sizeOf++;
    }
    // Author Jacob Watson (jrwatson@wpi.edu)
    template<class T>
    // Preview what will be popped
    T Queue<T>::previewPop()
    {
        assert(sizeOf!=0);
        T dataPopped = stackData.front(); // Take off the front
        return dataPopped;
    }
    // Author Jacob Watson (jrwatson@wpi.edu)
    template<class T>
    // Pop data from the front of the queue
    T Queue<T>::pop()
    {
        assert(sizeOf!=0);
        T dataPopped = stackData.front(); // Get the front of the queue
        stackData.erase(stackData.begin()); // Take it out
        sizeOf--;
        return dataPopped;
    }
    // Author Jacob Watson (jrwatson@wpi.edu)
    template<class T>
    int Queue<T>::getSize()
    {
        return sizeOf;
    }
    // Author Jacob Watson (jrwatson@wpi.edu)
    // Print the data in the queue
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
