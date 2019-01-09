#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <algorithm>
#include "ArgumentManager.h"
using namespace std;

bool isObracket(char ch) {
	if (ch == '(' || ch == '{' || ch == '[') return true;
	else return false;
}
bool isCbracket(char ch) {
	if (ch == ')' || ch == '}' || ch == ']') return true;
	else return false;
}
bool isOperand(char ch) {
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z' || ch >= '0' && ch <= '9')) return true;
	else return false;
}
string simplify(string line) {
	string result;
	stack<int> opt;
	opt.push(0);
	opt.push(0);
	opt.push(0);

	for (unsigned int i = 0; i < line.length(); i++) {
		if (line[i] == '+' && i == 0) continue;
		else if (line[i] == '+' && i > 0) {
			if (opt.top() == 0) result += '+';
			else if (result.back() != '-') result += '-';
		}
		else if (line[i] == '-') {
			if (opt.top() == 0 ) {
				if (i > 0 && result.back() == '+') result.pop_back();	
				result += '-'; 
			}
			else {
				if (result.back() == '-') result.pop_back();
				result += '+';
			}
		}
		else if (isObracket(line[i]) && i > 0) {
			if (line[i - 1] == '-') opt.push((opt.top() == 1) ? 0 : 1);
			else opt.push(opt.top());
		}
		else if (isCbracket(line[i])) opt.pop();
		else if (isOperand(line[i])) result += line[i];
	}
	if (result[0] == '+') result.erase(result.begin());
	return result;
}
//geeks for geeks helped with the parathesis checker
bool ParathesisChecker(string line) {
	stack<char> brackets;
	char x;

	for (unsigned int i = 0; i < line.length(); i++) {
		if (line[i] == '(' || line[i] == '[' || line[i] == '{') {
			brackets.push(line[i]);
			continue;
		}
		switch (line[i]) {
		case ')':
			x = brackets.top();
			brackets.pop();
			if (x == '{' || x == '[') return false;
			break;
		case '}':
			x = brackets.top();
			brackets.pop();
			if (x == '(' || x == '[') return false;
			break;
		case ']':
			x = brackets.top();
			brackets.pop();
			if (x == '(' || x == '{') return false;
			break;
		}
	}
	return (brackets.empty());
}
// I got help from Chanta Mak on the Evaluation function.
int Evaluation(string line) {
	int result = 0;
	char temp;
	for (int i = 0; i < line.length(); i++) {
		if (i == 0 && isOperand(line[i])) {
			if (isdigit(line[i])) {
				int num = line[i] - '0';
				result += num;
			}
			else result += line[i];
		}
		if (isOperand(line[i])) {
		}
		else if (line[i] == '+') {
			if (isdigit(line[i + 1])) {
				int num = line[i + 1] - '0';
				result += num;
			}
			else result += line[i + 1];
		}
		else if (line[i] == '-') {
			if (isdigit(line[i + 1])) {
				int num = line[i + 1] - '0';
				result -= num;
			}
			else {
				result -= line[i + 1];
			}
		}
	}
	return result;
}
void print(stack <string> Values, ofstream & opf) {
	stack <int> AsciiValues;
	int Temp = 0;
	int Size = Values.size();
	if (Values.size() > 1) {
	for (unsigned int i = 0; i < Size; i++) {
		AsciiValues.push(Evaluation(Values.top()));
		Values.pop();
	}
	for (unsigned int i = 0; i < Size-1; i++) {
		Temp = AsciiValues.top();
		AsciiValues.pop();
		if (Temp != AsciiValues.top()) {
			opf << "No";
			return;
		}
	} }
	opf << "Yes";
}
int main(int argc, char* argv[]) {
	ArgumentManager am(argc, argv);
	string infilename = am.get("input");
	string outfilename = am.get("output");

	ifstream ipf(infilename);
	ofstream opf(outfilename);
	bool Valid = true;
	int linecounter = 1;
	string line;

	stack <string> StoreExp;
	while (getline(ipf, line)) {
		if (line != "") {
			if (ParathesisChecker(line)) {
				StoreExp.push(simplify(line));
			}
			else {
				opf << "Error at: " << linecounter << endl;
				Valid = false;
			}
			linecounter++;
		}
	}
	if (Valid) print(StoreExp, opf);
	return 0;
}