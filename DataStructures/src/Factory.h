//============================================================================
// Name: Factory.h
// Author: David Ping
// Date: 5 Aug. 2017
// Description : Factory for returning a type of DataStructure depending on
// user input from command line
//============================================================================

#ifndef FACTORY_H_
#define FACTORY_H_

#include "DataStructure.h"
#include "CustomList.h"
#include "CustomTree.h"
#include "Vector.h"
#include "List.h"
#include "Set.h"
#include <memory>//unique_ptr, make_unique

class Factory {
public:
	static std::unique_ptr<DataStructure> getDataStructure(std::string str) {
		if (str == "custom_list") {
			return std::make_unique<CustomList>();
		} else if (str == "custom_tree") {
			return std::make_unique<CustomTree>();
		} else if (str == "vector") {
			return std::make_unique<Vector>();
		} else if (str == "list") {
			return std::make_unique<List>();
		} else if (str == "set") {
			return std::make_unique<Set>();
		} else {
			std::cerr << "Invalid data structure" << std::endl;
			exit(-1);
		}
	}
};

#endif /* FACTORY_H_ */
