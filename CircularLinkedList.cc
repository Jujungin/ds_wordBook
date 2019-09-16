#include "CircularLinkedList.h"
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

CircularLinkedList::CircularLinkedList()
{
	pHead = '\0';
	pTail = '\0';
}


CircularLinkedList::~CircularLinkedList()
{
	/* You must fill here */
	WordNode* p = pHead, *pp = 0;
	if (!pHead)return;
	pHead->SetNext(0);
	if (pHead == pTail) {
		delete pHead;
		return;
	}
	do {
		pp = p;
		p = p->GetNext();
		delete pp;
	} while (p != pHead);
}

void		CircularLinkedList::Insert(WordNode * node)			// LOAD, TEST
{
	WordNode* p = pHead;
	if (!pHead) {
		pHead = node;
		pTail = node;
		node->SetNext(node);
	}
	else {
		pTail->SetNext(node);
		pTail = node;
		pTail->SetNext(pHead);
	}
}
WordNode *	CircularLinkedList::Search(char * word)				// SEARCH, UPDATE
{
	WordNode* p = pHead;
	while (p) {
		if (strcmp(word, p->GetWord()) == 0)return p;
		p = p->GetNext();
	}
	return 0;
}
bool		CircularLinkedList::Print()							// 
{
	WordNode* p = pHead;
	ofstream fout;
	if (!pHead)return 0;
	fout.open("log.txt", ios_base::app);
	fout << "======== PRINT ========" << endl;
	do {
		fout << p->GetWord() << "\t" << p->GetMean() << endl;
		p = p->GetNext();
	} while (p != pHead);
	fout.close();
	return 1;
}
bool		CircularLinkedList::Save()								// SAVE
{
	WordNode * p = pHead;
	ofstream fout;
	fout.open("memorized_word.txt", ios_base::out);
	if (!fout.is_open() || !p)return 0;
	do {
		fout << p->GetWord() << "\t" << p->GetMean() << endl;
		p = p->GetNext();
	}while (p != pHead);
	fout.close();
	return 1;
}

WordNode *	CircularLinkedList::Delete(WordNode * node)
{
	WordNode *p = pHead, *pp = 0;
	while (p != node) {
		pp = p;
		p = p->GetNext();
	}
	pp->SetNext(p->GetNext());
	return p;
}

bool	CircularLinkedList::IsEmpty()
{
	if (pHead)return 0;
	else return 1;
}
