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

int WordLadder::findInVector(vector<string> vec, string str)
{
	for (vector<string>::iterator i = vec.begin(); i != vec.end(); i++)
	{
		if (*i == str)
		{
			return i - vec.begin();
		}
	}
	return -1;
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
	set<string> neighbors;
	for (set<string>::iterator i = lexicon.begin(); i != lexicon.end(); i++)
	{
		if (getHammingDistance(word, *i) == 1)
		{
			neighbors.insert(*i);
		}
	}
	return neighbors;
}

int WordLadder::getHammingDistance(string str1, string str2)
{
	if (str1.length() != str2.length()) return -1;
	int hammingDistance = 0;
	for (int i = 0; i < str1.length(); i++)
	{
		if (str1[i] != str2[i])
			hammingDistance++;
	}
	return hammingDistance;
}
