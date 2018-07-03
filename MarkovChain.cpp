#include "MarkovChain.h"

MarkovChain::MarkovChain(std::string filePath, bool isAdjList) {
	std::string fileContents = "";
	std::string singleLine;
	std::ifstream file(filePath);

	std::vector<std::string> lineSplit;

	WordSetItem setItem;


	int currentIndex = 0;

	if (isAdjList) {

	} else {
		
		if (file.is_open()) {

			while (std::getline(file, singleLine)) {
				//line's contents are in singleLine
				lineSplit = Helper::split(singleLine, " ");

				//loop through each word in the line
				for (int i = 0; i < lineSplit.size(); i++) {
					//is the word not in the wordset?
					if (wordSet.count(hash(lineSplit[i])) == 0) {
						setItem.index = currentIndex;
						currentIndex++;

						setItem.key = hash(lineSplit[i]);

						setItem.word = lineSplit[i];

						wordSet[hash(lineSplit[i])] = setItem;

						
					}
				}


			}


		} else {
			//file could not be opened
		}

		adjList.resize(wordSet.size());

		Word w;

		for (auto& x: wordSet) {
			w.word = x.second.word;
			w.count = 0;
			adjList[getIndexOfWord(w.word)].push_back(w);
		}
		file.close();

		std::ifstream file2(filePath);
		
		//run through the file again: This time to construct the columns of the adj list
		if (file2.is_open()) {

			
			while (std::getline(file2, singleLine)) {
				//line's contents are in singleLine
				lineSplit = Helper::split(singleLine, " ");

				
				

				//loop through each word in the line
				for (int i = 0; i < lineSplit.size() - 1; i++) {
					//word currently not in the list?
					if (!containedInAdjList(getIndexOfWord(lineSplit[i]), lineSplit[i+1])) {
						//add the word to the list
						w.word = lineSplit[i + 1];
						w.count = 1;
						adjList[getIndexOfWord(lineSplit[i])].push_back(w);
					} else {
						//in the adj list, increment.
						incrementWordFromAdjList(getIndexOfWord(lineSplit[i]), lineSplit[i + 1]);
					}

				}

				//collect the start of any sentence and put into a vector.


			}


		} else {
			//file could not be opened
		}

		//set probabilities correctly

		double totalCount = 0;
		for (int r = 0; r < adjList.size(); r++) {
			totalCount = 0;
			//get total count
			for (int c = 0; c < adjList[r].size(); c++) {
				totalCount += adjList[r][c].count;
			}

			//set appropriate probability
			for (int c = 0; c < adjList[r].size(); c++) {
				adjList[r][c].probability = adjList[r][c].count / totalCount;
			}
		}



	}
}


int MarkovChain::getIndexOfWord(std::string s) {
	if (wordSet.count(hash(s)) == 0) {
		return -1;
	}

	return wordSet.find(hash(s))->second.index;
}

bool MarkovChain::containedInAdjList(int row, std::string s) {

	for (int i = 0; i < adjList[row].size(); i++) {
		if (adjList[row][i].word == s) {
			return true;
		}
	}

	return false;
}

Word MarkovChain::getWordFromAdjList(int row, std::string s) {
	
	for (int i = 0; i < adjList[row].size(); i++) {
		if (adjList[row][i].word == s) {
			return adjList[row][i];
		}
	}
	Word w;
	return w;
}

void MarkovChain::incrementWordFromAdjList(int row, std::string s) {
	for (int i = 0; i < adjList[row].size(); i++) {
		if (adjList[row][i].word == s) {
			adjList[row][i].count++;
		}
	}
}

void MarkovChain::printHighestProbability() {
	std::string from;
	std::string to;
	double prob = 0;

	for (int r = 0; r < adjList.size(); r++) {
		for (int c = 0; c < adjList[r].size(); c++) {
			if (adjList[r][c].probability > prob) {
				from = adjList[r][0].word;
				to = adjList[r][c].word;
				prob = adjList[r][c].probability;
			}
		}
	}

	std::cout << "Highest Probability: " << from << " --> " << to << ": " << std::to_string(prob) << std::endl;
}


void MarkovChain::writeAdjListToFile(std::string path) {

}