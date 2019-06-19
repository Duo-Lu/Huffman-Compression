/*
 * PriorityQueue.h
 *
 * Description: Priority Queue
 * Class Invariant: The elements stored in this Priority Queue are always sorted.
 *
 * Author: Inspired by Frank M. Carrano and Tim Henry (textbook).
 * Modified: February 2019
 *
 */

#include "EmptyDataCollectionException.h"
#include <fstream>
#include <cstdio>
#include <iostream>

using namespace std;

#pragma once

template <class T>
class Node {
	public:
		T data;      
		Node<T> *next;

}; // Node


template <class T>
class PriorityQueue {
	private:
		// singly-linked list
		Node<T>* head;
    	int len;

	public:
		// Desc: Default Constructor. (O(1))
    	PriorityQueue();
 

    	// Desc: Copy Constructor. (O(N))
		PriorityQueue(const PriorityQueue& rhs);


    	// Desc: Destructor. (O(N))
    	~PriorityQueue();


    	// Desc: Returns true if Priority Queue empty. (O(1))
    	bool isEmpty() const;


    	// Desc: Returns length of the Priority Queue. (O(1))
    	int getLength() const;


    	// Desc: Inserts x in sorted order. (O(N))
    	//  Pre: Priority Queue is sorted.
		// Post: Priority Queue remains sorted.
		void enqueue(const T& x);
    

		// Desc: Removes the element with "highest" priority. (O(1))
		//  Pre: Priority Queue not empty.
		//       Throws EmptyDataCollectionException if Priority Queue empty.
		void dequeue() throw(EmptyDataCollectionException);


    	// Desc: Returns the element with the "highest" priority. (O(1))
    	//  Pre: Priority Queue not empty.
    	//       Throws EmptyDataCollectionException if Priority Queue empty.
    	// Post: Priority Queue is unchanged.
    	T& peek() const throw(EmptyDataCollectionException);

		void display();

}; // PriorityQueue

template <class T>
void PriorityQueue<T>::display()
{
    Node<T>* curr = head;
    while(curr != NULL)
    {
        cout << curr->data << "  ";
        curr = curr->next;
    }
    cout << endl;
}


// Desc: Default Constructor. (O(1))
template <class T>
PriorityQueue<T>::PriorityQueue()
{
	head = NULL;
	len = 0;
}


// Desc: Copy Constructor. (O(N))
template <class T>
PriorityQueue<T>::PriorityQueue(const PriorityQueue &rhs)
{
	if (rhs.head == NULL)
	{
		this->head = NULL;
		this->len = 0;
	}

	else
	{
		// renew the len
		this->len = rhs.len;

		Node<T> *curr_rhs = rhs.head;

		//base case
		Node<T> *newHead = new Node<T>;

		newHead->data = curr_rhs->data;
		newHead->next = NULL;

		this->head = newHead;
		Node<T> *curr = this->head;

		curr_rhs = curr_rhs->next;

		//2...n
		while (curr_rhs != NULL)
		{
			Node<T> *n = new Node<T>;
			n->data = curr_rhs->data;
			n->next = NULL;
			curr->next = n;
			curr = n;
			curr_rhs = curr_rhs->next;
		}
	}
} 


//Desc: Destructor. (O(N))
template <class T>
PriorityQueue<T>::~PriorityQueue()
{
	Node<T> *curr = head;

	while(curr != NULL)
	{
		curr = head;
		head = head->next;
		delete curr;
	}

	this->len = 0;
}


// Desc: Returns true if Priority Queue empty. (O(1))
template <class T>
bool PriorityQueue<T>::isEmpty() const
{
	return len == 0;
}


// Desc: Returns length of the Priority Queue. (O(1))
template <class T>
int PriorityQueue<T>::getLength() const
{
	return this->len;		
}


// Desc: Inserts x in sorted order. (O(N))
//  Pre: Priority Queue is sorted.
// Post: Priority Queue remains sorted.
template <class T>
void PriorityQueue<T>::enqueue(const T& x)  
{
	Node<T> *curr = head;
	Node<T> *prev = NULL;

	Node<T> *n = new Node<T>;
	n->data = x;
	n->next = NULL;


	// Empty PriorityQueue
	if (head == NULL)
	{
		head = n;
		len++;
		return;
	}

	// if the head is equal to NULL
	if (x < head->data)
	{
		n->next = head;
		head = n;
		len++;
		return;
	}

	// Insert in sorted order
	len++;
	while(curr != NULL)
	{
		if (x < curr->data)
		{
			prev->next = n;
			n->next = curr;
			return;
		}
							
		prev = curr;
		curr = curr->next;
	}

	// the situation of insert in the last 
	curr = head;
	while(curr->next != NULL)
	{
		curr = curr->next;
	}
	curr->next = n;

	return;
}


// Desc: Removes the element with "highest" priority. (O(1))
//  Pre: Priority Queue not empty.
//       Throws EmptyDataCollectionException if Priority Queue empty.
template <class T>
void PriorityQueue<T>::dequeue() throw(EmptyDataCollectionException)
{
	if (head == NULL)
		throw EmptyDataCollectionException("The PriorityQueue is Empty");
	Node<T>* curr = head;
	head = head->next;
	delete curr;
	len--;
}


// Desc: Returns the element with the "highest" priority. (O(1))
//  Pre: Priority Queue not empty.
//       Throws EmptyDataCollectionException if Priority Queue empty.
// Post: Priority Queue is unchanged.
template <class T>
T& PriorityQueue<T>::peek() const throw(EmptyDataCollectionException)
{
	if (head == NULL)
		throw EmptyDataCollectionException("The PriorityQueue is Empty");
	return head->data;
}

