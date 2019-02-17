#include <iostream>

using namespace std;

struct elem {
	char data;
	elem *next;
};

struct MyStack {
	elem *head;
	int size;
	MyStack() {
		head = NULL;
		size = 0;
	}
};

void push(MyStack &other, char value) {
	elem *temp = new elem;
	temp->data = value;
	temp->next = other.head;
	other.head = temp;
	other.size++;
}

bool pop(MyStack &other, char &value) {
	if (!other.head) {
		cout << "Stack is empty!\n";
		return false;
	}

	elem *del = other.head;
	value = other.head->data;
	other.head = other.head->next;
	delete del;
	other.size--;
	return true;
}

bool isEmpty(MyStack &other) {
	return (other.size == 0);
}

char top(MyStack &other) {
	elem *temp = other.head;
	return temp->data;
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

void PushMiddle(MyStack &other, char value) {
	if (other.size == 0) {
		cout << "Stack is empty!\n";
		return;
	}
	MyStack newStack;
	for (int i = 0; i < other.size/2; i++) {
		
	}
}

void Show(MyStack &other) {
	elem *temp = other.head;
	while (temp != NULL) {
		cout << temp->data << " ";
		temp = temp->next;
	}
	cout << endl;
}

int size(const MyStack &other) {
	return other.size;
}

int main() {
	MyStack x;
	push(x, '5');
	push(x, '7');
	push(x, '3');
	Show(x);

	char value = '0';
	if (pop(x, value))
		cout << value << endl;
	Show(x);
	if (pop(x, value))
		cout << value << endl;
	cout << top(x) << endl;
	clear(x);
	if (pop(x, value))
		cout << value << endl;

	return 0;
}
