//============================================================================
// Name: List.cpp
// Author: David Ping
// Date: 6 Aug. 2017
// Description : List class with required functions from the list container
//============================================================================

#include "List.h"

List::~List() {
}

//Adds a string the the list
void List::add(std::string str) {
	list.push_back(str);
}

//Checks if list contains the string, case insensitive
bool List::contains(std::string str) {
	//Uses boost function to_lower to make string lower case
	boost::to_lower(str);
	for (std::list<std::string>::iterator it = list.begin(); it != list.end();
			it++) {
		boost::to_lower(*it);
		if (str == *it) {
			return true;
		}
	}
	return false;
}

//Checks the list (textfile) contents against the dictionary
void List::checkFile(std::unique_ptr<DataStructure> &dictionary,
		std::string outputFile) {
	std::ofstream fout; //Output stream to file
	Utility util;
	fout.open(outputFile);

	//For all items in the list (text file)
	for (std::list<std::string>::iterator it = list.begin(); it != list.end();
			it++) {
		boost::to_lower(*it);

		//Checks if the dictionary contains the string from (text file) list
		if (!dictionary.operator *().contains(*it)) {
			if(util.checkAdded(*it)){
				continue;
			}
			//If not print the fuzzy matches to file
			fout << *it << " - was not found in the dictionary. Similar words: ";
			//Finds all the fuzzy matches and puts them into a map
			std::map<std::string, int> distMap =
					dictionary.operator *().fuzzyMatches(*it);
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
			util.addChecked(*it);
		}else{
			util.incrWordCount(*it);
		}
	}
	fout.close();
}

//Returns a map with the fuzzy matches for the string passed into it
std::map<std::string, int> List::fuzzyMatches(std::string str) {
	Utility util;
	std::map<std::string, int> distMap;
	boost::to_lower(str);
	for (std::list<std::string>::iterator it = list.begin(); it != list.end();
			it++) {
		boost::to_lower(*it);
		//Calculates the edit distance and assigns it to the string being compared from the dictionary
		distMap[*it] = util.editDistance(str, *it);
	}
	return distMap;
}
