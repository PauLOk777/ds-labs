#include <iostream>

using namespace std;

struct elem {
	char data;
	elem *next;
};

struct MyStack {
	elem *head;
	MyStack() {
		head = NULL;
	}
};

void push(MyStack &other, char value) {
	elem *temp = new elem;
	temp->data = value;
	temp->next = other.head;
	other.head = temp;
}

bool pop(MyStack &other, char &value) {
	if (!other.head) {
		cout << "Stack is empty!\n";
		return false;
	}
	if (!other.head->next) {
		value = other.head->data;
		delete other.head;
		other.head = NULL;
		return true;
	}

	elem *del = other.head;
	value = other.head->data;
	other.head = other.head->next;
	delete del;
	return true;
}

void clear(MyStack &other) {
	elem *del;
	while (other.head) {
		del = other.head;
		other.head = other.head->next;
		delete other.head;
	}
	cout << "Your stack is clear!\n";
}

int main() {
	MyStack x;
	push(x, '5');
	push(x, '7');
	push(x, '3');
	
	char value = '0';
	if (pop(x, value))
		cout << value << endl;
	if (pop(x, value))
		cout << value << endl;
	clear(x);
	if (pop(x, value))
		cout << value << endl;

	return 0;
}
