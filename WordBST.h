#ifndef _WORDBST_H_
#define _WORDBST_H_

#include "WordNode.h"

class WordBST
{
private:
	WordNode * root;	// Word BST Root
	void R_Preorder(WordNode * node);
	void R_Inorder(WordNode * node);
	void R_Postorder(WordNode * node);
	void I_Preorder();	// Preorder traversal
	void I_Inorder();
	void I_Postorder();
	void I_LEVEL();
	struct Stack {
		WordNode * pHead = 0;
		WordNode * Top() {
			return pHead;
		}
		void Push(WordNode * node) { 
			node->SetNext(pHead); 
			pHead = node; 
		}
		WordNode * Pop() { 
			WordNode * p = pHead; 
			pHead = pHead->GetNext(); 
			p->SetNext(0); 
			return p; 
		}
	};
	
public:
	WordBST();
	~WordBST();

	void		Insert(WordNode * node);			// LOAD, MOVE
	WordNode *	Delete(char * word);				// TEST
	WordNode *	Search(char * word);				// ADD, TEST, SEARCH, UPDATE
	bool		Print(char * order);				// PRINT
	bool		Save();								// SAVE
};

#endif
