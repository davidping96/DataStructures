//============================================================================
// Name: Utility.cpp
// Author: David Ping
// Date: 5 Aug. 2017
// Description : Common methods used by multiple classes and containers
//============================================================================

#include "Utility.h"

//Counts the number of times a word from the dictionary appears in the text file
std::map<std::string, int> Utility::wordMap;
//Used to check if a word has already been checked
std::map<std::string, bool> Utility::checkedStrings;

//Calculates edit distance between two strings
int Utility::editDistance(std::string s1, std::string s2) {
	int s1length = s1.length();
	int s2length = s2.length();

	std::vector<std::vector<int> > m;

	for(int i=0;i<=s1length+1;i++){
		std::vector<int> temp;
		for(int j=0;j<=s2length+1;j++){
			temp.push_back(0);
		}
		m.push_back(temp);
	}

	for (int i = 1; i <= s1length; i++) {
		m[i][0] = i;
	}
	for (int j = 0; j <= s2length; j++) {
		m[0][j] = j;
	}
	for (int i = 1; i <= s1length; i++) {
		for (int j = 1; j <= s2length; j++) {
			if (s1.at(i - 1) == s2.at(j - 1)) {
				m[i][j] = m[i - 1][j - 1];
			} else {
				m[i][j] = min(m[i - 1][j - 1], m[i - 1][j], m[i][j - 1]) + 1;
			}
		}
	}
	return m[s1length][s2length];
}

//Increments the string passed on the wordMap
void Utility::incrWordCount(std::string str) {
	++wordMap[str];
}

void Utility::addChecked(std::string str) {
	checkedStrings[str]=true;
}

bool Utility::checkAdded(std::string str){
	if(checkedStrings[str]==true){
		return true;
	}else{
		return false;
	}
}

//Writes the contents of the word count map to the file
void Utility::writeMap() {
	std::ofstream fout;
	fout.open(wordCountFile);
	for (std::map<std::string, int>::iterator it = wordMap.begin();
			it != wordMap.end(); it++) {
		if (it->second > 0) {
			fout << it->first << ", " << it->second << std::endl;
		}
	}
	fout.close();
}

//Finds the minimum of three integers
int Utility::min(int a, int b, int c) {
	int min = a;
	if (min > b) {
		min = b;
	}
	if (min > c) {
		min = c;
	}
	return min;
}
