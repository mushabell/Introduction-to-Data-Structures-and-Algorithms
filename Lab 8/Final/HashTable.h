#pragma once

#include <string>
#include <list>
#include <iostream>
#include "WordEntry.h"

using namespace std;

class HashTable {

 private:
	list<WordEntry> *hashTable;
	int size;

 public:
	//constructor
	HashTable(int size);

	//deconstructor, copy-constructor, and assignment operator 
	~HashTable(){
		delete[] hashTable;
	};
	HashTable(const HashTable&) = delete;
    HashTable& operator=(const HashTable&) = delete;

	//returns true if word is in the hash table or false if word is not in the hash table
	bool contains(const string& word) const;

	//the result of a call to getAverage() from the WordEntry
	double getAverage(const string& word) const;

	//adds a new entry into the hash table
	void put(const string& word , int score);
 
 private:
	// return an integer based on the input string used for index into the array in hash table
	int computeHash(const string &) const;
};
