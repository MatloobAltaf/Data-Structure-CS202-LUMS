#ifndef __STACK_CPP
#define __STACK_CPP
#include "stack.h"

template <class T>
Stack<T>::Stack()
{
    //Nothing to be done actually

}
    
template <class T>
Stack<T>::Stack(Stack<T>& otherStack)
{
	int len = otherStack.list.length();
	ListItem<T> *temp = otherStack.list.getHead();
	for (int i = 0; i < len; i++)
	{
		list.insertAtTail(temp->value);
		temp = temp->next;
    }
    
}

template <class T>
Stack<T>::~Stack()
{
    while(list.getHead()!=NULL)
    {
        list.deleteHead();
    }
}

template <class T>
void Stack<T>::push(T item)
{
    list.insertAtHead(item);
}

template <class T>
T Stack<T>::top()
{
    ListItem<T>* temp = list.getHead();
    return temp->value;
}

template <class T>
T Stack<T>::pop()
{
    ListItem<T>* temp = list.getHead();
    T ele = temp->value;
    list.deleteHead();
    return ele;
}

template <class T>
int Stack<T>::length()
{
    return list.length();
}

template <class T>
bool Stack<T>::isEmpty()
{
    if(list.length()==0)
    {
        return true;
    }
    else
    {
        return false;
    }
    
}

#endif

