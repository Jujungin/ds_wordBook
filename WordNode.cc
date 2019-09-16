#include "WordNode.h"

WordNode::WordNode()
{
	pLeft = '\0';
	pRight = '\0';
	pNext = '\0';
}


WordNode::~WordNode()
{
}

char *		WordNode::GetWord()					// Get Word
{
	return wordmean.first;
}
char *		WordNode::GetMean()					// Get Word Mean
{
	return wordmean.second;
}
WordNode *	WordNode::GetLeft()					// Get BST Left Pointer
{
	return pLeft;
}
WordNode *	WordNode::GetRight()					// Get BST Right Pointer
{
	return pRight;
}
WordNode *	WordNode::GetNext()					// Get Queue Next Pointer
{
	return pNext;
}

void		WordNode::SetWord(char * word)		// Set Word
{
	wordmean.first = word;
}
void		WordNode::SetMean(char * mean)		// Set Word Mean
{
	wordmean.second = mean;
}
void		WordNode::SetLeft(WordNode * node)	// Set BST Left Pointer
{
	pLeft = node;
}
void		WordNode::SetRight(WordNode * node)	// Set BST Right Pointer
{
	pRight = node;
}
void		WordNode::SetNext(WordNode * node)	// Set Queue Next Pointer
{
	pNext = node;
}