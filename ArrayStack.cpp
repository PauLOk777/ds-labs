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
			exit(1);					//Добавляем в конец стека елемент.
		}
		stack[last] = value;
		last++;
		stack[last] = NULL;
	}

	bool pop() {
		if (last < 1) {
			cout << "Stack is empty!!!\n";
			return false;
		}
		else {
			char value;					//Удаляем последний елемент и выводим его на экран.
			value = stack[last - 1];					
			stack[last-1] = NULL;
			last--;
			cout << "You deleted (" << value << ")\n";
			return true;
		}

	}

	char top() {
		if (last == 0) {
			cout << "Stack is empty!\n";
		}						      //Выводим на экран последний элемент без его удаления.
		else {
			return stack[last - 1];
		}
	}

	void clear() {
		if (last == 0) {
			cout << "Well done. Stack is empty!\n";
		}
		else {
			for (; last!=0; last--) {			 //Полная очистка стека.
				stack[last - 1] = NULL;
			}
		}
	}

	int size() {
		return last;						//Возвращаем размер стека.
	}

	bool isEmpty() {
		bool result = (last == 0);
		return result;							//Проверка на пустоту стека.
	}

	void PushMiddle(const char temp) {
		if (last == 0) {
			cout << "Stack is empty!\n";
		}
		else {
			int i = 0;
			int *newStack = new int[Size];
			for (; i < last / 2; i++) {
				newStack[i] = stack[last - i - 1];
				stack[last - i - 1] = NULL;
			}
			newStack[i] = temp;
			for (; i < last; i++) {
				newStack[i + 1] = stack[last - i - 1];		//Добавления в середину стека элемента.
				stack[last - i - 1] = NULL;
			}
			last++;
			
			for (int j = 0; j < last; j++) {
				stack[j] = newStack[last - j - 1];
				newStack[last - j - 1] = NULL;
			}
			stack[last] = NULL;
			delete[] newStack;
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
			char *newStack = new char[Size];
			for (int i = 0; i < last; i++) {
				newStack[i] = stack[last - i - 1];
				stack[last - i - 1] = NULL;			//Вывод нашего стека на экран без его удаления.
			}
			newStack[last] = NULL;
			for (int i = 0; i < last; i++) {
				stack[i] = newStack[last - i - 1];
				cout << newStack[last - i - 1] << " ";
				newStack[last - i - 1] = NULL;
			}
			cout << endl;
			stack[last] = NULL;
			delete[] newStack;
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

	Stack.pop();

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
