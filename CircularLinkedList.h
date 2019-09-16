#ifndef _CIRCULARLINKEDLIST_H_
#define _CIRCULARLINKEDLIST_H_

#include "WordNode.h"

class CircularLinkedList
{
private:
	WordNode * pHead;	// Circular Linked List Head Pointer
	WordNode * pTail;
public:
	CircularLinkedList();
	~CircularLinkedList();

	void		Insert(WordNode * node);			// LOAD, TEST
	WordNode *	Search(char * word);				// SEARCH, UPDATE
	bool		Print();							// PRINT
	bool		Save();								// SAVE
	WordNode *	Delete(WordNode * node);
	bool		IsEmpty();

};

#endif
