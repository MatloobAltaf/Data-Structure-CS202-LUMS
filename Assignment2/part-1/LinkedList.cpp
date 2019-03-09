#include<iostream>
#ifndef __LIST_CPP
#define __LIST_CPP

#include <cstdlib>
#include "LinkedList.h"
using namespace std;
template <class T>
LinkedList<T>::LinkedList()
{
	this->head = NULL;	
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& otherLinkedList)
{
	ListItem<T>* temp = otherLinkedList.head;
	this->head = NULL;
	if (temp==NULL)
	{
		this->head = NULL;
	}
	else //if(temp->next==NULL)
	{
		//cout<<"In else"<<endl;
		
		this->insertAtHead(temp->value);
		//cout<<"Done insertion at head"<<endl;
		while(temp!=NULL)
		{
			temp = temp->next;
			if (temp==NULL)
				break;
			this->insertAtTail(temp->value);
			//cout<<"Insertion at tail done"<<endl;
			
		}
	}
	//cout<<"Out of else"<<endl;

}

template <class T>
LinkedList<T>::~LinkedList()
{
	ListItem<T>* temp = this->head;
	for (int i=0; i<length();i++)
	{
		deleteHead();
	}
	this->head = NULL;
}

template <class T>
void LinkedList<T>::insertAtHead(T item)
{	//cout<<"In insert at head"<<endl;
	if (head==NULL)
	{
		//cout<<"In if"<<endl;
		ListItem<T>* temp = new ListItem<T>(item);
		this->head = temp;
	}
	else if(head!=NULL)
	{
		//cout<<"In else"<<endl;
		ListItem<T>* temp = new ListItem<T>(item);
		//cout<<"Step 1"<<endl;
		temp->prev = NULL;
		//cout<<"Step 2 "<<endl;
		temp->next=this->head;
		//cout<<"Step 3"<<endl;
		this->head->prev = temp;
		//cout<<"Step 4"<<endl;
		this->head = temp;
		//cout<<"End of else"<<endl;
	}
	//cout<<"End of insert at head"<<endl;
	
}

template <class T>
void LinkedList<T>::insertAtTail(T item)
{
	//cout<<"Start of insert at tail"<<endl;
	ListItem<T>* temp;
	if (head==NULL)
	{
		insertAtHead(item);
	}
	else if(head!=NULL)
	{
		temp = new ListItem<T>(item);
		
		ListItem<T>* temp1;
		temp1 = head;
		while(temp1->next !=NULL)
		{
			temp1 = temp1->next;
		}
		temp->prev = temp1;
		temp1->next = temp;
	}
	//cout<<"End of insert at tail"<<endl;
}

template <class T>
void LinkedList<T>::insertAfter(T toInsert, T afterWhat)
{
	ListItem<T>* insert = new ListItem<T>(toInsert);
	ListItem<T>* temp1 = head;
	while(temp1->value != afterWhat)
	{
		temp1 = temp1->next;
	}
	
	insert->prev = temp1;
	if (temp1->next!=NULL)
		temp1->next->prev = insert;
	insert->next = temp1->next;
	temp1->next = insert;
	

}

template <class T>
void LinkedList<T>::insertSorted(T item)
{
	if (head!=NULL)
	{
		ListItem<T>* temp = head;
		if (temp->value >= item)
			insertAtHead(item);
		else if(temp->value <item && temp->next==NULL)
			insertAtTail(item);
		else if(temp->value <item && temp->next!=NULL) //specifying last if condition
		{
			temp = temp->next;
			while(temp->value <= item)
			{
				if (temp->next==NULL)
					break;
				temp = temp->next;
			}
			
			if (temp->value > item) 
			{
				ListItem<T>* node = new ListItem<T>(item);
				node->next = temp;
				node->prev = temp->prev;
				node->prev->next = node;
				temp->prev = node; 
			}	
			else if(temp->next==NULL)
			{
				ListItem<T>* node = new ListItem<T>(item);
				temp->next = node;
				node->prev = temp;
				
			}
			
		}
		
	}
	else if(head==NULL)
		insertAtHead(item);
	
}

template <class T>
ListItem<T>* LinkedList<T>::getHead()
{
	return head;
}

template <class T>
ListItem<T>* LinkedList<T>::getTail()
{
	if (head==NULL)
		return NULL;
	else
	{
		ListItem<T>* temp = head;
		while(temp->next!=NULL)
			temp = temp->next;
		return temp;
	}
	
}

