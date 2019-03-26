#include <iostream>
#include <ctime>

using namespace std;

class elem {
public:
	int key;
	int data;
	unsigned int h;
	elem *left, *right;

	elem(int value = 0, int keyValue = 0) {
		left = nullptr;
		right = nullptr;
		data = value;
		key = keyValue;
		h = 0;
	}
};

class AVL_tree {
public:
	elem *top;
	int size;

	AVL_tree() {
		top = nullptr;
		size = 0;
	}

	unsigned int height(elem *el) {
		return el ? el->h : 0;
	}

	int balance_factor(elem *el) {
		return height(el->right) - height(el->left);
	}

	void calc_height(elem *el) {
		unsigned int h_left = height(el->left);
		unsigned int h_right = height(el->right);
		el->h = (h_left > h_right ? h_left : h_right) + 1;
	}

	elem* left_rotate(elem *el) {
		elem *newEl = el->right;
		el->right = newEl->left;
		newEl->left = el;

		calc_height(el);
		calc_height(newEl);
		return newEl;
	}

	elem* right_rotate(elem *el) {
		elem *newEl = el->left;
		el->left = newEl->right;
		newEl->right = el;

		calc_height(newEl);
		calc_height(el);
		return newEl;
	}

	elem* balancing(elem *el) {
		calc_height(el);
		if (balance_factor(el) == 2) {
			if (balance_factor(el->right) < 0) {
				el->right = right_rotate(el->right);
			}
			el = left_rotate(el);
			return el;
		}
		else if (balance_factor(el) == -2) {
			if (balance_factor(el->left) > 0) {
				el->left = left_rotate(el->left);
			}
			el = right_rotate(el);
			return el;
		}
		return el;
	}

	elem* ins(elem *el, int data, int keyData) {
		if (!el) {
			return new elem(data, keyData);
		}
		if (data < el->data) {
			el->left = ins(el->left, data, keyData);
		}
		if(data > el->data){
			el->right = ins(el->right, data, keyData);
		}
		return balancing(el);
	}

	void add(int data, int keyData) {
		top = ins(top, data, keyData);
		size++;
	}

	elem* find_left(elem *el) {
		return el->left ? find_left(el->left) : el;
	}

	elem* removemin(elem *el) {
		if (!el->left) {
			return el->right;
		}
		el->left = removemin(el->left);
		return balancing(el);
	}

	elem* remove(elem *el, int data) {
		if (!el) return 0;
		if (data < el->data) {
			el->left = remove(el->left, data);
		}
		else if (data > el->data) {
			el->right = remove(el->right, data);
		}
		else {
			elem *q = el->left;
			elem *r = el->right;
			delete el;

			if (!r) return q;

			elem *min = find_left(r);
			min->right = removemin(r);
			min->left = q;
			return balancing(min);
		}
		return balancing(el);
	}
	
	void del(int data) {
		top = remove(top, data);
		size--;
	}

	bool find(int data) {
		elem *p = top;
		while (p) {
			if (data < p->data) {
				p = p->left;
			}else if(data < p->data) {
				p = p->right;
			}
			else if (p->data == data) {
				return true;
			}
		}
		return false;
	}

	void prefix(elem *head) {
		if (!head) { return; }
		cout << head->data << "-" << head->key << " ";
		prefix(head->left);
		prefix(head->right);
	}

	void infix(elem *head) {
		if (!head) { return; }
		prefix(head->left);
		cout << head->data << "-" << head->key << " ";
		prefix(head->right);
	}

	void postfix(elem *head) {
		if (!head) { return; }
		prefix(head->left);
		prefix(head->right);
		cout << head->data << "-" << head->key << " ";
	}

	void MyFunction(int *Array, int size) {
		for (int i = 0; i < size - 1; i++) {
			for (int j = 0; j < size - 1 - i; j++) {
				if (Array[j] < Array[j + 1]) {
					int temp = Array[j];
					Array[j] = Array[j + 1];
					Array[j + 1] = temp;
				}
			}
		}
		del(Array[(size - 1) / 2]);
	}
};

void FillingArrayData(int *, int);
void PrintArray(int *, int);
void FillingArrayKeys(int *, int);
void PrintAVL(AVL_tree &newTree);

int main() {
	AVL_tree Tree;
	int size;
	cout << "Input how many elements u need: "; cin >> size;
	int *ArrayData = new int[size];
	int *ArrayKeys = new int[size];
	FillingArrayData(ArrayData, size);
	FillingArrayKeys(ArrayKeys, size);
	cout << "Our array of data: " << endl;
	PrintArray(ArrayData, size);
	cout << "Our array of keys: " << endl;
	PrintArray(ArrayKeys, size);
	for (int i = 0; i < size; i++) {
		Tree.add(ArrayData[i], ArrayKeys[i]);
	}
	PrintAVL(Tree);
	cout << "Now we use our function.\n";
	Tree.MyFunction(ArrayKeys, size);
	PrintAVL(Tree);
	
	delete[] ArrayKeys;
	delete[] ArrayData;
	system("pause");
	return 0;
}

void FillingArrayData(int *Array, int size){
	srand(time(NULL));
	int count = 1;
	while(count - 1 < size) {
		bool flag = true;
		int newRandom = rand() % size + 1;
		for (int j = 0; j < count; j++) {
			if (Array[j] == newRandom) {
				flag = false;
			}
		}
		if (flag) {
			Array[count - 1] = newRandom;
			count++;
		}
	}
}

void PrintArray(int *Array, int size){
	for (int i = 0; i < size; i++) {
		cout << Array[i] << " ";
	}
	cout << endl;
}

void FillingArrayKeys(int *ArrayKeys, int size) {
	srand(time(NULL));
	for (int i = 0; i < size; i++) {
		ArrayKeys[i] = rand() % size + 1;
	}
}

void PrintAVL(AVL_tree &newTree) {
	cout << "Infix: ";
	newTree.infix(newTree.top); cout << endl;
	cout << "Postfix: ";
	newTree.postfix(newTree.top); cout << endl;
	cout << "Prefix: ";
	newTree.prefix(newTree.top); cout << endl;
}
