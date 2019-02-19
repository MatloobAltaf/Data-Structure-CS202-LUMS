#ifndef __LIST_CPP
#define __LIST_CPP

#include <cstdlib>
#include "LinkedList.h"

template <class T>
LinkedList<T>::LinkedList()
{
    head=NULL;
    tail=NULL;
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& otherList)
{
	head = NULL;
	tail = NULL;
	
	ListItem<T> *temp = otherList.head;
	while (temp)
	{
		insertAtTail(temp->value);
		temp = temp->next;
    }
    
}

template <class T>
LinkedList<T>::~LinkedList()
{
    
    delete head;
    delete tail;
}

template <class T>
void LinkedList<T>::insertAtHead(T item)
{
    ListItem<T>* newItem;
    newItem=new ListItem<T>(item);
    if(head==NULL)
    {
        head=newItem;
        tail=newItem;
    }
    else
    {
        newItem->next=head;
        head->prev=newItem;
        head=newItem;
    }
}

template <class T>
void LinkedList<T>::insertAtTail(T item)
{
    ListItem<T>* newItem;
    newItem=new ListItem<T>(item);
    newItem->value=item;
    if(head==NULL)
    {
        head=newItem;
        tail=newItem;
    }
    else
    {
        newItem->prev=tail;
        tail->next=newItem;
        newItem->next=NULL;
        tail=newItem;
}
}

template <class T>
void LinkedList<T>::insertAfter(T toInsert, T afterWhat)
{
 	ListItem<T> *temp = searchFor(afterWhat);
	
	if (temp)
	{
		if (!temp->next)
		{
			insertAtTail(toInsert);
		}
		else
		{
			ListItem<T> *temp_ = new ListItem<T>(toInsert);
			temp_->next = temp->next;
			temp_->prev = temp;
			temp->next->prev = temp_;
			temp->next = temp_;
		}
}
}


template <class T>
ListItem<T>* LinkedList<T>::getHead()
{
    return head;
}

template <class T>
ListItem<T>* LinkedList<T>::getTail()
{
    return tail;
}

template <class T>
ListItem<T> *LinkedList<T>::searchFor(T item)
{
    ListItem<T>* temp;
    temp=head;
    while(temp!=NULL)
    {
        if(temp->value==item)
        {
            return temp;
            break;
        }
        temp=temp->next;
    }
    return NULL;
}

template <class T>
void LinkedList<T>::deleteElement(T item)
{
    ListItem<T>* temp;
    temp=head;
    if(head==tail)
    {
        if(head->value!=item)
        {
            //could not delete
            return;
        }
        head=NULL;
        tail=NULL;
        delete temp;
        return;
    }

    if(head->value==item)
    {
        head=head->next;
        head->prev=NULL;
        delete temp;
        return;
    }
    else if(tail->value==item)
    {
        temp=tail;
        tail=tail->prev;
        tail->next=NULL;
        delete temp;
        return;
    }
    while(temp->value!=item)
    {
        temp=temp->next;
        if(temp==NULL)
        {
            //element not found
            return;
        }
    }
    temp->next->prev=temp->prev;
    temp->prev->next=temp->next;
    delete temp;
}

template <class T>
void LinkedList<T>::deleteHead()
{
    if(head==NULL)
    {
        return;
    }
    if(head==tail)
    //one element in the list
    {
        ListItem<T>* cur;
        cur=head;
        head=NULL;
        tail=NULL;
        delete cur;
        return;
    }
    else
    {
        ListItem<T>* cur;
        cur=head;
        head=head->next;
        head->prev=NULL;
        delete cur;
}
}

template <class T>
void LinkedList<T>::deleteTail()
{
     if(head==NULL)
    {
         return;
    }
    if(head==tail)
    {
        ListItem<T>* cur;
        cur=head;
        head=NULL;
        tail=NULL;
        delete cur;
        return;
    }
    else
    {
        ListItem<T>* cur;
        cur=tail;
        tail=tail->prev;
        tail->next=NULL;
        delete cur;
}
}

template <class T>
int LinkedList<T>::length()
{
    ListItem<T>* temp;
    temp=head;
    int count=0;
    while(temp!=NULL)
    {
        count++;
        temp=temp->next;
    }
    return count;
}

#endif
