#pragma once

template<class T>
struct Snode {
	T data;
	Snode<T> *next;
	Snode(const T & val, Snode* n) : data(val), next(n) {}
	Snode(Snode *n = NULL) : next(n) {}
};

template<class T>
class stack {
private:


public:
	Snode<T> *top;
	int size;

	stack() {
		top = NULL;
		size = 0;
	}

	void push(T data) {
		Snode<T> *newNode = new Snode<T>(data, top);
		top = newNode;
		size++;
	}

	void pop() {
		if (isEmpty()) return;
		Snode<T> *temp = top;
		top = top->next;
		delete(temp);
		size--;
	}

	T getTop() {
		return top->data;
	}

	int getSize() {
		return size;
	}

	void print() {
		if (top == NULL)
			return;
		T x = getTop();
		std::cout << getTop() << std::endl;
		pop();
		print();
		push(x);
	}

	bool isEmpty() {
		return (top == NULL);

	}

	void clear() {
		while (top != NULL)
			pop();
	}
};