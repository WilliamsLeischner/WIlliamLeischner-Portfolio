
//============================================================================
// Name        : LinkedList.cpp
// Author      : William S Leischner
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Lab 3-3 Lists and Searching
// Course      : CS260
// Date        : 1/16/19
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
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
        bidId="";
        title="";
        fund="";
    }
};


//============================================================================
// Linked-List class definition
//============================================================================

/**
 * A class containing data members and methods to
 * implement a linked-list.
 */



class LinkedList {

private:
	// primary data structure of list
	struct Node
	{
		Bid bidDataValue; // data value of node
		Node *next;  // a pointer to the next node in the list
	};

	Node *head; // Ptr to the head of the list
	Node *tail; // Ptr to the tail of the list
	int sizeOfList; // count of objects in list




public:
    LinkedList();
    virtual ~LinkedList();
    void Append(Bid bid);
    void Prepend(Bid bid);
    void PrintList();
    void Remove(string bidId);
    Bid Search(string bidId);
    int Size();
};

/**
 * Default constructor
 */
LinkedList::LinkedList() {

	head =0;
	tail =0;
	sizeOfList=0;


}

/**
 * Destructor
 */
LinkedList::~LinkedList() {
	Node* currentNode;
	currentNode = head;
	while(currentNode!=0){
		head = currentNode->next;
		delete currentNode;
		currentNode = head;
	}
}

/**
 * Append a new bid to the end of the list
 */
void LinkedList::Append(Bid bid) {
	Node *newNode = new Node;
	if(head==0){// list empty
		newNode->bidDataValue = bid;
		newNode->next=0;
		head = newNode;
		tail = newNode;
	}
	else{
		newNode->bidDataValue = bid;
		newNode->next = 0; // append last item needs to point to 0 to signify end of list
		tail->next = newNode;
		tail = newNode;
	}
	sizeOfList+=1; //count node added
}




/**
 * Prepend a new bid to the start of the list
 */
void LinkedList::Prepend(Bid bid) {
	Node *newNode = new Node;
		if(head==0){// list empty
			newNode->bidDataValue = bid;
			newNode->next=0;
			head = newNode;
			tail = newNode;
		}
		else{
			newNode->bidDataValue = bid;
			newNode->next = head; // append last item needs to point to 0 to signify end of list
			head = newNode;
		}
		sizeOfList+=1; // count node added
}

/**
 * Simple output of all bids in the list
 */
void LinkedList::PrintList() {
	Node *currentNode;
	currentNode = head;
	while(currentNode!=0 ){
		 cout << currentNode->bidDataValue.bidId << ": " << currentNode->bidDataValue.title << " | " << currentNode->bidDataValue.amount
		         << " | " << currentNode->bidDataValue.fund << endl;
		currentNode = currentNode->next;
	}

}

/**
 * Remove a specified bid
 *
 * @param bidId The bid id to remove from the list
 */
void LinkedList::Remove(string bidId) {
	Node *currentNode;
	Node *prevNode;
		currentNode = head; // set both ptrs to head to start and when current incremented prevNode holds previous current value
		prevNode= head;
			while(currentNode!=0 ){

				if(currentNode->bidDataValue.bidId== bidId){
					prevNode->next = currentNode->next; // get currents next value so previous can now point to that next
					delete currentNode; // now safe to remove currentNode

				}
				prevNode = currentNode; // store nodes value before changing currentNode
				currentNode = currentNode->next;
			}
}

/**
 * Search for the specified bidId
 *
 * @param bidId The bid id to search for
 */
Bid LinkedList::Search(string bidId) {
	Node *currentNode;
	currentNode = head;
	Bid emptyBid;// to return empty obj when string not found
		while(currentNode!=0 ){
			if(currentNode->bidDataValue.bidId== bidId){
				return currentNode->bidDataValue;
			}
			currentNode = currentNode->next;
		}

	return emptyBid;// reached this point string not found
}

/**
 * Returns the current size (number of elements) in the list
 */
int LinkedList::Size() {
    return sizeOfList;
}

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information
 *
 * @param bid struct containing the bid info
 */
void displayBidLS(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount
         << " | " << bid.fund << endl;
    return;
}

/**
 * Prompt user for bid information
 *
 * @return Bid struct containing the bid info
 */
Bid getBidLS() {
    Bid bid;

    cout << "Enter Id: ";
    cin.ignore();
    getline(cin, bid.bidId);

    cout << "Enter title: ";
    getline(cin, bid.title);

    cout << "Enter fund: ";
    cin >> bid.fund;

    cout << "Enter amount: ";
    cin.ignore();
    string strAmount;
    getline(cin, strAmount);
    bid.amount = strToDouble(strAmount, '$');

    return bid;
}

/**
 * Load a CSV file containing bids into a LinkedList
 *
 * @return a LinkedList containing all the bids read
 */
void loadBids(string csvPath, LinkedList *list) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser
    csv::Parser file = csv::Parser(csvPath);

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // initialize a bid using data from current row (i)
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //cout << bid.bidId << ": " << bid.title << " | " << bid.fund << " | " << bid.amount << endl;

            // add this bid to the end
            list->Append(bid);
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
double strToDoubleLS(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 *
 * @param arg[1] path to CSV file to load from (optional)
 * @param arg[2] the bid Id to use when searching the list (optional)
 */
int LinkedList_main(int argc, char* argv[]) {

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

    clock_t ticks;

    LinkedList bidList; // main data structure

    Bid bid; // main data element

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Enter a Bid" << endl;
        cout << "  2. Load Bids" << endl;
        cout << "  3. Display All Bids" << endl;
        cout << "  4. Find Bid" << endl;
        cout << "  5. Remove Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            bid = getBidLS();
            bidList.Append(bid);
            displayBidLS(bid);

            break;

        case 2:
            ticks = clock();

            loadBids(csvPath, &bidList);

            cout << bidList.Size() << " bids read" << endl;

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " milliseconds" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 3:
            bidList.PrintList();

            break;

        case 4:
            ticks = clock();

            bid = bidList.Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                displayBidLS(bid);
            } else {
            	cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 5:
            bidList.Remove(bidKey);

            break;
        }
    }

    cout << "Good bye." << endl;

    return 0; // call Destructor function before exiting
}
