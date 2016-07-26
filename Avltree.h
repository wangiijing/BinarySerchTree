#include<iostream>

using namespace std;


template<class K,class V>
struct AvltreeNode
{
	K key;
	V value;
	AvltreeNode<K, V>* left;    

	AvltreeNode<K, V>* right;
	AvltreeNode<K, V>* parent;
	int balance_factor;
	AvltreeNode(const K &_key = K(), const V &_value = v())
		:key(_key)
		, value(_value)
		, left(NULL)
		, right(NULL)
		, parent(NULL)
		, balance_factor(0)
	{}
};

template<class K,class V>
class AVLTree
{
	typedef AvltreeNode<K, V> Node;
public:
	AVLTree()
		:_root(NULL)
	{}
	~AVLTree()
	{
		_destory(_root);
	}
	bool Insert(const K &key, const V &value)
	{
		//_rootΪ��
		if (_root == NULL)
		{
			_root = new Node(key, value);
			return true;
		}
		//_root��Ϊ��
		Node *parent = NULL;
		Node *cur = _root;
		while (cur)
		{
			//���Ѿ�����ʱ������false
			if (cur->key == key)
			{
				return false;
			}
			parent = cur;
			//��key�ȵ�ǰ����keyֵ��ʱ����������
			if (cur->key < key)
			{
				cur = cur->right;
			}
			//��key�ȵ�ǰ����keyֵ��ʱ����������
			else
			{
				cur = cur->left;
			}
		}
		Node* tmp;
		if (parent->key < key)
		{
			tmp = new Node(key, value);
			parent->right = tmp;
			tmp->parent = parent;
		}
		else
		{
			tmp = new Node(key, value);
			parent->left = tmp;
			tmp->parent = parent;
		}

		// ����ƽ������
		bool isRotate = false;
		cur = tmp;
		parent = cur->parent;
		//cur = new Node(key, value);
		//cur->parent = parent;
		////�жϵ�ǰ���Ӧ����parent�����ӻ����Һ���
		//if (parent->key < key)
		//{
		//	parent->right = cur;
		//}
		//else
		//{
		//	parent->left = cur;
		//}
		////����ƽ������
		//bool isRotate = false;
		while (parent)
		{
			if (parent->left == cur)
			{
				parent->balance_factor -= 1;
			}
			else
			{
				parent->balance_factor += 1;
			}
			if (parent->balance_factor == 0)
			{
				break;
			}
			if (parent->balance_factor == -1 || parent->balance_factor == 1)
			{
				cur = parent;
				parent = cur->parent;
			}
			else
			{
				//��ת
				if (parent->balance_factor == 2)
				{
					if (cur->balance_factor == 1)
					{
						_RotateL(parent);
					}
					else // -1
					{
						_RotateRL(parent);
					}
				}
				else // -2
				{
					if (cur->balance_factor == -1)
					{
						_RotateR(parent);
					}
					else // 1
					{
						_RotateLR(parent);
					}
				}

				isRotate = true;
				break;
			}
		}
		if (isRotate)
		{
			Node* ppNode = parent->parent;
			if (ppNode == NULL)
				_root = parent;
			else if (ppNode->key > parent->key)
				ppNode->left = parent;
			else
				ppNode->right = parent;
		}
	}
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}

	bool IsBlance()
	{
		return _IsBlance(_root);
	}
