#include "Runner.h"


int main() {
	srand(NULL);
	MarkovChain m = MarkovChain("MarkovChainData.txt", true);
	//MarkovChain m = MarkovChain("AGOT.txt", false);
	//m.printHighestProbability();
	//m.writeAdjListToFile("MarkovChainData.txt");

	for (int i = 0; i < 500; i++) {
		std::cout << m.generateText(1) << std::endl << std::endl;
	}
	
	while(true);
}