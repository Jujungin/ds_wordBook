#ifndef _ALPHABETBST_H_
#define _ALPHABETBST_H_

#include "AlphabetNode.h"

#define MAX_WORD 100	// Maximum MEMORIZING Words

class AlphabetBST
{
private:
	AlphabetNode * root;	// Root of ALPHABETBST
	int WordCnt;			// The number of words of MEMORIZING
	struct Stack {			// STACK data structure
		AlphabetNode * pHead = 0;
		bool IsEmpty() {
			if (!pHead)return 1;
			return 0;
		}
		AlphabetNode * Top() {
			return pHead;
		}
		void Push(AlphabetNode * node) { 
			node->SetNext(pHead); 
			pHead = node; 
		}
		AlphabetNode * Pop() { AlphabetNode * p = pHead; 
		pHead = pHead->GetNext(); 
		p->SetNext(0); 
		return p; 
		}
	};
	struct Queue {
		AlphabetNode * pHead = 0, *pTail = 0;
		bool IsEmpty() {
			if (!pHead)return 1;
			else return 0;
		}
		void Push(AlphabetNode * node) {
			if (IsEmpty()) {
				pHead = node;
				pTail = node;
				return;
			}
			else pTail->SetNext(node);
			pTail = node;
		}
		AlphabetNode * Pop() {
			AlphabetNode * p = pHead;
			if (!IsEmpty()) {
				pHead = pHead->GetNext();
				p->SetNext(0);
				return p;
			}
			return 0;
		}
	};

public:
	AlphabetBST();
	~AlphabetBST();

	void			Insert(AlphabetNode * node);	// run
	bool			Print(char * order);						// PRINT
	AlphabetNode *	Search(char alpabet);			// LOAD, MOVE, TEST, SEARCH, UPDATE
	bool			Save();							// SAVE
	void			Insert(WordNode * node);
	WordNode *		Search(char * node);
	WordNode *		Delete(WordNode * node);
	bool			IsFull();
	bool			IsEmpty();

	void			R_Preorder(AlphabetNode * node);
	void			R_Inorder(AlphabetNode * node);
	void			R_Postorder(AlphabetNode * node);
	void			I_Preorder();	// Preorder traversal
	void			I_Inorder();
	void			I_Postorder();
	void			I_LEVEL();
};

#endif
