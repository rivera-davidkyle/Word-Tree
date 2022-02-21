/*****************************************
 ** File:    bookTree.cpp
 ** Project: CMSC 341 Project 2, Fall 2020
 ** Author:  Kyle Rivera
 ** Date:    10/19/2020
 ** Section: 06
 ** E-mail:  drivera1@umbc.edu
 **
 ** This file contains the bookTree program for project 2.
 ** This program is the interface for the splay tree. This
 ** includes the functions that: inserts a node in the tree,
 ** rotates the tree, rebalances the tree, counts number
 ** of steps from root to child in a node tree, returns height
 **  of tree/child in a node tree. This class is also included
 ** with a dump function that prints the tree in an In Order
 ** fashion, as well as a load function to extract a data file.
 **
 ***********************************************/
#include "bookTree.h"

const int NULL_VAL = -1;	// Default value if title doesn't exist

BookTree::BookTree(){_root=nullptr;}

BookTree::~BookTree(){
	// Deletes tree by clear()
	clear(_root);
}

BNode* BookTree::makeSplay(BNode* root, string key){
	// If tree is empty, return nullptr
	if(root == nullptr)
	{
		return root;
	}
	// Base case for recursion
	if(key == root->_key)
	{
		return root;
	}
	// If key is in left subtree
	else if(key < root->_key)
	{
		// Base case for recursion
		if(root->_left == nullptr)
		{
			return root;
		}
		// For RR rotation
		if(root->_left->_key > key)
		{
			root->_left->_left = makeSplay(root->_left->_left, key);
			root = rightRotate(root);
		}
		// For LR rotation
		else if (root->_left->_key < key)
		{
			root->_left->_right = makeSplay(root->_left->_right, key);
			// Will rotate only if right of left child exists
			if(root->_left->_right)
			{
				root->_left = leftRotate(root->_left);
			}
		}
		// Second rotation: Rotates until  base case isn't cleared
		if(root->_left)
		{
			return rightRotate(root);
		}
	}
	// If key is in right subtree
	else if(key > root->_key)
	{
		// Base case for recursion
		if(root->_right == nullptr)
		{
			return root;
		}
		// For LL rotation
		if(root->_right->_key < key)
		{
			root->_right->_right = makeSplay(root->_right->_right, key);
			root = leftRotate(root);
		}
		// For RL rotation
		else if (root->_right->_key > key)
		{
			root->_right->_left = makeSplay(root->_right->_left, key);
			// Will rotate only if left of right child exists
			if(root->_right->_left)
			{
				root->_right = rightRotate(root->_right);
			}
		}
		// Second rotation: Rotate until base case isn't cleared
		if(root->_right)
		{
			return leftRotate(root);
		}
	}

	// Returns root if base case is achieved
    return root;
}
BNode* BookTree::rightRotate(BNode* x){
	BNode* new_par = x->_left;			// New parent in rotation
	BNode* new_left = new_par->_right;	// New left of new child in rotation

	// Rotates the tree to the right
	new_par->_parent = x->_parent;
	new_par->_right = x;
	x->_parent = new_par;
	x->_left = new_left;

	// Returns new parent of subtree/tree
	return new_par;
}
BNode* BookTree::leftRotate(BNode* x){
	BNode* new_par = x->_right;			// New parent in rotation
	BNode* new_right= new_par->_left;	// New right of new child in rotation

	// Rotates the tree to the left
	new_par->_parent = x->_parent;
	new_par->_left = x;
	x->_parent = new_par;
	x->_right = new_right;

	// Returns new parent of subtree/tree
	return new_par;
}

bool BookTree::insert(string key, string author, string text){
	//	Inserts new node in splay tree if node doesn't exist in the tree
	if(find(key) != nullptr)
	{
		return false;
	}
	else
	{
		_root = insertHelper(key, author, text, _root);
		// Rebalances the tree
		_root = makeSplay(_root, key);
	}
	return true;
}
BNode* BookTree :: insertHelper(const string& key, const string& author, const string& text, BNode* x)
{
	// Base case for recursion
	if(x == nullptr)
	{
		BNode* temp = new BNode(key, author, text);
		return temp;
	}
	// Inserts node in left subtree
	else if(key < x->_key)
	{
		BNode* temp = insertHelper(key, author, text, x->_left);
		x->_left = temp;
		temp->_parent = x;
	}
	// Inserts node in right subtree
	else
	{
		BNode* temp = insertHelper(key, author, text, x->_right);
		x->_right = temp;
		temp->_parent = x;
	}
	return x;
}
BNode* BookTree :: find(const string& title)
{
	// Uses recursive heleper function to find node
	BNode* temp = findHelper(_root, title);
	return temp;
}
BNode* BookTree :: findHelper(BNode* x, const string& title)
{
	// Returns null if tree is empty
	if(x == nullptr)
	{
		return nullptr;
	}
	// Base case for recursion
	if(x->_key == title)
	{
		return x;
	}
	else
	{
		// Finds node in left subtree
		if(title < x->_key)
		{
			return findHelper(x->_left, title);
		}
		// Finds node in right subtree
		else
		{
			return findHelper(x->_right, title);
		}
	}
	return nullptr;
}
void BookTree::clear(BNode* root){
	// Clears tree by deleting all nodes
	if(root)
	{
		clear(root->_left);
		clear(root->_right);
		delete root;
	}
}

