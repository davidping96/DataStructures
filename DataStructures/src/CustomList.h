//============================================================================
// Name: CustomList.h
// Author: David Ping
// Date: 4 Aug. 2017
// Description : Custom list header file
//============================================================================

#include "DataStructure.h"

#ifndef CUSTOMLIST_H_
#define CUSTOMLIST_H_

class CustomList: public DataStructure {
public:
	virtual ~CustomList();
	CustomList(): head(nullptr) {
	}
	//Embedded class node which holds the string value and a pointer to the next node
private:
	class Node {
	public:
		Node(std::string str):str(str), next(nullptr) {
		}
		std::string str;
		std::unique_ptr<Node> next;
		void setNext(std::unique_ptr<Node> &nextNode) {
			next = std::move(nextNode);
		}
		;
	};
	std::unique_ptr<Node> head;
public:
	void add(std::string str) override;
	bool contains(std::string str) override;
	void checkFile(std::unique_ptr<DataStructure> &dictionary,
			std::string outputFile) override;
	std::map<std::string, int> fuzzyMatches(std::string) override;
};

#endif /* CUSTOMLIST_H_ */
