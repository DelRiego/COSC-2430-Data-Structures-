#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
#include "ArgumentManager.h"
using namespace std;

typedef class AVLtree {
private:
	typedef struct Node {
		Node(int value, int height) : key(value), height(height), left(NULL), right(NULL) {}
		int key, height;
		Node* left;
		Node* right;
	}*nodeptr;

	int max(int a, int b) {
		return (a > b) ? a : b;
	}

	int height(nodeptr t) {
		return (t == NULL ? -1 : t->height);
	}

	nodeptr insert(int x, nodeptr t) {
		if (t == NULL) t = new Node(x, 0);

		else if (x < t->key) {
			t->left = insert(x, t->left);
			if (height(t->left) - height(t->right) == 2) {
				if (x < t->left->key)
					t = singleRightRotate(t);
				else
					t = doubleRightRotate(t);
			}
		}
		else if (x > t->key) {
			t->right = insert(x, t->right);
			if (height(t->right) - height(t->left) == 2) {
				if (x > t->right->key)
					t = singleLeftRotate(t);
				else
					t = doubleLeftRotate(t);
			}
		}
		t->height = max(height(t->left), height(t->right)) + 1;
		return t;
	}

	nodeptr singleRightRotate(nodeptr &t) {
		nodeptr temp = t->left;
		t->left = temp->right;
		temp->right = t;
		t->height = max(height(t->left), height(t->right)) + 1;
		temp->height = max(height(temp->left), t->height) + 1;
		return temp;
	}

	nodeptr singleLeftRotate(nodeptr &t) {
		nodeptr temp = t->right;
		t->right = temp->left;
		temp->left = t;
		t->height = max(height(t->left), height(t->right)) + 1;
		temp->height = max(height(t->right), t->height) + 1;
		return temp;
	}

	nodeptr doubleRightRotate(nodeptr &t) {
		t->left = singleLeftRotate(t->left);
		return singleRightRotate(t);
	}

	nodeptr doubleLeftRotate(nodeptr &t) {
		t->right = singleRightRotate(t->right);
		return singleLeftRotate(t);
	}
public:
	nodeptr root = NULL;
	void insert(int x) {
		root = insert(x, root);
	}

	void fillTree(string input) {
		ifstream ipf(input);
		string line;
		int value;
		while (getline(ipf, line)) {
			istringstream iss(line);
			while (iss >> value)
				insert(value);
		}
	}

	void getLevel(int level, ofstream &opf, nodeptr t) {
		if (t == NULL) return;
		if (root->height - level < - 1) {
			opf << "empty";
			return;
		}
		if (level == 1) {
			opf << t->key << " ";
			return;
		}
		getLevel(level - 1, opf, t->left);
		getLevel(level - 1, opf, t->right);
	}

	void display(string command, ofstream &opf, nodeptr t) {
		if (t != NULL) {
			if (command == "inordertraversal") {
				display(command, opf, t->left);
				opf << t->key << " ";
				display(command, opf, t->right);
			}
			else if (command == "preordertraversal") {
				opf << t->key << " ";
				display(command, opf, t->left);
				display(command, opf, t->right);
			}
			else if (command == "postordertraversal") {
				display(command, opf, t->left);
				display(command, opf, t->right);
				opf << t->key << " ";
			}
		}
	}
}Tree;

int main(int argc, char* argv[]) {
	ArgumentManager am(argc, argv);
	string inputf = am.get("value");
	string commandf = am.get("command");
	string outputf = am.get("output");

	ifstream cmf(commandf);
	ofstream opf(outputf);
	string line, Subline;
	Tree t;
	int level;
	t.fillTree(inputf);

	while (getline(cmf, line)) {
		if (line != "") {
			istringstream iss(line);
			iss >> Subline;
			if (Subline == "Level") {
				iss >> level;
				if (level != 0) t.getLevel(level, opf, t.root);
			}
			else {
				line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());
				transform(line.begin(), line.end(), line.begin(), ::tolower);
				t.display(line, opf, t.root);
			}
			opf << endl;
		}
	}
	return 0;
}