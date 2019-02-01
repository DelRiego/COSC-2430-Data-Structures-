#pragma once

template<class T>
struct Qnode {
	T data;
	Qnode<T> *next;
	Qnode(const T & val, Qnode* n = NULL) : data(val), next(n) {}
	Qnode(Qnode *n = NULL) : next(n) {}
};

template<class T>
class queue {
private:
	Qnode<T> *front;
	Qnode<T> *rear;
	int size;

public:

	queue() {
		front = NULL;
		rear = NULL;
		size = 0;
	}

	void enqueue(T data) {
		Qnode<T> *newNode = new Qnode<T>(data);
		if (front == NULL) {
			newNode->next = front;
			front = newNode;
		}
		else rear->next = newNode;
		rear = newNode;
		size++;
	}

	void dequeue() {
		if (isEmpty()) return;
		Qnode<T> *temp = front;
		front = front->next;
		delete(temp);
		size--;
	}

	void clear() {
		while (size != 0)
			dequeue();
	}

	void print() {
		if (front == NULL)
			return;
		T x = getFront();
		std::cout << getFront() << std::endl;
		dequeue();
		print();
		enqueue(x);
	}

	bool isEmpty() {
		return (front == NULL);
	}

	int getSize() {
		return size;
	}

	T getFront() {
		return front->data;
	}

	T getRear() {
		return rear->data;
	}

	
};
