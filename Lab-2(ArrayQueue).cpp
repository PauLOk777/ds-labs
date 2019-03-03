#include <iostream>
#include <ctime>

using namespace std;

class Queue {
private:
	int *data;
	int Size, elements;
	int back, front;
public:
	Queue(int size) {
		this->Size = size;
		elements = 0;
		data = new int[size];
		for (int i = 0; i < size; i++) {
			data[i] = NULL;
		}
		back = front = size - 1;
	}

	~Queue() {
		delete[] data;
	}

	void push_front(int value) {
		if (elements >= Size) {
			cout << "Queue is full!\n";
			return;
		}
		data[back] = value;
		back = (back + Size - 1) % Size;
		elements++;
	}

	void push_back(int value) {
		if (elements >= Size) {
			cout << "Queue is full!\n";
			return;
		}
		front = (front + 1) % Size;
		data[front] = value;
		elements++;
	}

	bool pop_front(int &out) {
		if (!elements) {
			cout << "Queue is empty!\n";
			exit(1);
		}
		if (data[back] == NULL) {
			back = (back + 1) % Size;
			return false;
		}
		else {
			out = data[back];
			data[back] = NULL;
			back = (back + 1) % Size;
			elements--;
			return true;
		}
	}

	bool pop_back(int &out) {
		if (!elements) {
			cout << "Queue is empty!\n";
			exit(1);
		}
		if (data[front] == NULL) {
			front = (front + Size - 1) % Size;
			return false;
		}
		else {
			out = data[front];
			data[front] = NULL;
			front = (front + Size - 1) % Size;
			elements--;
			return true;
		}
	}

	int size() {
		return elements;
	}

	bool isEmpty() {
		return (elements == 0);
	}

	void clear() {
		for (int i = 0; i < Size; i++) {
			data[i] = NULL;
			elements = 0;
		}
		cout << "Queue is clear.\n";
	}

	void Delete_3rdElem() {
		int temp_back;
		temp_back = back;
		back = 2;
		for (int i = 1; i <= Size; i++) {
			if (data[i] == NULL) {
				continue;
			}
			if (i % 3 == 0) {
				int newTemp;
				pop_front(newTemp);
				cout << "We deleted: " << newTemp << endl;
				back += 2;
			}
		}
		back = temp_back;
	}

	void show() {
		cout << "Our queue: \n";
		for (int i = 0; i < Size; i++) {
			cout << data[i] << "\t";
		}
		cout << endl;
	}
};

int main() {
	srand(time(NULL));
	setlocale(LC_ALL, "rus");
	cout << "На основi масиву!!!\n";
	int size;
	cout << "Input your size: "; cin >> size;
	Queue x(size);
	x.show();
	int temp;
	cout << "Input how much times u wanna push back: "; cin >> temp;
	for (int i = 0; i < temp; i++) {
		x.push_back(rand() % 20 + 1);
	}
	x.show();
	cout << "Input how much times u wanna push front: "; cin >> temp;
	for (int i = 0; i < temp; i++) {
		x.push_front(rand() % 20 + 1);
	}
	x.show();
	int temp_2;
	x.Delete_3rdElem();
	cout << "We used function which deleted every 3rd element.\n";
	x.show();
	cout << "Input how much times u wanna pop back: "; cin >> temp;
	for (int i = 0; i < temp; i++) {
		if (!x.pop_back(temp_2)) {
			i--;
		}
		else {
			cout << "We deleted: " << temp_2 << endl;
		}
	}
	x.show();
	cout << "Input how much times u wanna pop front: "; cin >> temp;
	for (int i = 0; i < temp; i++) {
		if (!x.pop_front(temp_2)) {
			i--;
		}
		else {
			cout << "We deleted: " << temp_2 << endl;
		}
	}
	x.show();
	cout << "Size of queue: " << x.size() << endl;
	x.clear();
	x.show();
	if (x.isEmpty()) {
		cout << "Queue really empty.\n";
	}
	else {
		"Function 'clear' not working:(\n";
	}
	return 0;
}
