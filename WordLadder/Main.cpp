#include "WordLadder.h"
#include <iostream>

using namespace std;

string toUpper(string& s)
{
	for (int i = 0; i < s.length(); i++)
		s[i] = toupper(s[i]);
}

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		cout << "Incorrect number of arguments" << endl;
		return;
	}
	string lexicon = argv[1];
	string firstWord = argv[2];
	string lastWord = argv[3];
	if (firstWord.length() != lastWord.length())
	{
		cout << "First and last word must be of the same length" << endl;
		return;
	}
	WordLadder* WL = new WordLadder(lexicon, firstWord.length);
	toUpper(firstWord);
	toUpper(lastWord);
	vector<string> minLadder = WL->getMinLadder(firstWord, lastWord);
	WL->displayResult(minLadder);
}