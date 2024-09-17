#pragma once

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class WordEntry {

 private:
	string word;
	int numAppearances;
	int totalScore;
 public:
 	//Constructor
	WordEntry(const string &, int);

	//no new declared so no deconstructor, copy-constructor, and assignment operator needed
	
	//increase total score by s and also should increase numAppearances
	void addNewAppearance(int);

	//returns the word of the WordEntry
	const string & getWord() const;
	
	// returns the average score of the word based on totalScore and numAppearances
	double getAverage() const;
};
