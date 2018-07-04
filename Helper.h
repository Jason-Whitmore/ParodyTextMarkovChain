#include <string>
#include <vector>
#include <random>
class Helper {
	public:
	static std::vector<std::string> split(std::string target, std::string splitter);
	static bool contains(std::string s, std::string targetString);
	static int randomInt(int min, int max);
	static double randomDouble(double min, double max);
};