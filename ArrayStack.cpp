#include <iostream>

using namespace std;

class MyStack {
private:
	char *stack;
	int Size;
	int last;
public:
	MyStack(int valueSize) {
		Size = valueSize;
		this->stack = new char[Size];
		last = 0;
	}

	void push(char value) {
		if (last == Size) {
			cout << "Your stack is full!!!\n";
			exit(1);
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
			char value;
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
		}
		else {
			return stack[last - 1];
		}
	}

	void clear() {
		if (last == 0) {
			cout << "Well done. Stack is empty!\n";
		}
		else {
			for (; last!=0; last--) {
				stack[last - 1] = NULL;
			}
		}
	}

	int size() {
		return last;
	}

	bool isEmpty() {
		if (last == 0) {
			return true;
		}
		else {
			return false;
		}
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
				newStack[i + 1] = stack[last - i - 1];
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
		delete[] stack;
	}

	void Print() {
		if (last == 0) {
			cout << "Stack is empty!\n";
		}
		else {
			for (int i = 0; i < last; i++) {
				cout << stack[i] << "  ";
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

	Stack.Print();

	Stack.PushMiddle('&');

	Stack.Print();

	Stack.pop();

	Stack.Print();

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
