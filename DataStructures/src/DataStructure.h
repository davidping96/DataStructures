//============================================================================
// Name: DataStructure.h
// Author: David Ping
// Date: 3 Aug. 2017
// Description : Parent class for all the data structure classes, contains
// abstract methods using "virtual return_type method_name(parameters)=0;"
//============================================================================

#include "Utility.h" //Class with common methods
#include <iostream> //std::cout
#include <memory> //unique_ptr, shared_ptr
#include <boost/algorithm/string.hpp> //std::to_lower()
#include <string> //std::string

#ifndef DATASTRUCTURE_H_
#define DATASTRUCTURE_H_

class DataStructure {
public:
	virtual~DataStructure();
	virtual void add(std::string str)=0;
	virtual bool contains(std::string str)=0;
	virtual void checkFile(std::unique_ptr<DataStructure> &dictionary, std::string outputFile)=0;
	virtual std::map<std::string, int> fuzzyMatches(std::string)=0;
};

#endif /* DATASTRUCTURE_H_ */