template <class T>
ListItem<T> *LinkedList<T>::searchFor(T item)
{
	ListItem<T>* temp = head;
	while(temp->value!=item && temp->next!=NULL)
	{
		temp = temp->next;
	}
	if (temp->value == item)
		return temp;
	else
		return NULL;
}

template <class T>
void LinkedList<T>::deleteElement(T item)
{
	ListItem<T>* temp = head;
	if (head!=NULL)
	{
		
		if (temp->value==item) //head needs to be deleted
			deleteHead();
		else
		{
			while(temp->value!=item)
			{
				if (temp->next==NULL)
					break;
				temp = temp->next;
			}
			if (temp->value==item)
			{
				temp->prev->next = temp->next;
				if (temp->next!=NULL)
					temp->next->prev = temp->prev;
				delete temp;// cout<<"After delete "<<length()<<endl;
				temp = NULL;
			}
			else if(temp->next==NULL)
				return;
		}


	}
}

template <class T>
void LinkedList<T>::deleteHead()
{
	if (head!=NULL)
	{
		
		ListItem<T>* temp = head;
		ListItem<T>* temp1 =temp->next;
		
		if (temp1!=NULL)
		{
			temp1->prev = NULL;
		}
		head = temp1;
		delete temp;
		temp = NULL;
	}
	
}

template <class T>
void LinkedList<T>::deleteTail()
{
	if (head!=NULL)
	{
		if (head->next==NULL)
			deleteHead();
		else{
		ListItem<T>* temp = head;
		while(temp->next!=NULL)
		{
			temp = temp->next;
		}
		if (temp->prev!=NULL)
			temp->prev->next = NULL;
		
		delete temp;
		temp = NULL;}
	}
		
}

template <class T>
int LinkedList<T>::length()
{
	ListItem<T>* temp = head;
	int count=0;
	if (head!=NULL)
	{
		while(temp->next!=NULL)
		{
			count++;
			temp = temp->next;
		}
			++count;	
	}
	
	return count;
}

template <class T>
void LinkedList<T>::reverse() 
{
	if(head==NULL || head->next==NULL) //No nodes or only one(head) node.
		return;
	else
	{
		ListItem<T>* temp = head; //head
		ListItem<T>* temp1 = NULL; 
		ListItem<T>* temp2 = temp->next;
		temp->prev = temp2; //changes pointers of head node
		temp->next = temp1;
		while(temp2!=NULL)
		{
			temp = temp2;
			temp2 = temp->next;
			temp1 = temp->prev;
			temp->next = temp1;
			temp->prev = temp2;
		}	
		head = temp;
	}	
}

template <class T>
void LinkedList<T>::parityArrangement()
{
	int numnodes = length();
	ListItem<T>* temp = head;
	ListItem<T>* temp1 = temp->next; //second node of linked list
	ListItem<T>* secondnode = temp->next; // another pointer
	if (numnodes%2 == 0) //link list is of even length.. equal number of odd and even parity nodes
	{
		while(temp1->next!=NULL) //temp1 will be nodes of even parity. Since link list has even number of nodes, will go to the end
		{
			temp->next = temp1->next; //skip one node. For first iteration temp->next(next of first node) is 3rd node 
			temp1->next->prev = temp; //prev of third node is first node
			temp = temp1->next; //temp was first node. Now 3rd node.
			temp1->next = temp->next; //second node->next becomes 4th node
			temp->next->prev = temp1; 
			temp1 = temp->next; //temp1 now points to 4th node.
		}
	}
	else
	{
		while(temp->next!=NULL)
		{
			temp->next = temp1->next;
			temp1->next->prev = temp;
			temp = temp1->next;
			temp1->next = temp->next;
			temp->next->prev = temp1;
			temp1 = temp->next;
		}
	}
	temp->next = secondnode; //at thispoint we have all even nodes pointing to each other and all odds to each other. This step
							//will point the end of odd list to start of even list(second node)
	secondnode->prev = temp;	
}

template <class T>
bool LinkedList<T>::isPalindrome()
{
	bool result;
	if (head!=NULL)
	{
		int size = length();
		//cout<<size<<endl;
		T* array = new T[size];
		int i=0;
		ListItem<T>* temp = head;
		while(temp->next!=NULL)
		{
			array[i] = temp->value;
			++i;
			temp = temp->next;
		}
		array[size-1] = temp->value;
		result = 1;
		for (int j=0;j<size/2;j++)
		{
			if (array[j]!=array[size-j-1])
			{
				result = 0;
				break;
			}
		}
	}
	else 
		result = 0;
	return result;
}
#endif
