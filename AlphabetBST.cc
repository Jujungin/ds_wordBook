#include "AlphabetBST.h"
#include "AlphabetNode.h"
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct BST_Queue {
	AlphabetNode* pHead = 0;
	AlphabetNode* pTail = 0;
	void Push(AlphabetNode* node) {
		if (!pHead) {
			pHead = node;
			pTail = node;
		}
		else {
			pTail->SetNext(node);
			pTail = node;
		}
	}
	AlphabetNode * Pop() {
		AlphabetNode * temp;
		if (!pHead)return 0;
		else {
			temp = pHead;
			pHead = pHead->GetNext();
			if (pHead == 0)pTail = 0;
			return temp;
		}
	}
};
AlphabetBST::AlphabetBST()
{
	root = '\0';
	WordCnt = 0;
	
	BST_Queue queue;
	AlphabetNode * p;
	char arr[26] = { 'p', 'h', 'x', 'd', 'l', 't', 'z', 'b', 'f', 'j', 'n', 'r', 'v', 
					'y', 'a', 'c', 'e', 'g', 'i', 'k', 'm', 'o', 'q', 's', 'u', 'w' };
	for (int i = 0; i < 26; i++) {
		p = new AlphabetNode;
		p->SetAlphabet(arr[i]);
		Insert(p);
	}
}

AlphabetBST::~AlphabetBST()
{
	/* You must fill here */
	BST_Queue queue;
	if (!root)return;
	AlphabetNode* p = root, *pp = 0;
	while (p) {
		if (p->GetLeft())queue.Push(p->GetLeft());
		if (p->GetRight())queue.Push(p->GetRight());
		delete p;
		p = queue.Pop();
	}
}


void			AlphabetBST::Insert(AlphabetNode * node)	// run
{
	AlphabetNode* p = root, *pp = 0;
	if (!root) {
		root = node;
		return;
	}
	while (p) {
		if (node->GetAlphabet() < p->GetAlphabet()) {
			pp = p;
			p = p->GetLeft();
		}
		else if (node->GetAlphabet() > p->GetAlphabet()) {
			pp = p;
			p = p->GetRight();
		}
		else {
			delete node;
			return;
		}
	}
	if (node->GetAlphabet() < pp->GetAlphabet())pp->SetLeft(node);
	else pp->SetRight(node);

}
bool			AlphabetBST::Print(char * order)						// PRINT
{
	if (!WordCnt)return 0;												// MEMORIZING is empty
	ofstream fout;
	fout.open("log.txt", ios_base::app);
	if (!fout.is_open() || IsEmpty())return 0;
	if		(!strcmp("R_PRE", order)){// Recursive preorder
		fout << "======== PRINT ========" << endl;
		R_Preorder(root);
	}
	else if (!strcmp("R_IN", order)){		// Recursive inorder
		fout << "======== PRINT ========" << endl;
		R_Inorder(root);
	}
	else if (!strcmp("R_POST", order))	{
		fout << "======== PRINT ========" << endl;
		R_Postorder(root);			// Recursive postorder
	}
	else if	(!strcmp("I_PRE", order)){
		fout << "======== PRINT ========" << endl;
		I_Preorder();				// Iterative preorder
	}
	else if (!strcmp("I_IN", order)){
		fout << "======== PRINT ========" << endl;
		I_Inorder();				// Iterative inorder
	}
	else if (!strcmp("I_POST", order)){
		fout << "======== PRINT ========" << endl;
		I_Postorder();				// Iterative postorder
	}
	else if (!strcmp("I_LEVEL", order)){
		fout << "======== PRINT ========" << endl;
		I_LEVEL();					// Iterative level-order
	}
	else {
		fout.close();
		return 0;
	}
	fout.close();
	return 1;
}
AlphabetNode *	AlphabetBST::Search(char alpabet)			// LOAD, MOVE, TEST, SEARCH, UPDATE
{
	AlphabetNode* p = root;
	if (!root)return 0;
	while (p) {
		if (alpabet < p->GetAlphabet())p = p->GetLeft();
		else if (alpabet > p->GetAlphabet())p = p->GetRight();
		else return p;
	}
	return 0;
}
bool			AlphabetBST::Save()							// SAVE
{
	AlphabetNode * p = root;
	Stack stack;
	ofstream fout;
	fout.open("memorizing_word.txt", ios_base::out);
	fout.close();
	if (!root)return 0;
	while (1) {
		while (p) {
			if (p->GetRight())stack.Push(p->GetRight());
			p->GetBST()->Save();
			p = p->GetLeft();
		}
		if (!stack.pHead)break;
		p = stack.Pop();
	}
	return 1;
}

