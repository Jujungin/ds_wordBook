#include "Manager.h"
#include <fstream>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <ctype.h>
#include <climits>

using namespace std;
Manager::Manager()
{
	cll = new CircularLinkedList;
	bst = new AlphabetBST;
	queue = new Queue;
}


Manager::~Manager()
{
	delete cll;
	delete bst;
	delete queue;
}

void Manager::run(const char * command)
{
	ifstream fin;							// file object
	fin.open(command, ios_base::in);		// open file for read
	if (!fin.is_open())return;				// if opening file is fail, exit program
	char com_str[150];						// char array to be saved string from file
	char menu[7];							// menu string		ex) LOAD, ADD, SAVE etc.
	char num[4];							// number to be moved to MEMORIZING from TO_MEMORIZE at MOVE
	unsigned char* com_copy;				// for coping hangul
	unsigned int hangul = 0, temp[3] = {};	// for coping hangul
	bool error;								// check error
	int i;									// for statement variable
	int index[3];							// index of com_str for each distinguished string area ex) MOVE/50, PRINT/MEMORIZING/R_IN
	while (!fin.eof()) {					// if file counter is eof, exit program
		error = true;						// initialize error
		fin.getline(com_str, 150, '\n');	//  read file
		/* set index[0] */
		for (index[0] = 0; index[0] < 7; index[0]++)
			if (com_str[index[0]] == ' ' || com_str[index[0]] == '\r')break;
		copy(com_str, &com_str[index[0]], menu);
		menu[index[0]] = 0;
		/* check whether character is upper or not */
		for(i = 0; i < index[0];i++){
			if(!isupper(com_str[i])){
				error = false;
				break;
			}
		}
		if (!error) {
			fin.clear();
			if(com_str[strlen(com_str) - 1] != '\r')
				fin.ignore(INT_MAX, '\n');
			continue;
		}
		if (!strcmp(menu, "LOAD")) {
			if (com_str[index[0]] != '\r')LOG(1, 0);
			else LOG(1, LOAD());
		}
		else if (!strcmp(menu, "ADD")) {
			if (com_str[index[0]] != '\r')LOG(2, 0);
			else LOG(2, ADD());
		}
		else if (!strcmp(menu, "MOVE")) {
			if (com_str[index[0]] == '\r') {
				error = false;
			}
			else {
				for (index[1] = index[0] + 1; index[1] - index[0] - 1 < 3 && com_str[index[1]] != '\0'; index[1] ++) {
					if (com_str[index[1]] < '0' || com_str[index[1]] > '9') {
						break;
					}
				}
				if (com_str[index[1]] != '\r')error = false;
			}
			if (error) {
				copy(&com_str[index[0] + 1], &com_str[index[1]], num);
				num[index[1] - index[0] - 1] = 0;
				m_Move = atoi(num);
				if (m_Move >= 1 && m_Move <= 100) {
					LOG(3, MOVE());
				}
				else error = false;
			}

			if(error == false) {
				LOG(3, 0);
			}
		}
		else if (!strcmp(menu, "SAVE")) {
			if (com_str[index[0]] != '\r') {
				error = false;
				LOG(4, 0);
			}
			else LOG(4, SAVE());
		}
		else if (!strcmp(menu, "TEST")) {
			if (com_str[index[0]] != ' ')error = false;
			else {
				for (index[1] = index[0] + 1; index[1] - index[0] - 1 < 50; index[1]++)
					if (!isalpha(com_str[index[1]]))break;

				if (com_str[index[1]] != ' ')error = false;
			}
			if (error) {
				copy(&com_str[index[0] + 1], &com_str[index[1]], m_Word);
				m_Word[index[1] - index[0] - 1] = 0;/*
				for (int i = 0; ; i++) {
					if (isupper(m_Word[i])){
						m_Word[i] = tolower(m_Word[i]);
					}
				}*/
				for(i = 0; m_Word[i] != 0; i++){
					m_Word[i] = tolower(m_Word[i]);
				}
				for(index[2] = index[1] + 1; index[2] - index[1] - 1 < 50 && com_str[index[2]] != '\r'; index[2]++){
					if(((index[2] - index[1]) % 3) == 1){
						if(com_str[index[2]] < -32 || com_str[index[2]] > -17){
							error = false;
							break;
						}
					}
					else {
						if(com_str[index[2]] < -128 || com_str[index[2]] > -65){
							error = false;
							break;
						}
					}
				}
				if (com_str[index[2]] != '\r')error = false;
				if(error && ((index[2] - index[1] - 1) % 3) == 0){
					com_copy = new unsigned char[index[2] - index[1]];
					copy(&com_str[index[1] + 1], &com_str[index[2]], com_copy);
					com_copy[index[2] - index[1] - 1] = '\0';
					for(i = 0; i < index[2] - index[1] - 1;i += 3){
						temp[0] = temp[0] ^ (com_copy[i] % 16);
						temp[1] = temp[1] ^ (com_copy[i + 1] % 64);
						temp[2] = temp[2] ^ (com_copy[i + 2] % 64);
						hangul = (hangul ^ temp[0]) << 12;
						hangul = hangul ^ (temp[1] << 6);
						hangul = hangul ^ temp[2];
						if (hangul < 0xAC00 || hangul > 0xD7FB) {
							error = false;
							break;
						}
						hangul = 0;
						temp[0] = 0;
						temp[1] = 0;
						temp[2] = 0;
					}
				}
				if (error) {
					copy(&com_str[index[1] + 1], &com_str[index[2]], m_Mean);
					m_Mean[index[2] - index[1] - 1] = 0;
					LOG(5, TEST());
				}
			}
			if (!error){
				hangul = 0;
				temp[0] = 0;
				temp[1] = 0;
				temp[2] = 0;
				LOG(5, 0);
			}
		}
		else if (!strcmp(menu, "SEARCH")) {
			if (com_str[index[0]] != ' ')error = false;
			else {
				for (index[1] = index[0] + 1; index[1] - index[0] - 1 < 50; index[1]++)
					if (!isalpha(com_str[index[1]]))break;
				if (com_str[index[1]] != '\r')error = false;
			}
			if (error) {
				copy(&com_str[index[0] + 1], &com_str[index[1]], m_Word);
				m_Word[index[1] - index[0] - 1] = 0;
				for (i = 0; m_Word[i] != '\0'; i++) {
					if (isupper(m_Word[i]))tolower(m_Word[i]);
				}
				LOG(6, SEARCH());
			}
			else LOG(6, 0);
		}
		else if (!strcmp(menu, "PRINT")) {
			if (com_str[index[0]] != ' ')error = false;
			else {
				for (index[1] = index[0] + 1; index[1] - index[0] - 1 < 13; index[1]++) {
					if ((com_str[index[1]] < 'a' || com_str[index[1]] > 'z') && (com_str[index[1]] < 'A' || com_str[index[1]] > 'Z') && com_str[index[1]] != '_') {
						break;
					}
				}
			}
			if (error) {
				copy(&com_str[index[0] + 1], &com_str[index[1]], m_Print);
				m_Print[index[1] - index[0] - 1] = 0;
				if (!strcmp("MEMORIZING", m_Print)) {
					if (com_str[index[1]] != ' ')error = false;
					else {
						for (index[2] = index[1] + 1; index[2] - index[1] - 1 < 9; index[2]++) {
							if ((com_str[index[2]] < 'a' || com_str[index[2]] > 'z') && (com_str[index[2]] < 'A' || com_str[index[2]] > 'Z') && com_str[index[2]] != '_') {
								break;
							}
						}
						if (com_str[index[2]] != '\r')error = false;
					}
					if (error) {
						copy(&com_str[index[1] + 1], &com_str[index[2]], m_Print2);
						m_Print2[index[2] - index[1] - 1] = 0;
					}
				}
			}
			if(!error) {
				LOG(7, 0);
			}
			else LOG(7, PRINT());
		}
		else if (!strcmp(menu, "UPDATE")) {
			if (com_str[index[0]] != ' ')error = false;
			else {
				for (index[1] = index[0] + 1; index[1] - index[0] - 1 < 50; index[1]++) {
					if ((com_str[index[1]] < 'a' || com_str[index[1]] > 'z') && (com_str[index[1]] < 'A' || com_str[index[1]] > 'Z')) {
						break;
					}
				}
				if (com_str[index[1]] != ' ')error = false;
			}
			if (error) {
				copy(&com_str[index[0] + 1], &com_str[index[1]], m_Word);
				m_Word[index[1] - index[0] - 1] = 0;
				for (i = 0; m_Word[i] != '\0'; i++) {
					if (isupper(m_Word[i]))tolower(m_Word[i]);
				}
				for(index[2] = index[1] + 1; index[2] - index[1] - 1 < 50 && com_str[index[2]] != '\r'; index[2]++){
					if(((index[2] - index[1]) % 3) == 1){
						if(com_str[index[2]] < -32 || com_str[index[2]] > -17){
							error = false;
							break;
						}
					}
					else {
						if(com_str[index[2]] < -128 || com_str[index[2]] > -65){
							error = false;
							break;
						}
					}
				}
				if (com_str[index[2]] != '\r')error = false;
				if(error && ((index[2] - index[1] - 1) % 3) == 0){
					com_copy = new unsigned char[index[2] - index[1]];
					copy(&com_str[index[1] + 1], &com_str[index[2]], com_copy);
					com_copy[index[2] - index[1] - 1] = '\0';
					for(i = 0; i < index[2] - index[1] - 1;i += 3){
						temp[0] = temp[0] ^ (com_copy[i] % 16);
						temp[1] = temp[1] ^ (com_copy[i + 1] % 64);
						temp[2] = temp[2] ^ (com_copy[i + 2] % 64);
						hangul = (hangul ^ temp[0]) << 12;
						hangul = hangul ^ (temp[1] << 6);
						hangul = hangul ^ temp[2];
						if (hangul < 0xAC00 || hangul > 0xD7FB) {
							error = false;
							break;
						}
						hangul = 0;
						temp[0] = 0;
						temp[1] = 0;
						temp[2] = 0;
					}
				}
				if (error) {
					copy(&com_str[index[1] + 1], &com_str[index[2]], m_Mean);
					m_Mean[index[2] - index[1] - 1] = 0;
				}
			}
			if (!error){

				hangul = 0;
				temp[0] = 0;
				temp[1] = 0;
				temp[2] = 0;
				LOG(8, 0);
			}
			else LOG(8, UPDATE());
		}
		else if (!strcmp(menu, "EXIT")) {
			return;
		}
		else {
			cout << "Fatal error" << endl;
			return;
		}
		fin.clear();
		if(com_str[strlen(com_str) - 1] != '\r')
		fin.ignore(INT_MAX, '\n');
	}
	fin.close();
}

