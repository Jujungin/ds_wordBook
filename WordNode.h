#ifndef _WORDNODE_H_
#define _WORDNODE_H_

#include <utility>

class WordNode
{
private:
	std::pair<char *, char *> wordmean;
	//char word[32];
	//char mean[32];
	WordNode * pLeft;	// BST Left Pointer
	WordNode * pRight;	// BST Right Pointer
	WordNode * pNext;	// Queue Next Pointer


public:
	WordNode();
	~WordNode();

	char *		GetWord();					// Get Word
	char *		GetMean();					// Get Word Mean
	WordNode *	GetLeft();					// Get BST Left Pointer
	WordNode *	GetRight();					// Get BST Right Pointer
	WordNode *	GetNext();					// Get Queue Next Pointer

	void		SetWord(char * word);		// Set Word
	void		SetMean(char * mean);		// Set Word Mean
	void		SetLeft(WordNode * node);	// Set BST Left Pointer
	void		SetRight(WordNode * node);	// Set BST Right Pointer
	void		SetNext(WordNode * node);	// Set Queue Next Pointer
};

#endif
