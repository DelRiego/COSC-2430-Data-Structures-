#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include "ArgumentManager.h"

using namespace std;
class list {
private:
	typedef struct Employees {
		string sID;
		string sfirst;
		string slast;
		string sDOB;
		int sYearsworked;
		int sSalary;
		string sPosition;
		Employees *next;
	}*nodeptr;

	ofstream out;
	string OriginalCopy;
	vector<string> storeRecords;
	nodeptr head = NULL, current = NULL, temp = NULL, prev = NULL, p1 = NULL, p2 = NULL, newnode = NULL;
public:
	list() {
		head = NULL, current = NULL, temp = NULL, prev = NULL, p1 = NULL, p2 = NULL, newnode = NULL;
	}
	nodeptr createNode(string line) {
		int newYearsworked = 0, newSalary = 0;
		string newID, newfirst, newlast, newDOB, MM, DD, YYYY, newPosition; istringstream iss(line);
		iss >> newID >> newfirst >> newlast >> MM >> DD >> YYYY >> newYearsworked >> newSalary >> newPosition;
		newDOB = YYYY + " " + MM + " " + DD;

		nodeptr n = new Employees;
		n->next = NULL;
		n->sID = newID;
		n->sfirst = newfirst;
		n->slast = newlast;
		n->sDOB = newDOB;
		n->sYearsworked = newYearsworked;
		n->sSalary = newSalary;
		n->sPosition = newPosition;
		return n;
	}

	void AddNode(string line) {
		nodeptr n = new Employees;
		n = createNode(line);
		if (head != NULL) {
			current = head;
			while (current->next != NULL) current = current->next;

			current->next = n;
			n->next = NULL;
		}
		else  head = n;
	}