bool Manager::LOAD()
{
	// to_memorize_word.txt
	// memorizing_word.txt
	// memorized_word.txt
	if (!(queue->IsEmpty()))return 0;
	if (!(bst->IsEmpty()))return 0;
	if (!(cll->IsEmpty()))return 0;
	ifstream fin;
	char* str1 = 0;
	char* str2 = 0;
	WordNode* temp;
	char str[100];
	bool error = true;
	fin.open("to_memorize_word.txt", ios_base::in);
	if (!fin.is_open())error = false;
	while (!fin.eof()) {
		if (!(fin >> str))break;
		if (str2)
			if (!strcmp(str, str2))break;
		temp = new WordNode;
		if (str1)temp->SetWord(str1);
		str1 = new char[strlen(str) + 1];
		strcpy(str1, str);
		temp->SetWord(str1);
		fin.clear();
		fin >> str;
		str2 = new char[strlen(str) + 1];
		strcpy(str2, str);
		temp->SetMean(str2);
		fin.clear();
		queue->Push(temp);
	}
	fin.close();
	fin.open("memorizing_word.txt", ios_base::in);
	if (!fin.is_open())error = false;
	while (!fin.eof()) {
		if (!(fin >> str))break;
		if (str2)
			if (!strcmp(str, str2))break;
		temp = new WordNode;
		if (str1)temp->SetWord(str1);
		str1 = new char[strlen(str) + 1];
		strcpy(str1, str);
		temp->SetWord(str1);
		fin.clear();
		fin >> str;
		str2 = new char[strlen(str) + 1];
		strcpy(str2, str);
		temp->SetMean(str2);
		fin.clear();
		bst->Insert(temp);
	}
	fin.close();
	fin.open("memorized_word.txt", ios_base::in);
	if (!fin.is_open())error = false;
	while (!fin.eof()) {
		if (!(fin >> str))break;
		if (str2)
			if (!strcmp(str, str2))break;
		temp = new WordNode;
		if (str1)temp->SetWord(str1);
		str1 = new char[strlen(str) + 1];
		strcpy(str1, str);
		temp->SetWord(str1);
		fin.clear();
		fin >> str;
		str2 = new char[strlen(str) + 1];
		strcpy(str2, str);
		temp->SetMean(str2);
		fin.clear();
		cll->Insert(temp);
	}
	fin.close();
	return error;
}
bool Manager::ADD()
{
	ifstream fin;
	char* str1 = 0;
	WordNode* temp;
	char str[100];
	fin.open("word.txt", ios_base::in);
	if (!fin.is_open())return 0;
	while (!fin.eof()) {
		if (!(fin >> str))break;
		if(str1)
			if (!strcmp(str, str1))break;
		temp = new WordNode;
		str1 = new char[strlen(str) + 1];
		strcpy(str1, str);
		strcpy(m_Word, str1);
		fin.clear();
		if (SEARCH()) {
			delete temp;
			delete str1;
			fin >> str;
			continue;
		}
		temp->SetWord(str1);
		fin >> str;
		str1 = new char[strlen(str) + 1];
		strcpy(str1, str);
		temp->SetMean(str1);
		queue->Push(temp);
		fin.clear();
	}
	fin.close();
	return 1;
}
bool Manager::MOVE()
{
	WordNode * temp;
	if(m_Move > queue->WordNumber())return 0;
	for (int i = 0; i < m_Move; i++) {
		if (!bst->IsFull()) {
			if (temp = queue->Pop())bst->Insert(temp);
			else return 0;
		}
		else return 0;
	}
	return 1;
}
bool Manager::SAVE()
{
	bool error = true;
	if (!queue->Save())	error = false;		// TO_MEMORIZE	save failed
	if (!bst->Save())	error = false;		// MEMORIZING	save failed
	if (!cll->Save())	error = false;		// MEMORIZED	save failed
	return error;
}
bool Manager::TEST()
{
	WordNode * node;
	if ((node = bst->Search(m_Word))) {
		if (!strcmp(m_Mean, node->GetMean())) {
			cll->Insert(bst->Delete(node));
			return 1;
		}
	}
	return 0;
}
bool Manager::SEARCH()
{
	WordNode * temp;
	ofstream fout;
	if (temp = queue->Search(m_Word));
	else if (temp = bst->Search(m_Word));
	else if (temp = cll->Search(m_Word));
	else return 0;
	strcpy(m_Word, temp->GetWord());
	strcpy(m_Mean, temp->GetMean());
	return 1;
}
bool Manager::PRINT()
{
	ofstream fout;
	fout.open("log.txt", ios_base::app);
	fout.close();

	if (!strcmp("TO_MEMORIZE", m_Print)) {		// PRINT TO_MEMORIZE
		if (!queue->Print())return 0;				// FAILED TO PRINT TO_MEMORIZE
	}
	else if (!strcmp("MEMORIZING", m_Print)) { 	// PRINT MEMORIZING
		if (!bst->Print(m_Print2))return 0;			//FAILED TO PRINT MEMORIZING
	}
	else if (!strcmp("MEMORIZED", m_Print)) {		// PRINT MEMORIZED
		if (!cll->Print())return 0;					//FAILED TO PRINT MEMORIZED
	}
	else return 0;								// INPUT ERROR

	return 1;
}
bool Manager::UPDATE()
{
	WordNode * node;
	if(node = queue->Search(m_Word)){}
	else if(node = cll->Search(m_Word)){}
	else if (node = bst->Search(m_Word)) {}
	else return 0;
	strcpy(m_search, node->GetMean());
	node->SetMean(m_Mean);
	return 1;
}

