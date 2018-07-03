#include "Helper.h"
#include <iostream>
#include <map>
#include <fstream>



struct Word {

	std::string word;

	double probability;

	int count;
};

struct WordSetItem {
	int key;
	std::string word;
	int index;
};



class MarkovChain {
	public:
	MarkovChain(std::string filePath, bool isAdjList);

	private:
	std::map<int, WordSetItem> wordSet;

	std::vector<std::vector<Word>> adjList;
};
