#include "WordLadder.h"
#include <fstream>
#include <iostream>

using namespace std;

WordLadder::WordLadder(string lexiconFileName, int len)
{
	ifstream lexiconFile;
	lexiconFile.open(lexiconFileName);
	if (lexiconFile.fail())
	{
		cout << "Couldn't open lexicon file" << endl;
		return;
	}
	while (!lexiconFile.eof())
	{
		string word;
		lexiconFile >> word;
		if (word.length() != len) continue;
		lexicon.insert(word);
	}
}

vector<string> WordLadder::getMinLadder(string start, string end)
{
	return vector<string>();
}

int WordLadder::getWordCount()
{
	return 0;
}

void WordLadder::displayResult(vector<string> sequence)
{
}

int WordLadder::findInVector(vector<string> vec, string)
{
	return 0;
}

bool WordLadder::isWord(string str)
{
	set<string>::iterator it = lexicon.find(str);
	if (it == lexicon.end()) return false;
	return true;
}

bool WordLadder::isWordLadder(vector<string> sequence)
{
	return false;
}

set<string> WordLadder::getNeighbors(string word)
{
	return set<string>();
}

int WordLadder::getHammingDistance(string str1, string str2)
{
	return 0;
}
