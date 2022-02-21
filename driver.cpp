/*****************************************
 ** File:    mytest.cpp
 ** Project: CMSC 341 Project 2, Fall 2020
 ** Author:  Kyle Rivera
 ** Date:    10/19/2020
 ** Section: 06
 ** E-mail:  drivera1@umbc.edu
 **
 ** This file contains the test program for project 2.
 ** This program is contains every test for each public fn.
 ** of the tree interfaces. It also tests edge cases such as:
 ** non-existing inputs, change of root in splay trees,
 ** rotations of AVL trees, etc.
**
 **
 ***********************************************/
#include "bookTree.h"
using namespace std;

int main(){
    cout << "//*****Test for wordTree*****\\\\" << endl;
    WordTree test_avl;
    cout << "\ncherry-bananas-apples (Right rotation rebalance)" << endl;
    test_avl.insert("cherry");
    test_avl.insert("bananas");
    test_avl.insert("apples");
    test_avl.dump();
    cout << endl;
    cout << "\n++dandelion-eggs (Left rotation rebalance)" << endl;
    test_avl.insert("dandelion");
    test_avl.insert("eggs");
    test_avl.dump();
    cout << endl;
    cout << "\n++ambulance-announce (Left-right rotation rebalance)" << endl;
    test_avl.insert("ambulance");
    test_avl.insert("announce");
    test_avl.dump();
    cout << endl;
    cout << "\n++grapes-flower (Right-left rotation rebalance)" << endl;
    test_avl.insert("grapes");
    test_avl.insert("flower");
    test_avl.dump();
    cout << endl;
    cout << "\n++grapes (Add count)" << endl;
    test_avl.insert("grapes");
    test_avl.dump();
    cout << endl;
    cout << "\ncount of steps from bananas to grapes (searchCount(); should return 3)" << endl;
    cout << "Step count: " << test_avl.searchCount("grapes") << endl << endl;
    cout << "getRootHeight() (should return 3)" << endl;
    cout << "Root height: " << test_avl.getRootHeight() << endl << endl;
    cout << "getNodeHeight of dandelion (should return 2)" << endl;
    cout << "Node height: " << test_avl.getNodeHeight("dandelion") << endl << endl;
    cout << "find() of bananas (should return bananas through getValue())" << endl;
    cout << test_avl.find("bananas")->getValue() << endl << endl;

    cout << "//-------Non-existing element test for each function-------\\\\" << endl;
    cout << "\ncount of steps from bananas to mangoes (searchCount(); should return -1)" << endl;
    cout << "Step count: " << test_avl.searchCount("mangoes") << endl << endl;
    cout << "getNodeHeight of watermelon (should return -1)" << endl;
    cout << "Node height: " << test_avl.getNodeHeight("watermelon") << endl << endl;
    cout << "find() of onion (should return 0 address)" << endl;
    cout << test_avl.find("onion") << endl << endl;

    string make_d;
    cout << "Make your own AVL tree? (y to create/any key to skip) " << endl;
    cin >> make_d;
    if(make_d == "y")
    {
    	WordTree user_test;
    	string user_in;
    	cout << "Insert your element (0 to STOP): " ;
    	cin >> user_in;
    	while(user_in != "0")
    	{
    		user_test.insert(user_in);
    	    user_test.dump();
    	    cout << endl;
        	cout << "Insert your element (0 to STOP): ";
        	cin >> user_in;
    	}
    }
    cout << "//*****Test for bookTree*****\\\\" << endl;
	BookTree test_splay;
	test_splay.loadData("data.txt");
	cout << "\nfindFrequency() of 'one' in 'a tale of two cities'" << endl;
	cout << "Frequency: " << test_splay.findFrequency("a tale of two cities", "one") << endl;
	cout << "Current root: " << test_splay.getRootKey() << endl << endl;
	cout << "searchCount() of 'and' in 'moby dick'" << endl;
	cout << "Count: " << test_splay.searchCount("moby dick", "and") << endl;
	cout << "Current root: " << test_splay.getRootKey() << endl << endl;
	cout << "getTextTreeHeight() of 'the masque of the red death'" << endl;
	cout << "Word Tree Height: " << test_splay.getTextTreeHeight("the masque of the red death") << endl;
	cout << "Current root: " << test_splay.getRootKey() << endl << endl;
	cout << "getWordHeight() of 'was' in 'pride and prejudice'" << endl;
	cout << "Word Height: " << test_splay.getWordHeight("pride and prejudice", "was") << endl;
	cout << "Current root: " << test_splay.getRootKey() << endl << endl;

	cout << "//-------Non-existing element test for each function-------\\\\" << endl;
	cout << "Root should still change after search" << endl;
	cout << "\nfindFrequency() of 'maktub' in 'the alchemist'" << endl;
	cout << "Frequency: " << test_splay.findFrequency("the alchemist", "maktub") << endl;
	cout << "Current root: " << test_splay.getRootKey() << endl << endl;
	cout << "searchCount() of 'music' in 'the magic strings of frankie pesto'" << endl;
	cout << "Count: " << test_splay.searchCount("the magic strings of frankie pesto", "music") << endl;
	cout << "Current root: " << test_splay.getRootKey() << endl << endl;
	cout << "getTextTreeHeight() of 'manuscript in accra'" << endl;
	cout << "Word Tree Height: " << test_splay.getTextTreeHeight("manuscript in accra") << endl;
	cout << "Current root: " << test_splay.getRootKey() << endl << endl;
	cout << "getWordHeight() of 'love' in 'warrior of light'" << endl;
	cout << "Word Height: " << test_splay.getWordHeight("warrior of light", "love") << endl;
	cout << "Current root: " << test_splay.getRootKey() << endl << endl;
    return 0;
}


