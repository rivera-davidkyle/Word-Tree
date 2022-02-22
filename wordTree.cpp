/*****************************************
 ** This file contains the wordTree program for project 2.
 ** This program is the interface for the AVL tree. This
 ** includes the functions that: inserts a node in the tree,
 ** rotates the tree, rebalances the tree, counts number
 ** of steps from root to child, returns height of tree/child
 ** This class is also included with a dump function that prints
 ** the tree in an In Order fashion.
 **
 ***********************************************/
#include "wordTree.h"

const int HEIGHT_INC = 1;	// Height increment
const int NULL_HEIGHT = -1;	// Null height
const int PB_THRESHOLD = 1;	// Positive balance threshold
const int NB_THRESHOLD = -1;	// Negative balance threshold

WordTree::~WordTree(){
	// Uses clearTree() to delete the tree
	clearTree(_root);
}

void WordTree::updateHeight(Node *aNode) {
	// Uses compareHeight() to get the highest height from children
	aNode->_height = HEIGHT_INC + compareHeight(aNode);
}

void WordTree::clearTree(Node* aNode){
	// Recursively deletes the nodes in the tree
	if(aNode)
	{
		clearTree(aNode->_left);
		clearTree(aNode->_right);
		delete aNode;
	}
}

void WordTree::inOrder(Node* aNode, std::ostream& ostr){
    /***********************************
     *      Do not modify
     * ********************************/
    if (aNode != nullptr){
        ostr << "[";
        inOrder(aNode->_left, ostr);
        ostr << aNode->_value << ":" << aNode->_count << ":" << aNode->_height;
        inOrder(aNode->_right, ostr);
        ostr << "]";
    }
}

Node* WordTree::find(Node* aNode, const string& element){
	if(aNode == nullptr)
	{
		return nullptr;
	}
	// Base case for recursion
	if(aNode->_value == element)
    {
    	return aNode;
    }
    else
    {
    	// Recursively finds node in left subtree
    	if(element < aNode->_value)
    	{
    		return find(aNode->_left, element);
    	}
    	// Recursively finds node in right subtree
    	else
    	{
    		return find(aNode->_right, element);
    	}
    }
	// Returns nullptr if node isn't found
    return nullptr;
}
Node* WordTree::find(const string& element){
	// Uses helper function to return needed node
	Node* temp = find(_root, element);
	return temp;
}

Node* WordTree::leftRotation(Node* aNode){
	Node* new_par = aNode->_right;		// New parent in rotation
	Node* new_right= new_par->_left;	// New right of new child in rotation

	// Rotates the tree to the left
	new_par->_parent = aNode->_parent;
	new_par->_left = aNode;
	aNode->_parent = new_par;
	aNode->_right = new_right;

	// Updates height of the changed nodes
	updateHeight(aNode);
	updateHeight(new_par);

	// Returns new parent of subtree/tree
	return new_par;

}

Node* WordTree::rightRotation(Node* aNode){
	Node* new_par = aNode->_left;		// New parent in rotation
	Node* new_left = new_par->_right;	// New left of new child in rotation

	// Rotates the tree to the right
	new_par->_parent = aNode->_parent;
	new_par->_right = aNode;
	aNode->_parent = new_par;
	aNode->_left = new_left;

	// Updates height of the changed nodes
	updateHeight(aNode);
	updateHeight(new_par);

	// Returns new parent of subtree/tree
	return new_par;

}

int WordTree::checkBalance(Node* aNode){
	int l_height;	// Height of left child
	int r_height;	// Height of right child
	if(aNode->_left == nullptr)
	{
		l_height = NULL_HEIGHT;
	}
	else
	{
		l_height = aNode->_left->_height;
	}
	if(aNode->_right == nullptr)
	{
		r_height = NULL_HEIGHT;
	}
	else
	{
		r_height = aNode->_right->_height;
	}

	// Returns balance factor of a node
	return l_height - r_height;
}

