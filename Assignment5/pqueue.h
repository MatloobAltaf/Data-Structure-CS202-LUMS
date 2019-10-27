#ifndef PQUEUE__H
#define PQUEUE__H
#include <iostream>
using namespace std;
#include <vector>

template<class T>
class pqueue
{
	protected:
		int size;
	public:
		int numE;
		T* heap;
		pqueue(vector<T> elem);
		void buildbottomup(int index);
		void minheapify(int index, int size);
		T ExtractMin();		
		void DecreaseKey(T node);
};


#endif
