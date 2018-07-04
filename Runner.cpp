#include "Runner.h"


int main() {
	MarkovChain m = MarkovChain("MarkovChainData.txt", true);
	//MarkovChain m = MarkovChain("AGOT.txt", false);
	m.printHighestProbability();
	//m.writeAdjListToFile("MarkovChainData.txt");
	while(true);
}