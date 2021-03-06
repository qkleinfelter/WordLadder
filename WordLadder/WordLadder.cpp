/*
	File: WordLadder.cpp - Word Ladder implementation
	c.f.: WordLadder.h

	This class implements the Word Ladder as
	declared in WordLadder.h. A word ladder is defined in
	the header comment located in that file.

	Author: Quinn Kleinfelter
	Class: EECS 2510-001 Non Linear Data Structures Spring 2020
	Instructor: Dr. Thomas
	Last Edited: 4/24/20
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
	// This function takes in a starting and ending word
	// both of which must be the same length as the length
	// that was passed into the word ladder construction.
	// Then, this method will ensure both words exist within
	// the lexicon, and run a breadth-first search algorithm
	// to find the shortest word ladder (each step having a 
	// hamming distance of 1), from the start word to the end word
	// eventually returning a vector<string> containing the finished ladder

	vector<string> ladder; // Empty vector of strings to hold our ladder

	if (!isWord(start) || !isWord(end) || start == end)
	{
		// If either the start word, or the end word
		// don't exist in our lexicon (i.e. they aren't words)
		// then we can't make a word ladder, so simply
		// return our empty ladder

		// Similarly, if the start word is exactly the same
		// as the end word, we don't need to bother doing any more
		// work and can simply return an empty ladder
		return ladder;
	}

	vector<string> wordsSeen;		// Vector of strings to hold all the words we've seen
	vector<string> predecessors;	// Vector of strings to hold the predecessors of each word we've seen
	list<string> queue;				// List of strings to use as our queue for BFS

	queue.push_back(start);		// Our queue needs to start with just the starting word for the ladder
	wordsSeen.push_back(start);	// And, we've seen the starting word so add it there as well
	predecessors.push_back(""); // Since our starting word has no predecessor, put an empty string in that place in the predecessor vector

	while (!queue.empty())
	{
		// Loop while we still have things inside our queue

		string QFront = queue.front(); // Keep track of the front item of the queue
		queue.pop_front();			   // and pop it off
		
		set<string> neighbors = getNeighbors(QFront); // Get all of the neighbors of our first item in the queue

		for (const string& s : neighbors)
		{
			// For each string s in neighbors, i.e. For each neighbor s

			if (findInVector(wordsSeen, s) == -1)
			{
				// If we haven't seen s yet, check if it is the end word
				// of the ladder
				if (s == end)
				{
					// If s is the final word in the ladder,
					wordsSeen.push_back(s);			// Push it onto the back of words seen
					predecessors.push_back(QFront); // and push the front item from the queue into predecessors

					int index = findInVector(wordsSeen, s); // Figure out what index s occupies in words seen
					string prevWord = predecessors[index];  // Get the previous word by accessing s's location in predecessors (always QFront here)
					ladder.push_back(s);				   // and push s onto the back of our ladder vector

					while (prevWord != start)
					{
						// While the previous word isn't our starting word
						// we need to loop through going backwards through our lists

						ladder.insert(ladder.begin(), prevWord);  // Put the previous word onto the start of our ladder (initially, our ladder will be prevWord -> s)
						index = findInVector(wordsSeen, prevWord);// update our index variable to be the location of our previous word in words seen
						prevWord = predecessors[index];			  // Then, find the predecessor of that word and make it the prevWord
					}
					// Finally, our ladder will contain everything following start up
					// through the end, so we just need to insert the starting word
					// at the beginning of the ladder
					ladder.insert(ladder.begin(), start); 
					return ladder; // and return our finished ladder
				}
				else
				{
					// Otherwise, if s wasn't our last word in the ladder
					wordsSeen.push_back(s);			// Push s onto the end of words seen
					predecessors.push_back(QFront); // and push QFront onto the end of predecessors

					queue.push_back(s);				// then, add s to the back of the queue
				}
			}
		}
	}
	// Return the (empty) ladder - only hit this if both words exist 
	// in the dictionary, but we can't find a ladder between them
	return ladder; 
}

int WordLadder::getWordCount()
{
	// This method simply returns the total number of words in the lexicon
	// It is not used at all in the BFS implementation but was used
	// in debugging

	// All we need to do is leverage the vector's size method
	// to return how many words we have in the lexicon
	return lexicon.size();
}

void WordLadder::displayResult(vector<string> sequence)
{
	// This method takes in a word ladder (sequence),
	// held in a vector of strings, and displays the appropriate output 

	if (sequence.empty())
	{
		// If we have an empty sequence then we need to let the
		// user know that no word ladder exists with this dictionary
		// between the two words, in this EXACT format
		cout << "Word Ladder is empty - No Solution" << endl;
		return;
	}

	if (!isWordLadder(sequence))
	{
		// Ensure that what is passed into displayResult is
		// actually a word ladder
		// Based on current usage of this program this should never run,
		// but we keep it here just in case
		cout << "Invalid word ladder passed to display result" << endl;
		return;
	}
	// Output the beginning of the text as specified in the document
	// Including the number of steps we took to get there, 
	// which is always 1 less than the total size of the sequence
	cout << "A Shortest Word Ladder (" << sequence.size() - 1 << " steps) is: ";

	for (vector<string>::iterator i = sequence.begin(); i != sequence.end(); i++)
	{
		// Loop through all of the items in the sequence
		// starting off our iterator at sequence.begin(), 
		// and increasing it by 1 each time until we get to sequence.end()

		cout << *i; // First, simply output the dereferenced item located at our iterator's current location

		// Here, we want to check if we just output the last item
		// if our iterator is at sequence.end() - 1, we know that 
		// we did just output the final item in the sequence.
		// Anytime that we haven't just output the last item we
		// want to print a space.
		if (i != sequence.end() - 1) cout << " ";
	}
	cout << endl; // Finally, after we have looped through our whole sequence, print out an endl
}

int WordLadder::findInVector(vector<string> vec, string str)
{
	// This method takes in a vector of strings, and a string
	// to search for within that vector, and returns
	// the location that the string is at in the vector,
	// or -1 if we are unable to find the string in it
	
	// Here we get an iterator of our vector by using the find 
	// method between the beginning and end of our vector
	// to look for the string
	vector<string>::iterator i = find(vec.begin(), vec.end(), str);
	
	// Then, if the iterator is not located at the end
	// of the vector, we can return the distance between
	// i and the beginning of the vector (i - vec.begin())
	// which is the index the string is located at
	// Otherwise, return -1 because i is only located at vec.end()
	// after using find if we were unable to find the string
	return i != vec.end() ? i - vec.begin() : -1;
}

bool WordLadder::isWord(string str)
{
	// This method takes in a string, and determines
	// if it is a word by checking if it is located in our dictionary

	// First off, use the set's built in find function on the lexicon
	// with the string we are looking for passed in, this returns
	// an iterator of a set of strings
	set<string>::iterator it = lexicon.find(str);

	// If our iterator is located at lexicon.end()
	// then we know we were unable to find our string
	// so it must not be a word, thus return false

	// Otherwise, it exists, and we don't care where it
	// is located so return true

	return !(it == lexicon.end());
}

bool WordLadder::isWordLadder(vector<string> sequence)
{
	// This method takes in a vector of strings (sequence)
	// and determines if it constitutes a word ladder
	// defined as successive words having a hamming distance of 1

	// If we have less than 2 words in our sequence
	// Then by definition we cannot have a word ladder - from (https://en.wikipedia.org/wiki/Word_ladder)
	if (sequence.size() < 2) return false;

	for (vector<string>::iterator i = sequence.begin(); i != sequence.end() - 1; i++)
	{
		// Here we get an iterator, starting at the beginning of our sequence
		// and we loop through until we reach the second to last item
		// in the word ladder (located at sequence.end() -1)
		
		// Then for each word, we get the hamming distance between it (dereferenced iterator)
		// and the next word in the list (dereferenced iterator + 1)
		// Then, if our hamming distance is not exactly 1,
		// we return false because we don't have a word ladder
		if (getHammingDistance(*i, *(i+1)) != 1) return false;
	}

	// If we make it to this statement, we must have a word ladder
	// so return true
	return true;
}

set<string> WordLadder::getNeighbors(string word)
{
	// This method takes in a string
	// and returns a set of strings which contains
	// all of its neighbors in our lexicon
	set<string> neighbors; // Empty set of strings to store the neighbors

	// Check if the string exists in our dictionary before we bother looking for neighbors
	// and if its not in the dictionary, return the empty set
	if (!isWord(word)) return neighbors;

	for (const string& dictionaryWord : lexicon)
	{
		// Loop through a reference to every string in our dictionary
		// And check the hamming distance between our word
		// and the dictionaryWord
		// If the hamming distance is 1, then we consider the dictionary word a neighbor
		// so add it to our set
		if (getHammingDistance(word, dictionaryWord) == 1)
		{
			neighbors.insert(dictionaryWord);
		}
	}
	// Once we've looped through the dictionary
	// we can return our set of neighbors
	return neighbors;
}

int WordLadder::getHammingDistance(string str1, string str2)
{
	// This method takes 2 strings, 
	// and calculates their hamming distance
	// See https://en.wikipedia.org/wiki/Hamming_distance for more

	// If the length of the 2 strings isn't the same
	// then they don't have a hamming distance so 
	// return -1
	if (str1.length() != str2.length()) return -1;

	int hammingDistance = 0; // Int to keep track of our hamming distance
	
	for (int i = 0; i < str1.length(); i++)
	{
		// Loop through every character in the strings
		// We could have used either strings length for 
		// our looping condition since they are the same length,

		// Check if the character at the current position
		// is the same in both strings,
		// if it isn't the same, increment the hamming distance
		if (str1[i] != str2[i])
			hammingDistance++;
	}

	// Once we've looped through the strings, return the hamming distance
	return hammingDistance;
}
