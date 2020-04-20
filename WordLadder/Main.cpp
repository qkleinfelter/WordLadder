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
		return 0;
	}
	string lexicon = argv[1]; // File location to use as our lexicon
	string firstWord = argv[2]; // Starting word for the ladder
	string lastWord = argv[3]; // Ending word for the ladder
	if (firstWord.length() != lastWord.length())
	{
		cout << "First and last word must be of the same length" << endl;
		return 0;
	}
	WordLadder wordLadder(lexicon, firstWord.length()); // Initialize the ladder
	toUpper(firstWord); // Convert the first word to uppercase
	toUpper(lastWord); // Convert the last word to uppercase
	vector<string> minLadder = wordLadder.getMinLadder(firstWord, lastWord); // Get the min ladder from the first word to the last word
	wordLadder.displayResult(minLadder); // Display the correctly formatted result
}