#include "MarkovChain.h"

MarkovChain::MarkovChain(std::string filePath) {
	std::string fileContents = "";
	std::string singleLine;
	std::ifstream file(filePath);

	std::vector<std::string> lineSplit;

	WordSetItem setItem;

	
	int currentIndex = 0;

	
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

			//add the start of the line into the sentence starters vector for use later
			if (lineSplit[0].length() > 0) {
				sentenceStarters.push_back(lineSplit[0]);
			}
			
			
			

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
			if (totalCount == 0) {
				adjList[r][c].probability = 0;
			} else {
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
	//save the sentence starters
	std::string output = "Starters ";


	for (int i = 0; i < sentenceStarters.size(); i++) {
		output += sentenceStarters[i] + " ";
	}
	output += "\n";
	//save the wordSetItems
	WordSetItem w;
	for (auto& x : wordSet) {
		w = x.second;
		output += "WordSetItem " + std::to_string(w.index) + " " + std::to_string(w.key) + " " + w.word + "\n";
	}


	//save the adj List
	for (int r = 0; r < adjList.size(); r++) {
		for (int c = 0; c < adjList[r].size(); c++) {
			output += "AdjList " + adjList[r][0].word + " " + adjList[r][c].word + " " + std::to_string(adjList[r][c].probability) + "\n";
		}
	}

	std::ofstream file;
	file.open(path);
	file << output;
	file.close();
}

std::string MarkovChain::generateText(int numWords) {
	usleep(100);
	srand(time(0));
	
	int words = 0;

	std::string result = "";
	int randInt = Helper::randomInt(0, sentenceStarters.size());
	std::string startWord = sentenceStarters[randInt];
	std::string currentWord = startWord;
	result += currentWord;
	while (words < numWords ) {
		currentWord = pickWordFromRow(getIndexOfWord(currentWord));

		if (currentWord == "") {
			//hit a dud. start a new sentence
			result += ".";
			currentWord = sentenceStarters[Helper::randomInt(0, sentenceStarters.size())];
		} else {
			result += " " + currentWord;
			words++;
		}
	}

	return result;
}

std::string MarkovChain::pickWordFromRow(int row) {
	if (adjList[row].size() == 1) {
		//basically a dead end
		return "";
	}

	double rand;
	for (int i = 1; i < adjList[row].size(); i++) {
		rand = Helper::randomDouble(0, 1);
		if (rand < adjList[row][i].probability) {
			return adjList[row][i].word;
		}
	}
	return adjList[row][adjList[row].size() - 1].word;
}