#include <iostream>
#include <ctime>

using namespace std;

struct elem {
	char data;			//Даные элемента.
	elem *next;			//Ссылка на предыдущий элемент.
};

struct MyStack {
	elem *head;			//Ссылка на начало стека(верхний элемент).
	int size;			//Размер стека.
	MyStack() {
		head = NULL;
		size = 0;
	}
};

void push(MyStack &other, char value) {
	elem *temp = new elem;
	temp->data = value;
	temp->next = other.head;					//Добавление элемента в стэк.
	other.head = temp;
	other.size++;
}

void pop(MyStack &other, char &value) {
	if (!other.head) {
		cout << "Stack is empty!\n";
		return;
	}
	elem *del = other.head;
	value = other.head->data;					//Удаление елемента из стэка.
	other.head = other.head->next;
	delete del;
	other.size--;
	return;
}

bool isEmpty(MyStack &other) {
	return (other.size == 0);					//Проверка на пустоту стека.
}

char top(MyStack &other) {
	if (other.size == 0) {
		cout << "Stack is empty!\n";
	}											//Возврат крайнего єлемента стека.
	else {
		return other.head->data;
	}
}

void clear(MyStack &other) {
	char temp;
	for (int i = 0; other.size != 0; i++) {
		pop(other, temp);							//Очищение стека.
		cout << "Deleted: " << temp << endl;
	}
	cout << "Your stack is clear!\n";
}

void PushMiddle(MyStack &other,const char value) {
	if (other.size == 0) {
		cout << "Stack is empty!\n";
		return;
	}
	char check;
	MyStack newStack;
	int newSize = other.size;
	for (int i = 0; i < newSize/2; i++) {					//Добавление элемента в середину, если кол-во
		pop(other, check);						//элементов парное и выше середины, если непарное.
		push(newStack, check);
	}
	push(other, value);
	for (int i = 0; i < newSize/2; i++) {
		pop(newStack, check);
		push(other, check);
	}
}

void Show(MyStack &other) {
	if (other.size == 0) {
		cout << "Stack is empty!\n";
	}
	else {
		char value;
		int newSize = other.size;
		MyStack newStack;
		for (int i = 0; i < newSize; i++) {
			pop(other, value);						//Вывод нашего стека на экран без его удаления.
			push(newStack, value);
		}
		for (int i = 0; i < newSize; i++) {
			pop(newStack, value);
			cout << value << " ";
			push(other, value);
		}
		cout << endl;
	}
}

int size(const MyStack &other) {
	return other.size;							//Возврат размера стека.
}

int main() {
	srand(time(NULL));
	MyStack x;
	char ch;
	int elems;
	cout << "Input how much elements u need: "; cin >> elems;
	for (int i = 0; i < elems; i++) {
		ch = rand() % 21 + 65;
		push(x, ch);
	}

	Show(x);

	char MyCh;
	cout << "Input which element you wanna add: "; cin >> MyCh;
	PushMiddle(x, MyCh);
	Show(x);

	cout << "Now we will delete the head of stack.\n";
	char temp;
	pop(x, temp);
	cout << "We deleted: " << temp << endl;
	Show(x);

	cout << "The head of stack: " << top(x) << endl;

	cout << "Size of stack: " << size(x) << endl;

	cout << "Now we will clear all stack.\n";
	clear(x);

	if (isEmpty(x)) {
		cout << "Really clear!\n";
	}
	else {
		cout << "He is not clear.\n";
	}

	return 0;

}