void BookTree::inorderHelp(BNode* root, bool verbose) const{
     /***********************************
     *      Do not modify
     * ********************************/
    if (root != nullptr){
        if (verbose){
            cout << "(";
            inorderHelp( root->_left, verbose );
            cout << root->_key << ":" << root->_author;
			root->_tree.dump();
            inorderHelp( root->_right, verbose );
            cout << ")";
        }
        else{
            inorderHelp( root->_left, verbose );
            cout << root->_key;
            inorderHelp( root->_right, verbose );
        }
    }
}
void BookTree::dump(bool verbose) const{
     /***********************************
     *      Do not modify
     * ********************************/
    inorderHelp(_root, verbose);
}

int BookTree::findFrequency(string title, string word){
	// Uses find() to return frequency
	BNode* temp = find(title);
	int frequency = NULL_VAL;
	if(temp)
	{
		frequency = temp->findFrequency(word);
	}
	// Rebalances the tree
	_root = makeSplay(_root, title);

	return frequency;
}

void BookTree::dumpTitle(string title){
	// Uses find() to dump tree
	BNode* temp = find(title);
	temp->_tree.dump();

	// Rebalances the tree
	_root = makeSplay(_root, title);
}

int BookTree::searchCount(string title, string word){
	// Uses find() to find step counts for word
	BNode* temp = find(title);
	int search_count = NULL_VAL;
	if(temp)
	{
		search_count = temp->searchCount(word);
	}
	// Rebalances the tree
	_root = makeSplay(_root, title);
    return search_count;
}

int BookTree::getTextTreeHeight(string title){
	// Uses find() to get height of book/AVL tree
	BNode* temp = find(title);
	int tree_height = NULL_VAL;
	if(temp)
	{
		tree_height = temp->getTextTreeHeight();
	}
	// Rebalances the tree
	_root = makeSplay(_root, title);
    return tree_height;
}
int BookTree::getWordHeight(string title, string word){
	// Uses find() to get height of word in book/AVL tree
	BNode* temp = find(title);
	int word_height = NULL_VAL;
	if(temp)
		{
			word_height= temp->getNodeHeight(word);
		}
	// Rebalances the tree
	_root = makeSplay(_root, title);
    return word_height;

}

string BookTree::getRootKey(){
     /***********************************
     *      Do not modify
     * ********************************/
	return _root->_key;
}

void BookTree::loadData(string dataFile){
     /***********************************
     *      This function is implemented
     *      to help you. You should't need
     *      to modify it.
     * ********************************/
	//read the entire file at once
	std::ifstream t(dataFile);
	std::stringstream buffer;
	buffer << t.rdbuf();

	//time to parse the information
	string titleDelimiter = "<==>";
	string itemsDeleimiter = "<=>";
	string s = buffer.str();
	size_t pos = 0;
	string token;

	while ((pos = s.find(titleDelimiter)) != string::npos) {
		token = s.substr(0, pos);//token is complete data for one title
		//get the title
		int tempPos = token.find(itemsDeleimiter);
		string title = token.substr(0,tempPos);
		//convert title to lower case
		std::transform (title.begin(), title.end(), title.begin(), ::tolower);
		token.erase(0, tempPos + itemsDeleimiter.length()+1);
		//get the author
		tempPos = token.find(itemsDeleimiter);
		string author = token.substr(0,tempPos);
		//convert author to lower case
		std::transform (author.begin(), author.end(), author.begin(), ::tolower);
		token.erase(0, tempPos + itemsDeleimiter.length()+1);
		//get the text
		string text = token.substr(0,token.length() - 1);//remove last newline
		//clean up the text, remove all non-alphanumeric characters
          for( std::string::iterator iter = text.begin() ; iter != text.end() ; ){
               if( !std::isalnum(*iter) && *iter != ' ')
                    iter = text.erase(iter) ;
               else
                    ++iter ; // not erased, increment iterator
          }
		//convert text to lower case
		std::transform (text.begin(), text.end(), text.begin(), ::tolower);
		insert(title,author,text);

		//move to info for the next title
		s.erase(0, pos + titleDelimiter.length()+1);

	}

}