private:
	int _Height(Node* root)
	{
		if (root == NULL)
			return 0;

		int left = _Height(root->left);
		int right = _Height(root->right);

		return left > right ? left + 1 : right + 1;
	}

	bool _IsBlance(Node* root)
	{
		if (root == NULL)
			return true;

		int balance_factor = _Height(root->right) - _Height(root->left);
		//assert(bf == root->_bf);

		if (balance_factor != root->balance_factor)
		{
			cout << "ƽ�������쳣��" << root->key << endl;
		}

		return balance_factor == root->balance_factor && abs(balance_factor) < 2
			&& _IsBlance(root->left) && _IsBlance(root->right);
	}

	void _InOrder(Node* root)
	{
		if (root == NULL)
			return;

		_InOrder(root->left);
		cout << root->key << " ";
		_InOrder(root->right);
	}
	void _RotateL(Node *&parent)
	{
		Node* subR = parent->right;                       //parent                                 subR
		Node* subRL = subR->left;                     //     / \	                              /      \             
		parent->right = subRL;                      //    subL  subR                        parent      subRR
		if (subRL)                                  //           /   \                       /    \     /    \ 
		{                                            //       subRL subRR                 subL  subRL subRRL subRRR
			subRL->parent = parent;       //                        / \  
		}                                  //                   subRRL  subRRR        
		subR->left = parent;
		subR->parent = parent->parent;
		parent->parent = subR;

		// ����ƽ������
		parent->balance_factor = subR->balance_factor = 0;

		parent = subR;
	}
	void _RotateR(Node *&parent)
	{
		Node* subL = parent->left;              //         parent                   subL
		Node* subLR = subL->right;             //          /    \                 /      \ 
		parent->left = subLR;                   //      subL    subR         subLL        parent
		if (subLR)                             //      /    \               /   \          /   \ 
		{                                     //     subLL subLR         subLLL subLLR   subLR subR
			subLR->parent = parent;        //        /  \ 
	    }	                               //   subLLL subLLR
	    subL->right = parent;
	    subL->parent = parent->parent;
	    parent->parent = subL;
	    // ����ƽ������
	    parent->balance_factor = subL->balance_factor = 0;
	    parent = subL;
    }
	void _RotateLR(Node *&parent)
	{
		Node* pNode = parent;                                 //  parenrt                parent                 subLR
		Node* subLNode = parent->left;                  //        /    \                /      \               /     \ 
		Node* subLRNode = subLNode->right;             //      subL     subR          subLR    subR         subL      parent
		int balance_factor = subLRNode->balance_factor;//      /  \                   /   \                /   \      /     \ 
		_RotateL(parent->left);                    //     subLL  subLR             subL subLRR         subLL subLRL subLRR  subR  
		_RotateR(parent);                          //            /   \            /   \  
		// ����ƽ������                   //                 subLRL subLRR      subLL subLRL
		if (balance_factor == -1)
		{
			subLNode->balance_factor = 0;
			pNode->balance_factor = 1;
		}
		else if (balance_factor == 1)
		{
			subLNode->balance_factor = -1;
			pNode->balance_factor = 0;
		}
		else
		{
			subLNode->balance_factor = 0;
			pNode->balance_factor = 0;
		}
		subLRNode->balance_factor = 0;
	}
	void _RotateRL(Node *&parent)
	{
		Node* pNode = parent;                            //        parent               parent                    subRL
		Node* subRNode = parent->right;                   //       /    \               /    \                    /    \ 
		Node* subRLNode = subRNode->left;                //      subL  subR          subL    subRL           parent     subR
	    int balance_factor = subRLNode->balance_factor;  //            /   \                 /   \          /     \     /    \ 
		_RotateR(parent->right);                        //          subRL subRR          subRLL  subR      subL subRLL subRLR subRR
		_RotateL(parent);                            //             /   \                        /   \
		// ����ƽ������                              //         subRLL subRLR                 sunRLR subRR      
		if (balance_factor == 1)           
		{
			subRNode->balance_factor = 0;
			pNode->balance_factor = -1;
		}
		else if (balance_factor == -1)
		{
			subRNode->balance_factor = 1;
			pNode->balance_factor = 0;
		}
		else
		{
			subRNode->balance_factor = 0;
			pNode->balance_factor = 0;
		}
		subRLNode->balance_factor = 0;
	}

	void _destory(Node *&_root)
	{
		if (_root == NULL || (_root->left == NULL && _root->right == NULL))
		{
			return;
		}
		_destory(_root->left);
		_destory(_root->right);

		delete _root;
	}
private:
	Node *_root;
};
void TestAVLTree()
{
	AVLTree<int, int> t;
	int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	for (size_t i = 0; i < sizeof(a) / sizeof(a[0]); ++i)
	{
		t.Insert(a[i], i);
	}

	t.InOrder();

	cout << "t�Ƿ�ƽ�⣿" << t.IsBlance() << endl;

	AVLTree<int, int> t1;
	int a1[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	for (size_t i = 0; i < sizeof(a1) / sizeof(a1[0]); ++i)
	{
		t1.Insert(a1[i], i);
	}

	t1.InOrder();

	cout << "t1�Ƿ�ƽ�⣿" << t1.IsBlance() << endl;
}