void AlphabetBST::Insert(WordNode * node)
{
	AlphabetNode* temp;
	if (WordCnt == 100)return;

	temp = Search((node->GetWord())[0]);
	temp->GetBST()->Insert(node);
	WordCnt++;
}

WordNode *	AlphabetBST::Search(char * word)
{
	WordNode * node;
	node = Search(word[0])->GetBST()->Search(word);
	return node;
}

WordNode * AlphabetBST::Delete(WordNode * word)
{

	return Search(word->GetWord()[0])->GetBST()->Delete(word->GetWord());

}

bool	AlphabetBST::IsFull()
{
	if (WordCnt == 100)return 1;
	else return 0;
}

bool	AlphabetBST::IsEmpty()
{
	if (WordCnt == 0)return 1;
	else return 0;
}
void	AlphabetBST::R_Preorder(AlphabetNode * node)
{
	if (node) {
		node->GetBST()->Print("R_PRE");
		R_Preorder(node->GetLeft());
		R_Preorder(node->GetRight());
	}
}

void	AlphabetBST::R_Inorder(AlphabetNode * node)
{
	if (node) {
		R_Inorder(node->GetLeft());
		node->GetBST()->Print("R_IN");
		R_Inorder(node->GetRight());
	}
}

void	AlphabetBST::R_Postorder(AlphabetNode * node)
{
	if (node) {
		R_Postorder(node->GetLeft());
		R_Postorder(node->GetRight());
		node->GetBST()->Print("R_POST");
	}
}

void	AlphabetBST::I_Preorder()	// Preorder traversal
{
	AlphabetNode * p = root;
	Stack stack;
	while (1) {
		while (p) {
			if (p->GetRight())stack.Push(p->GetRight());
			p->GetBST()->Print("I_PRE");
			p = p->GetLeft();
		}
		if (!stack.pHead)return;
		p = stack.Pop();
	}
}

void	AlphabetBST::I_Inorder()
{
	AlphabetNode * p = root;
	Stack stack;
	while (1) {
		while (p) {
			stack.Push(p);
			p = p->GetLeft();
		}
		if (!stack.pHead)return;
		p = stack.Pop();
		p->GetBST()->Print("I_IN");
		p = p->GetRight();
	}
}

void	AlphabetBST::I_Postorder()
{
	AlphabetNode * p = root;
	Stack stack;
	while (1) {
		while (p) {
			if (p->GetRight())stack.Push(p->GetRight());
			stack.Push(p);
			p = p->GetLeft();
		}
		if (stack.IsEmpty())return;
		p = stack.Pop();
		if (p->GetRight() == stack.Top() && p->GetRight()) {
			stack.Pop();
			stack.Push(p);
			p = p->GetRight();
		}
		else {
			p->GetBST()->Print("I_POST");
			p = 0;
		}
	}
}

void	AlphabetBST::I_LEVEL()
{
	Queue queue;
	AlphabetNode * p = root;
		while (p) {
			if (p->GetLeft())queue.Push(p->GetLeft());
			if (p->GetRight())queue.Push(p->GetRight());
			p->GetBST()->Print("I_LEVEL");
			p = queue.Pop();
		}
}
