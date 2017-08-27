//============================================================================
// Name: CustomList.cpp
// Author: David Ping
// Date: 4 Aug. 2017
// Description : Custom linked list class, has embedded nodes with string and
// pointer to the next node on the list
//============================================================================

#include "CustomList.h"

CustomList::~CustomList() {
}

//Add new element to the singly linked list
void CustomList::add(std::string str) {

	//Create the new node
	std::unique_ptr<Node> newNode = std::make_unique<Node>(str);

	//If the CustomList is empty then make the new node the head
	if (head == nullptr) {
		head = std::move(newNode);
		return;
	}
	Node* temp = head.get();

	//Move through the linked list starting from
	//the head until the next node is null
	while (temp->next != nullptr) {
		temp = temp->next.get();
	}
	//Put the new node here
	temp->setNext(newNode);
	return;
}

//Checks if the List contains a string
bool CustomList::contains(std::string str) {
	Node* temp = head.get();
	boost::to_lower(temp->str);
	if (temp->str == str) {
		return true;
	}
	while (temp->next != nullptr) {
		temp = temp->next.get();
		boost::to_lower(temp->str);
		if (temp->str == str) {
			return true;
		}
	}
	return false;
}

//Checks the list (textfile) contents against the dictionary
void CustomList::checkFile(std::unique_ptr<DataStructure> &dictionary,
		std::string outputFile) {
	std::ofstream fout; //Output stream to file
	Utility util;
	fout.open(outputFile);

	Node* temp = head.get();
	while (temp != nullptr) {
		boost::to_lower(temp->str);
		if (!dictionary.operator *().contains(temp->str)) {
			if(util.checkAdded(temp->str)){
				temp = temp->next.get();
				continue;
			}
			//Make a map with the edit distance of every word in the dictionary against
			//the Invalid word, print to the output file the name of the string,
			//and all the words with the minimum edit distance
			fout << temp->str << " - was not found in the dictionary. Similar words: ";
			std::map<std::string, int> distMap =
				dictionary.operator *().fuzzyMatches(temp->str);
			int minEditDist = 1;
			bool minPrinted = false;
			while(!minPrinted) {
				for (std::map<std::string, int>::iterator it = distMap.begin();
						it != distMap.end(); it++) {
					if (minEditDist == it->second) {
						fout << it->first + " ";
						minPrinted=true;
					}
				}
				minEditDist++;
			}
			fout << std::endl;
			util.addChecked(temp->str);
		}else{
			util.incrWordCount(temp->str);
		}
		temp = temp->next.get();
	}
	fout.close();
}

//Returns a map with the fuzzy matches for the string passed into it
std::map<std::string, int> CustomList::fuzzyMatches(std::string str) {
	Utility util;
	std::map<std::string, int> distMap;
	Node* temp = head.get();
	boost::to_lower(str);
	boost::to_lower(temp->str);
	distMap[temp->str] = util.editDistance(str,temp->str);
	//Iterates through the list until the next node is nullptr
	while (temp->next != nullptr) {
		temp = temp->next.get();
		boost::to_lower(temp->str);
		distMap[temp->str] = util.editDistance(str,temp->str);
	}
	return distMap;
}