void Manager::LOG(const int FUNCTION, const bool result)
{
	ofstream fout;
	fout.open("log.txt", ios_base::app);
	if (!result) {
		fout << "======== ERROR ========" << endl
			<< FUNCTION << "00" << endl;
	}
	else
		switch (FUNCTION) {
		case 1:											// LOAD
			fout << "======== LOAD ========" << endl
				<< "Success" << endl;
			break;
		case 2:											// ADD
			fout << "======== ADD ========" << endl
				<< "Success" << endl;
			break;
		case 3:											// MOVE
			fout << "======== MOVE ========" << endl
				<< "Success" << endl;
			break;
		case 4:											// SAVE
			fout << "======== SAVE ========" << endl
				<< "Success" << endl;
			break;
		case 5:											// TEST
			fout << "======== TEST ========" << endl
				<< "Pass" << endl;
			break;
		case 6:											// SEARCH
			fout << "======== SEARCH ========" << endl
				<< m_Word << " " << m_Mean << endl;
			break;
		case 7:											// PRINT
			break;
		case 8:											// UPDATE
			fout << "======== UPDATE ========" << endl
				 << m_Word << " " << m_search << " -> " << m_Mean << endl;
			break;
		default:										// ERROR
			fout << "======== LOG ERROR ========" << endl;
			fout.close();
			return;
		}
	fout << "====================" << endl << endl;
	fout.close();
}

bool Manager::AlphabetCheck(bool& error, const int begin, const int end, const char * str)
{
	for (int i = begin; i < end && str[i] != '\0'; i++) {
		if (!isalpha(str[i]) && str[i] != '\r') {
			error = false;
			return 0;
		}
	}
	return 1;
}
