/*
	File: WordLadder.cpp - Word Ladder implementation
	c.f.: WordLadder.h

	This class implements the Word Ladder as
	declared in WordLadder.h. A word ladder is defined in
	the header comment located in that file.

	Author: Quinn Kleinfelter
	Class: EECS 2510-001 Non Linear Data Structures Spring 2020
	Instructor: Dr. Thomas
	Last Edited: 4/20/20
	Copyright: Copyright 2020 by Quinn Kleinfelter. All rights reserved.
*/

#include "WordLadder.h"
#include <fstream>
#include <iostream>
#include <list>

using namespace std;

WordLadder::WordLadder(string lexiconFileName, int len)
{
	// Constructor for our word ladder
	// Takes in a file name where our lexicon resides
	// And the length of words we are going to use
	// with our word ladder

	ifstream lexiconFile; // Input file stream variable to hold the lexicon
	lexiconFile.open(lexiconFileName); // Open up the lexicon file as passed in
	if (lexiconFile.fail())
	{
		// If we failed when opening the lexicon file
		// for whatever reason, we can't do anything else
		// so print out an error message and exit immediately
		cout << "Couldn't open lexicon file" << endl;
		exit(0);
	}

	string word; // String variable to hold words that we read in from the lexicon

	while (lexiconFile >> word)
	{
		// Loop through every word in the lexicon file
		// first placing them into our string variable
		// then checking if their length is equal to that
		// of the words we will be using in the ladder,
		// if it is equivalent, insert them into our lexicon 
		if (word.length() == len) lexicon.insert(word);
	}
}

vector<string> WordLadder::getMinLadder(string start, string end)
{
	vector<string> ladder;

	if (!isWord(start) || !isWord(end))
	{
		return ladder;
	}

	vector<string> wordsSeen;
	vector<string> predecessors;
	list<string> queue;

	queue.push_back(start);
	wordsSeen.push_back(start);
	predecessors.push_back("");

	while (!queue.empty())
	{
		string QFront = queue.front();
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
	if (sequence.empty())
	{
		cout << "Word Ladder is empty - No Solution" << endl;
		return;
	}
	cout << "A Shortest Word Ladder (" << sequence.size() - 1 << " steps) is: ";

	for (vector<string>::iterator i = sequence.begin(); i != sequence.end(); i++)
	{
		cout << *i;
		if (i - sequence.begin() != sequence.size() - 1) cout << " ";
	}
	cout << endl;
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
		if (getHammingDistance(*i, *(i+1)) != 1) return false;
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
