#include <iostream>
#include <ctime>

using namespace std;

class oneSideQueue {
private:
	int *data;
	int Size, elements;
	int back, front;
public:
	oneSideQueue(int size) {
		data = new int[size];
		Size = size;
		elements = 0;
		for (int i = 0; i < size; i++)
		{
			data[i] = NULL;
		}
		back = front = size - 1;
	}
	~oneSideQueue() {
		delete[] data;
	}

	void push(int value) {
		if (elements >= Size) {
			cout << "Queue is full!" << endl;
			exit(1);
		}
		data[back] = value;
		back = (back + Size - 1) % Size;
		elements++;
	}

	void pop(int &out) {
		if (elements <= 0) {
			cout << "Queue is empty!" << endl;
			exit(1);
		}
		out = data[front];
		data[front] = NULL;
		front = (front + Size - 1) % Size;
		elements--;
	}

	void show() {
		int index = back;
		for (; index <= front; index++) {
			cout << data[index] << " ";
		}
		cout << endl;
	}

	void clear() {
		int index = back;
		for (; index <= front; index++) {
			data[index] = NULL;
			elements--;
		}
	}

	int size() {
		return elements;
	}

	bool isEmpty() {
		return (elements == 0);
	}
};

int main() {
	srand(time(NULL));
	int size;
	cout << "Input size of queue: "; cin >> size;
	oneSideQueue queue(size);
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
	}
	queue.show();
	cout << "Size of array: " << queue.size() << endl;
	queue.clear();
	if (!queue.isEmpty()) {
		cout << "Queue is clear!" << endl;
	}
	else {
		cout << "Queue isn't clear!" << endl;
	}

	return 0;
}
