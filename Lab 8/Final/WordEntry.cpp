#include "WordEntry.h"
#include "WordEntry.h"

// WordEntry contructor
WordEntry::WordEntry(const string &text, int score)
 : word(text), numAppearances(1), totalScore(score) {
	 
}

//increase total score by s and also should increase numAppearances
void WordEntry::addNewAppearance(int s) {
	totalScore += s;
	++numAppearances;
}

//returns the word of the WordEntry
const string & WordEntry::getWord() const {
    return word;
}

// returns the average score of the word based on totalScore and numAppearances
double WordEntry::getAverage() const {
	return static_cast<double>(totalScore) / numAppearances;
}
