#include "WordBST.h"
#include "Queue.h"
#include<cstring>
#include<iostream>
#include<fstream>
using namespace std;
WordBST::WordBST()
{
	root = '\0';
}


WordBST::~WordBST()
{
	/* You must fill here */
	Queue queue;
	if (!root)return;
	WordNode* p = root, *pp = 0;
	while (p) {
		if(p->GetLeft())queue.Push(p->GetLeft());
		if(p->GetRight())queue.Push(p->GetRight());
		delete p;
		p = queue.Pop();
	}
}



void		WordBST::Insert(WordNode * node)			// LOAD, MOVE
{
	WordNode* p = root, *pp = 0;
	int  cmp;
	if (!root) {
		root = node;
		return;
	}
	while (p) {
		cmp = strcmp(node->GetWord(), p->GetWord());
		if (cmp < 0) {
			pp = p;
			p = p->GetLeft();
		}
		else if (cmp > 0) {
			pp = p;
			p = p->GetRight();
		}
		else {
			delete node;
			return;
		}
	}
	if (strcmp(node->GetWord(), pp->GetWord()) < 0)pp->SetLeft(node);
	else pp->SetRight(node);
}
WordNode *	WordBST::Delete(char * word)				// TEST
{
	WordNode* p = root, *pp = 0;
	int cmp;
	if (!root)return 0;
	while (p) {
		cmp = strcmp(word, p->GetWord());
		
		if (strcmp(word, p->GetWord()) < 0) {
			pp = p;
			p = p->GetLeft();
		}
		else if (strcmp(word, p->GetWord()) > 0) {
			pp = p;
			p = p->GetRight();
		}
		else break;
	}
	if (!p)return 0;
	WordNode *prev = 0, *prevprev = 0;
	if(p->GetLeft()){
		prev = p->GetLeft();
		prevprev = p;
		while (prev->GetRight()) {
			prevprev = prev;
			prev = prev->GetRight();
		}
		if(prevprev == p)prevprev->SetLeft(0);
		else prevprev->SetRight(0);
		prev->SetLeft(p->GetLeft());
		prev->SetRight(p->GetRight());
	}
	else if(p->GetRight()){
		prev = p->GetRight();
		prevprev = p;
		while (prev->GetLeft()) {
			prevprev = prev;
			prev = prev->GetLeft();
		}
		if (prevprev == p)prevprev->SetRight(0);
		else prevprev->SetLeft(0);
		prev->SetLeft(p->GetLeft());
		prev->SetRight(p->GetRight());
	}
	if (pp) {
		if (p == pp->GetLeft())pp->SetLeft(prev);
		else pp->SetRight(prev);
	}


	return p;
}
WordNode *	WordBST::Search(char * word)				// ADD, TEST, SEARCH, UPDATE
{
	WordNode* p = root;
	if (!root)return 0;
	while (p) {
		if (strcmp(word, p->GetWord()) < 0)p = p->GetLeft();
		else if (strcmp(word, p->GetWord()) > 0)p = p->GetRight();
		else return p;
	}
	return 0;
}
bool		WordBST::Print(char * order)							// PRINT
{
		if		(!strcmp(order, "R_PRE"))	R_Preorder(root);
		else if (!strcmp(order, "R_IN"))	R_Inorder(root);
		else if (!strcmp(order, "R_POST"))	R_Postorder(root);
		else if (!strcmp(order, "I_PRE"))	I_Preorder();
		else if (!strcmp(order, "I_IN"))	I_Inorder();
		else if (!strcmp(order, "I_POST"))	I_Postorder();
		else if (!strcmp(order, "I_LEVEL")) I_LEVEL();
		else return 0;
		return 1;
}
bool		WordBST::Save()								// SAVE
{
	Queue queue;
	WordNode * p = root;
	Stack stack;
	ofstream fout;
	if (!root)return 0;
	fout.open("memorizing_word.txt", ios_base::app);
	if (!fout.is_open())return 0;
	while (1) {
		while (p) {
			if (p->GetRight())stack.Push(p->GetRight());
			fout << p->GetWord() << "\t" << p->GetMean() << endl;
			p = p->GetLeft();
		}
		if (!stack.pHead)break;
		p = stack.Pop();
	}
	fout.close();
	return 1;
}

void		WordBST::R_Preorder(WordNode* node)
{
	ofstream fout;
	fout.open("log.txt", ios_base::app);
	if (!fout.is_open())return;
	if (node) {
		fout << node->GetWord() << "\t" << node->GetMean() << endl;
		R_Preorder(node->GetLeft());
		R_Preorder(node->GetRight());
	}
	fout.close();
}

void		WordBST::R_Inorder(WordNode * node)
{
	ofstream fout;
	fout.open("log.txt", ios_base::app);
	if (!fout.is_open())return;
	if (node) {
		R_Inorder(node->GetLeft());
		fout << node->GetWord() << "\t" << node->GetMean() << endl;
		R_Inorder(node->GetRight());
	}
	fout.close();
}

void		WordBST::R_Postorder(WordNode * node)
{
	ofstream fout;
	fout.open("log.txt", ios_base::app);
	if (!fout.is_open())return;
	if (node) {
		R_Postorder(node->GetLeft());
		R_Postorder(node->GetRight());
		fout << node->GetWord() << "\t" << node->GetMean() << endl;
	}
	fout.close();
}

void		WordBST::I_Preorder()							//preorder traversal
{
	WordNode * p = root;
	Stack stack;
	ofstream fout;
	fout.open("log.txt", ios_base::app);
	if (!fout.is_open())return;
	while(1){
		while (p) {
			if (p->GetRight())stack.Push(p->GetRight());
			fout << p->GetWord() << "\t" << p->GetMean() << endl;
			p = p->GetLeft();
		}
		if (!stack.pHead)break;;
		p = stack.Pop();
	}
	fout.close();
}

void		WordBST::I_Inorder()
{
	WordNode * p = root;
	Stack stack;
	ofstream fout;
	fout.open("log.txt", ios_base::app);
	if (!fout.is_open())return;
	while(1){
		while (p) {
			stack.Push(p);
			p = p->GetLeft();
		}
		if (!stack.pHead)break;;
		p = stack.Pop();
		fout << p->GetWord() << "\t" << p->GetMean() << endl;
		p = p->GetRight();
	}
	fout.close();
}

void		WordBST::I_Postorder()
{
	WordNode * p = root;
	Stack stack;
	ofstream fout;
	fout.open("log.txt", ios_base::app);
	if (!fout.is_open())return;
	while(1) {
		while (p) {
			if (p->GetRight())stack.Push(p->GetRight());
			stack.Push(p);
			p = p->GetLeft();
		}
		if (!stack.pHead)break;
		p = stack.Pop();
		if (p->GetRight() == stack.Top() && p->GetRight()) {
			stack.Pop();
			stack.Push(p);
			p = p->GetRight();
		}
		else {
			fout << p->GetWord() << "\t" << p->GetMean() << endl;
			p = 0;
		}
	}
	fout.close();
}

void		WordBST::I_LEVEL()
{
	WordNode * p = root;
	ofstream fout;
	fout.open("log.txt", ios_base::app);
	if (!fout.is_open())return;
	Queue queue;
	while (p) {
		if (p->GetLeft())queue.Push(p->GetLeft());
		if (p->GetRight())queue.Push(p->GetRight());
		fout << p->GetWord() << "\t" << p->GetMean() << endl;
		p = queue.Pop();
	}
	fout.close();
}
