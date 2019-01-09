#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "ArgumentManager.h"
using namespace std;

class list {
protected:
	typedef struct node {
		string BookTitle;
		node *next;
		node(const string & val, node* n = 0) : BookTitle(val), next(n) {}
		node(node* n = 0) : next(n) {}
	}*nodeptr;
	nodeptr head = 0, rear = 0, cu = 0;

	void insert(string Book_Name, int pos) {
		nodeptr newnode = new node(Book_Name);
		if (pos == 0) {
			newnode->next = head;
			head = newnode;
		}
		else rear->next = newnode;
		rear = newnode;
	}
	void remove() {
		if (empty()) return;
		nodeptr temp;
		temp = head;
		head = head->next;
		delete(temp);
	}
	string retrieve() {
		if (head == 0) return "";
		return head->BookTitle;
	}
public:
	bool empty() {
		return (head == NULL);
	}
	int size() {
		int c = 0;
		cu = head;
		while (cu != 0) {
			cu = cu->next;
			c++;
		}
		return c;
	}
};

class stack : public list {
public:
	void push(string Book_Name) {
		insert(Book_Name, 0);
	}
	void pop() {
		remove();
	}
	string top() {  
		return retrieve(); 
	}
};

class queue : public list {
public:
	void enqueue(string Book_Name) {
		insert(Book_Name, size());
	}
	void dequeue() {
		remove();
	}
	string front() {
		return retrieve();
	}
};

int main(int argc, char* argv[]) {
	ArgumentManager am(argc, argv);
	string inputf = am.get("input");
	string outputf = am.get("output");

	stack s;
	queue q;
	queue tempQ;
	string book_name, command, key;
	ifstream in(inputf);
	ofstream out(outputf);

	while (getline(in, book_name)) {
		bool sSuccess = false, qSuccess = false;
		int sCost = 1, qCost = 1;
		istringstream iss(book_name);
		iss >> command;
		while (iss >> book_name)
			key += book_name + " ";
		if (command == "buy") {
			s.push(key);
			q.enqueue(key);
		}
		else if (command == "sale") {
			while (!s.empty()) {
				if (s.top() == key) {
					sSuccess = true;
					s.pop();
					break;
				}
				sCost++;
				tempQ.enqueue(s.top());
				s.pop();
			}
			while (!tempQ.empty()) {
				s.push(tempQ.front());
				tempQ.dequeue();
			}
			while (!q.empty()) {
				if (q.front() == key) {
					qSuccess = true;
					q.dequeue();
					break;
				}
				qCost++;
				tempQ.enqueue(q.front());
				q.dequeue();
			}
			while (!tempQ.empty()) {
				q.enqueue(tempQ.front());
				tempQ.dequeue();
			}
			if (sSuccess && qSuccess) {
				out << key << "finding cost at stack: " << sCost << ", at queue:" << qCost << endl;
			}
			else out << key << "not found" << endl;
		}
		command.clear();
		book_name.clear();
		key.clear();
		iss.clear();
	}

	return 0;
}