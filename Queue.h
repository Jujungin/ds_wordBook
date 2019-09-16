#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "WordNode.h"

class Queue
{
private:
	WordNode * pHead;
	WordNode * pTail;
	int WordCnt;
public:
	Queue();
	~Queue();

	void		Push(WordNode * node);				// LOAD, ADD
	WordNode *	Pop();						// MOVE
	WordNode *	Search(char * word);				// SEARCH, UPDATE
	bool		Print();							// PRINT
	bool		Save();								// SAVE
	bool		IsEmpty();
	int			WordNumber();
};

#endif