	void read(string recordsFile,string outputFile) {
		string line;
		out.open(outputFile);
		ifstream iFile(recordsFile);
		while (getline(iFile, line)) {
			OriginalCopy += line + '\n';
			AddNode(line);
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

	void CommandFunnel(string ComLine) {
		ifstream Commandfile(ComLine); int counter = 0;
		string recordcheck, index, cLine, command;
		while (getline(Commandfile, cLine)) {
			istringstream iss(cLine);
		while (iss >> cLine) {
			if (!isdigit(cLine[0]))
				command += cLine;
			else {
				if (counter != 1) {
					index += cLine;
					counter++; }
				else index += " " + cLine; } }
			counter = 0;
			string sortType = command.substr(0, 3);
			if (sortType == "sor"){  
				sorter(command);
				PrintOutPut(); }
			else if (sortType == "out")  out << OriginalCopy;
			else if (sortType == "del") {
				DelFunc(index, command);
				PrintOutPut(); }
			else if (sortType == "add") {
				while (isdigit(Commandfile.peek()) || isspace(Commandfile.peek())) {
					getline(Commandfile, recordcheck);
					storeRecords.push_back(recordcheck);
				}				
				AddFunc(index, command, checkDupes(storeRecords));
				PrintOutPut();
			}
			storeRecords.clear(); iss.clear(); index.clear(); command.clear();
		}
	}

	vector <string> checkDupes(vector<string> storeRecords) {
		temp = head;
		while (temp != NULL) {
			for (unsigned int i = 0; i < storeRecords.size(); i++)
				if (storeRecords[i].substr(0, 5) == temp->sID)storeRecords[i] = "";

			temp = temp->next;
		}
		return storeRecords;
	}

	void sorter(string command) {
		string c1 = "", c2 = ""; int c3 = 0, c4 = 0;
		for (int i = 0; i < count(); ++i) {
			current = head;
			temp = NULL; prev = NULL; p1 = NULL; p2 = NULL;
		while (current != NULL && current->next != NULL) {
			if (command == "sortid") {
				c1 = current->sID; c2 = current->next->sID;}
			if (command == "sortfirstname") {
				c1 = current->sfirst; c2 = current->next->sfirst;}
			if (command == "sortlastname") {
				c1 = current->slast; c2 = current->next->slast;}
			if (command == "sortDOB") {
				c1 = current->sDOB; c2 = current->next->sDOB;}
			if (command == "sortyearsworked") {
				c3 = current->sYearsworked; c4 = current->next->sYearsworked;}
			if (command == "sortsalary") {
				c3 = current->sSalary; c4 = current->next->sSalary;}
			if (command == "sortposition") {
				c1 = current->sPosition; c2 = current->next->sPosition;}
			if (c1 > c2 || c3 > c4) {
				p1 = current;
				p2 = current->next;
				temp = p2->next;
				p1->next = temp;
				p2->next = p1;
				if (prev == NULL) {
					head = p2;
					prev = p2; }
				else {
					prev->next = p2;
					prev = prev->next; }
				}
			else {
				prev = current;
				current = current->next;
	} } } }

	void AddFunc(string nIndex, string Command, vector<string> storeRecords) {
	temp = NULL; prev = NULL; string line;

	if(Command == "addatend") {
	for (unsigned int i = 0; i < storeRecords.size(); i++)  
		if(storeRecords[i] != "") AddNode(storeRecords[i]);
	return;
	}
	for (int i =  storeRecords.size()-1; 0 <= i; i--) {
	if (storeRecords[i] != "") { newnode = createNode(storeRecords[i]);
	
	if(Command == "addatbeginning"){
		newnode->next = head;
		head = newnode;
	}else if (nIndex != "" && count() > stoi(nIndex)){
		current = head;
	for (int i = 0; i < stoi(nIndex); i++) {
		prev = current;
		current = current->next;
	}
	if(Command == "addafter"){

	temp = current->next;
	current->next = newnode;
	newnode->next = temp;

	}else if(Command == "addbefore"){

	if (current == head) {
		newnode->next = head;
		head = newnode; } 
	else {
	prev->next = newnode;
	newnode->next = current;
	} } } } } }

	void DelFunc(string nIndex, string Command) {
		istringstream iss(nIndex); temp = head; prev = NULL;
		int a = 0, b = 0, counter = 0; 
		if (count() == 0) return;

		if(Command == "deleteatbeginning") {
			head = temp->next;
			delete(temp);
		}else if (Command == "deleteatend") {
			while(temp != NULL && temp->next != NULL){
				prev = temp;
				temp = temp->next;
			} 
			prev->next = NULL;
			delete(temp);
		}else if (Command == "delete"){
			while (temp != NULL) {
				if (temp->sID == nIndex && temp == head) {
					head = head->next;
					delete(temp);
					return;
				}
				if (temp->sID == nIndex) {
					prev->next = temp->next;
					delete(temp);
					return;
				}
				prev = temp;
				temp = temp->next;
			}
		}else if (Command == "deleteto"){
			iss >> a >> b;
			int DeleteAmount = b - a;
			if (counter == a && temp == head) {
				for (int i = 0; i <= DeleteAmount; i++) {
					temp = head;
					head = head->next;
					delete(temp); } 
			}else {
				while (temp != NULL) {
					if (counter >= a && counter <= b) {
						prev->next = temp->next;
						delete(temp);
						temp = prev->next;
						counter++;
					} else {
						prev = temp;
						temp = temp->next;
						counter++; }}}}} 

	void PrintOutPut() {
		string DOB;
		current = head;
		while (current != NULL) {
			DOB = current->sDOB.substr(5, 5) + " " + current->sDOB.substr(0, 4);
			out << current->sID << " " << current->sfirst << " " << current->slast << " " << DOB << " "
			    << current->sYearsworked << " " << current->sSalary << " " << current->sPosition << endl;
			current = current->next;
		}
		out << endl;
	}
};

int main(int argc, char* argv[]) {
	ArgumentManager am(argc, argv);
	string recordsFile = am.get("input");
	string outputFile = am.get("output");
	string commandFile = am.get("command");
	list Employees;
	Employees.read(recordsFile,outputFile);
	Employees.CommandFunnel(commandFile);
	return 0;
}