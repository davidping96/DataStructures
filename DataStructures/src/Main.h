//============================================================================
// Name: Main.h
// Author: David Ping
// Date: 9 Aug. 2017
// Description : Header file for Main.cpp
//============================================================================

#include "Factory.h" //Factory used to create objects from different classes
#include "CustomList.h" //Class for the custom made list
#include "CustomTree.h" //Class for the custom made binary tree
#include "Vector.h" //Class for the vector
#include "List.h" //Class for the list
#include "Set.h" //Class for the set
#include <boost/tokenizer.hpp> //boost::tokenizer<boost::char_separator<char>>
//Set(-lboost_system -lboost_program_options) Addd this to cmake
#ifndef MAIN_H_
#define MAIN_H_

void readFile(std::string file, std::unique_ptr<DataStructure> &ds);

#endif /* MAIN_H_ */
