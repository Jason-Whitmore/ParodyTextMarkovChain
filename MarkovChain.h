#pragma once
#include <vector>
#include <random>
#include <map>
#include <cmath>
#include <string>
#include <iostream>


class MarkovChain {


	public:
	MarkovChain(std::string filePath);


	private:

	int numUniqueWords;
	std::map<int,std::string> wordSet;

	std::vector<std::vector<WordStruct>> adjMatrix;


};