/*****************************************
 ** File:    bNode.cpp
 ** Project: CMSC 341 Project 2, Fall 2020
 ** Author:  Kyle Rivera
 ** Date:    10/19/2020
 ** Section: 06
 ** E-mail:  drivera1@umbc.edu
 **
 ** This file contains the bNode program for project 2.
 ** This program is the node class for the splay tree. This
 ** includes the functions that: finds frequency of word in
 ** the node tree, counts the steps of a child from root in
 ** the node tree, gets the height of the node tree.
 **
 ***********************************************/
#include "bNode.h"
BNode::BNode(){}
BNode::BNode(string key, string author, string text){
            _key = key;
            _author = author;
            _left = nullptr;
            _right = nullptr;
            _flag = false;
            _parent = nullptr;
            createTextTree(text);
        }
BNode::~BNode(){

}

void BNode::createTextTree(string text){
    istringstream iss(text);
    vector<string> tokens;
    copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(tokens));

    for (std::vector<string>::iterator it = tokens.begin() ; it != tokens.end(); ++it){
        _tree.insert(*it);
    }

}

int BNode::findFrequency(string word){
	int count = 0;
	// If node exists, assigns count to its _count
	if(_tree.find(word))
	{
		count = _tree.find(word)->getFrequency();
	}
	return count;
}

int BNode::searchCount(string word){
    return _tree.searchCount(word);
}

int BNode::getTextTreeHeight(){
    return _tree.getRootHeight();
}

int BNode::getNodeHeight(string word){
    return _tree.getNodeHeight(word);
}
