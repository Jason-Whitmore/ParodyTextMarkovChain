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
	void printHighestProbability();
	void writeAdjListToFile(std::string path);

	private:
	std::map<int, WordSetItem> wordSet;
	std::vector<std::string> sentenceStarters;
	std::vector<std::vector<Word>> adjList;

	std::hash<std::string> hash;

	int getIndexOfWord(std::string s);
	bool containedInAdjList(int row, std::string s);
	Word getWordFromAdjList(int row, std::string s);
	void incrementWordFromAdjList(int row, std::string s);
	
	
};
