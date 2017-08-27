//============================================================================
// Name: Set.cpp
// Author: David Ping
// Date: 6 Aug. 2017
// Description : Set class with required functions from the set container
//============================================================================

#include "Set.h"

Set::~Set() {
}

//Adds a string the the set
void Set::add(std::string str) {
	set.insert(str);
}

//Checks if set contains the string, case insensitive
bool Set::contains(std::string str) {
	//Uses boost function to_lower to make string lower case
	boost::to_lower(str);
	if (set.count(str)) {
		return true;
	} else {
		return false;
	}
}

//Checks the set (textfile) contents against the dictionary
void Set::checkFile(std::unique_ptr<DataStructure> &dictionary,
		std::string outputFile) {
	std::ofstream fout; //Output stream to file
	Utility util;
	fout.open(outputFile);

	//For all items in the set (text file)
	for (std::multiset<std::string>::iterator it = set.begin(); it != set.end();
			it++) {
		std::string temp = *it;
		boost::to_lower(temp);

		//Checks if the dictionary contains the string from (text file) set
		if (!dictionary.operator *().contains(temp)) {
			if (util.checkAdded(temp)) {
				continue;
			}
			//If not print the fuzzy matches to file
			fout << temp << " - was not found in the dictionary. Similar words: ";
			//Finds all the fuzzy matches and puts them into a map
			std::map<std::string, int> distMap =
					dictionary.operator *().fuzzyMatches(temp);
			int minEditDist = 1;
			bool minPrinted = false;
			//Print out all the fuzzy matches that are between 1 and the maximum edit distance
			while(!minPrinted) {
				for (std::map<std::string, int>::iterator it = distMap.begin();
						it != distMap.end(); it++) {
					if (minEditDist == it->second) {
						fout << it->first + " ";
						minPrinted = true;
					}
				}
				minEditDist++;
			}
			fout << std::endl;
			util.addChecked(temp);
		}else{
			util.incrWordCount(temp);
		}
	}
	fout.close();
}

//Returns a map with the fuzzy matches for the string passed into it
std::map<std::string, int> Set::fuzzyMatches(std::string str) {
	Utility util;
	std::map<std::string, int> distMap;
	boost::to_lower(str);
	for (std::multiset<std::string>::iterator it = set.begin(); it != set.end();
			it++) {
		std::string temp = *it;
		boost::to_lower(temp);
		//Calculates the edit distance and assigns it to the string being compared from the dictionary
		distMap[*it] = util.editDistance(str, temp);
	}
	return distMap;
}
