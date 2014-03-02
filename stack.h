#ifndef STACK_H
#define STACK_H
#include <vector>
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
}
#include "stack.template"
#endif
