#pragma once
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

template <class T> 
class BinaryTree 
{
private:
	int _depth;
	vector<vector<T>> _tree;
public:
	BinaryTree() : _depth(0) {};
	BinaryTree(int depth)
	{
		_depth = depth;
		_tree.resize(_depth + 1); 
		for (int i = 0; i < _tree.size(); i++)
		{
			_tree[i].resize(i + 1);
		}

	};
	void setDepth(int);
	void setNode(int, int, T);
	T getNode(int, int);
	void display();
private:
	string printChar(int, string);
	
};

using namespace std;

template <class T>
void BinaryTree<T>::setDepth(int z)
{
	_depth = z;
	_tree.resize(_depth + 1);
	for (int i = 0; i <= _depth; ++i)
	{
		_tree[i].resize(i + 1);
	}
}

template <class T>
void BinaryTree<T>::setNode(int ind1, int ind2, T value)
{
	for (int i = 0;i <= _depth;++i)
	{
		if (i == ind1)
		{
			for (int j = 0; j <= _tree[i].size(); ++j)
			{
				if (j == ind2)
				{
					_tree[i][j] = value;
				}
			}
		}
	}
}




template <class T>
T BinaryTree<T>::getNode(int i, int j)
{
	T value;
	if (i <= _depth && j <= i + 1)
	{
		value = _tree[i][j];
	}
	return value;
}


template <class T>
void BinaryTree<T>::display()
{
	for (int i = 0; i <= _depth; ++i)
	{
		for (int j = 0; j <= i; ++j)
		{
			cout << getNode(i, j) << " ";
		}
		cout << endl;
	}

	cout << "\n\n" << endl;
	int i = 0;
	string space = " ";
	string temp = "/   \\ ";
	do
	{
		if (i < _depth) {
			cout << printChar((_depth - i) * 3, space);
		}
		for (int j = 0;j <= i;j++)
		{
			if (getNode(i, j)== 0 || getNode(i, j) == 1)
			{
				cout << getNode(i, j) << ".000";
			}
			else {
				cout << setprecision(4)<<double(getNode(i, j));
			}
			if (i > 0)
			{
				cout << printChar(1, space);
			}
			if (j == i)
			{
				cout << "\n";
			}
		}
		if (i < _depth) 
		{
			cout << printChar((_depth - i) * 3 , space) << printChar(i + 1, temp) << "\n";
		}
		i++;
	} while (i <= _depth);
}

template <class T>
string BinaryTree<T>::printChar(int n,string c)
{
	string res = "";
	for (int i = 0;i < n;i++)
	{
		res += c;
	}

	return res;
}