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
		std::hash<std::string> hash;
		
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


	}
}