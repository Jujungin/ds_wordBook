#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "CircularLinkedList.h"
#include "AlphabetBST.h"
#include "Queue.h"
#include <utility>

class Manager
{
private:
	CircularLinkedList * cll;	// MEMORIZED Circular Linked List
	AlphabetBST	* bst;			// MEMORIZING BST
	Queue * queue;				// TO_MEMORIZE Queue
	char m_Word[50];
	char m_Mean[50];			// Mean to UPDATE or TEST
	char m_search[50];
	char m_Print[13];			// Way to PRINT
	char m_Print2[8];			// Way to PRINT
	int m_Move;					// The number of MOVE

public:
	Manager();
	~Manager();

	void run(const char * command);	// ifstream fin; fin.open(command); // and read all line
	
	bool LOAD();
	bool ADD();
	bool MOVE();
	bool SAVE();
	bool TEST();
	bool SEARCH();
	bool PRINT();
	bool UPDATE();
	void LOG(const int, const bool);
	bool AlphabetCheck(bool& error, const int begin, const int end, const char * str);
};

#endif
