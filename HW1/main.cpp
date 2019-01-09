#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>
#include "ArgumentManager.h"
using namespace std;

void loader(ifstream & filename, double a[20][20], int x, int y) {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++)
			a[i][j] = 0;
	}
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++)
			filename >> a[i][j];
	}
	filename.clear();
	filename.seekg(0, ios::beg);
}

void multiply(double a[20][20], double b[20][20], double c[20][20], int x1, int y1, int x2, int y2) { //Multiplys Array A and B and inputs into C
	for (int i = 0; i < x1; ++i)
		for (int j = 0; j < y2; ++j)
			for (int k = 0; k < y1; ++k)
				c[i][j] += a[i][k] * b[k][j];
}

int getrows(ifstream & filename) {
	string line;
	int rowCounter = 0;

	while (getline(filename, line)) {
		string::iterator end_pos = remove(line.begin(), line.end(), ' ');
		line .erase(end_pos, line.end());
		if (line != "") rowCounter++;
	}
	cout << "line: " << line << endl;

	filename.clear();
	filename.seekg(0, ios::beg);
	return rowCounter;
}

int getcolumns(ifstream & filename) {
	string line;
	int columncounter = 0; double num;
	
	getline(filename, line);
	istringstream iss(line);
	while (iss >> num)
		 columncounter++;

	filename.clear();
	filename.seekg(0, ios::beg);
	return columncounter;
}

bool invalidChar(char c) {
	if (c >= 'A' && c <= 'z')
		return false;
	if (c == '#' || c == '!' || c == '@' || c == '$' || c == '%' || c == '^' || c == '&' || c == '*')
		return false;
	return true;
}

bool SignCheck(ifstream & file) {
	string line, line2;
	if (file.is_open()) {
		file.seekg(0, ios::end);
		if (file.tellg() != 0) {
			file.clear();
			file.seekg(0, ios::beg);
			while (getline(file, line)) {
				istringstream iss (line);
				for (int i = 0; i < line.length(); i++) {
					if (!invalidChar(line[i])) return false;
					line2 += line[i];
				}
			}
		}
		else return false;
	}
	else return false;
	if (line2.find("--") != -1) return false;
	file.clear();
	file.seekg(0, ios::beg);
	return true;
}

int main(int argc, char* argv[]) {

	ArgumentManager am(argc, argv);
	string GetFileName = am.get("A");
	string GetFileName2 = am.get("B");
	string OutFilename = am.get("C");

	ifstream infile1(GetFileName);
	ifstream infile2(GetFileName2);
	ofstream Output(OutFilename);

	int x1 = getrows(infile1);
	int y2 = getcolumns(infile2);
	int y1 = getcolumns(infile1);
	int x2 = getrows(infile2);

	double Matrix[20][20] = { { 0 } };
	double Matrix2[20][20] = { { 0 } };
	double rMatrix[20][20] = { { 0 } };

	if (SignCheck(infile1) && SignCheck(infile2) && x2 == y1) {
		loader(infile1, Matrix, x1, y1);
		loader(infile2, Matrix2, x2, y2);
		multiply(Matrix, Matrix2, rMatrix, x1, y1, x2, y2);
		Output.precision(2);
		Output.setf(ios::fixed);
		for (int i = 0; i < x1; ++i) {
			for (int j = 0; j < y2; ++j)
				 Output << rMatrix[i][j] << " ";
			Output << endl;
		}
	}
	else Output << "error";

	return 0;
}