/**********************************************************************************************************
CSCI 340 - Assignment 08 - Fall 2020

Programmer: Leonart Jaos
Z-ID: z1911688
Section: 0002
TA: Saiteja Alubelli
Date Due: November 2nd, 2020

Purpose: The purpose of this program is to expand upon the BinaryTree class that was implemented in Assign-
ment #7. As a derived class of the BinaryTree, BinarySearchTree will its own insertion and with that,
a search function and a removal function that removes leaf nodes, which are nodes that do not have children
A binary search tree is a binary tree where the values in the tree are sorted where all the values to the
left of the node have data with smaller values and all values to the right have data with higher values. 
To display the features of the class, values are generated and inserted into the BST and then values are 
removed until the tree is empty.

***********************************************************************************************************/

#ifndef BINARYSEARCHTREE_H_
#define BINARYSEARCHTREE_H_

#include "node.h"
#include "bstDriver.h"
// This flag is used to determine whether or not a removal has been made
bool rflag = false;

// Since the following tree is a binary tree and not a binary search tree, I used the following logic prov-
// ided in the assignment details to determine the position of the inserted value
typedef enum {left_side, right_side } SIDE;

SIDE rnd()
{
	return rand()%2 ? right_side : left_side;
};

template <typename T> class BinaryTree{

public:
    BinaryTree();                                      // default constructor
    unsigned     getSize() const;                      // returns size of tree
    unsigned     getHeight() const;                    // returns height of tree
    virtual void Insert(const T &v);                     // inserts node in tree
    void         Inorder(void (*fptr)(const T &));          // inorder traversal of tree

protected:
    Node<T> *root;                                      // root of tree

private:
    unsigned _getSize(Node<T>* n) const;                 // private version of getSize()
    unsigned _getHeight(Node<T>* n) const;               // private version of getHeight()
    void     _Insert(Node<T> * &n, const T &v);             // private version of Insert()
    void     _Inorder(Node<T> *n, void (*fptr)(const T &));   // private version of Inorder()
};
// default constructor
template <typename T>
BinaryTree<T>::BinaryTree()
{
	root = NULL;
};
// if the root is NULL, the size is 0
// otherwise recursion is used on each branch until NULL is achieved and adds 1 each time
template <typename T>
unsigned BinaryTree<T>::_getSize(Node<T>* n) const
{
	if(n == NULL)
	{	
		return 0;
	}
	else
		return(_getSize(n->left) + 1 + _getSize(n->right));
};
// a public member function that allows the user to view private member data, but not
// change it
template <typename T>
unsigned BinaryTree<T>::getSize() const
{
	return(_getSize(root));
};
// inserts a node randomly with the value stored at v
// if the node is empty, allocates new memory
template <typename T>
void BinaryTree<T>::_Insert(Node<T> * &n, const T &v)
{
	if(n == NULL)
	{
		n = new Node<T>(v);
	}
	else if(rnd() == left_side)
	{
		_Insert(n->left,v);
	}
	else
	{
		_Insert(n->right,v);
	}
};
// public access of insert that doesn't allow user to alter other values in the tree
template <typename T>
void BinaryTree<T>::Insert(const T &v)
{
	_Insert(root,v);
};
// uses recursion to find which subtree is longer to return the max depth of the
// tree. Adds 1 for every level, assumed root height is 1
template <typename T>
unsigned BinaryTree<T>::_getHeight(Node<T>* n) const
{
	if(n == NULL)
	{
		return 0;
	}
	else
	{
		unsigned ldepth = _getHeight(n->left);
		unsigned rdepth = _getHeight(n->right);
		if(ldepth > rdepth)
			return(ldepth + 1);
		else
			return(rdepth + 1);
	}
};
// public access of protected class data 
template <typename T>
unsigned BinaryTree<T>::getHeight() const
{
	return(_getHeight(root));
};
// inorder traversal of tree, performs function passed with data from
// node passed as parameter
template <typename T>
void BinaryTree<T>::_Inorder(Node<T> *n, void (*fptr)(const T &))
{
	if(n != NULL)
	{
		_Inorder(n->left,fptr);
		fptr(n->data);
		_Inorder(n->right,fptr);
	}
};
// public access of Inorder 
template <typename T>
void BinaryTree<T>::Inorder(void (*fptr)(const T &))
{
	_Inorder(root,fptr);
};
// START OF BST DEFINITION
// -----------------------------------------------------------------------
template <typename T>
class BinarySearchTree : public BinaryTree<T>
{
public:
    void Insert(const T &x);       // inserts node with value x
    bool Search(const T &x) const; // searches leaf with value x
    bool Remove(const T &x);       // removes leaf with value x
private:
    void _Insert(Node<T> * &n, const T &a);      // private version of insert
    bool _Search(Node<T> * n, const T &a) const; // private version of search
    void _Remove(Node<T> * &n, const T &a);      // private version of remove
    bool _Leaf(Node<T> * n) const;          // checks if node is leaf
};

// Insert function, does NOT allow for duplicates
// Recursively inserts values to either the left or
// right subtrees of a node. 
template <typename T>
void BinarySearchTree<T>::_Insert(Node<T> * &n, const T &a)
{
	if(n == NULL)
	{
		n = new Node<T>(a);
	}
	else if(a < n->data)
	{
		_Insert(n->left,a);
	}
	else if(a > n->data)
	{
		_Insert(n->right,a);
	}
	else
	{
		// do nothing
	}
};

// Public version of _Insert
// Calls private version and passes pointer to root and value to insert
template <typename T>
void BinarySearchTree<T>::Insert(const T &x)
{
	_Insert(this->root,x);
};

// Recursive search that searches based off of data stored in node
// If data isn't found, returns false
template <typename T>
bool BinarySearchTree<T>::_Search(Node<T> * n, const T &a) const
{
	if(n != NULL)
	{
		if(a < n->data)
		{
			return(_Search(n->left,a));
		}
		else if(a == n->data)
		{
			return true;
		}
		else
		{
			return(_Search(n->right,a));
		}
	}
	return false;
};

// Public version of _Search, calls private version
// with pointer to root and value to search
template <typename T>
bool BinarySearchTree<T>::Search(const T &x) const
{
	return(_Search(this->root,x));
};

// This function checks if a node is a leaf node by looking
// at the values of the left and right nodes
template <typename T>
bool BinarySearchTree<T>::_Leaf(Node<T> * n) const
{
	if((n->left == NULL)&&(n->right == NULL))
	{
		return true;
	}
	else
		return false;
};

// The remove function recursively searches for a value and 
// removes the value when found if it is a leaf.
// When a value is removed, it changes a removal flag to true
// to indicate that a value was removed
template <typename T>
void BinarySearchTree<T>::_Remove(Node<T> * &n, const T &a)
{
	if(n != NULL)
	{
		if(n->data == a)
		{	if(_Leaf(n))
			{
				n->data = 0;
				n = NULL;
				rflag = true;
				free(n);
			}
			else
				return;
		}
		else if(a > n->data)
		{
			_Remove(n->right,a);
		}
		else
		{
			_Remove(n->left,a);
		}
	}
};

// The public version of the Remove function checks that first,
// the value is in the tree, and then calls the private removal.
// If the removal didn't occur, the flag we set would be false 
// and the return value would indicate that a value was not
// actually removed. 
template <typename T>
bool BinarySearchTree<T>::Remove(const T &x)
{
	if(_Search(this->root,x))
	{
		_Remove(this->root,x);
		if(rflag == true)
		{
			rflag = false;
			return true;
		}
		return false;
	}
	else
		return false;
};
#endif
