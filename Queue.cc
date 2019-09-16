#include "Queue.h"
#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;


Queue::Queue()
{
	pHead = '\0';
	pTail = '\0';
	WordCnt = 0;
}


Queue::~Queue()
{
	/* You must fill here */
	WordNode*p = pHead, *pp = 0;
	while (p) {
		pp = p;
		p = p->GetNext();
		if (p == pp)p = 0;
		delete pp;
	}
}

void		Queue::Push(WordNode * node)			// LOAD, ADD
{
	WordNode* temp = pTail;
	if (!pHead) {
		pHead = node;
		pTail = node;
	}
	else{
		pTail->SetNext(node);
		pTail = node;
	}
	WordCnt++;
}
WordNode *	Queue::Pop()							// MOVE
{
	WordNode* temp = pHead;
	if(IsEmpty())return 0;
	else {
		temp = pHead;
		pHead = pHead->GetNext();
		if (pHead == 0)pTail = 0;
		temp->SetNext(0);
		WordCnt--;
		return temp;
	}
	return 0;
}
WordNode *	Queue::Search(char * word)				// SEARCH, UPDATE
{
	WordNode* p = pHead;
	while (p) {
		if (strcmp(p->GetWord(), word) == 0)return p;
		p = p->GetNext();
	}
	return 0;
}
bool		Queue::Print()							// PRINT
{
	ofstream fout;
	WordNode* p = pHead;
	if (!pHead)return 0;
	else {
		fout.open("log.txt", ios_base::app);
		fout << "======== PRINT ========" << endl;
		while(p){
			fout << p->GetWord() << "\t" << p->GetMean() << endl;
			p = p->GetNext();
		}
		fout.close();
		return 1;
	}
}
bool		Queue::Save()							// SAVE
{
	ofstream fout;
	WordNode * p = pHead;
	fout.open("to_memorize_word.txt", ios_base::out);
	if (!p || !fout.is_open())return 0;
	while (p) {
		fout << p->GetWord() << '\t' << p->GetMean() << endl;
		p = p->GetNext();
	}
	fout.close();
	return 1;
}

bool		Queue::IsEmpty()
{
	if (pHead == 0)return 1;
	else return 0;
}

int			Queue::WordNumber()
{
	return WordCnt;
}
