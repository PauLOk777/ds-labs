#include <iostream>

using namespace std;

class MyStack {
private:
	char *stack;     //Указатель на наш стек.
	int Size;		//Размер стека.
	int last;		//Количество логических элементов стека.
public:
	MyStack(int valueSize) {
		Size = valueSize;
		this->stack = new char[Size];				//Конструктор нашего стека.
		last = 0;
		stack[last] = NULL;
	}

	void push(char value) {					
		if (last == Size) {
			cout << "Your stack is full!!!\n";
			exit(1);								//Добавляем в конец стека елемент.
		}
		stack[this->last] = value;
		this->last++;
		stack[this->last] = NULL;
	}

	void pop(char &temp) {
		if (last < 1) {
			cout << "Stack is empty!!!\n";
			return;
		}
		else {
			temp = stack[this->last - 1];					
			stack[this->last-1] = NULL;			//Удаляем последний елемент и выводим его на экран.
			this->last--;
			return;
		}

	}

	char top() {
		if (last == 0) {
			cout << "Stack is empty!\n";
		}							//Выводим на экран последний элемент без его удаления.
		else {
			return stack[last - 1];
		}
	}

	void clear() {
		if (last == 0) {
			cout << "Well done. Stack is empty!\n";
		}
		else {
			for (; last!=0; last--) {				//Полная очистка стека.
				stack[last - 1] = NULL;
			}
		}
	}

	int size() {
		return last;							//Возвращаем размер стека.
	}

	bool isEmpty() {
		if (last == 0) {
			return true;
		}									//Проверка на пустоту стека.
		else {
			return false;
		}
	}

	void PushMiddle(const char temp) {
		if (last == 0) {
			cout << "Stack is empty!\n";
		}
		else {
			char value;
			MyStack newStack(Size);				//Добавление элемента в середину, если кол-во элементов парное,
			int newLast = last;							//и выше середины если непарное.
			for (int i = 0; i < newLast / 2; i++) {
				this->pop(value);
				newStack.push(value);
			}
			this->push(temp);
			for (int i = 0; i < newLast / 2; i++) {
				newStack.pop(value);
				this->push(value);
			}
		}
	}

	~MyStack() {
		delete[] stack;				//Деструктор нашего стека.
	}

	void Show() {
		if (last == 0) {
			cout << "Stack is empty!\n";
		}
		else {
			char value;
			int newLast = last;
			MyStack newStack(Size);
			for (int i = 0; i < newLast; i++) {
				this->pop(value);				//Вывод нашего стека на экран без его удаления.
				newStack.push(value);
			}
			for (int i = 0; i < newLast; i++) {
				newStack.pop(value);
				cout << value << " ";
				this->push(value);
			}
			cout << endl;
		}
	}
};

int main() {
	int size;
	cout << "Input size of stack: " << endl;
	cin >> size;
	MyStack Stack(size);
	char ch;
	cout << "Input your char: "; cin >> ch;
	
	Stack.push(ch);
	Stack.push(ch);
	Stack.push(ch);
	Stack.push(ch);

	Stack.Show();

	char MyCh;
	cout << "Input which element you wanna to add: "; cin >> MyCh;

	Stack.PushMiddle(MyCh);

	Stack.Show();

	char value;
	Stack.pop(value);

	Stack.Show();

	cout << "Size of stack: " << Stack.size() << endl;
	
	cout << "Head of stack: " << Stack.top() << endl;

	Stack.clear();
	
	if (Stack.isEmpty()) {
		cout << "Stack is really empty.\n";
	}
	else {
		cout << "Stack isn't empty.\n";
	}

	return 0;
}
