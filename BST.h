#pragma once
#include <iostream>
using namespace std;

template <class T>
class BinarySearchTree;

template <class T>
class TreeNode {
private:
	T _item;
	TreeNode<T>* _left;
	TreeNode<T>* _right;
	int _height;
public:
	TreeNode(T x) { _left = _right = NULL; _item = x; _height = 0; };

	friend BinarySearchTree<T>;
};

template <class T>
class BinarySearchTree {
protected:
	int _size;
	TreeNode<T>* _root;
	void _printTree(int indent, TreeNode<T>*, bool withHeight);

	// The following functions are optional for you to implement. 
	TreeNode<T>* _insert(TreeNode<T>* current, T x);
	void _inOrderPrint(TreeNode<T>* node);
	void _postOrderPrint(TreeNode<T>* node);
	void _preOrderPrint(TreeNode<T>* node);
	TreeNode<T>* _rightRotation(TreeNode<T>*);
	TreeNode<T>* _leftRotation(TreeNode<T>*);
	TreeNode<T>* _searchMax(TreeNode<T>* node);
	TreeNode<T>* _searchMin(TreeNode<T>* node);
	TreeNode<T>* _search(TreeNode<T>* current, T x);
	TreeNode<T>* _successor(TreeNode<T>* node, T x);
	void _destroySubTree(TreeNode<T>*);
	int _get_height(TreeNode<T>* node);
	int _get_balance(TreeNode<T>* node);
	void _update_height(TreeNode<T>* node);

public:
	BinarySearchTree() { _root = NULL; _size = 0; }
	~BinarySearchTree();
	int size() { return _size; };
	void insert(T);
	void printTree(bool withHeight = 1);
	void inOrderPrint();
	void postOrderPrint();
	void preOrderPrint();
	T searchMax();
	T searchMin();
	bool exist(T x);
	T search(T x) { return T(); };
	T successor(T);
};

template <class T>
void BinarySearchTree<T>::_printTree(int indent, TreeNode<T>* node, bool withHeight) {

	if (!node)
		return;

	if (node->_right)
		_printTree(indent + 2, node->_right, withHeight);
	for (int i = 0; i < indent; i++)
		cout << "  ";
	cout << node->_item;
	if (withHeight)
		cout << "(h=" << node->_height << ")";
	cout << endl;
	if (node->_left)
		_printTree(indent + 2, node->_left, withHeight);


};

template <class T>
void BinarySearchTree<T>::printTree(bool withHeight) {
	_printTree(0, _root, withHeight);
}


template <class T>
void BinarySearchTree<T>::preOrderPrint() {

	_preOrderPrint(_root);
	cout << endl;
}


template <class T>
void BinarySearchTree<T>::_preOrderPrint(TreeNode<T>* node) {
	if (!node) return;
	cout << node->_item << " ";
	_preOrderPrint(node->_left);
	_preOrderPrint(node->_right);
}


template <class T>
void BinarySearchTree<T> ::_destroySubTree(TreeNode<T>* node)
{
	if (node->_left)
		_destroySubTree(node->_left);
	if (node->_right)
		_destroySubTree(node->_right);
	delete node;
}

template <class T>
BinarySearchTree<T> :: ~BinarySearchTree()
{
	if (_root)
		_destroySubTree(_root);
}



template <class T>
void BinarySearchTree<T>::inOrderPrint() {
	_inOrderPrint(_root);
	cout << endl;
}


template <class T>
void BinarySearchTree<T>::_inOrderPrint(TreeNode<T>* node) {
	if (!node) return;
	_inOrderPrint(node->_left);
	cout << node->_item << " ";
	_inOrderPrint(node->_right);
}


template <class T>
void BinarySearchTree<T>::postOrderPrint() {
	_postOrderPrint(_root);
	cout << endl;
}


template <class T>
void BinarySearchTree<T>::_postOrderPrint(TreeNode<T>* node) {
	if (!node) return;
	_postOrderPrint(node->_left);
	_postOrderPrint(node->_right);
	cout << node->_item << " ";
}

template <class T>
int BinarySearchTree<T>::_get_height(TreeNode<T>* node) {
	if (!node) return -1;
	return node->_height;
}

template <class T>
int BinarySearchTree<T>::_get_balance(TreeNode<T>* node) {
	if (!node) return 0;
	return _get_height(node->_left) - _get_height(node->_right);
}

