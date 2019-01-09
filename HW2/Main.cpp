#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include "ArgumentManager.h"

using namespace std;
class list {
private:
	typedef struct student {
		string sID;
		string sfirst;
		string slast;
		string sDOB;
		string sGPA;
		student *next;
	}*nodeptr;

	nodeptr head; nodeptr current; nodeptr temp; nodeptr prev; nodeptr p1; nodeptr p2;
public:
	list() {
		head = NULL;
		current = NULL;
		temp = NULL;
		prev = NULL;
		p1 = NULL;
		p2 = NULL;
	}
	void read(string recordsFile) {
		ifstream Records(recordsFile); char delimiter = ':';  istringstream iss; ;
		string line, data, ID, first, last, DOB, GPA;

		while (getline(Records, line)) {
			string::iterator end_pos = remove(line.begin(), line.end(), ' ');
			line.erase(end_pos, line.end());
			if (line[0] != '{') {
				line.erase(0, 6);
				deleteByContent(line);
			}
			else {
				for (unsigned int i = 0; i <= line.length(); i++) {
					if (line[i] == delimiter) {
						line[i] = ' ';
					}
				}
				bool inB = false; string result;
				for (size_t i = 0; i < line.size(); i++) {
					char ch = line[i];
					if (ch == ',' || ch == '{' || ch == '}')
						inB = true;
					else
						if (ch == ' ') {
							inB = false;
							result += ch;
						}
						else
							if (!inB)
								result += ch;
				}
				line = result;
				line.erase(0, 1);
				if (line != "") {
					iss.str(line);
					iss >> ID >> first >> last >> DOB >> GPA;
					AddNode(ID, first, last, DOB, GPA);
					iss.clear();
				}
			}
		}
	}

	void deleteByContent(string key) {
		student * temp1 = head;
		student * prev1 = new student;
		if (temp1 != NULL && temp1->sID == key)
		{
			head = temp1->next;
			delete (temp1);
			return;
		}
		while (temp1 != NULL && temp1->sID != key) {
			prev1 = temp1;
			temp1 = temp1->next;
		}
		if (temp1 == NULL)return;

		prev1->next = temp1->next;

		delete (temp1);
	}

	void removeDupes() {

		student * arrow = head;
		if (arrow == NULL)
			return;

		student *next = new student;
		while (arrow != NULL && arrow->next != NULL) {

			if (arrow->sID == arrow->next->sID) {
				swap(arrow, arrow->next);
				next = arrow->next->next;
				free(arrow->next);
				arrow->next = next;
			}
			else {
				arrow = arrow->next;
			}
		}
	}

	int count() {
		int c = 0;
		current = head;
		while (current != 0) {
			current = current->next;
			c++;
		}
		return c;
	}

	void swap(student *a, student * b) {
		string temp = a->sID;
		a-> sID = b->sID;
		b-> sID = temp;
		string ftemp = a->sfirst;
		a->sfirst = b->sfirst;
		b->sfirst = ftemp;
		string ltemp = a->slast;
		a->slast = b->slast;
		b->slast = ltemp;
		string dtemp = a->sDOB;
		a->sDOB = b->sDOB;
		b->sDOB = dtemp;
		string gtemp = a->sGPA;
		a->sGPA = b->sGPA;
		b->sGPA = gtemp;
	}
		void AddNode(string newID, string newfirst, string newlast, string newDOB, string newGPA) {
		nodeptr n = new student;
		n->next = NULL;
		n->sID = newID;
		n->sGPA = newGPA;
		n->sfirst = newfirst;
		n->slast = newlast;
		n->sDOB = newDOB;
		if (head != NULL) {
			current = head;
			while (current->next != NULL) {
				current = current->next;
			}
			current->next = n;
		}
		else {
			head = n;
		}
	}

	void sort(string sortBy) {
		ifstream test(sortBy); string line = "id"; int NumOfNodes = count();
		string c1 = ""; string c2 = "";

		do {
			string::iterator end_pos = remove(line.begin(), line.end(), ' ');
			line.erase(end_pos, line.end());
			for (int j = 0; j < NumOfNodes; ++j) {
				current = head;
				temp = NULL;
				prev = NULL;
				p1 = NULL;
				p2 = NULL;
				while (current != NULL && current->next != NULL) {
					if (line == "id") {
						c1 = current->sID; c2 = current->next->sID;
					}
					if (line == "first") {
						c1 = current->sfirst; c2 = current->next->sfirst;
					}
					if (line == "last") {
						c1 = current->slast; c2 = current->next->slast;
					}
					if (line == "DOB") {
						c1 = current->sDOB; c2 = current->next->sDOB;
					}
					if (line == "GPA") {
						c1 = current->sGPA; c2 = current->next->sGPA;
					}
					if (c1 > c2) {
						p1 = current;
						p2 = current->next;
						temp = p2->next;
						p1->next = temp;
						p2->next = p1;
						if (prev == NULL) {
							head = p2;
							prev = p2;
						}
						else {
							prev->next = p2;
							prev = prev->next;
						}
					}
					else {
						prev = current;
						current = current->next;
					}
				}
			}
		} while (getline(test, line));
	}

	void PrintOutPut(string output) {
		ofstream outputFile(output);
		current = head;
		while (current != NULL) {
			outputFile << "{id:" << current->sID << ",first:" << current->sfirst << ",last:" << current->slast
				<< ",DOB:" << current->sDOB << ",GPA:" << current->sGPA << "}" << endl;
			current = current->next;
		}
	}
};

int main(int argc, char* argv[]) {
	ArgumentManager am(argc, argv);
	string recordsFile = am.get("input");
	string sortFile = am.get("sort");
	string outputFile = am.get("output");
	list students;
	students.read(recordsFile);
	students.sort(sortFile);
	students.removeDupes();
	students.PrintOutPut(outputFile);
	return 0;
}