Node* WordTree::reBalance(Node* aNode){
	int b_factor = checkBalance(aNode);	// Balance factor of node
	Node* left = aNode->_left;			// Left child of node
	Node* right = aNode->_right;		// Right child of node

	// Self-balances the tree by balancing the nodes and their children in
	// the following conditional statements:

	// Right rotation of node
	if((b_factor > PB_THRESHOLD)&&(left->_left)&&(compareHeight(left) == left->_left->_height))
	{
		return rightRotation(aNode);
	}
	// Left rotation of node
	else if((b_factor < NB_THRESHOLD)&&(right->_right)&&(compareHeight(right) == right->_right->_height))
	{
		return leftRotation(aNode);
	}
	// Left-right rotation of node
	else if ((b_factor > PB_THRESHOLD)&&(left->_right)&&(compareHeight(left) == left->_right->_height)) //LR
	{
		aNode->_left = leftRotation(aNode->_left);
		return rightRotation(aNode);
	}
	// Right-left rotation of node
	else if((b_factor < NB_THRESHOLD)&&(right->_left)&&(compareHeight(right) == right->_left->_height))
	{
		aNode->_right = rightRotation(aNode->_right);
		return leftRotation(aNode);
	}

    return aNode;
}

void WordTree::insert(const string& element){
	Node* check = find(element);	// Check if node exists already

	// Insert if node doesn't exist in tree
	if(check == nullptr)
	{
		Node* temp = insert(element, _root);
		_root = temp;
	}
	// Adds count instead if it exists
	else
	{
		check->_count++;
	}

}
Node* WordTree::insert(const string& element, Node*& aNode){
	// BST insertion while updating the height

	// Base case for recursive insertion
	if(aNode == nullptr)
	{
		Node* temp = new Node(element);
		temp->_count++;
		return temp;
	}
	// If given element is in the left subtree
	else if(element < aNode->_value)
	{
		Node* temp = insert(element, aNode->_left);
		aNode->_left = temp;
		temp->_parent = aNode;
		updateHeight(aNode->_left);
	}
	// If given element is in the right subtree
	else
	{
		Node* temp = insert(element, aNode->_right);
		aNode->_right = temp;
		temp->_parent = aNode;
		updateHeight(aNode->_right);
	}

	// Update root's height
	updateHeight(aNode);
	// Rebalances the tree by L/R rotations
	aNode = reBalance(aNode);

	return aNode;
}

int WordTree :: compareHeight(Node* aNode)
{
	int l_height;	// Left child of node
	int r_height;	// Right child of node
	if(aNode->_left == nullptr)
	{
		l_height = NULL_HEIGHT;
	}
	else
	{
		l_height = aNode->_left->_height;
	}
	if(aNode->_right == nullptr)
	{
		r_height = NULL_HEIGHT;
	}
	else
	{
		r_height = aNode->_right->_height;
	}

	// Returns highest height between the children
	if(l_height < r_height)
	{
		return r_height;
	}
	return l_height;
}

void WordTree::dump(std::ostream& ostr){
    /***********************************
     *      Do not modify
     * ********************************/
    inOrder(_root, ostr);
}

int WordTree::searchCount(string word){
	// Uses recursive helper function
    return searchCountHelp(_root, word, 0);
}

int WordTree::searchCountHelp(Node* aNode, string word, int counter){
	if(aNode == nullptr)
	{
		return NULL_HEIGHT;
	}
	// Base case for recursion
	if(aNode->_value == word)
	{
		return counter;
	}
	// Searches for word then returns count of steps
	else
	{
		if(word < aNode->_value)
		{
			return searchCountHelp(aNode->_left, word, ++counter);
		}
		else
		{
			return searchCountHelp(aNode->_right, word, ++counter);
		}
	}
    return NULL_HEIGHT;
}

int WordTree::getRootHeight(){
    if(_root == nullptr)
    {
    	return NULL_HEIGHT;
    }
    return _root->_height;
}

int WordTree::getNodeHeight(string word){
	// Uses recursive helper function
    return getNodeHeightHelp(_root, word);
}

int WordTree::getNodeHeightHelp(Node* aNode, string word){
    if(aNode == nullptr)
    {
    	return NULL_HEIGHT;
    }
    // Base case for recursion
    if(aNode->_value == word)
    {
    	return aNode->_height;
    }
    // Searches for word then returns node height
    else if(word < aNode->_value)
    {
    	return getNodeHeightHelp(aNode->_left, word);
    }
    else if(word > aNode->_value)
	{
    	return getNodeHeightHelp(aNode->_right, word);
	}
    return NULL_HEIGHT;
}
