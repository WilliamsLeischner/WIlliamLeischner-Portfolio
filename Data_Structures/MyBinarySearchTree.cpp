//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : William S Leischner
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Binary Tree
// Course      : CS260
// Date        : 2/12/19
//============================================================================

#include <algorithm>
#include <iostream>
#include <time.h>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDoubleBST(string str, char ch);


// define a structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

// Internal structure for tree node
struct Node {
	Bid bidDataValue; // data value of node
	Node *rightNext;
	Node *leftNext;
};
/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayBidBST(Bid bid);
//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* root;
    int nOfNodes =0;

    void addNode(Node* node, Bid bid);
    void inOrder(Node* node);
    void destroyTree(Node* Node);
    Bid search(Node* node, string bidId);
    Node* removeNode(Node* root, string bidId);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void Insert(Bid bid);
    void Remove(string bidId);
    void DestroyTree();
    Bid Search(string bidId);
    int getNumberOfNodes();
    int BinarySearchTree_main(int argc, char* argv[]);

};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
	// Initialize root
	root = 0;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {

	DestroyTree();
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
	inOrder(root);
}
/**
 * Insert a bid
 */
void BinarySearchTree::Insert(Bid bid) {
    // Inserting a bid into the tree
	if(root != 0){
			addNode(root,bid);
			nOfNodes +=1;
	}

	 else{
        // no root exist create one now
		root = new Node;
		root->bidDataValue = bid;
		root->leftNext = 0;
		root->rightNext = 0;
		nOfNodes =1;

	}
}

/**
 * Remove a bid
 */
void BinarySearchTree::Remove(string bidId) {
    // Implement removing a bid from the tree
	// Assign root to new value
	root = removeNode(root,bidId);

}

/**
 * Search for a bid
 */
Bid BinarySearchTree::Search(string bidId) {
    // searching the tree for a bid
    return search(root,bidId);
}
void BinarySearchTree::DestroyTree(){
	destroyTree(root);
}

int BinarySearchTree::getNumberOfNodes(){
	return nOfNodes;
}

/**
 * Add a bid to some node (recursive)
 *
 * @param node Current node in tree
 * @param bid Bid to be added
 */
void BinarySearchTree::addNode(Node* node, Bid bid) {
    // Implement inserting a bid into the tree
	if(bid.bidId < node->bidDataValue.bidId){
			if(node->leftNext != 0)
				addNode(node->leftNext, bid);
			else{
				node->leftNext = new Node;             // set values for leaf
				node->leftNext->bidDataValue = bid;
				node->leftNext->leftNext = 0;
				node->leftNext->rightNext = 0;
			}

	}
    else if(bid.bidId >= node->bidDataValue.bidId){
		if(node->rightNext != 0)
			addNode(node->rightNext, bid);
		else{                                       // set values for leaf
			node->rightNext = new Node;
			node->rightNext->bidDataValue = bid;
			node->rightNext->rightNext = 0;
			node->rightNext->leftNext = 0;

		}

	}
}
Node* BinarySearchTree::removeNode(Node* root, string bidId){
	Node* emptyTree = 0;
	if (root == 0)
	     return emptyTree;
	  if (bidId < root->bidDataValue.bidId) // data is in the left sub tree.
	      root->leftNext = removeNode(root->leftNext,bidId);
	  else if (bidId > root->bidDataValue.bidId) // data is in the right sub tree.
	      root->rightNext = removeNode(root->rightNext, bidId);
	else {
		 // case 1: no children
	  if (root->leftNext == 0 && root->rightNext == 0) {
		delete root; // remove node and free mem
		root = 0;
	  }
		 // case 2: one child (right)
	  else if (root->leftNext == 0) {
		 Node *temp = root; // save current node as a backup
		 root = root->rightNext;
		 delete temp; // remove node and free mem
	  }
		 // case 3: one child (left)
	  else if (root->rightNext == 0) {
		 Node *temp = root; // save current node as a backup
		 root = root->leftNext;
		 delete temp; // remove node and free mem
	  }
		 // case 4: two children
	    else {
		   Node* suc = root->rightNext;
		   while (suc->leftNext != 0) // find min value
			  suc = suc->leftNext;
		   root->bidDataValue = suc->bidDataValue;                       // Copy successor to current node
	       root->rightNext = removeNode(root->rightNext, suc->bidDataValue.bidId);
	     }
	 }
	 return root; // parent node can update reference

}
void BinarySearchTree::inOrder(Node* node) {
	if(node != 0){
		inOrder(node->leftNext);
		displayBidBST(node->bidDataValue);
		inOrder(node->rightNext);

	}
}
void BinarySearchTree::destroyTree(Node *node){
	// recurse from root deleting every node
	if(node != 0){
		destroyTree(node->leftNext); // left side first
		destroyTree(node->rightNext); // then right side
		delete node;

	}

}
Bid BinarySearchTree::search(Node* node, string bidId){
	Bid notFound;
	if(node != 0){
			if(bidId == node->bidDataValue.bidId)
				return node->bidDataValue;

            //check left node recursively
			if(bidId < node->bidDataValue.bidId)
				return search(node->leftNext, bidId);
			else
				// check right node recursively
				return search(node->rightNext, bidId);
	}
	else
	   return notFound;

}
//============================================================================
// Static methods used for testing
//============================================================================



/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void displayBidBST(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
            << bid.fund << endl;
    return;
}
void loadBids(string csvPath, BinarySearchTree* bst) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    // read and display header row - optional
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        cout << c << " | ";
    }
    cout << "" << endl;

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDoubleBST(file[i][4], '$');

            //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

            // push this bid to the end
            bst->Insert(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDoubleBST(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int BinarySearchTree_main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, bidKey, searchString;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        bidKey = "98109";
        break;
    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;
    default:
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
        bidKey = "98109";
    }

    // Define a timer variable
    clock_t ticks;

    // Define a binary search tree to hold all bids
    BinarySearchTree* bst;

    Bid bid;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids" << endl;
        cout << "  3. Find Bid" << endl;
        cout << "  4. Remove Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            bst = new BinarySearchTree();

            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            loadBids(csvPath, bst);

            //cout << bst->Size() << " bids read" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "Number of bids loaded is "<<bst->getNumberOfNodes()<<endl;
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:
            bst->InOrder();
            break;

        case 3:
        	searchString="";
            ticks = clock();
            cout << "Enter a BidID or Name or Fund to search for or (d)for default\n";
            cin >> searchString;
			if(searchString == "d")

				bid = bst->Search(bidKey);

			else
				bid = bst->Search(searchString);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                displayBidBST(bid);
            } else {
            	cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 4:
            bst->Remove(bidKey);
            break;
        }
    }

    cout << "Good bye." << endl;

	return 0;
}
