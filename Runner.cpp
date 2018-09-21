#include "Runner.h"


int main() {
	srand(time(0));


	std::cout << "Loading text into Markov Chain. Please wait." << std::endl;

	MarkovChain m = MarkovChain("book.txt", false);
	//MarkovChain m = MarkovChain("AGOT.txt", false);
	


	while(true){
		std::cout << "Press any key to generate parody text." << std::endl << std::endl;
		std::cin.get();
		std::cout << m.generateText(100) << std::endl << std::endl;
	}
	
}