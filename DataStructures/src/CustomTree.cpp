//============================================================================
// Name: CustomTree.cpp
// Author: David Ping
// Date: 4 Aug. 2017
// Description : Custom binary tree class, has embedded nodes with string and
// pointer to the left and right branches
//============================================================================

#include "CustomTree.h"

//Add new element to the binary tree
void CustomTree::add(std::string str) {
	Utility util;
	boost::to_lower(str);

	std::unique_ptr<Node> newNode = std::make_unique<Node>(str);

	if (root == nullptr) {
		root = std::move(newNode);
		return;
	}
	Node* temp = root.get();

	/**
	 * Move through the binary search tree go right if string is
	 * lexicographically greater than the current string and go left if it is
	 * less keep going until the next left/right is nullptr and put the string there
	 * */
	while (1) {
		if (str >= temp->str) {
			if (temp->rightBranch != nullptr) {
				temp = temp->rightBranch.get();
			} else {
				temp->setRight(newNode);
				break;
			}
		} else if (str < temp->str) {
			if (temp->leftBranch != nullptr) {
				temp = temp->leftBranch.get();
			} else {
				temp->setLeft(newNode);
				break;
			}
		}
	}
	return;
}

//Checks if the binary tree contains a string
bool CustomTree::contains(std::string str) {
	if(root.get()==nullptr){
		return false;
	}
	Node* temp = root.get();
	boost::to_lower(str);

	while (1) {
		boost::to_lower(temp->str);
		if (temp->str == str) {
			return true;
		}
		if (str > temp->str) {
			if (temp->rightBranch.get() != nullptr) {
				temp = temp->rightBranch.get();
			} else {
				return false;
			}
		} else if (str < temp->str) {
			if (temp->leftBranch.get() != nullptr) {
				temp = temp->leftBranch.get();
			} else {
				return false;
			}
		}
	}
	return false;
}

//Checks the binary tree (textfile) contents against the dictionary
void CustomTree::checkFile(std::unique_ptr<DataStructure> &dictionary,
		std::string outputFile) {
	//Go through the binary search tree and write all fuzzy matches to a vector
	Node* temp = root.get();

	std::ofstream fout;
	fout.open(outputFile);
	/**
	 * Go through the dictionary tree using POST ORDER TRAVERSAL
	 * LEFT => RIGHT => CURRENT
	 * For each string in the tree find the edit distance between
	 * the dictionary strings and print it to the file
	 * */
	checkTree(temp, dictionary, fout);
	fout.close();
}

//Cycles through the tree using post order traversal writes edit distances to the file
void CustomTree::checkTree(Node* node,
		std::unique_ptr<DataStructure> &dictionary, std::ofstream &fout) {
	if (node->leftBranch.get() != nullptr) {
		Node* temp = node->leftBranch.get();
		checkTree(temp, dictionary, fout);
	}
	if (node->rightBranch.get() != nullptr) {
		Node* temp = node->rightBranch.get();
		checkTree(temp, dictionary, fout);
	}
	Utility util;
	boost::to_lower(node->str);

	//Checks if the dictionary contains the string from (text file) binary tree
	if (!dictionary.operator *().contains(node->str)) {
		if (!util.checkAdded(node->str)) {

			//If not print the fuzzy matches to file
			fout << node->str << " - was not found in the dictionary. Similar words: ";
			//Finds all the fuzzy matches and puts them into a map
			std::map<std::string, int> distMap =
					dictionary.operator *().fuzzyMatches(node->str);
			int minEditDist = 1;
			bool minPrinted = false;
			//Print out all the fuzzy matches that are between 1
			//and the maximum edit distance
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
		}
	}else{
		util.incrWordCount(node->str);
	}
	util.addChecked(node->str);
}

//Returns a map with the fuzzy matches for the string passed into it
std::map<std::string, int> CustomTree::fuzzyMatches(std::string str) {
	std::map<std::string, int> distMap;
	boost::to_lower(str);
	Node* temp = root.get();
	searchTree(temp, str, distMap);
	return distMap;
}

/**
 * Recursively goes through the binary tree until text file string has been
 * compared against all dictionary strings
 * */
void CustomTree::searchTree(Node* node, std::string str,
		std::map<std::string, int> &distMap) {
	Utility util;
	if (node->leftBranch.get() != nullptr) {
		Node* temp = node->leftBranch.get();
		searchTree(temp, str, distMap);
	}
	if (node->rightBranch.get() != nullptr) {
		Node* temp = node->rightBranch.get();
		searchTree(temp, str, distMap);
	}
	boost::to_lower(node->str);
	distMap[node->str] = util.editDistance(str,
			node->str);
}
