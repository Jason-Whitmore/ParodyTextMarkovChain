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

		int wordIndex = 0;
		for (auto& x: wordSet) {
			w.word = x.second.word;
			w.count = 0;

			adjList[wordIndex][0] = w;
		}
		file.close();


		
		//run through the file again: This time to construct the columns of the adj list
		if (file.is_open()) {

			
			while (std::getline(file, singleLine)) {
				//line's contents are in singleLine
				lineSplit = Helper::split(singleLine, " ");

				
				

				//loop through each word in the line
				for (int i = 0; i < lineSplit.size() - 1; i++) {
					
				}

				//collect the start of any sentence and put into a vector.


			}


		} else {
			//file could not be opened
		}


	}
}


int MarkovChain::getIndexOfWord(std::string s) {


	if (wordSet.count(hash(s)) == 0) {
		return -1;
	}

	return wordSet.find(hash(s))->second.index;
}