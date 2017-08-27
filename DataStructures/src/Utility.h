//============================================================================
// Name: Utility.h
// Author: David Ping
// Date: 5 Aug. 2017
// Description : Header file for Utility.cpp
//============================================================================

#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <iostream>

#ifndef UTILITY_H_
#define UTILITY_H_

class Utility {
private:
	//A map that keeps count of the number of times a word appears in the text file
	static std::map<std::string, int> wordMap;
	static std::map<std::string, bool> checkedStrings;
	//The name of the file that the wordMap is written to
	const std::string wordCountFile = "wordCount.csv";
public:
	int editDistance(std::string s1, std::string s2);
	void incrWordCount(std::string str);
	void addChecked(std::string str);
	bool checkAdded(std::string str);
	void writeMap();
	int min(int a, int b, int c);
};

#endif /* UTILITY_H_ */
