#include "pch.h"
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
	}
	bool pop() {
		if (last < 1) {
			cout << "Stack is empty!!!\n";
			return false;
		}
		else {
			int value;
			value = stack[last];
			stack[last] = NULL;
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
			return stack[last];
		}
	}

	void clear() {
		if (last == 0) {
			cout << "Well done. Stack is empty!\n";
		}
		else {
			stack[last] = NULL;
			last--;
		}
	}

	int size() {
		return last;
	}

	bool isEmpty() {
		bool result = (last == 0);
		return result;
	}

	~MyStack() {
		delete[] stack;
  }
};
