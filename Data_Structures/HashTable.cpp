//============================================================================
// Name        : HashTable.cpp
// Author      : William S. Leischner
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Hash Table
// Course      : CS260
// Date        : 2/04/19
//============================================================================

#include <algorithm>
#include <climits>
#include <iostream>
#include <string> // atoi
#include <time.h>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

const unsigned int DEFAULT_SIZE = 179;

// forward declarations
double strToDouble(string str, char ch);

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
void displayBidHT(Bid bid);

class Node {
public:
	int key; // hold key value of the node
	Bid bidDataValue; // data value of node
	Node *next;  // a pointer to the next node in the list
	Node(){
		Bid bid;
		this->key = -1;
		this->bidDataValue = bid;
		this->next=0;
	}
	Node(int key, Bid bidObj){
		this->key = key;
		this->bidDataValue = bidObj;
		this->next =0;
	}
};
//============================================================================
// Hash Table class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a hash table with chaining.
 */
class HashTable {

private:
    // structures to hold bids
		Node **hashTable; // list of pointers of a list of pointers

    unsigned int hash(int key);

public:
    HashTable();
    virtual ~HashTable();
    void Insert(Bid bid);
    void PrintAll();
    void Remove(string bidId);
    Bid Search(string bidId);
    int HashTable_main(int argc, char* argv[]);
};

/**
 * Default constructor
 */
HashTable::HashTable() {
    // Initialize the structures used to hold bids
	hashTable = new Node*[DEFAULT_SIZE];
	for(unsigned int i=0; i<DEFAULT_SIZE;i++)
		hashTable[i]=0;
}

/**
 * Destructor
 */
HashTable::~HashTable() {
    // logic to free storage when class is destroyed
	for(unsigned int i=0; i<DEFAULT_SIZE;++i){
		Node* current = hashTable[i];
		while(current != 0){ // delete each element in the chain if exists
			Node* prev = current;
			current = current->next;
			delete prev;
		}

	}
	delete[] hashTable;

}

/**
 * Calculate the hash value of a given key.
 * Note that key is specifically defined as
 * unsigned int to prevent undefined results
 * of a negative list index.
 *
 * @param key The key to hash
 * @return The calculated hash
 */
unsigned int HashTable::hash(int key) {
    // logic to calculate a hash value
	return key % DEFAULT_SIZE;
}

/**
 * Insert a bid
 *
 * @param bid The bid to insert
 */
void HashTable::Insert(Bid bid) {
    // logic to insert a bid
	unsigned int hashValue = hash(atoi(bid.bidId.c_str()));
	Node* prev =0;
	Node* current = hashTable[hashValue];
	while(current != 0){
		prev = current;
		current = current->next;
	}
	if(current == 0){
		current = new Node(atoi(bid.bidId.c_str()), bid);
		if(prev == 0){
			hashTable[hashValue] = current;
		}
		else{
			prev->next = current;
		}
	}
	else{
		current->bidDataValue = bid;
	}
}

/**
 * Print all bids
 */
void HashTable::PrintAll() {
    // logic to print all bids
	Node* current=0;
	for(unsigned int i=0; i<DEFAULT_SIZE;i++){
		if(hashTable[i]!=0){
			cout<<"Key: "<<i <<" ";
			displayBidHT(hashTable[i]->bidDataValue);
			current = hashTable[i];
			while(current->next !=0){ // print out rest of chain
				current = current->next;
				cout<<"     "<<i<<" ";
				displayBidHT(current->bidDataValue);
			}
		}

	}
}

/**
 * Remove a bid
 *
 * @param bidId The bid id to search for
 */
void HashTable::Remove(string bidId) {
    // logic to remove a bid
    unsigned int hashValue = hash(atoi(bidId.c_str()));

    if (hashTable[hashValue] != 0) {
		  Node *prevNode = 0;
		  Node *current = hashTable[hashValue];
		  while (current->next != 0 && current->bidDataValue.bidId != bidId) { // move to node that contains key
				prevNode = current;
				current = current->next;
		  }
		  if (current->bidDataValue.bidId == bidId) {
				if (prevNode == 0) { // at head of chain
					 Node *nextCurrent = current->next;
					 delete current;
					 hashTable[hashValue] = nextCurrent; // set table to point to new head of chain
				} else {
					 Node *nextNode = current->next;
					  delete current;                    // delete past head of chain
					 prevNode->next=nextNode->next;
				}
		  }
	}
}

/**
 * Search for the specified bidId
 *
 * @param bidId The bid id to search for
 */
Bid HashTable::Search(string bidId) {
    Bid bid;

    // logic to search for and return a bid
    int key = atoi(bidId.c_str());
    unsigned int hashValue = hash(key);
    Node* current = hashTable[hashValue];
    while(current != 0){
    	if(current->key== key){
    		bid = current->bidDataValue;
    	}
    	current = current->next;
    }

    return bid;
}

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayBidHT(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
            << bid.fund << endl;
    return;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadBids(string csvPath, HashTable* hashTable) {
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
            bid.amount = strToDouble(file[i][4], '$');

            //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

            // push this bid to the end
            hashTable->Insert(bid);
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
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int HashTable_main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, bidKey;
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

    // Define a hash table to hold all the bids
    HashTable* bidTable;

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
            bidTable = new HashTable();

            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            loadBids(csvPath, bidTable);

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:
            bidTable->PrintAll();
            break;

        case 3:
            ticks = clock();

            bid = bidTable->Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                displayBidHT(bid);
            } else {
                cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 4:
            bidTable->Remove(bidKey);
            break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}
