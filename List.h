#pragma once
#include <iostream>
//Make copy constructor

template<class T>
struct node {
	T data;
	node<T> *next;
	node(const T & val, node* n = NULL) : data(val), next(n) {}
	node(node* n = NULL) : next(n) {}
};

template<class T>
class List {
private:

	node<T> *mergeS(node<T> *a, node<T> *b) {
		node<T> *result(NULL);
		if (!a)
			return b;
		if (!b)
			return a;

		if (a->data < b->data) {
			result = a;
			result->next = mergeS(a->next, b);
		}
		else {
			result = b;
			result->next = mergeS(a, b->next);
		}
		return result;
	}

public:
	node <T> *head;
	node <T> *tail;
	node <T> *temp;
	int size;

	List() {
		head = NULL;
		tail = NULL;
		temp = NULL;
		size = 0;
	}

	void push_front(const T &value)	{
		node<T> *newNode = new node<T>(value);
		newNode->next = head;
		head = newNode;
		if (head->next == 0)
			tail = head;
		size++;
	}

	void push_back(const T &value) {
		node<T> *newNode = new node<T>(value);
		if (!head)
			head = newNode;
		if (tail)
			tail->next = newNode;
		tail = newNode;
		size++;
	}

	bool pop_front() {
		if (head != NULL) {
			temp = head;
			head = head->next;
			delete (temp);
			size--;
			return true;
		}
		return false;
	}

	bool pop_back() {
		if (isEmpty()) return false;
		temp = head;
		if (head == tail) {
			delete(head);
			head = NULL;
			tail = NULL;
		}
		else {
			while (temp->next != tail)
				temp = temp->next;
			delete(tail);
			tail = temp;
			tail->next = NULL;
		}
		size--;
		return true;
	}

	void removePosition(int x) {
		if (x > size || x <= 0) return;
		if (x == 1)
			pop_front();
		else if (x == size)
			pop_back();
		else {
			temp = head;
			node<T> *prev(NULL);
			for (int i = 1; i < x; i++) {
				prev = temp;
				temp = temp->next;
			}
			prev->next = temp->next;
		}
	}

	void removeContent(T content) {
		if (head->data == content)
			pop_front();
		else if (tail->data == content)
			pop_back();
		else {
			temp = head;
			node<T> *prev(NULL);
			while (temp->next != NULL && temp->data != content) {
				prev = temp;
				temp = temp->next;
			}
			if (temp->data == content) prev->next = temp->next;
		}
	}

	bool getContent(int x) {
		if (x > size || x <= 0) return false;
		temp = head;
		for (int i = 1; i < x; i++)
			temp = temp->next;
		std::cout << temp->data << std::endl;
		return true;
	}

	bool getIndex(T content) {
		temp = head;
		int count = 1;
		while (temp->next != NULL && temp->data != content) {
			temp = temp->next;
			count++;
		}
		if (temp->data == content) {
			std::cout << count << std::endl;
			return true;
		}
		return false;
	}

	int getSize() {
		return size;
	}

	bool isEmpty() {
		return (head == NULL && tail == NULL);
	}

	T front() {
		return head->data;
	}

	T back() {
		return tail->data;
	}

	void clear() {
		for (int i = size; i > 0; i--)
			pop_front();
	}

	void mergeSort() {
		node<T> *a(head);
		node<T> *c(head->next);
		a->next = NULL;
		while (c) {
			node<T> *b(c);
			c = c->next;
			b->next = NULL;
			head = mergeS(a, b);
			a = head;
		}
	}

	void print(node <T> *curr)const {
		if (curr == NULL)
			return;
		std::cout << curr->data << " ";
		print(curr->next);
	}
};
