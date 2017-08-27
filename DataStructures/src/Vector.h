//============================================================================
// Name: Vector.h
// Author: David Ping
// Date: 6 Aug. 2017
// Description : Header file for the vector class
//============================================================================

#include "DataStructure.h"
#include <vector>

#ifndef VECTOR_H_
#define VECTOR_H_

class Vector: public DataStructure {
private:
	std::vector<std::string> vector;
public:
	virtual ~Vector();
	Vector() {
	}
	void add(std::string str) override;
	bool contains(std::string str) override;
	void checkFile(std::unique_ptr<DataStructure> &dictionary,
			std::string outputFile) override;
	std::map<std::string, int> fuzzyMatches(std::string) override;
};

#endif /* VECTOR_H_ */
