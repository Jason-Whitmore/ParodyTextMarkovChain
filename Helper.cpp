#include "Helper.h"



std::vector<std::string> Helper::split(std::string s, std::string splitter) {
	std::vector<std::string> r = std::vector<std::string>();

	std::string copy = s;

	while (Helper::contains(copy, splitter)) {
		r.push_back(copy.substr(0, copy.find_first_of(splitter)));
		copy = copy.substr(copy.find_first_of(splitter) + splitter.length());
	}

	r.push_back(copy);


	return r;
}

bool Helper::contains(std::string s, std::string targetString) {
	int targetLength = targetString.length();

	int currentPosition = 0;

	while (currentPosition + targetLength <= s.length()) {
		if (s.substr(currentPosition, targetLength) == targetString) {
			return true;
		}
		currentPosition++;
	}

	return false;
}

double Helper::randomDouble(double min, double max) {
	double scalar = (double)rand() / RAND_MAX;

	return min + (scalar * (max - min));
}

int Helper::randomInt(int min, int max) {
	return (int)randomDouble(min,max);
}