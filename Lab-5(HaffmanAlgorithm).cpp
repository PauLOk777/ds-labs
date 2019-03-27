#include <iostream>
#include <vector>

using namespace std;

class elem {
public:
	char data;
	unsigned int amount;
	elem *left, *right;

	elem(int value = 0, char temp = '\0') {
		data = temp;
		amount = value;
		left = right = nullptr;
	}
};

class HaffmanTree {
public:
	elem *top;

	HaffmanTree(elem* temp = nullptr) {
		top = temp;
	}

	bool compare(elem *one, elem *two) {
		return one->amount < two->amount;
	}

	elem *min(vector<elem *> &elems) {
		elem *min = elems[0];
		unsigned int erase_position = 0;
		for (unsigned int i = 1; i < elems.size(); i++) {
			if (!compare(min, elems[i])) {
				min = elems[i];
				erase_position = i;
			}
		}
		elems.erase(elems.begin() + erase_position);
		return min;
	}

	elem *add(elem *left, elem *right) {
		elem *new_top = new elem;
		new_top->amount = left->amount + right->amount;
		if (compare(left, right)) {
			new_top->left = left;
			new_top->right = right;
		}
		else {
			new_top->left = right;
			new_top->right = left;
		}
		return new_top;
	}

	char find(const string &kod) {
		elem *temp = top;
		for (int i = 0; temp, i < kod.length(); i++)
			if (kod[i] == '0')
				temp = temp->left;
			else if (kod[i] == '1')
				temp = temp->right;
			else exit(1);

		if (!temp || temp->right || temp->left) return '\0';
		return temp->data;
	}

	elem *haffman_algorithm(vector<elem*> &elems) {
		while (elems.size() > 1)
			elems.insert(elems.begin(), add(min(elems), min(elems)));
		return elems[0];
	}

	void infix(elem *top) {
		if (!top) return;
		infix(top->left);
		if (!(top->left && top->right))
			cout << top->data << " ";
		infix(top->right);
	}
};

int main() {
	HaffmanTree Tree;
	int N;
	cin >> N;
	vector<elem*> elems(N);
	elems[0] = new elem('a', 3);
	elems[1] = new elem('b', 7);
	elems[2] = new elem('c', 13);
	elems[3] = new elem('d', 5);
	elems[4] = new elem('e', 2);
	Tree.top = Tree.haffman_algorithm(elems);
	cout << "top = " << Tree.top->amount << endl;

	Tree.infix(Tree.top);

	system("pause");
	return 0;
}
