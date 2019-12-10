/*
 * Data_Structures_and_Algorithms_Main.cpp
 *
 *  Created on: Nov 19, 2019
 *      Author: William S Leischner
 */
#include <iostream>

using namespace std;

int HashTable_main(int argc, char* argv[]);
int VectorSorting_main(int argc, char* argv[]);
int LinkedList_main(int argc, char* argv[]);
int BinarySearchTree_main(int argc, char* argv[]);

int main(int argc, char* argv[]){

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
	int choice = 0;
	    while (choice != 5) {
	cout << "Chose Selection:" << endl;
	cout << "  1. VectorSort" << endl;
    cout << "  2. HashTable" << endl;
	cout << "  3. LinkedList" << endl;
	cout << "  4. BinarySearchTree" << endl;
	cout << "  5. Exit" << endl;
	cin >> choice;
	switch (choice) {
	        case 1:
	        	VectorSorting_main(argc, argv );

	            break;

	        case 2:
                HashTable_main(argc, argv );


	            break;

	        case 3:
	        	LinkedList_main(argc, argv);


	            break;

	        case 4:
	        	BinarySearchTree_main(argc, argv);


	            break;

	        }
	    }

}
