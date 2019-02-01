#pragma once

struct HT {
	std::string key;
	int value;
	HT(const std::string & nkey, int nvalue) : key(nkey), value(nvalue) {}
	HT() : key(""), value(0) {}
};

class hashtable {
private:
	static const int default_size = 10;
	int tsize, nstored = 0;
	HT **book;

	HT *createRecord() {
		struct HT *pbook = new HT();
		return pbook;
	}

	bool isPrime(int n) const {
		bool isPrime(true);
		for (int count = 2; count < n && isPrime; count++)
			if (n%count == 0)
				isPrime = false;
		return isPrime;
	}

	int getPrime(int n) const { //gets prime and allocates 4x space
		int i = 4 * n;
		while (!isPrime(i))
			i++;
		return i;
	}

	int hash(std::string key) {
		int hash = 0, ascii;
		for (unsigned int i = 0; i < key.length(); i++) {
			ascii = key[i] > 96 ? key[i] - 96 : key[i] - 64;
			hash = (hash * 32 + ascii) % tsize;
		}
		return hash;
	}
	int sillyhash(std::string key) {
		return key.length() % tsize;
	}
	int probefunction(int val, int iter) {
		int keyval = val;
		while (book[val]->value != 0) {
			if (val == tsize) val = 0;
			iter++;
			val++;
		}
		std::cout << "Iterations: " << iter << std::endl;
		if (iter == tsize)
			return -1;
		else return val;
	}
public:
	hashtable() {
		tsize = default_size;
		book = new HT*[tsize];
		for (int i = 0; i < tsize; i++)
			book[i] = createRecord();
	}

	hashtable(int nsize) {
		tsize = getPrime(nsize);
		book = new HT*[tsize];
		for (int i = 0; i < tsize; i++)
			book[i] = createRecord();
	}

	~hashtable() {
		delete book;
	}

	bool insert(std::string key, int value) {
		HT *temp = new HT(key, value);
		int hashIndex = hash(key);

		hashIndex = probefunction(hashIndex, 0);

		if (hashIndex == -1)
			return false;

		nstored++;
		book[hashIndex] = temp;
		std::cout << key << " is successfully added into table: " << hashIndex << std::endl;
		return true;
	}

	void init(int tsizei) {
		tsize = tsizei;
	}

	bool remove(std::string key, int value) {
		int hashindex = hash(key), iter = 0;

		while (book[hashindex]->value != 0) {
			if (iter == tsize) return false;

			else if (hashindex == tsize) hashindex = 0;

			if (book[hashindex]->key == key && book[hashindex]->value == value) {

				book[hashindex]->key = "";
				book[hashindex]->value = 0;
				nstored--;

				std::cout << "Element at: " << hashindex << " Successfully deleted " << std::endl;
				return true;
			}

			hashindex++;
		}
		return false;
	}

	bool lookup(std::string key, int &value) {
		int hashindex = hash(key), iter = 0;

		while (book[hashindex]->value != 0) {
			if (iter == tsize) return false;

			else if (hashindex == tsize) hashindex = 0;

			if (book[hashindex]->key == key) {
				std::cout << "The value for " << key << " at index " << hashindex << " is: " << std::endl;
				value = book[hashindex]->value;
				return true;
			}

			hashindex++;
		}
		return false;
	}

	bool modify(std::string key, int value) {
		int hashindex = hash(key), iter = 0;


		while (book[hashindex]->value != 0) {
			if (iter == tsize) return false;

			else if (hashindex == tsize) hashindex = 0;

			else if (book[hashindex]->key == key) {
				std::cout << "The value for " << key << " at index " << hashindex << " is: " << std::endl;
				value = book[hashindex]->value;
				return true;
			}
			iter++;
			hashindex++;
		}
		return false;
	}

	void getKeys(std::string *&all_key, int &nkeys) {
		std::string *all_keys = new std::string[nstored]();

		for (int i = 0; i < tsize; i++) {
			if (book[i]->key != "" && book[i]->value != 0) {
				nkeys++;
				all_key[nkeys] = book[i]->key;
			}
		}
	}

	int getTableSize() {
		return tsize;
	}

	int getNumbersStored() {
		return nstored;
	}

	void printTable() {
		for (int i = 0; i < tsize; i++) {
			if (book[i]->key != "" && book[i]->value != 0)
				std::cout << "Name: " << book[i]->key << " Phone Number: " << book[i]->value << " Index: " << i << std::endl;
		}
	}
};
