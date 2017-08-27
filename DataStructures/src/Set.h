//============================================================================
// Name: Set.h
// Author: David Ping
// Date: 6 Aug. 2017
// Description : Header file for the set class
//============================================================================

#include "DataStructure.h"
#include <set>

#ifndef SET_H_
#define SET_H_

class Set: public DataStructure {
private:
	std::multiset<std::string> set;
public:
	virtual ~Set();
	Set() {
	}
	void add(std::string str) override;
	bool contains(std::string str) override;
	void checkFile(std::unique_ptr<DataStructure> &dictionary,
			std::string outputFile) override;
	std::map<std::string, int> fuzzyMatches(std::string) override;
};

#endif /* SET_H_ */
