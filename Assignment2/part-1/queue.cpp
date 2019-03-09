#ifndef __QUEUE_CPP
#define __QUEUE_CPP
#include "queue.h"

template <class T>
Queue<T>::Queue()
{
	//Empty
}
    
template <class T>
Queue<T>::Queue(Queue<T>& otherQueue)
{
	ListItem<T>* temp_head = otherQueue.list.getHead();

	while (temp_head != NULL)
	{
		list.insertAtTail(temp_head->value);
		temp_head = temp_head->next;
	}
}

template <class T>
Queue<T>::~Queue()
{
	//Empty
}

template <class T>
void Queue<T>::enqueue(T item)
{
	list.insertAtTail(item);
}

template <class T>
T Queue<T>::front()
{
	return list.getHead()->value;
}

template <class T>
T Queue<T>::dequeue()
{
	T temp_head = list.getHead()->value;
	list.deleteHead();
	return temp_head;
}

template <class T>
int Queue<T>::length()
{
	return list.length();
}

template <class T>
bool Queue<T>::isEmpty()
{
	if(list.length() == 0)
	{
		return 1;
	}

	else
	{
		return 0;
	}
}


#endif
