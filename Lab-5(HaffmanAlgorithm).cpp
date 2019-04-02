#include <iostream>
#include <string>
#include <fstream>
#include "queue_priority.h"

using namespace std;

struct element
{
	char value;
	element *Left, *Right;
};

class half_tree
{
	element *Head;
	int tabs;
public:
	half_tree();
	void build_half_tree(queue_priority<element*> &);
	void print(element *);
	element *add(element *, element *, int, int);
	element *GetHead() { return Head; }
	void show_codes(element *, string);
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
	element *fElem, *sElem;
	int fPriority, sPriority;

	while (frequency.size() != 1)
	{
		frequency.pop_priority(fPriority);
		frequency.pop(fElem);
		frequency.pop_priority(sPriority);
		frequency.pop(sElem);

		frequency.push(add(fElem, sElem, fPriority, sPriority), fPriority + sPriority);
	}
	frequency.pop(Head);
}
void half_tree::show_codes(element *next, string code)
{
	bool flag = false;
	if (next->Left != nullptr)
	{
		show_codes(next->Left, code + "0");
		flag = true;
	}
	if (next->Right != nullptr)
	{
		show_codes(next->Right, code + "1");
		flag = true;
	}
	if (!flag)
		cout << code << endl;
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
int main()
{
	half_tree example;
	queue_priority<element *> frequency;
	string Input = "", buff;

	ofstream fout("text.txt");

	if (!fout.is_open()) {
		cout << "Error.\n";
		cin.get();
		exit(1);
	}

	int count = 0;
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
	buff = "";
	count_frequency(frequency, Input);
	example.build_half_tree(frequency);
	example.print(example.GetHead());
	example.show_codes(example.GetHead(), "");

	cout << "ender code for decoding: ";
	while (true)
	{
		cin >> buff;
		if (buff == "quit") {
			break;
		}
		cout << decoder(example.GetHead(), buff) << endl;
	}
	return 0;
}
