/*
	Author: Quinn Kleinfelter
	Class: EECS 2510-001 Non Linear Data Structures Spring 2020
	Instructor: Dr. Thomas
	Last Edited: 4/24/20

	Main File used to determine the shortest word ladder
	from a user entered start word to a user entered 
	end word, based on a user defined dictionary (lexicon).
*/

#include "WordLadder.h"
#include <iostream>

using namespace std;

void toUpper(string& s)
{
	// Helper function to convert a string to uppercase, in place
	// Takes in a reference to the string to convert
	for (int i = 0; i < s.length(); i++)
		s[i] = toupper(s[i]); // Converts each character of the string to uppercase
}

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		// If we don't have exactly 4 arguments error out
		cout << "Incorrect number of arguments" << endl;
		cout << "Correct usage: WordLadder.exe lexiconFileName startingWord endingWord" << endl;
		return 0;
	}

	string lexicon = argv[1]; // File location to use as our lexicon
	string firstWord = argv[2]; // Starting word for the ladder
	string lastWord = argv[3]; // Ending word for the ladder

	if (firstWord.length() != lastWord.length())
	{
		// We can only determine a word ladder if our two words
		// have the same length
		cout << "First and last word must be of the same length" << endl;
		return 0;
	}

	WordLadder* wl = new WordLadder(lexicon, firstWord.length()); // Initialize our word ladder
	toUpper(firstWord); // Convert the first word to upper case in place
	toUpper(lastWord);  // Convert the last word to upper case in place
	vector<string> minLadder = wl->getMinLadder(firstWord, lastWord); // Get the minimum word ladder from the first word to the last word
	wl->displayResult(minLadder); // Display the correctly formatted result

	return 0;
}