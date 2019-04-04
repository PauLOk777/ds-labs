#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include "queue_priority.h"

using namespace std;

struct element
{
	char value;
	element *Left, *Right;
	void print() {
		cout << value << endl;
	}


};

class half_tree
{
	element *Head;
	map<char, int> f;
	int tabs;
public:
	half_tree();
	void build_half_tree(queue_priority<element*> &);
	void print(element *);
	element *add(element *, element *, int, int);
	element *GetHead() { return Head; }
	void show_codes(element *, string, string &);
	void mass(element *, string, int &, int &, int &, int &);
};

half_tree::half_tree()
{
	tabs = 0;
	Head = nullptr;
}

element *half_tree::add(element *fElem, element *sElem, int fPriority, int sPriority)
{
	element *t = new element;
	t->value = '*';
	if (sPriority >= fPriority)
	{
		t->Left = fElem;
		t->Right = sElem;
	}
	else
	{
		t->Left = sElem;
		t->Right = fElem;
	}
	return t;
}

void half_tree::build_half_tree(queue_priority<element*> &frequency)
{
	std::map<char, int>::iterator it = f.end();

	element *fElem, *sElem;
	int fPriority, sPriority;
	while (frequency.size() != 1)
	{
		frequency.pop_priority(fPriority);
		frequency.pop(fElem);
		frequency.pop_priority(sPriority);
		frequency.pop(sElem);

		f.insert(f.begin(), pair<char, int>(fElem->value, fPriority));
		f.insert(f.begin(), pair<char, int>(sElem->value, sPriority));

		frequency.push(add(fElem, sElem, fPriority, sPriority), fPriority + sPriority);
	}
	frequency.pop(Head);
}
void half_tree::show_codes(element *next, string code, string &out)
{
	bool flag = false;
	if (next->Left != nullptr)
	{
		show_codes(next->Left, code + "0", out);
		flag = true;
	}
	if (next->Right != nullptr)
	{
		show_codes(next->Right, code + "1", out);
		flag = true;
	}
	if (!flag)
	{
		cout << code << " " << next->value << endl;
		out += code + " " + next->value + "\n";
	}
}
void half_tree::print(element *next)
{
	if (next == nullptr)
		return;
	tabs++;
	print(next->Left);
	for (int i = 0; i < tabs; i++)
		cout << "  ";
	cout << next->value << endl;
	print(next->Right);
	tabs--;
	return;
}
void count_frequency(queue_priority<element*> &frequency, string &Input)
{
	element *next;
	char buff;
	int count;
	while (Input.size() != 0)
	{
		count = 0;
		buff = Input[0];
		for (int i = 0; i < Input.size(); i++)
		{
			if (Input[i] == buff)
			{
				count++;
				Input.erase(Input.begin() + i);
				i--;
			}
		}
		next = new element;
		next->value = buff;
		next->Left = nullptr;
		next->Right = nullptr;
		frequency.push(next, count);
		next = nullptr;
	}
}
char decoder(element *next, string code)
{
	if (code.size() == 0)
	{
		return next->value;
	}
	if (code[0] == '1' && next->Right != nullptr)
	{
		return decoder(next->Right, code.substr(1));
	}
	if (code[0] == '0' && next->Left != nullptr)
	{
		return decoder(next->Left, code.substr(1));
	}
	return '*';
}

void half_tree::mass(element *next, string code, int &weight, int &averageLength, int &count, int &maxLength)
{
	bool flag = false;
	if (next->Left != nullptr)
	{
		mass(next->Left, code + "0", weight, averageLength, count, maxLength);
		flag = true;
	}
	if (next->Right != nullptr)
	{
		mass(next->Right, code + "1", weight, averageLength, count, maxLength);
		flag = true;
	}
	if (!flag)
	{
		cout << code << " " << code.length() << " " << next->value << " " << f.find(next->value)->second << endl;
		weight += code.size() * f.find(next->value)->second;
		averageLength += code.length();
		if (code.length() > maxLength) {
			maxLength = code.length();
		}
		count++;
	}
}

int main()
{
	int m = 0;
	half_tree example;
	queue_priority<element *> frequency;
	string Input = "", buff, temp;
	ofstream fout("output.txt");

	if (!fout.is_open()) {
		cout << "Error.\n";
		cin.get();
		exit(1);
	}

	int count = 0;
	int num;
	cout << "To read from file press 1, to get your lines press 2.\n"; cin >> num;
	if (num == 1) {
		ifstream fin("input.txt");
		if (!fin.is_open()) {
			cout << "Error.\n";
			cin.get();
			exit(1);
		}
		while (!fin.eof()) {
			buff = "";
			getline(fin, buff);
			count += buff.length();
			Input.append(buff);
		}
	}
	else {
		while (true)
		{
			buff = "";
			getline(cin, buff);
			if (buff == "quit") {
				break;
			}
			count += buff.length();
			Input.append(buff);
		}
	}
	int count_1 = 0;
	int averageLength = 0;
	int maxLength = 0;
	count_frequency(frequency, Input);
	example.build_half_tree(frequency);
	example.mass(example.GetHead(), "", m, averageLength, count_1, maxLength);

	fout << temp;

	fout.close();

	cout << "Mass of tree: " << m << endl;
	cout << "Enter decoding: " << endl;
	while (true) {
		cin >> buff;
		if (buff == "quit") {
			break;
		}
		cout << decoder(example.GetHead(), buff) << endl;
	}
	
	cout << "You have " << count << " symbols." << endl;
	cout << "Average length: " << averageLength / count_1 << endl;
	cout << "Max length: " << maxLength << endl;

	system("pause");
	return 0;
}
