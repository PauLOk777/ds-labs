#include <iostream>
#include <ctime>

using namespace std;

class elem {
public:
	int data;
	unsigned int h;
	elem *left, *right;

	elem(int value = 0) {
		left = nullptr;
		right = nullptr;
		data = value;
		h = 0;
	}
};

class AVL_tree {
private:
	elem *top;
public:
	AVL_tree() {
		top = nullptr;
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

		calc_height(el);
		calc_height(newEl);
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
			if (balance_factor(el->left) < 0) {
				el->left = left_rotate(el->left);
			}
			el = right_rotate(el);
			return el;
		}
		return el;
	}

	elem* ins(elem *el, const int &data) {
		if (!el) {
			return new elem(data);
		}
		if (data < el->data) {
			el->left = ins(el->left, data);
		}
		else {
			el->right = ins(el->right, data);
		}
		return balancing(el);
	}

	void add(const int &data) {
		this->top = ins(top, data);
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

	elem* remove(elem *el, const int &data) {
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
	
	void del(const int &data) {
		top = remove(top, data);
	}
};

int main() {
	cout << "Hello its AVL FUCKING TREE" << endl;

	return 0;
}
