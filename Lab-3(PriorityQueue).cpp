#include <iostream>
#include <ctime>

using namespace std;

class elem {
public:
	int data;
	int priority;
	elem *next;
};

class priorityQueue {
private:
	int elements;
	elem *back;
public:
	priorityQueue() {
		back = NULL;
		elements = 0;
	}
	void push(int value, int priority) {
		elem *temp = new elem;
		temp->data = value;
		temp->priority = priority;
		temp->next = NULL;
		if (!back) {
			back = temp;
			elements++;
			return;
		}
		elem *current = back;
		elem *prev = NULL;
		for (; current && current->priority > priority; prev = current, current = current->next);

		if (current == back) {
			temp->next = back;
			back = temp;
			elements++;
			return;
		}
		prev->next = temp;
		if (!current) {
			elements++;
			return;
		}

		temp->next = current;
		elements++;
	}

	void pop(int &out, int &outPriority) {
		if (!back) {
			cout << "Queue is empty!" << endl;
			return;
		}
		if (!back->next) {
			out = back->data;
			outPriority = back->priority;
			delete back;
			back = NULL;
			elements--;
		}
		else {
			elem *temp;
			temp = back;
			out = back->data;
			outPriority = back->priority;
			back = back->next;
			delete temp;
			elements--;
		}
	}

	void clear() {
		elem *temp;
		while (back) {
			temp = back;
			back = back->next;
			delete temp;
			elements--;
		}
	}

	bool isEmpty() { return (elements == 0); }

	int size() {
		return elements;
	}

	void changePriorities() {
		int highPriority = back->priority;
		elem *end, *prev;
		end = prev = back;
		while (end) {
			prev = end;
			end = end->next;
		}
		int lowPriority = prev->priority;
		end = prev = back;
		int countHighPriorities = 0;
		int countLowPriorities = 0;
		while (end) {
			prev = end;
			if (prev->priority == highPriority) {
				countHighPriorities++;
			}
			if (prev->priority == lowPriority) {
				countLowPriorities++;
			}
			end = end->next;
		}
		int *ArrayHighPriority = new int[countHighPriorities];
		int *ArrayLowPriority = new int[countLowPriorities];
		end = prev = back;
		int end_2 = countHighPriorities;
		int head = countLowPriorities;
		while (end) {
			prev = end;
			if (prev->priority == highPriority) {
				ArrayHighPriority[countHighPriorities - 1] = end->data;
				countHighPriorities--;
			}
			if (prev->priority == lowPriority) {
				ArrayLowPriority[countLowPriorities - 1] = end->data;
				countLowPriorities--;
			}
			end = end->next;
		}
		end = prev = back;
		int out;
		int outPriority;
		for (int i = 0; i < end_2; i++) {
			pop(out, outPriority);
		}
		int count = 0;
		priorityQueue newQueue;
		int newElements = elements;
		for (int i = 0; i < newElements - head; i++) {
			pop(out, outPriority);
			newQueue.push(out, outPriority);
			count++;
		}
		for (int i = 0; i < head; i++) {
			pop(out, outPriority);
		}
		for(int i = 0; i < end_2; i++){
			push(ArrayHighPriority[i], lowPriority);
		}
		for (int i = 0; i < head; i++) {
			push(ArrayLowPriority[i], highPriority);
		}
		for (int i = 0; i < count; i++) {
			newQueue.pop(out, outPriority);
			push(out, outPriority);
		}
		delete[] ArrayHighPriority;
		delete[] ArrayLowPriority;
	}

	void show() {
		elem *temp, *newBack;
		newBack = back;
		int value;
		int priority;
		while (newBack) {
			temp = newBack;
			cout << temp->data << "-" << temp->priority << " ";
			newBack = newBack->next;
		}
		cout << endl;
	}
};

int main() {
	srand(time(NULL));
	priorityQueue queue;
	int temp;
	cout << "How many times you wanna push: "; cin >> temp;
	for (int i = 0; i < temp; i++) {
		int newRand = rand() % 20 + 1;
		int newRand_2 = rand() % 10;
		queue.push(newRand, newRand_2);
	}
	queue.show();
	cout << "How many times you wanna pop: "; cin >> temp;
	int out;
	int outPriority;
	for (int i = 0; i < temp; i++) {
		queue.pop(out, outPriority);
		cout << "We deleted: " << out << "-" << outPriority << endl;
	}
	queue.show();
	cout << "Now we will change the highest priority with the lowest.\n";
	queue.changePriorities();
	queue.show();
	cout << "Size of array: " << queue.size() << endl;
	queue.clear();
	if (queue.isEmpty()) {
		cout << "Queue is clear!" << endl;
	}
	else {
		cout << "Queue isn't clear!" << endl;
	}
	
	return 0;
}
