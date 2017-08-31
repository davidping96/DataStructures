/*
============================================================================
 Name: Main.cpp
 Author: David Ping
 Date: 3 Aug. 2017
 Description : Main class - Defines the entry point for the console application.
============================================================================
*/
#include "Main.h"

//@param argc, argv - the number or command line arguments and their vectors
int main(int argc, char *argv[]) {
	Factory f; //Used to access factory pattern for data structures
	Utility util; //Used to access utility methods

	/**
	 * These variables store the names of the data structure/files entered in the command line
	 * */
	std::string dataStructure;
	std::string dictionary;
	std::string textFile;
	std::string outputFile;

	//Read the command lines arguments there must be 8 arguments

	//Check the number of command line arguments
	if (argc != 9) {
		std::cerr << "Invalid number of arguments" << std::endl;
		return -1;
	}

	/**
	 * -s precedes the data structure being used
	 * Valid data structures = vector | list | set | custom_list | custom_tree
	 * -d precedes the dictionary file
	 * -t precedes the text file that we are processing
	 * -o precedes the output file - saves the list of words without matches
	 * in the dictionary and the closest matches in the dictionary according to edit distance
	 * */
	for (int i = 1; i < argc; i++) {
		std::string str = argv[i];
		if (str == "-s") {
			i++;
			dataStructure = argv[i];
		} else if (str == "-d") {
			i++;
			dictionary = argv[i];
		} else if (str == "-t") {
			i++;
			textFile = argv[i];
		} else if (str == "-o") {
			i++;
			outputFile = argv[i];
		} else {
			std::cerr << "Invalid arguments" << std::endl;
			return -1;
		}
	}

	//Verifies and initialize the data structure using the factory
	std::unique_ptr<DataStructure> inputFileDS = f.getDataStructure(dataStructure);
	std::unique_ptr<DataStructure> dictionaryDS = f.getDataStructure(dataStructure);

	//Reads the contents of the files and add them to the data structures

	/*clock_t startTime = clock();
			std::cout << "Start Time: " << startTime << std::endl;*/

	readFile(textFile, inputFileDS);

	/*clock_t endTime = clock();
			std::cout << "End Time: " << endTime << std::endl;
			clock_t clockTicksTaken = endTime - startTime;
			double timeInSeconds = clockTicksTaken / (double) CLOCKS_PER_SEC;

			std::cout << "Time taken to add (seconds): " << timeInSeconds << std::endl;*/

	readFile(dictionary, dictionaryDS);

	/**
	 * Goes through every character in the data structure for text file and compare it against
	 * the other data structure containing the dictionary
	 * */

	/*clock_t startTime2 = clock();
				std::cout << "Start Time2: " << startTime2 << std::endl;*/

	inputFileDS.operator *().checkFile(dictionaryDS, outputFile);

	/*clock_t endTime2 = clock();
					std::cout << "End Time2: " << endTime2 << std::endl;
					clock_t clockTicksTaken2 = endTime2 - startTime2;
					double timeInSeconds2 = clockTicksTaken2 / (double) CLOCKS_PER_SEC;

					std::cout << "Time taken to check (seconds): " << timeInSeconds2 << std::endl;
*/
	//Writes the contents of the map containing the count of each word to the output file
	util.writeMap();

	std::cout << "DONE!" << std::endl;
	return 0;
}

/**
 * Reads the file into the data structure, gets one line at a time and then
 * tokenizes line and adds the tokens to the data structure
 * */
void readFile(std::string fileName, std::unique_ptr<DataStructure> &ds) {
	bool empty = true;
	typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
	//Delimiters are all characters in sep
	boost::char_separator<char> sep(
			"//1234567890!@#$%^&*() _+=[{}]\\|;:'\"<>,./?-	");

	std::ifstream fin; //Input stream from file
	fin.open(fileName); //Opens the file

	if (!fin) {
		std::cerr << "File "<< fileName <<" does not exist" << std::endl;
		exit(-1);
	}
	while (!fin.eof()) {
		std::string str;
		std::getline(fin, str);
		tokenizer tokens(str, sep);
		for (tokenizer::iterator it = tokens.begin(); it != tokens.end();
				it++) {
			//Adds the token to the data structure
			ds->add(*it);
			empty=false;
		}
	}
	fin.close();
	if(empty == true){
		std::cerr<< "File "<< fileName <<" is empty or no valid strings exist"<<std::endl;
		exit(-1);
	}
	return;
}
