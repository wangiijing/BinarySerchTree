#include<iostream>
using namespace std;

template <class K,class V>
struct  BinarySerchTreeNode
{
	K _key;
	V _value;
	BinarySerchTreeNode<K, V> * _left;
	BinarySerchTreeNode<K, V> * _right;

	BinarySerchTreeNode(K key, V value)
		:_key(key)
		,_value(value)
		, _left(NULL)
		, _right(NULL)
	{}
};
template <class K, class V>
class BinarySerchTree
{
	typedef BinarySerchTreeNode<K, V>  Node;
public:
	BinarySerchTree()
	:_root(NULL)
	{}
	void Insert(const K& key, const V& value)
	{
		_insert(_root,key, value);
	}
	bool Find(const K& key)
	{
		return _find(root, key);
	}
	bool Remove(const K& key)
	{
		return _remove(_root, key);
	}
	void Display()
	{
		_display(_root);
		cout << endl;
	}
protected:
	void _display(Node * root)
	{
		if (root == NULL)
		{
			return;
		}
		cout << root->_key << "  ";
		_display(root->_left);
		_display(root->_right);
		
	}
	bool _remove(Node *& root, const K& key)
	{
		if (root == NULL)
		{
			return false;
		}
		if (root->_key < key)
		{
			return _remove(root->_right, key);
		}
		if (root->_key > key)
		{
			return _remove(root->_left, key);

		}
		if (root->_key == key)
		{
			if (root->_left == NULL && root->_right == NULL)
			{
				delete root;
				root = NULL;
				return true;
			}
			if (root->_left == NULL)
			{
				Node * tmp = root;
				root = root->_right;
				delete tmp;
				return true;
			}
			if (root->_right == NULL)
			{
				Node * tmp = root;
				root = root->_left;
				delete tmp;
				return true;
			}
			else
			{
				Node *right = root->_right;
				Node *left = root->_left;
				if (left->_right == NULL)
				{
					Node *tmp = root;
					root = root->_left;
					root->_right = right;
					delete tmp;
					return true;
				}
				if (right->_left == NULL)
				{
					Node *tmp = root;
					root = root->_right;
					root->_left = left;
					delete tmp;
					return true;
				}
				else
				{
					Node * cur = left->_right;
					while (cur->_right)
					{
						cur = cur->_right;
					}
					swap(cur->_key, root->_key);
					swap(cur->_value, root->_value);
					delete cur;
					return true;
				}
			}
		}
		return false;
	}
	bool _find(const Node *& root, const K &key)
	{
		if (root == NULL)
		{
			return false;
		}
		if (root->_key == key)
		{
			return true;
		}
		if (root->_key > key)
		{
			return _find(root->_left, key);
		}
		if (root->_key < key)
		{
			return _find(root->_right, key);
		}
	}
	void _insert(Node *& root, const K& key, const V& value)
	{
		if (root == NULL)
		{
			root = new Node(key, value);
			return;
		}
		if (root->_key < key)
		{
			_insert(root->_right, key, value);
		}
		if (root->_key > key)
		{
			_insert(root->_left, key, value);
		}
		if (root->_key == key)
		{
			return;
		}
	}
protected:
	Node * _root;
};

void test()
{
	BinarySerchTree<int, int> _b;
	_b.Insert(5, 1);
	_b.Insert(4, 1);
	_b.Insert(6, 1);
	_b.Insert(7, 1);
	_b.Insert(3, 1);

	_b.Display();
	_b.Remove(4);
	_b.Display();

}