#include "WordLadder.h"
#include <fstream>
#include <iostream>
#include <list>

using namespace std;

WordLadder::WordLadder(string lexiconFileName, int len)
{
	ifstream lexiconFile;
	lexiconFile.open(lexiconFileName);
	if (lexiconFile.fail())
	{
		cout << "Couldn't open lexicon file" << endl;
		exit(0);
	}
	string word;

	while (lexiconFile >> word)
	{
		if (word.length() == len) lexicon.insert(word);
	}
}

vector<string> WordLadder::getMinLadder(string start, string end)
{
	vector<string> ladder;
	vector<string> wordsSeen;
	vector<string> predecessors;
	list<string> queue;

	queue.push_back(start);
	wordsSeen.push_back(start);
	predecessors.push_back("");

	while (!queue.empty())
	{
		string QFront = queue.front;
		queue.pop_front();
		
		set<string> neighbors = getNeighbors(QFront);
		for (const string& s : neighbors)
		{
			if (findInVector(wordsSeen, s) == -1)
			{
				if (s == end)
				{
					wordsSeen.push_back(s);
					predecessors.push_back(QFront);

					int sLoc = findInVector(wordsSeen, s);
					string prevWord = predecessors[sLoc];
					ladder.push_back(s);

					while (prevWord != start)
					{
						ladder.insert(ladder.begin(), prevWord);
						sLoc = findInVector(wordsSeen, prevWord);
						prevWord = predecessors[sLoc];
					}
					ladder.insert(ladder.begin(), start);
					return ladder;
				}
				else
				{
					wordsSeen.push_back(s);
					predecessors.push_back(QFront);

					queue.push_back(s);
				}
			}
		}
	}

	return ladder;
}

int WordLadder::getWordCount()
{
	return lexicon.size();
}

void WordLadder::displayResult(vector<string> sequence)
{
}

int WordLadder::findInVector(vector<string> vec, string str)
{
	vector<string>::iterator i = find(vec.begin(), vec.end(), str);
	return i != vec.end() ? i - vec.begin() : -1;
}

bool WordLadder::isWord(string str)
{
	set<string>::iterator it = lexicon.find(str);
	if (it == lexicon.end()) return false;
	return true;
}

bool WordLadder::isWordLadder(vector<string> sequence)
{
	if (sequence.size() < 2) return false;

	for (vector<string>::iterator i = sequence.begin(); i != sequence.end(); i++)
	{
		if (getHammingDistance(*i, *i++) != 1) return false;
	}

	return true;
}

set<string> WordLadder::getNeighbors(string word)
{
	set<string> neighbors;
	for (const string& dictionaryWord : lexicon)
	{
		if (getHammingDistance(word, dictionaryWord) == 1)
		{
			neighbors.insert(dictionaryWord);
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
