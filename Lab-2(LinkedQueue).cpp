#include <iostream>
#include <ctime>

using namespace std;

class elem {
public:
	int data;
	elem *next;
	elem *prev;
};

class Queue {
public:
	Queue() {
		back = NULL;
		front = NULL;
		Size = 0;
	}

	void push_back(int value) {
		elem *temp = new elem;
		temp->data = value;
		temp->prev = NULL;
		if (!back) {
			back = front = temp;
			temp->next = NULL;
		}
		else {
			temp->next = back;
			back->prev = temp;
			back = temp;
		}
		Size++;
	}

	void push_front(int value) {
		elem *temp = new elem;
		temp->data = value;
		temp->next = NULL;
		if (!front) {
			front = back = temp;
			temp->prev = NULL;
		}else{
		temp->prev = front;
		front->next = temp;
		front = temp;
		}
		Size++;
	}

	void pop_back(int &out) {
		if (!back) {
			cout << "Queue is empty.\n";
			exit(1);
		}
		if (!back->next) {
			out = back->data;
			delete back;
			back = front = NULL;
			Size--;
		}
		else {
			elem *del = back;
			out = back->data;
			back = back->next;
			delete del;
			back->prev = NULL;
			Size--;
		}
	}

	void pop_front(int &out) {
		if (!front) {
			cout << "Queue is empty.\n";
			exit(1);
		}
		if (!front->prev) {
			out = front->data;
			delete front;
			back = front = NULL;
			Size--;
	
		}
		else {
			elem *del = front;
			out = front->data;
			front = front->prev;
			delete del;
			front->next = NULL;
			Size--;
		}
	}

	void clear() {
		elem *del;
		while (back) {
			del = back;
			back = back->next;
			delete del;
		}
		front = NULL;
		Size = 0;
	}

	int size() {
		return Size;
	}

	bool isEmpty() {
		return (Size == 0);
	}

	void Delete_3rdElem() {
		Queue newQueue;
		int temp, count = 0;
		int newSize = Size;
		for (int i = 1; i <= newSize; i++) {
			this->pop_back(temp);
			if (!(i % 3 == 0)) {
				newQueue.push_back(temp);
			}
			else count++;
		}
		this->clear();
		for (int i = 1; i <= newSize - count; i++) {
			newQueue.pop_back(temp);
			this->push_back(temp);
		}
		newQueue.clear();
	}

	void show() {
		if (!Size) {
			cout << "Queue is empty.\n";
		}
		cout << "Our queue:\n";
		elem *cursor = back;
		while (cursor) {
			cout << cursor->data << " ";
			cursor = cursor->next;
		}
		cout << endl;
	}

private:
	elem *back, *front;
	int Size;
};

int main() {
	srand(time(NULL));
	Queue x;
	int first, second;
	cout << "How many times you want to push back? Input: "; cin >> first;
	for (int i = 0; i < first; i++) {
		x.push_back(rand() % 20 + 1);
	}
	x.show();
	cout << "How many times you want to push front? Input: "; cin >> second;
	for (int i = 0; i < second; i++) {
		x.push_front(rand() % 20 + 1);
	}
	x.show();
	int number_1, number_2;
	int temp;
	x.Delete_3rdElem();
	cout << "We used function which deleted every 3rd element.\n";
	x.show();
	cout << "How many times you want to pop back? Input: "; cin >> number_1;
	for (int i = 0; i < number_1; i++) {
		x.pop_back(temp);
		cout << "We deleted: " << temp << endl;
	}
	x.show();
	cout << "How many times you want to push front? Input: "; cin >> number_2;
	for (int i = 0; i < number_2; i++) {
		x.pop_front(temp);
		cout << "We deleted: " << temp << endl;
	}
	x.show();
	cout << "Size of queue: " << x.size() << endl;
	x.clear();
	if (x.isEmpty()) {
		cout << "Queue really empty.\n";
	}
	else {
		"Function 'clear' not working:(\n";
	}
	return 0;
}
