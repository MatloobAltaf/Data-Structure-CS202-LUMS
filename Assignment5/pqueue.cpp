#ifndef _PQUEUE_CPP
#define _PQUEUE_CPP

#include "pqueue.h"

template <class T>
pqueue<T>::pqueue(vector<T> elem)
{
	size = elem.size();
	numE = 0;
	heap = new T[size];
	
	for (int i = 0; i < size; i++)
	{
		heap[i] = elem[i];
		buildbottomup(i);
		numE++;
	}
	
}

template <class T>
void pqueue<T>::buildbottomup(int index)
{
	if (index == 0)
	{
		return;
	}
	
	int p_index = (index - 1) / 2;
	if (heap[p_index] > heap[index])
	{
		T temp = heap[p_index];
		heap[p_index] = heap[index];
		heap[index] = temp;
		buildbottomup(p_index);
	}
}

template <class T>
void pqueue<T>::minheapify(int index, int size)
{
	if (index >= numE - 1)
	{
		return;
	}
	
	int left = 2*index + 1;
	int right = 2*index + 2;
	
	if (right <= numE - 1 && heap[right] < heap[index])
	{
		T temp = heap[right];
		heap[right] = heap[index];
		heap[index] = temp;
		minheapify(right, size);
	}
	
	if (left <= numE - 1 && heap[left] < heap[index])
	{
		T temp = heap[left];
		heap[left] = heap[index];
		heap[index] = temp;
		minheapify(left, size);
	}
}
template <class T>
void pqueue<T>::DecreaseKey(T node)
{
	int index = 0;
	for (int i = 0; i < numE; i++)
	{
		if (heap[i]->name == node->name)
		{
			index = i;
			break;
		}
	}
	
	buildbottomup(index);
	
}
	
template <class T>
T pqueue<T>::ExtractMin()
{
	T min = heap[0];
	heap[0] = heap[numE - 1];
	numE--;
	minheapify(0, size);
	
	return min;
}

#endif
