//============================================================================
// Name: List.h
// Author: David Ping
// Date: 6 Aug. 2017
// Description : Header file for the list class
//============================================================================

#include "DataStructure.h"
#include <list>

#ifndef LIST_H_
#define LIST_H_

class List: public DataStructure {
private:
	std::list<std::string> list;
public:
	virtual ~List();
	List() {}
	void add(std::string str) override;
	bool contains(std::string str) override;
	void checkFile(std::unique_ptr<DataStructure> &dictionary,
			std::string outputFile) override;
	std::map<std::string, int> fuzzyMatches(std::string) override;
};

#endif /* LIST_H_ */
