//============================================================================
// Name: CustomTree.h
// Author: David Ping
// Date: 4 Aug. 2017
// Description : Binary search tree data structure header file
//============================================================================

#include "DataStructure.h"

#ifndef CUSTOMTREE_H_
#define CUSTOMTREE_H_

class CustomTree: public DataStructure {
public:
	virtual ~CustomTree() {
	}
	CustomTree() {
	}
	//Embedded class node which holds the string value and a pointer to the left and right children
private:
	class Node {
	public:
		Node(std::string str):str(str),leftBranch(nullptr),rightBranch(nullptr) {
		}
		std::string str;
		std::unique_ptr<Node> leftBranch;
		std::unique_ptr<Node> rightBranch;
		void setLeft(std::unique_ptr<Node> &newNode) {
			leftBranch = std::move(newNode);
		}
		;
		void setRight(std::unique_ptr<Node> &newNode) {
			rightBranch = std::move(newNode);
		}
		;
	};
private:
	std::unique_ptr<Node> root;
public:
	void add(std::string str) override;
	bool contains(std::string str) override;
	void checkFile(std::unique_ptr<DataStructure> &dictionary,
			std::string outputFile) override;
	void checkTree(Node* node,
			std::unique_ptr<DataStructure> &dictionary, std::ofstream &fout);
	std::map<std::string, int> fuzzyMatches(std::string) override;
	void searchTree(Node* node,
			std::string str, std::map<std::string, int> &distMap);
};

#endif  /* CUSTOMTREE_H_ */