template <class T>
void BinarySearchTree<T>::_update_height(TreeNode<T>* node) {
	if (!node) return;
	node->_height = 1 + std::max(_get_height(node->_left), _get_height(node->_right));
}

template <class T>
void BinarySearchTree<T>::insert(T x)
{
	_root = _root ? _insert(_root, x) : new TreeNode<T>(x);
	if (_size == 0) _size++;
}

template <class T>
TreeNode<T>* BinarySearchTree<T>::_insert(TreeNode<T>* current, T x) {
	if (current == nullptr) {
		_size++;
		return new TreeNode<T>(x);
	}
	if (x < current->_item) current->_left = _insert(current->_left, x); // Pass current node as the parent of the left subtree
	else if (x > current->_item) current->_right = _insert(current->_right, x); // Pass current node as the parent of the right subtree
	else return current; // Node already exists in the tree
	_update_height(current);
	int balance = _get_balance(current);
	if (balance >= 2 && _get_balance(current->_left) >= 1) {
		return _rightRotation(current);
	}
	if (balance <= -2 && _get_balance(current->_right) <= -1) {
		return _leftRotation(current);
	}
	if (balance >= 2 && _get_balance(current->_left) <= -1) {
		current->_left = _leftRotation(current->_left);
		return _rightRotation(current);
	}
	if (balance <= -2 && _get_balance(current->_right) >= 1) {
		current->_right = _rightRotation(current->_right);
		return _leftRotation(current);
	}
	return current;
}

template <class T>
T BinarySearchTree<T>::searchMax() {
	return _searchMax(_root)->_item;
}

template <class T>
TreeNode<T>* BinarySearchTree<T>::_searchMax(TreeNode<T>* current) {
	while (current->_right) current = current->_right;
	return current;
}

template <class T>
T BinarySearchTree<T>::searchMin() {
	return _searchMin(_root)->_item;
}

template <class T>
TreeNode<T>* BinarySearchTree<T>::_searchMin(TreeNode<T>* current) {
	while (current->_left) current = current->_left;
	return current;
}

template <class T>
TreeNode<T>* BinarySearchTree<T>::_search(TreeNode<T>* current, T x) {
	if (current == NULL) return NULL; // the value is not found
	if (current->_item == x) return current; // the node containing the value is found
	if (current->_item > x) return _search(current->_left, x);
	else return _search(current->_right, x);
}


template <class T>
T BinarySearchTree<T>::successor(T x)
{
	return _successor(_root, x)->_item;
}

template <class T>
TreeNode<T>* BinarySearchTree<T>::_successor(TreeNode<T>* node, T x) {
	TreeNode<T>* current = _search(node, x);
	if (!current) { // Case 1: Node is not in the tree
		TreeNode<T>* successor = NULL;
		TreeNode<T>* ancestor = _root;
		while (ancestor) {
			if (ancestor->_item > x) {
				successor = ancestor;
				ancestor = ancestor->_left;
			}
			else ancestor = ancestor->_right;
		} return successor;
	}
	else { // Case 2: Node is in the tree
		// Case 2(a): Node has right subtree
		if (current->_right) return _searchMin(current->_right);
		else { // Case 2(b): Node has no right subtree
			TreeNode<T>* successor = NULL;
			TreeNode<T>* ancestor = _root;
			while (ancestor != current) {
				if (ancestor->_item > current->_item) {
					successor = ancestor;
					ancestor = ancestor->_left;
				}
				else ancestor = ancestor->_right;
			} return successor;
		}
	}
}

template <class T>
TreeNode<T>* BinarySearchTree<T>::_rightRotation(TreeNode<T>* node) {
	TreeNode<T>* new_root = node->_left;
	node->_left = new_root->_right;
	new_root->_right = node;
	_update_height(node);
	_update_height(new_root);
	return new_root;
}

template <class T>
TreeNode<T>* BinarySearchTree<T>::_leftRotation(TreeNode<T>* node) {
	TreeNode<T>* new_root = node->_right;
	node->_right = new_root->_left;
	new_root->_left = node;
	_update_height(node);
	_update_height(new_root);
	return new_root;
}

template <class T>
bool BinarySearchTree<T>::exist(T x) {
	if (!_search(_root, x)) return 0;
	else return 1;
}