#ifndef __QUEUE_CPP
#define __QUEUE_CPP
#include "queue.h"

template <class T>
Queue<T>::Queue()
{
    //Nothing to be done actually
}
    
template <class T>
Queue<T>::Queue(Queue<T>& otherQueue)
{
	int len = otherQueue.list.length();
	ListItem<T> *temp = otherQueue.list.getHead();
	for (int i = 0; i < len; i++)
	{
		list.insertAtTail(temp->value);
		temp = temp->next;
    }
}

template <class T>
Queue<T>::~Queue()
{
    while(list.getHead()!=NULL)
    {
        list.deleteHead();
    }
}

template <class T>
void Queue<T>::enqueue(T item)
{
    list.insertAtTail(item);
    return;
}

template <class T>
T Queue<T>::front()
{
    return list.getHead()->value;
}

template <class T>
T Queue<T>::dequeue()
{
    T ele = list.getHead()->value;
    list.deleteHead();
    return ele;
}

template <class T>
int Queue<T>::length()
{
	return list.length();
}

template <class T>
bool Queue<T>::isEmpty()
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
