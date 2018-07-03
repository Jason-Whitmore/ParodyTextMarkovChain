#include "Runner.h"


int main() {
	MarkovChain m = MarkovChain("AGOT.txt", false);
	m.printHighestProbability();
	while(true);
}