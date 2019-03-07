#include <iostream>
#include <ctime>

using namespace std;

class elem {
public:
	int data;
	elem *next;
};

class oneSideQueue {
private:
	elem *back;
	int elements;
public:
	oneSideQueue() {
		elements = 0;
		back = NULL;
	}
	void push(int value) {
		elem *temp = new elem;
		temp->data = value;
		temp->next = back;
		back = temp;
		elements++;
	}
	void pop(int &out) {
		if (!this->back) {
			cout << "Queue is empty!" << endl;
			return;
		}
		if (!this->back->next) {
			out = this->back->data;
			delete this->back;
			back = NULL;
			elements--;
		}
		elem *prev, *end;
		prev = end = this->back;
		while (end->next) {
			prev = end;
			end = end->next;
		}
		out = end->data;
		delete end;
		prev->next = NULL;
		elements--;
	}
	int size() {
		return elements;
	}
	void clear() {
		elem *del;
		while (back) {
			del = back;
			back = back->next;
			delete del;
			elements--;
		}
	}
	bool isEmpty() {
		return (elements == 0);
	}
	void show() {
		elem *temp, *newBack;
		oneSideQueue newQueue;
		newBack = back;
		while (newBack) {
			temp = newBack;
			newQueue.push(temp->data);
			newBack = newBack->next;
		}
		elem *newBack_2 = newQueue.back;
		while (newBack_2) {
			temp = newBack_2;
			cout << temp->data << " ";
			newBack_2 = newBack_2->next;
		}
		newQueue.clear();
		cout << endl;
	}
};

int main() {
	srand(time(NULL));
	oneSideQueue queue;
	int temp;
	cout << "How many times you wanna push: "; cin >> temp;
	for (int i = 0; i < temp; i++) {
		queue.push(rand() % 20 + 1);
	}
	queue.show();
	cout << "How many times you wanna pop: "; cin >> temp;
	int out;
	for (int i = 0; i < temp; i++) {
		queue.pop(out);
		cout << "We deleted: " << out << endl;
	}
	queue.show();
	cout << "Size of array: " << queue.size() << endl;
	queue.clear();
	if (queue.isEmpty()) {
		cout << "Queue is clear!" << endl;
	}
	else {
		cout << "Queue isn't clear!" << endl;
	}

	return 0;
}
