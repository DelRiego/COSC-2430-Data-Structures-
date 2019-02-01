#pragma once
template<class T>
struct Tnode {
	Tnode(int value, int height) : key(value), height(height), left(NULL), right(NULL) {}
	int key, height;
	Tnode* left;
	Tnode* right;
};

template<class T>
class tree {
private:

int max(int a, int b) {
	return (a > b) ? a : b;
}

int height(Tnode<T> *t) {
	return (t == NULL ? -1 : t->height);
}

Tnode<T>* insert(int x, Tnode<T> *t) {
	if (t == NULL) t = new Tnode<T>(x, 0);

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

Tnode<T>* singleRightRotate(Tnode<T>* &t) {
	Tnode<T> *temp = t->left;
	t->left = temp->right;
	temp->right = t;
	t->height = max(height(t->left), height(t->right)) + 1;
	temp->height = max(height(temp->left), t->height) + 1;
	return temp;
}

Tnode<T>* singleLeftRotate(Tnode<T>* &t) {
	Tnode<T> *temp = t->right;
	t->right = temp->left;
	temp->left = t;
	t->height = max(height(t->left), height(t->right)) + 1;
	temp->height = max(height(t->right), t->height) + 1;
	return temp;
}

Tnode<T>* doubleRightRotate(Tnode<T>* &t) {
	t->left = singleLeftRotate(t->left);
	return singleRightRotate(t);
}

Tnode<T>* doubleLeftRotate(Tnode<T>* &t) {
	t->right = singleRightRotate(t->right);
	return singleLeftRotate(t);
}
public:
	Tnode<T> *root;
	int size;

	tree() {
		root = NULL;
		size = 0;
	}

	void insert(T x) {
		root = insert(x, root);
	}

	void inorder(Tnode<T>* t) {
		if (t != NULL) {
			inorder(t->left);
			std::cout << t->key << " ";
			inorder(t->right);
		}
	}

	void preorder(Tnode<T>* t) {
		if (t != NULL) {
			std::cout << t->key << " ";
			preorder(t->left);
			preorder(t->right);
		}
	}

	void postorder(Tnode<T>* t) {
		if (t != NULL) {
			postorder(t->left);
			postorder(t->right);
			std::cout << t->key << " ";
		}
	}

	void getLevel(int level, Tnode<T>* t) {
		if (t == NULL) return;
		if (root->height - level < -1) {
			std::cout << "empty";
			return;
		}
		if (level == 1) {
			std::cout << t->key << " ";
			return;
		}
		getLevel(level - 1, t->left);
		getLevel(level - 1, t->right);
	}



};