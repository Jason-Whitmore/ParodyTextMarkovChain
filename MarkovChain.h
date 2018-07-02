#include <iostream>
#include <string>
#include <map>

class MarkovChain {
	public:
	MarkovChain(std::string filePath, bool isAdjList);

	private:
	std::map<int, std::string> wordset;

};

struct Word {
	std::string word;
	int index;

	double probability;

	int count;
};