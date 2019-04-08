#include <iostream>
#include <ctime>

using namespace std;

struct rb_node
{
	int red;
	int data;
	rb_node *link[2]; //link[ 0 ] - лівий нащадок, link[ 1 ] - правий
};

struct rb_tree
{
	rb_node *root;
	rb_tree(void) : root(NULL) {}
};

int is_red(rb_node *node)
{
	return node != NULL && node->red == 1;
}

rb_node *rb_single(rb_node *root, int dir) //якщо dir == 1, то повертаємо направо, інакше - вліво
{
	rb_node *save = root->link[!dir];

	root->link[!dir] = save->link[dir];
	save->link[dir] = root;

	root->red = 1;
	save->red = 0;

	return save;
}

rb_node *rb_double(rb_node *root, int dir)
{
	root->link[!dir] = rb_single(root->link[!dir], !dir);
	return rb_single(root, dir);
}

rb_node *make_node(int data)
{
	rb_node *rn = new rb_node;

	if (rn) {
		rn->data = data;
		rn->red = 1; //ініціалізація червоним кольором
		rn->link[0] = NULL;
		rn->link[1] = NULL;
	}
	return rn;
}

bool rb_insert(rb_tree *tree, int data)
{
	//якщо маємо пусте дерево
	if (!tree->root)
	{
		tree->root = make_node(data);
		if (!tree->root)
			return false;
	}
	else //якщо в дереві вже є хоча б один елемент
	{
		rb_node head = { 0 }; //тимчасовий корінь дерева
		rb_node *g, *t;     //дід та батьківська вершина
		rb_node *p, *q;     //батьківська вершина та ітератор
		int dir = 0, last;

		//просто допоміжні змінні
		t = &head;
		g = p = NULL;
		q = t->link[1] = tree->root;

		//основний цикл проходу по дереву
		while (true)
		{
			if (!q)
			{
				//вставка вершини
				p->link[dir] = q = make_node(data);
				if (!q) return false;
			}
			else if (is_red(q->link[0]) && is_red(q->link[1]))
			{
				//заміна кольору. Перший випадок.
				q->red = 1;
				q->link[0]->red = 0;
				q->link[1]->red = 0;
			}

			//маємо 2 червоні кольори
			if (is_red(q) && is_red(p))
			{
				int dir2 = t->link[1] == g;

				if (q == p->link[last])
					t->link[dir2] = rb_single(g, !last); //одинарний поворот. Другий випадок
				else
					t->link[dir2] = rb_double(g, !last); //подвійний поворот. Третій випадок
			}

			//якщо зазначена вершина вже існує - вихід з функції
			if (q->data == data) break;

			last = dir;
			dir = q->data < data;

			if (g)
				t = g;
			g = p, p = q;
			q = q->link[dir];
		}

		// обновити покажчик на корінь дерева
		tree->root = head.link[1];
	}
	//корінь дерева завжди має бути чорний
	tree->root->red = 0;

	return true;
}


bool br_remove(rb_tree *tree, int data)
{
	if (tree->root)
	{
		rb_node head = { 0 }; //тимчасовий покажчик на корінь дерева
		rb_node *q, *p, *g; //допоміжні змінні
		rb_node *f = NULL;  //вершина, яку видаляємо
		int dir = 1;

		//просто допоміжні змінні
		q = &head;
		g = p = NULL;
		q->link[1] = tree->root;

		//пошук та видадення
		while (q->link[dir])
		{
			int last = dir;

			//зберігання ієрархії вершин в допоміжні змінні
			g = p, p = q;
			q = q->link[dir];
			dir = q->data < data;

			//зберігання знайденої вершини
			if (q->data == data)
				f = q;

			if (!is_red(q) && !is_red(q->link[dir]))
				if (is_red(q->link[!dir]))
					p = p->link[last] = rb_single(q, dir); //одинарний поворот першого типу
				else if (!is_red(q->link[!dir]))
				{
					rb_node *s = p->link[!last];

					if (s)
						if (!is_red(s->link[!last]) && !is_red(s->link[last]))
						{
							//перший випадок - перемальовуємо кольори вершин
							p->red = 0;
							s->red = 1;
							q->red = 1;
						}
						else
						{
							int dir2 = (g->link[1] == p);

							if (is_red(s->link[last]))
								g->link[dir2] = rb_double(p, last); //третій випадок - подвійний поворот
							else if (is_red(s->link[!last]))
								g->link[dir2] = rb_single(p, last); //четвертий випадок - одинарний поворот другого типу

							//корекція корльору вершин
							q->red = g->link[dir2]->red = 1;
							g->link[dir2]->link[0]->red = 0;
							g->link[dir2]->link[1]->red = 0;
						}
				}
		}

		//видалення вершини
		if (f)
		{
			f->data = q->data;
			p->link[p->link[1] == q] = q->link[q->link[0] == NULL];
			delete q;
		}

		//корінь дерева завжди є чорним
		tree->root = head.link[1];
		if (tree->root)
			tree->root->red = 0;
	}

	return true;
}

void infix_(rb_node *top)
{
	if (!top) return;
	infix_(top->link[0]);
	cout << top->data << " ";
	infix_(top->link[1]);
}

void prefix_(rb_node *top) {
	if (!top) return;
	cout << top->data << " ";
	prefix_(top->link[0]);
	prefix_(top->link[1]);
}

void postfix_(rb_node *top) {
	if (!top) return;
	postfix_(top->link[0]);
	postfix_(top->link[1]);
	cout << top->data << " ";
}

void printTree(rb_tree *top) {

}

int main()
{
	rb_tree *my_tree = new rb_tree;
	rb_insert(my_tree, 5);
	rb_insert(my_tree, 7);
	rb_insert(my_tree, 9);
	rb_insert(my_tree, 10);
	rb_insert(my_tree, 12);
	rb_insert(my_tree, 14);
	rb_insert(my_tree, 15);
	rb_insert(my_tree, 17);

	cout << "Root: " << endl;
	cout << my_tree->root->data << endl;
	infix_(my_tree->root);
	cout << endl;
	br_remove(my_tree, 12);
	cout << "Root: " << endl;
	cout << my_tree->root->data << endl;
	infix_(my_tree->root);
	cout << endl;
	prefix_(my_tree->root);
	
	cout << endl;
	system("pause");
	return 0;
}
