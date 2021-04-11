#include <cstddef>
#include <iostream>
#include <cstdlib>
using namespace std;

#ifndef DYNTEMPSTACK_H
#define DYNTEMPSTACK_H

template <class T>
class DynTempStack
{
private:
    //template <class T>
    class StackNode
    {
        friend class DynTempStack;
        T value;
        StackNode* next;
        // Constructor
        StackNode(T value1, StackNode* next1 = NULL)
        {
            value = value1;
            next = next1;
        }
        void printNode();
        T accessSpecificNode(int num);
    };
    StackNode* top;
public:
    DynTempStack() { top = NULL; }
    void push(T num);
    void pop(T& num);
    T getTop();
    T accessSpecificNode(int num);
    void printStack();
    bool isEmpty() const;
};

//**************************************************
// Member function push pushes the argument onto   *
// the stack.                                      *
//**************************************************
template <class T>
void DynTempStack<T>::push(T num)
{
    top = new StackNode(num, top);
}

//*****************************************************
// Member function pop removes the value at the top   *
// of the stack and copies it into the variable       *
// passed as an argument.                             *
//*****************************************************
template <class T>
void DynTempStack<T>::pop(T& num)
{
    StackNode* temp;

    if (isEmpty())
    {
        cout << "The stack is empty.\n";
        exit(1);
    }
    else   // Pop value off top of stack
    {
        num = top->value;
        temp = top;
        top = top->next;
        delete temp;
    }
}

//returns the value of the top element
template<class T>
T DynTempStack<T>::getTop()
{
    return top->value;
}

template<class T>
T DynTempStack<T>::accessSpecificNode(int num)
{
    if (isEmpty())
    {
        cout << "The stack is empty.\n";
        exit(1);
    }
    else if (num == 0)
    {
        return top->value;
    }
    else
    {
        int i = num--;
        return top->accessSpecificNode(i);
    }
}

//prints the whole stack
template<class T>
void DynTempStack<T>::printStack()
{
    if (!isEmpty())
    {//the printNode function requires the template data type to have an overloaded << operator in order to work
        top->printNode();
    }
}

//*****************************************************
// Member function isEmpty returns true if the stack  *
// is empty, or false otherwise.                      *
//*****************************************************
template <class T>
bool DynTempStack<T>::isEmpty() const
{
    if (!top)
        return true;
    else
        return false;
}

template<class T>
void DynTempStack<T>::StackNode::printNode()
{//T must have an overloaded << operator in order for this function to work
    cout << value << " ";
    if (next != NULL)
    {
        next->printNode();
    }
}
template<class T>
T DynTempStack<T>::StackNode::accessSpecificNode(int num)
{
    
    if (num == 0)
    {
        return this->value;
    }
    else if (next == NULL)
    {
        cout << "Stack size exceeded";
        exit(1);
    }
    else
    {
        int i = --num;
        return next->accessSpecificNode(i);
    }
}
#endif