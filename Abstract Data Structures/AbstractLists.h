/*
 * Author: Daniel Szelogowski
 * Created: 9/19/16
 * Purpose: A collection of data structures written in C++ using templates.
 *
 * Currently implemented:
 *	-Linked List
 *	-Doubly Linked list
 *	-Stack (Linked List)
 *	-Stack
 *	-Queue (Linked List)
 *	-Queue
 *	-Set (Linked List)
 *	-Multiset (Linked List) (Sorted List)
 *	-Binary (Search) Tree
 *	-Priority Queue
 *	-ArrayList
 *  -Deque (Double Ended Queue)
 *	-Circular Queue
 *	-Circular Linked List
 *	-Map
 *
 * To do:
 *	-HashMap (Dictionary)
 *	-Heap
 *	-Skip List
 *	-Bitset
 *	-Undirected Graph
 *	-Directed Graph
 *
 **************************************************************************/

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#ifndef ABSTRACTLISTS_H
#define ABSTRACTLISTS_H

namespace adscol {

template<class T> class Node {
	public:
		T myObj;
		Node *myPrev;
		Node *myNext;

		~Node() {
			delete myObj;
			delete myNext;
			delete myPrev;
		}

		Node(T t) {
			myObj = t;
			myNext = NULL;
			myPrev = NULL;
		}
};

template<class T> class LinkedList {
	private:
		Node<T> *myList;
		Node<T> *myLast;

		void addLast(T t) {
			myLast = myList;
			while (myLast->myNext != NULL) {
				myLast = myLast->myNext;
			}

			Node<T> *temp = new Node<T>(t);
			myLast->myNext = temp;
		}
	public:
		~LinkedList() {
			delete myList;
			delete myLast;
		}

		LinkedList() {
			myList = NULL;
			myLast = NULL;
		}

		LinkedList(T t) {
			myList = new Node<T>(t);
			myLast = myList;
		}

		void add(T t) {
			if (myList == NULL) {
				Node<T> *temp = new Node<T>(t);
				myList = temp;
				myLast = temp;
			} else {
				this->addLast(t);
			}
		}

		void add(int index, T t) {
			if (index == 0) {
				Node<T> *temp = new Node<T>(t);
				temp->myNext = myList;
				myList = temp;
			} else if (index >= this->size() - 1) {
				this->addLast(t);
			} else {
				int cnt = 0;
				myLast = myList;
				Node<T> *temp = new Node<T>(t);
				while ((myLast->myNext != NULL) && (cnt <= index)) {
					if (cnt == (index - 1)) {
						temp->myNext = myLast->myNext;
						myLast->myNext = temp;
					}
					cnt++;
					myLast = myLast->myNext;
				}
			}
		}

		void remove(int index) {
			if (index == 0) {
				myLast = myList;
				Node<T> *temp = myLast->myNext;
				myList = temp;
				myLast = myList;
			} else if (index == (this->size() - 1)) {
				myLast = myList;
				while (myLast->myNext->myNext != NULL) {
					myLast = myLast->myNext;
				}
				myLast->myNext = NULL;
			} else {
				int cnt = 0;
				myLast = myList;
				while ((myLast->myNext != NULL) && (cnt <= index)) {
					if (cnt == (index - 1)) {
						Node<T> *temp = myLast;
						temp->myNext = myLast->myNext->myNext;
						myLast = temp;
					}
					cnt++;
					myLast = myLast->myNext;
				}
			}
		}

		void set(int index, T t) {
			Node<T> *temp = new Node<T>(t);
			if (index == 0) {
				temp->myNext = myList->myNext;
				myList = temp;
				myLast = myList;
			} else if (index == (this->size() - 1)) {
				myLast = myList;
				while (myLast->myNext->myNext != NULL) {
					myLast = myLast->myNext;
				}
				myLast->myNext = temp;
			} else {
				int cnt = 0;
				myLast = myList;
				while ((myLast->myNext != NULL) && (cnt <= index)) {
					if (cnt == (index - 1)) {
						temp->myNext = myLast->myNext->myNext;
						myLast->myNext = temp;
					}
					cnt++;
					myLast = myLast->myNext;
				}
			}
		}

		T get(int index) {
			int cnt = 0;
			myLast = myList;
			while ((myLast->myNext != NULL) && (cnt <= index)) {
				if (cnt == index) return myLast->myObj;
				myLast = myLast->myNext;
				cnt++;
			}
			if (cnt == index) return myLast->myObj;
		}

		void print() {
			myLast = myList;
			while (myLast != NULL) {
				std::cout << myLast->myObj << std::endl;
				myLast = myLast->myNext;
			}
		}

		std::vector<T>* getList() {
			std::vector<T> *items = new std::vector<T>();

			for (int i = 0; i < this->size(); i++) {
				items->push_back(this->get(i));
			}
			return items;
		}

		bool contains(T t) {
			std::vector<T> *items = this->getList();

			for (int i = 0; i < items->size(); i++) {
				if (items->at(i) == t) return true;
			}
			return false;
		}

		void clear() { 
			myLast, myList = NULL; 
		}

		int size() {
			int cnt = 0;
			myLast = myList;
			while (myLast != NULL) {
				cnt++;
				myLast = myLast->myNext;
			}
			return cnt;
		}

		bool isEmpty() {
			return (this->size() == 0);
		}
};

template<class T> class DoublyLinkedList {
	private:
		Node<T> *myList;
	public:
		//TODO: add remove(index), add(index), set(index)
		~DoublyLinkedList() {
			delete myList;
		}

		DoublyLinkedList() {
			myList = NULL;
		}

		DoublyLinkedList(T t) {
			myList = new Node<T>(t);
		}

		void add(T t) {
			Node<T> *temp = new Node<T>(t);
			if (myList == NULL) {
				myList = temp;
				myList->myNext = myList;
				myList->myPrev = myList;
			} else {
				temp->myNext = myList;
				temp->myPrev = myList->myPrev;
				myList->myPrev = temp;
				temp->myPrev->myNext = temp;
			}
		}

		void removeLast() {
			myList->myPrev = myList->myPrev->myPrev;
			myList->myPrev->myNext = myList;
			return;
		}

		void removeFirst() {
			Node<T> *temp = myList->myNext;
			temp->myPrev = myList->myPrev;
			temp->myNext = myList->myNext->myNext;
			myList->myPrev->myNext = temp;
			myList = temp;
		}

		T get(int index) {
			int cnt = 0;
			Node<T> *temp = myList;
			if (cnt == index) {
				return temp->myObj;
			} else {
				cnt++;
				if (cnt == index) return temp->myNext->myObj;
			}
			temp = temp->myNext;

			while ((temp != myList) && (cnt <= index)) {
				if (cnt == index) return temp->myObj;
				temp = temp->myNext;
				cnt++;
			}
			if (cnt == index) return temp->myObj;
		}

		void print() {
			Node<T> *temp = myList;
			std::cout << myList->myObj << std::endl;
			temp = temp->myNext;

			while (temp != myList) {
				std::cout << temp->myObj << std::endl;
				temp = temp->myNext;
			}

		}

		std::vector<T>* getList() {
			std::vector<T> *items = new std::vector<T>();

			for (int i = 0; i < this->size(); i++) {
				items->push_back(this->get(i));
			}
			return items;
		}

		bool contains(T t) {
			std::vector<T> *items = this->getList();

			for (int i = 0; i < items->size(); i++) {
				if (items->at(i) == t) return true;
			}
			return false;
		}

		void clear() { 
			myList = NULL; 
		}

		int size() {
			if (myList == NULL) return 0;

			int cnt = 0;

			Node<T> *temp = myList;
			cnt++;
			temp = myList->myNext;

			while (temp != myList) {
				cnt++;
				temp = temp->myNext;
			}

			return cnt;
		}

		bool isEmpty() {
			return (this->size() == 0);
		}
};

template<class T> class LinkedListStack {
	private:
		Node<T> *myList;
		Node<T> *myLast;

		void addFirst(T t) {
			Node<T> *temp = new Node<T>(t);
			temp->myNext = myList;
			myList = temp;
		}
	public:
		~LinkedListStack() {
			delete myList;
			delete myLast;
		}

		LinkedListStack() {
			myList = NULL;
			myLast = NULL;
		}

		LinkedListStack(T t) {
			myList = new Node<T>(t);
			myLast = myList;
		}

		void push(T t) {
			Node<T> *temp = new Node<T>(t);
			if (myList == NULL) {
				myList = temp;
				myLast = temp;
			}
			else {
				this->addFirst(t);
			}
		}

		T pop() {
			T obj = myList->myObj;
			myLast = myList;
			Node<T> *temp = myLast->myNext;
			myList = temp;
			myLast = myList;
			return obj;
		}

		T peek() {
			return myList->myObj;
		}

		void print() {
			myLast = myList;
			while (myLast != NULL) {
				std::cout << myLast->myObj << std::endl;
				myLast = myLast->myNext;
			}
		}

		std::vector<T>* getList() {
			std::vector<T> *items = new std::vector<T>();

			myLast = myList;
			while (myLast != null) {
				items->push_back(myLast->myObj);
				myLast = myLast.myNext;
			}
			
			return items;
		}

		bool contains(T t) {
			std::vector<T> *items = this->getList();

			for (int i = 0; i < items->size(); i++) {
				if (items->at(i) == t) return true;
			}
			return false;
		}

		void clear() { 
			myLast, myList = NULL; 
		}

		int size() {
			int cnt = 0;
			myLast = myList;
			while (myLast != NULL) {
				cnt++;
				myLast = myLast->myNext;
			}
			return cnt;
		}

		bool isEmpty() {
			return (this->size() == 0);
		}
};

template<class T> class Stack {
	private:
		std::vector<T> *myList;

	public:
		~Stack() {
			delete[] myList;
		}

		Stack() {
			myList = new std::vector<T>();
		}

		Stack(T t) {
			myList = new std::vector<T>();
			myList->push_back(t);
		}

		void push(T t) {
			myList->push_back(t);
		}

		T pop() {
			if (myList->size() == 0) { return (T)NULL; }
			T temp = myList->at(myList->size() - 1);
			myList->erase(myList->begin() + myList->size() - 1);
			return temp;
		}

		T peek() {
			return myList->at(myList->size() - 1);
		}

		void print() {
			for (int i = myList->size() - 1; i >= 0; i--) {
				std::cout << myList->at(i) << std::endl;
			}
		}

		std::vector<T>* getList() {
			return myList;
		}

		bool contains(T t) {
			
			for (int i = 0; i < myList->size(); i++) {
				if (myList->at(i) == t) return true;
			}
			return false;
		}

		void clear() { 
			myList->clear(); 
		}

		int size() {
			return myList->size();
		}

		bool isEmpty() {
			return (myList->size() == 0);
		}
};

template<class T> class LinkedListQueue {
	private:
		Node<T> *myList;
		Node<T> *myLast;

	public:
		~LinkedListQueue() {
			delete myList;
			delete myLast;
		}

		LinkedListQueue() {
			myList = NULL;
			myLast = NULL;
		}

		LinkedListQueue(T t) {
			myList = new Node<T>(t);
			myLast = myList;
		}

		LinkedListQueue(LinkedListQueue<T> *copy) {
			this->myLast = copy->myLast;
			this->myList = copy->myList;
		}

		void enqueue(T t) {
			Node<T> *temp = new Node<T>(t);
			if (myList == NULL) {
				myList = temp;
				myLast = temp;
			} else {
				myLast = myList;
				while (myLast->myNext != NULL) {
					myLast = myLast->myNext;
				}
				myLast->myNext = temp;
			}
		}

		T dequeue() {
			T obj = myList->myObj;
			myLast = myList;
			Node<T> *temp = myLast->myNext;
			myList = temp;
			myLast = myList;
			return obj;
		}

		T peek() {
			return myList->myObj;
		}

		void print() {
			myLast = myList;
			LinkedListQueue<T> *listx = new LinkedListQueue<T>(this);
			while (!listx->isEmpty()) {
				std::cout << listx->dequeue() << std::endl;
			}
		}

		std::vector<T>* getList() {
			std::vector<T> *list = new std::vector<T>();
			LinkedListQueue<T> *listx = new LinkedListQueue<T>(this);
			while (!listx->isEmpty()) {
				list->push_back(listx->dequeue());
			}
			return list;
		}

		bool contains(T t) {
			std::vector<T> *items = this->getList();

			for (int i = 0; i < items->size(); i++) {
				if (items->at(i) == t) return true;
			}
			return false;
		}

		void clear() { 
			myLast, myList = NULL; 
		}

		int size() {
			int cnt = 0;
			myLast = myList;
			while (myLast != NULL) {
				cnt++;
				myLast = myLast->myNext;
			}
			return cnt;
		}

		bool isEmpty() {
			return (this->size() == 0);
		}
};

template<class T> class Queue {
	private:
		std::vector<T> *myList;

	public:
		~Queue() {
			delete[] myList;
		}

		Queue() {
			myList = new std::vector<T>();
		}

		Queue(T t) {
			myList = new std::vector<T>();
			myList->push_back(t);
		}

		Queue(Queue<T> *copy) {
			myList = new std::vector<T>();
			for (int i = 0; i < copy->size(); i++) {
				this->enqueue(copy->myList->at(i));
			}
		}

		void enqueue(T t) {
			myList->push_back(t);
		}

		T dequeue() {
			if (myList->size() == 0) { return (T)NULL; }
			T temp = myList->at(0);
			myList->erase(myList->begin() + 0);
			return temp;
		}

		T peek() {
			if (myList->size() == 0) { return (T)NULL; }
			return myList->at(0);
		}

		void print() {
			for (int i = 0; i < myList->size(); i++) {
				std::cout << myList->at(i) << std::endl;
			}
		}

		std::vector<T>* getList() {
			return myList;
		}

		bool contains(T t) {
			for (int i = 0; i < myList->size(); i++) {
				if (myList->at(i) == t) return true;
			}
			return false;
		}

		void clear() { 
			myList->clear(); 
		}

		int size() {
			return myList->size();
		}

		bool isEmpty() {
			return (myList->size() == 0);
		}
};

template<class T> class LinkedListSet {
	private:
		Node<T> *myList;
		Node<T> *myLast;

		void addSorted(T t) {
			myLast = myList;
			Node<T> *temp = new Node<T>(t);
			if (temp->myObj < myLast->myObj) {
				temp->myNext = myLast;
				myList = temp;
				return;
			}
			while (myLast->myNext != NULL) {
				if (temp->myObj < myLast->myNext->myObj) {
					temp->myNext = myLast->myNext;
					myLast->myNext = temp;
					return;
				}
				myLast = myLast->myNext;
			}

			myLast->myNext = temp;
		}

	public:
		~LinkedListSet() {
			delete myList;
			delete myLast;
		}

		LinkedListSet() {
			myList = NULL;
			myLast = NULL;
		}

		LinkedListSet(T t) {
			myList = new Node<T>(t);
			myLast = myList;
		}

		void add(T t) {
			Node<T> *temp = new Node<T>(t);
			if (myList == NULL) {
				myList = temp;
				myLast = temp;
			} else {
				if (!this->contains(t)) this->addSorted(t);
			}
		}

		void remove(int index) {
			if (index == 0) {
				myLast = myList;
				Node<T> *temp = myLast->myNext;
				myList = temp;
				myLast = myList;
			} else if (index >= (this->size() - 1)) {
				myLast = myList;
				while (myLast->myNext->myNext != NULL) {
					myLast = myLast->myNext;
				}
				myLast->myNext = NULL;
			} else {
				int cnt = 0;
				myLast = myList;
				Node<T> *tempx;
				while ((myLast->myNext != NULL) && (cnt <= index)) {
					if (cnt == (index - 1)) {
						tempx = myLast;
						tempx->myNext = myLast->myNext->myNext;
						myLast = tempx;
					}
					cnt++;
					myLast = myLast->myNext;
				}
			}
		}

		T get(int index) {
			int cnt = 0;
			myLast = myList;
			T obj = NULL;
			while ((myLast->myNext != NULL) && (cnt <= index)) {
				if (cnt == index) obj = myLast->myObj;
				myLast = myLast->myNext;
				cnt++;
			}
			if (cnt == index) obj = myLast->myObj;
			myLast = myList;
			return obj;
		}

		void print() {
			myLast = myList;
			while (myLast != NULL) {
				std::cout << myLast->myObj << std::endl;
				myLast = myLast->myNext;
			}
		}

		std::vector<T>* getList() {
			std::vector<T> *items = new std::vector<T>();

			for (int i = 0; i < this->size(); i++) {
				items->push_back(this->get(i));
			}
			return items;
		}

		bool contains(T t) {
			std::vector<T> *items = this->getList();

			for (int i = 0; i < items->size(); i++) {
				if (items->at(i) == t) return true;
			}
			return false;
		}

		void clear() { 
			myLast, myList = NULL; 
		}

		int size() {
			int cnt = 0;
			myLast = myList;
			while (myLast != NULL) {
				cnt++;
				myLast = myLast->myNext;
			}
			return cnt;
		}

		bool isEmpty() {
			return (this->size() == 0);
		}
};

template<class T> class Multiset {
	private:
		Node<T> *myList;
		Node<T> *myLast;

		void addSorted(T t) {
			myLast = myList;
			Node<T> *temp = new Node<T>(t);
			if (temp->myObj < myLast->myObj) {
				temp->myNext = myLast;
				myList = temp;
				return;
			}
			while (myLast->myNext != NULL) {
				if (temp->myObj < myLast->myNext->myObj) {
					temp->myNext = myLast->myNext;
					myLast->myNext = temp;
					return;
				}
				myLast = myLast->myNext;
			}

			myLast->myNext = temp;
		}

	public:
		~Multiset() {
			delete myList;
			delete myLast;
		}

		Multiset() {
			myList = NULL;
			myLast = NULL;
		}

		Multiset(T t) {
			myList = new Node<T>(t);
			myLast = myList;
		}

		void add(T t) {
			Node<T> *temp = new Node<T>(t);
			if (myList == NULL) {
				myList = temp;
				myLast = temp;
			}
			else {
				this->addSorted(t);
			}
		}

		void remove(int index) {
			if (index == 0) {
				myLast = myList;
				Node<T> *temp = myLast->myNext;
				myList = temp;
				myLast = myList;
			} else if (index >= (this->size() - 1)) {
				myLast = myList;
				while (myLast->myNext->myNext != NULL) {
					myLast = myLast->myNext;
				}
				myLast->myNext = NULL;
			} else {
				int cnt = 0;
				myLast = myList;
				Node<T> *tempx;
				while ((myLast->myNext != NULL) && (cnt <= index)) {
					if (cnt == (index - 1)) {
						tempx = myLast;
						tempx->myNext = myLast->myNext->myNext;
						myLast = tempx;
					}
					cnt++;
					myLast = myLast->myNext;
				}
			}
		}

		T get(int index) {
			int cnt = 0;
			myLast = myList;
			T obj = (T)NULL;
			while ((myLast->myNext != NULL) && (cnt <= index)) {
				if (cnt == index) obj = myLast->myObj;
				myLast = myLast->myNext;
				cnt++;
			}
			if (cnt == index) obj = myLast->myObj;
			myLast = myList;
			return obj;
		}

		void print() {
			myLast = myList;
			while (myLast != NULL) {
				std::cout << myLast->myObj << std::endl;
				myLast = myLast->myNext;
			}
		}

		std::vector<T>* getList() {
			std::vector<T> *items = new std::vector<T>();

			for (int i = 0; i < this->size(); i++) {
				items->push_back(this->get(i));
			}
			return items;
		}

		adscol::Set<T>* getSet() {
			adscol::Set<T> *items = new adscol::Set<T>();

			for (int i = 0; i < this->size(); i++) {
				items->add(this->get(i));
			}
			return items;
		}

		bool contains(T t) {
			std::vector<T> *items = this->getList();

			for (int i = 0; i < items->size(); i++) {
				if (items->at(i) == t) return true;
			}
			return false;
		}

		void clear() { 
			myLast, myList = NULL; 
		}

		int size() {
			int cnt = 0;
			myLast = myList;
			while (myLast != NULL) {
				cnt++;
				myLast = myLast->myNext;
			}
			return cnt;
		}

		bool isEmpty() {
			return (this->size() == 0);
		}
};

template<class T> class TreeNode {
	public:
		T myObj;
		TreeNode *myLeft;
		TreeNode *myRight;

		~TreeNode() {
			delete myObj;
			delete myLeft;
			delete myRight;
		}

		TreeNode(T t) {
			myObj = t;
			myLeft = NULL;
			myRight = NULL;
		}
	};

template<class T> class BinaryTree {
	private:
		TreeNode<T> *root;
		std::vector<T> *items;

		void getListInOrderT(TreeNode<T> *r) {
			if (r == NULL) { return; }
			getListInOrderT(r->myLeft);
			items->push_back(r->myObj);
			getListInOrderT(r->myRight);
		}

		void getListPreOrderT(TreeNode<T> *r) {
			if (r == NULL) { return; }
			items->push_back(r->myObj);
			getListPreOrderT(r->myLeft);
			getListPreOrderT(r->myRight);
		}

		void getListPostOrderT(TreeNode<T> *r) {
			if (r == NULL) { return; }
			getListPostOrderT(r->myLeft);
			getListPostOrderT(r->myRight);
			items->push_back(r->myObj);
		}

		static void printInOrderT(TreeNode<T> *r) {
			if (r == NULL) { return; }
			printInOrderT(r->myLeft);
			std::cout << r->myObj << std::endl;
			printInOrderT(r->myRight);
		}

		static void printPreOrderT(TreeNode<T> *r) {
			if (r == NULL) { return; }
			std::cout << r->myObj << std::endl;
			printPreOrderT(r->myLeft);
			printPreOrderT(r->myRight);
		}

		static void printPostOrderT(TreeNode<T> *r) {
			if (r == NULL) { return; }
			printPostOrderT(r->myLeft);
			printPostOrderT(r->myRight);
			std::cout << r->myObj << std::endl;
		}

		static void invertTree(TreeNode<T> *r) {
			if (r == NULL) { return; }
			TreeNode<T> *temp = r->myLeft;
			r->myLeft = r->myRight;
			r->myRight = temp;
			invertTree(r->myLeft);
			invertTree(r->myRight);
		}

		static int countItems(TreeNode<T> *r) {
			if (r == NULL) { return 0; }
			return countItems(r->myLeft) + 1 + countItems(r->myRight);
		}

		static int numCounter(TreeNode<T> *r, T t) {
			if (r == NULL) { return 0; }

			if (r->myObj == t) {
				return numCounter(r->myLeft, t) + 1 + numCounter(r->myRight, t);
			} else {
				return numCounter(r->myLeft, t) + 0 + numCounter(r->myRight, t);
			}
		}

		int maxWidth = 0;

		int findMaxWidth(TreeNode<T> *r) {
			Queue<TreeNode<T>*> *q = new Queue<TreeNode<T>*>();
			int levelNodes = 0;
			if (r == NULL) return 0;
			q->enqueue(r);

			while (!q->isEmpty()) {
				levelNodes = q->size();

				if (levelNodes > maxWidth) {
					maxWidth = levelNodes;
				}

				while (levelNodes > 0) {
					TreeNode<T> *n = q->dequeue();
					if (n->myLeft != NULL) q->enqueue(n->myLeft);
					if (n->myRight != NULL) q->enqueue(n->myRight);
					levelNodes--;
				}
			}

			return maxWidth;
		}

		int findMaxHeight(TreeNode<T> *r) {
			if (r == NULL) { return 0; }
			return (1 + std::max(findMaxHeight(r->myLeft), findMaxHeight(r->myRight)));
		}

		void addNode(TreeNode<T> *node) {
			if (root == NULL) {
				root = node;
			} else {
				TreeNode<T> *prev = root;
				TreeNode<T> *spot = root;

				while (spot != NULL) {
					if (node->myObj < spot->myObj) {
						prev = spot;
						spot = spot->myLeft;
					} else {
						prev = spot;
						spot = spot->myRight;
					}
				}

				if (node->myObj < prev->myObj) {
					prev->myLeft = node;
				} else {
					prev->myRight = node;
				}
			}
		}

	public:
		~BinaryTree() {
			delete root;
		}

		BinaryTree() {
			root = NULL;
			items = new std::vector<T>();
		}

		void add(T t) {
			TreeNode<T> *temp = new TreeNode<T>(t);

			if (root == NULL) {
				root = temp;
			} else {
				TreeNode<T> *prev = root;
				TreeNode<T> *spot = root;

				while (spot != NULL) {
					if (temp->myObj < spot->myObj) {
						prev = spot;
						spot = spot->myLeft;
					} else {
						prev = spot;
						spot = spot->myRight;
					}
				}

				if (temp->myObj < prev->myObj) {
					prev->myLeft = temp;
				} else {
					prev->myRight = temp;
				}
			}
		}

		void remove(T t) {
			TreeNode<T> *prev = root;
			TreeNode<T> *spot = root;
			bool passedRoot = false;
			while (numCounter(root, t) != 0) {
				if (spot->myObj == t && !passedRoot) {
					if (root->myRight != NULL) {
						TreeNode<T> *temp = root->myRight->myLeft;
						TreeNode<T> *tempL = root->myLeft;
						root = root->myRight;
						root->myLeft = tempL;
						this->addNode(temp);
					} else if (root->myLeft != NULL) {
						TreeNode<T> *temp = root->myLeft->myRight;
						TreeNode<T> *tempR = root->myRight;
						root = root->myLeft;
						root->myRight = tempR;
						this->addNode(temp);
					} else {
						root = NULL;
					}
				}

				while (spot->myObj != t) {
					if (t < spot->myObj) {
						prev = spot;
						spot = spot->myLeft;
					} else {
						prev = spot;
						spot = spot->myRight;
					}
				}

				if ((spot->myLeft == NULL) && (spot->myRight == NULL)) {
					if (t < prev->myObj) {
						prev->myLeft = NULL;
					} else {
						prev->myRight = NULL;
					}
				} else {
					if ((spot->myLeft == NULL) || (spot->myRight == NULL)) {
						if (t < prev->myObj) {
							if (spot->myLeft == NULL) {
								prev->myLeft = spot->myRight;
							} else {
								prev->myLeft = spot->myLeft;
							}
						} else {
							if (spot->myRight == NULL) {
								prev->myRight = spot->myRight;
							} else {
								prev->myRight = spot->myLeft;
							}
						}
					} else {
						TreeNode<T> *pmover = spot->myRight;
						TreeNode<T> *mover = spot->myRight;
						while (mover->myLeft != NULL) {
							pmover = mover;
							mover = mover->myLeft;
						}
						if (pmover == mover) {
							spot->myObj = mover->myObj;
							spot->myRight = mover->myRight;
						} else {
							spot->myObj = mover->myObj;
							pmover->myLeft = mover->myRight;
						}
					}
				}
				passedRoot = true;
			}
		}

		int width() {
			int w = findMaxWidth(root);
			maxWidth = 0;
			return w;
		}

		int height() { return findMaxHeight(root); }

		void invert() { invertTree(root); }

		void printPreOrder()  { printPreOrderT(root); }
		void printInOrder()	  { printInOrderT(root);  }
		void printPostOrder() { printPreOrderT(root); }

		std::vector<T>* getListPreOrder() {
			items->clear();
			getListPreOrderT(root);
			return items;
		}

		std::vector<T>* getListInOrder() {
			items->clear();
			getListInOrderT(root);
			return items;
		}

		std::vector<T>* getListPostOrder() {
			items->clear();
			getListPreOrderT(root);
			return items;
		}

		bool contains(T t) {
			std::vector<T> *items = this->getListInOrder();

			for (int i = 0; i < items->size(); i++) {
				if (items->at(i) == t) return true;
			}
			return false;
		}

		void clear() { 
			root = NULL; 
		}

		int size() { return countItems(root); }

		bool isEmpty() {
			return (this->size() == 0);
		}

};

template<class T> class PQNode {
	private:
		int priority;
		Queue<T> *queue;
	public:
		~PQNode() {
			delete priority;
			delete queue;
		}

		PQNode(int p) {
			priority = p;
			queue = new Queue<T>();
		}

		void add(T t) {
			queue->enqueue(t);
		}

		int compareTo(PQNode<T> *o) {
			if (o->getPriority() == this->getPriority()) {
				return 0;
			}
			else if (o->getPriority() < this->getPriority()) {
				return 1;
			}
			else if (o->getPriority() > this->getPriority()) {
				return -1;
			}
			return -1;
		}

		int getPriority() {
			return priority;
		}

		Queue<T>* getList() {
			return queue;
		}

		int size() {
			return queue->size();
		}

		bool isEmpty() {
			return queue->isEmpty();
		}
};

template<class T> class PriorityQueue {
	private:
		std::vector<PQNode<T>*> *list;
	public:
		~PriorityQueue() {
			delete list;
		}

		PriorityQueue() {
			list = new std::vector<PQNode<T>*>();
		}

		void enqueue(T t, int priority) {
			PQNode<T> *temp = new PQNode<T>(priority);
			temp->add(t);
			enqueue(temp);
		}

		void enqueue(PQNode<T> *item) {
			for (int i = 0; i < list->size(); i++) {
				PQNode<T> *temp = list->at(i);
				if (item->compareTo(temp) > 0) {
					list->insert(list->begin() + i, item);
					return;
				} else if (item->compareTo(temp) == 0) {
					for (int j = 0; j < item->getList()->getList()->size(); j++) {
						temp->add(item->getList()->getList()->at(j));
					}
					list->erase(list->begin() + i);
					list->insert(list->begin() + i, temp);
					return;
				}
			}

			list->push_back(item);
		}

		PQNode<T>* dequeue() {
			for (int i = 0; i < list->size(); i++) {
				PQNode<T> *temp = list->at(i);
				if (!temp->isEmpty()) {
					list->erase(list->begin() + i);
					return temp;
				}
			}
			return new PQNode<T>(0);
		}

		PQNode<T>* peek() {
			for (int i = 0; i < list->size(); i++) {
				PQNode<T> *temp = list->at(i);
				if (!temp->isEmpty()) {
					return temp;
				}
			}
			return new PQNode<T>(0);
		}

		void print() {
			for (int i = 0; i < list->size(); i++) {
				PQNode<T> *temp = list->at(i);
				temp->getList()->print();
			}
		}


		std::vector<PQNode<T>*>* getList() {
			return list;
		}

		bool contains(T t) {
			std::vector<PQNode<T>*> *items = this->getList();

			for (int i = 0; i < items->size(); i++) {
				if (items->at(i)->getList()->contains(t)) return true;
			}
			return false;
		}

		void clear() {
			list->clear();
		}

		int size() {
			if (list->size() == 0) return 0;
			else {
				int cnt = 0;
				for (int i = 0; i < list->size(); i++) {
					PQNode<T> *temp = list->at(i);
					cnt += temp->size();
				}
			}
		}

		bool isEmpty() {
			return (this->size() == 0);
		}
};

template<class T> class ArrayList {
	private:
		T* array;
		unsigned int _size;
		unsigned int memsize;
		const static int basesize = 16;

		void copy(const ArrayList<T> &a) {
			array = new T[a.memsize];
			if (array == NULL) {
				memFail();
			}
			for (int i = 0; i<a._size; i++) {
				array[i] = a.array[i];
			}
			memsize = a.memsize;
			_size = a._size;
		}

		void doublesize() {
			T* temp = NULL;
			int new_size;
			if (memsize == 0) {
				temp = new T[basesize];
				new_size = 1;
			}
			else {
				temp = new T[memsize * 2];
				new_size = memsize * 2;
			}
			if (temp == NULL) {
				memFail();
			}
			for (int i = 0; i<_size; i++) {
				temp[i] = array[i];
			}
			delete[] array;
			array = temp;
			memsize = new_size;
		}

		void halfsize() {
			int resize = memsize / 2;
			if (memsize < (basesize * 2)) {
				resize = basesize;
			}
			T* temp = new T[resize];
			if (temp == NULL) {
				memFail();
			}
			for (int i = 0; i<_size; i++) {
				temp[i] = array[i];
			}
			delete[] array;
			array = temp;
			memsize = resize;
		}

		void memFail() {
			std::cout << "Memory Allocation Failed" << std::endl;
		}

		void badAccess() {
			std::cout << "Attempting to subscript array element that doesn't exist" << std::endl;
		}

	public:
		~ArrayList() {
			if (array) {
				delete[] array;
				array = NULL;
			}
		}

		ArrayList() {
			array = new T[basesize];
			if (array == NULL) {
				memFail();
			}
			_size = 0;
			memsize = basesize;
		}

		ArrayList(unsigned int size) {
			if (size == 0) {
				array = NULL;
			}
			else {
				array = new T[size];
				if (array == NULL) {
					memFail();
				}
			}
			_size = 0;
			memsize = size;
		}

		ArrayList(const ArrayList<T> &a) {
			copy(a);
		}

		T& operator [] (unsigned int index) {
			return get(index);
		}

		void add(unsigned int index, const T &item) {
			if (index > _size) {
				badAccess();
			}
			if ((_size + 1) > memsize) {
				doublesize();
			}
			for (int i = _size; i>index; i--) {
				array[i] = array[i - 1];
			}
			array[index] = item;
			_size++;
		}

		void add(const T &item) {
			if ((_size + 1) > memsize) {
				doublesize();
			}
			array[_size] = item;
			_size++;
		}

		void appendAll(const ArrayList<T> &items) {
			for (int i = 0; i<items._size; i++) {
				add(items.array[i]);
			}
		}

		bool contains(const T &item) {
			for (int i = 0; i<_size; i++) {
				if (array[i] == item) {
					return true;
				}
			}
			return false;
		}

		bool equals(const ArrayList<T> &a) {
			if (_size != a._size) {
				return false;
			}
			for (int i = 0; i<_size; i++) {
				if (array[i] != a.array[i]) {
					return false;
				}
			}
			return true;
		}

		T& get(unsigned int index) {
			if (index >(_size - 1)) {
				badAccess();
			}
			return array[index];
		}


		void remove(unsigned int index) {
			if (index > (_size - 1)) {
				badAccess();
			}
			for (unsigned int i = index; i<_size - 1; i++) {
				array[i] = array[i + 1];
			}
			_size--;
			if (_size <= (memsize / 4) && memsize > basesize) {
				halfsize();
			}
		}

		void print() {
			for (int i = 0; i <= _size; i++) {
				std::cout << this->get(i) << std::endl;
			}
		}

		std::vector<T>* getList() {
			std::vector<T> *items = new std::vector<T>();

			for (int i = 0; i < this->size(); i++) {
				items->push_back(this->get(i));
			}
			return items;
		}

		bool contains(T t) {
			std::vector<T> *items = this->getList();

			for (int i = 0; i < items->size(); i++) {
				if (items->at(i) == t) return true;
			}
			return false;
		}

		void clear() {
			for (int i = _size - 1; i >= 0; i--) {
				remove(i);
			}
		}

		void reverse() {
			T *temp = new T[memsize];
			if (temp == NULL) {
				memFail();
			}
			for (int i = _size - 1; i >= 0; i--) {
				temp[_size - 1 - i] = array[i];
			}
			delete[] array;
			array = temp;
		}


		void set(unsigned int index, const T &item) {
			if (index > _size) {
				badAccess();
			}
			array[index] = item;
		}


		int size() {
			return _size;
		}

		bool isEmpty() {
			return (_size == 0);
		}

		ArrayList<T>* subList(unsigned int fromIndex, unsigned int toIndex) {
			ArrayList<T>* temp = new ArrayList();
			if (temp == NULL) {
				memFail();
			}
			if (toIndex >= _size || fromIndex >= _size) {
				badAccess();
			}
			if (fromIndex >= toIndex) {
				return temp;
			}
			for (int i = fromIndex; i<toIndex; i++) {
				temp->add(array[i]);
			}
			return temp;
		}

		void trimToSize() {
			if (_size == memsize) {
				return;
			}
			T* temp = new T[_size];
			if (temp == NULL) {
				memFail();
			}
			for (int i = 0; i<_size; i++) {
				temp[i] = array[i];
			}
			delete[] array;
			array = temp;
			memsize = _size;
		}
};

template<class T> class Deque {
	private:
		std::vector<T> *myList;

	public:
		~Deque() {
			delete myList;
		}

		Deque() {
			myList = new std::vector<T>;
		}

		void pushFront(T t) {
			myList->insert(myList->begin(), t);
		}

		void pushBack(T t) {
			myList->push_back(t);
		}

		T popFront() {
			T obj = myList->at(0);
			myList->erase(myList->begin());
			return obj;
		}

		T popBack() {
			T obj = myList->back();
			myList->pop_back();
			return obj;
		}

		T peekFront() {
			return myList->at(0);
		}

		T peekBack() {
			return myList->back();
		}

		void print() {
			for (int i = 0; i < this->size(); i++) {
				std::cout << myList[i] << std::endl;
			}
		}

		std::vector<T>* getList() {
			return myList;
		}

		bool contains(T t) {
			std::vector<T> *items = this->getList();

			for (int i = 0; i < items->size(); i++) {
				if (items->at(i) == t) return true;
			}
			return false;
		}

		void clear() { 
			myList->clear(); 
		}

		int size() {
			int s = myList->size();
			return s;
		}

		bool isEmpty() {
			return (this->size() == 0);
		}
};

template<class T> class CircularQueue {
	private:
		const int DEFAULT_SIZE = 10;

		int myMaxSize;
		int myCurrentSize;
		int myStart;
		int myEnd;

		T *myBuffer;

		CircularQueue(CircularQueue<T> *copy) {
			myMaxSize = copy->myMaxSize;
			myCurrentSize = copy->myCurrentSize;
			myStart = copy->myStart;
			myEnd = copy->myEnd;
			myBuffer = copy->myBuffer;
		}

	public:
		~CircularQueue() {
			delete DEFAULT_SIZE;
			delete myMaxSize;
			delete myCurrentSize;
			delete myStart;
			delete myEnd;
			delete[] myBuffer;
		}

		CircularQueue() {
			myMaxSize = DEFAULT_SIZE;
			myBuffer = new T[myMaxSize];
			myStart = 0;
			myEnd = 0;
			myCurrentSize = 0;
		}

		CircularQueue(int size) {
			myMaxSize = size;
			myBuffer = new T[myMaxSize];
			myStart = 0;
			myEnd = 0;
			myCurrentSize = 0;
		}

		void enqueue(T t) {
			myEnd = (myEnd + 1) % myMaxSize;
			myBuffer[myEnd] = t;
			if (myCurrentSize == myMaxSize) {
				myStart = (myStart + 1) % myMaxSize;
			} else {
				myCurrentSize++;
			}
		}

		T dequeue() {
			if (myCurrentSize == 0) {
				std::cout << "The buffer is empty!" << std::endl;
				return (T)NULL;
			} else {
				myStart = (myStart + 1) % myMaxSize;
				myCurrentSize--;
				return myBuffer[myStart];
			}
		}

		T peek() {
			if (myCurrentSize == 0) {
				std::cout << "The buffer is empty!" << std::endl;
				return (T)NULL;
			} else {
				myStart = (myStart + 1) % myMaxSize;
				return myBuffer[myStart];
			}
		}

		void print() {
			CircularQueue<T> *temp = new CircularQueue<T>(this);

			while (!(temp->isEmpty())) {
				std::cout << temp->dequeue() << std::endl;
			}
		}

		std::vector<T>* getList() {
			std::vector<T> *items = new std::vector<T>();
			CircularQueue<T> *temp = new CircularQueue<T>(this);

			while (!(temp->isEmpty())) {
				items->push_back(temp->dequeue());
			}
			return items;
		}

		bool contains(T t) {
			std::vector<T> *items = this->getList();

			for (int i = 0; i < items->size(); i++) {
				if (items->at(i) == t) return true;
			}
			return false;
		}

		void clear() {
			myCurrentSize = 0;
			myStart = 0;
			myEnd = 0;
			myBuffer = new T[myMaxSize];
		}

		int size() {
			return myCurrentSize;
		}

		bool isEmpty() {
			return (myCurrentSize == 0);
		}

		bool isFull() {
			return (myCurrentSize == myMaxSize);
		}
};

template<class T> class CircularLinkedList {
	private:
		Node<T> *myList;

	public:
		~CircularLinkedList() {
			delete myList;
		}

		CircularLinkedList() {
			myList = NULL;
		}

		void addFront(T t) {
			Node<T> *temp = new Node<T>(t);

			if (myList == NULL) {
				temp->myNext = temp;
				myList = temp;
				return;
			}

			Node<T> *myLast = myList;

			while (myLast->myNext != myList) {
				myLast = myLast->myNext;
			}

			if (myList != NULL) {
				temp->myNext = myList;
				myLast->myNext = temp;
				myList = temp;
			}
		}

		void addBack(T t) {
			Node<T> *temp = new Node<T>(t);

			if (myList == NULL) {
				temp->myNext = temp;
				myList = temp;
				return;
			}

			Node<T> *myLast = myList;
			while (myLast->myNext != myList) {
				myLast = myLast->myNext;
			}

			myLast->myNext = temp;
			temp->myNext = myList;
		}

		T popFront() {
			Node<T> *temp = myList;
			Node<T> *myLast = myList;

			if (myList != NULL) {
				while (myLast->myNext != myList) {
					myLast = myLast->myNext;
				}
				myList = temp->myNext;
				myLast->myNext = myList;
				T obj = temp->myObj;
				temp = NULL;
				return obj;
			}
			return (T)NULL;
		}

		T popBack() {
			Node<T> *temp = myList;
			Node<T> *myLast = myList;

			if (myList != NULL) {
				while (myLast->myNext != myList) {
					temp = myLast;
					myLast = myLast->myNext;
				}
				T obj = temp->myObj;
				temp->myNext = myList;
				myLast = NULL;
				return obj;
			}
			return (T)NULL;
		}

		void print() {
			Node<T> *myLast = myList;

			if (myList != NULL) {
				while (myLast->myNext != myList) {
					std::cout << myLast->myObj << std::endl;
					myLast = myLast->myNext;
				}
				std::cout << myLast->myObj << std::endl;
			}
		}

		std::vector<T>* getList() {
			std::vector<T> *items = new std::vector<T>();

			Node<T> *myLast = myList;

			if (myList != NULL) {
				while (myLast->myNext != myList) {
					items->push_back(myLast->myObj);
					myLast = myLast->myNext;
				}
				items->push_back(myLast->myObj);
			}
			return items;
		}

		bool contains(T t) {
			std::vector<T> *items = this->getList();

			for (int i = 0; i < items->size(); i++) {
				if (items->at(i) == t) return true;
			}
			return false;
		}

		void clear() { 
			myList = NULL; 
		}

		int size() {
			Node<T> *myLast = myList;
			int cnt = 0;
			if (myList != NULL) {
				cnt++;
				while (myLast->myNext != myList) {
					myLast = myLast->myNext;
					cnt++;
				}
				return cnt;
			}
			return 0;
		}

		bool isEmpty() {
			return (this->size() == 0);
		}
};

template<class K, class V> class Entry {
	private:
		K key;
		V value;
		bool cleared;

	public:
		~Entry() {
			delete key;
			delete value;
			delete cleared;
		}

		Entry(K key, V value) {
			this->key = key;
			this->value = value;
			this->cleared = false;
		}

		K getKey() {
			return key;
		}

		V getValue() {
			return value;
		}

		bool isCleared() {
			return cleared;
		}

		void setKey(K key) {
			this->key = key;
		}

		void setValue(V value) {
			this->value = value;
		}

		void setCleared(bool cleared) {
			this->cleared = cleared;
		}
};

template<class K, class V> class Map {
	private:
		std::vector<Entry<K, V>*> *myMap;

		int indexOf(K key) {
			for (int i = 0; i < myMap->size(); i++) {
				if (myMap->at(i)->getKey() == key) return i;
			}
			return -1;
		}

	public:
		~Map() {
			delete[] myMap;
		}

		Map() {
			myMap = new std::vector<Entry<K, V>*>();
		}

		void add(K key, V value) {
			if (!containsKey(key)) {
				Entry<K, V> *temp = new Entry<K, V>(key, value);
				myMap->push_back(temp);
			}
		}

		void remove(K key) {
			if (containsKey(key)) {
				myMap->erase(myMap->begin() + this->indexOf(key));
			}
		}

		V get(K key) {
			if (containsKey(key)) {
				return myMap->at(this->indexOf(key))->getValue();
			}
			return NULL;
		}

		void print() {
			for (int i = 0; i < myMap->size(); i++) {
				std::cout << "Key: " << myMap->at(i)->getKey() << "\tValue: " << myMap->at(i)->getValue() << std::endl;
			}
		}

		std::vector<K>* getKeyList() {
			std::vector<K> *keys = new std::vector<K>();

			for (int i = 0; i < myMap->size(); i++) {
				keys->push_back(myMap->at(i)->getKey());
			}

			return keys;
		}

		std::vector<V>* getValueList() {
			std::vector<V> *values = new std::vector<V>();

			for (int i = 0; i < myMap->size(); i++) {
				values->push_back(myMap->at(i)->getValue());
			}

			return values;
		}

		bool containsKey(K key) {
			for (int i = 0; i < myMap->size(); i++) {
				if (myMap->at(i)->getKey() == key) return true;
			}
			return false;
		}

		bool containsValue(V value) {
			for (int i = 0; i < myMap->size(); i++) {
				if (myMap->at(i)->getValue() == value) return true;
			}
			return false;
		}

		void clear() { 
			myMap->clear(); 
		}

		int size() {
			return myMap->size();
		}

		bool isEmpty() {
			return (this->size() == 0);
		}
};



// TODO:
template<class K, class V> class HashMap {};

template<class T> class SkipNode {};

template<class T> class SkipList {};

template<class T> class Heap {};

template<class T> class GraphNode {};

template<class T> class UndirectedGraph {};

template<class T> class DirectedGraph {};

};
#endif
