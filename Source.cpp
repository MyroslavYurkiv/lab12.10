#include <iostream>
#include <iomanip>
#include <Windows.h>

using namespace std;

typedef int INF;
struct Derevo
{
	Derevo* left,
		* right;
	INF kluch_d;
};

Derevo* BinarySearchInsert(Derevo*& root, INF value, bool& found);
void PrintTree(Derevo* root, int level);

Derevo* dobavut(Derevo*& root, INF value, bool& found);

void RightRotation(Derevo*& root);
void LeftRotation(Derevo*& root);
int Height(Derevo* root);
int BFactor(Derevo* root);
void BalanceHeight(Derevo*& root);

Derevo* BinarySearchDelete(Derevo* root, INF value, int level);
Derevo* FindMax(Derevo* root, int& level);

bool Find_vyzol(Derevo* root, INF value, bool& b);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int kilkist{}, N{}, level{};
	Derevo* node{};

	INF value;
	bool found = false, b;

	int menutowar;
	do {
		cout << "Виберіть дію:" << endl << endl;

		cout << " [1] - створення дерева" << endl;
		cout << " [2] - вивід вузлів даного дерева" << endl;
		cout << " [3] - добавлення вузла до даного дерево" << endl;
		cout << " [4] - балансування дерева" << endl;
		cout << " [5] - вилучення вузла з даного дерево" << endl;
		cout << " [6] - пошук вузлів дерева" << endl;
		cout << " [7] - пошук максимального значення вузла" << endl << endl;

		cout << " [0] - вихід та завершення роботи програми" << endl << endl;

		cout << "Введіть пункт меню: "; cin >> menutowar;
		cout << endl;
		switch (menutowar)
		{
		case 1:
			cout << "Введіть кількість вузлів: "; cin >> kilkist;
			cout << endl;
			for (int i = 0; i < kilkist; i++)
			{
				cout << "Введіть значення №" << i + 1 << ": "; cin >> value;
				BinarySearchInsert(node, value, found);
			}
			break;
		case 2:
			PrintTree(node, 0);
			break;
		case 3:
			cout << "Введіть кількість вузлів щоб добавити до даного дерева: "; cin >> N;
			for (int i = 0; i < N; i++)
			{
				cout << "Введіть значення №" << i + 1 << ": "; cin >> value;
				dobavut(node, value, found);
			}
			break;
		case 4:
			BalanceHeight(node);
			break;
		case 5:
			cout << "Введіть значення певного вузла для вилучення: "; cin >> value;
			node = BinarySearchDelete(node, value, level);
			break;
		case 6:
			cout << "Введіть значення вузла для пошуку його: "; cin >> value;
			b = false;
			Find_vyzol(node, value, b);

			if (b)
				cout << "Введене значення знайшлося: ";
			else
				cout << "Введене значення не знайшлося: ";
			break;
		case 7:
			level = 0;
			cout << "Максимальне значення даного дерева становить = " << FindMax(node, level)->kluch_d << endl;
			cout << "Рівень Максимальне значення становить: " << level << endl;
			cout << endl;
			break;
		case 0:
			cout << endl;
			cout << "завершення роботи програми" << endl;
			break;
		default:
			cout << endl;
			cout << "Ви ввели помилкове значення! "
				"Слід ввести число - номер вибраного пункту меню" << endl;
		}
		cout << endl;
	} while (menutowar != 0);
}

Derevo* BinarySearchInsert(Derevo*& root, INF value, bool& found)
{
	if (root == NULL)
	{
		root = new Derevo;
		root->kluch_d = value;
		root->left = NULL;
		root->right = NULL;
		found = false;
		return root;
	}
	else
		if (value == root->kluch_d)
		{
			found = true;
			return root;
		}
		else
			if (value < root->kluch_d)
				return BinarySearchInsert(root->left, value, found);
			else
				return BinarySearchInsert(root->right, value, found);
}

void PrintTree(Derevo* root, int level)
{
	if (root != NULL)
	{
		PrintTree(root->right, level + 1);
		for (int i = 1; i <= level; i++)
			cout << " ";
		cout << root->kluch_d << endl;
		PrintTree(root->left, level + 1);
	}
}

Derevo* dobavut(Derevo*& root, INF value, bool& found)
{
	if (root == NULL)
	{
		root = new Derevo;
		root->kluch_d = value;
		root->left = NULL;
		root->right = NULL;
		found = false;
		return root;
	}
	else
		if (value == root->kluch_d)
		{
			found = true;
			return root;
		}
		else
			if (value < root->kluch_d)
				return BinarySearchInsert(root->left, value, found);
			else
				return BinarySearchInsert(root->right, value, found);
}

void RightRotation(Derevo*& root)
{
	Derevo* tmp1 = root->left;
	Derevo* tmp2 = tmp1->right;
	tmp1->right = root;
	root->left = tmp2;
	root = tmp1;
}

void LeftRotation(Derevo*& root)
{
	Derevo* tmp1 = root->right;
	Derevo* tmp2 = tmp1->left;
	tmp1->left = root;
	root->right = tmp2;
	root = tmp1;
}
int Height(Derevo* root)
{
	if (root == NULL)
		return 0;
	int hL = Height(root->left);
	int hR = Height(root->right);
	return (hL > hR ? hL : hR) + 1;
}
int BFactor(Derevo* root)
{
	return Height(root->right) - Height(root->left);
}
void BalanceHeight(Derevo*& root)
{
	if (root != NULL)
	{
		while (BFactor(root) >= 2)
		{
			if (BFactor(root->right) < 0)
				RightRotation(root->right);
			LeftRotation(root);
		}
		while (BFactor(root) <= -2)
		{
			if (BFactor(root->left) > 0)
				LeftRotation(root->left);
			RightRotation(root);
		}
		BalanceHeight(root->left);
		BalanceHeight(root->right);
	}
}

Derevo* BinarySearchDelete(Derevo* root, INF value, int level)
{
	if (NULL == root) return NULL; 
	if (root->kluch_d == value) 
	{
		if (NULL == root->left && NULL == root->right) 
		{
			delete root;
			return NULL;
		}
		if (NULL == root->right && root->left != NULL) 
		{ 
			Derevo* temp = root->left;
			delete root;
			return temp;
		}
		if (NULL == root->left && root->right != NULL) 
		{ 
			Derevo* temp = root->right;
			delete root;
			return temp;
		}
		
		root->kluch_d = FindMax(root->left, level)->kluch_d; 
		root->left = BinarySearchDelete(root->left, root->kluch_d, level);
		return root;
	}
	
	if (value < root->kluch_d) 
	{ 
		root->left = BinarySearchDelete(root->left, value, level);
		return root;
	}
	if (value > root->kluch_d) 
	{ 
		root->right = BinarySearchDelete(root->right, value, level);
		return root;
	}
	return root;
}

Derevo* FindMax(Derevo* root, int& level)
{
	if (root->right != NULL)
	{
		level++;
		return FindMax(root->right, level);
	}
	else
		return root;
}

bool Find_vyzol(Derevo* root, INF value, bool& b)
{
	if (root != NULL)
	{
		if (value == root->kluch_d)
			b = true;
		Find_vyzol(root->left, value, b);
		if (value == root->kluch_d)
			b = true;
		Find_vyzol(root->right, value, b);
	}
	return b;
}
