#include <string>
#include <set>

class LCS
{
private:
	enum Direction {LEFT, UP};
protected:
	int max(int a, int b);
	int ** LCSMatrix(std::string first, std::string second); // always need to clean array inside calling fuction
	void getSubsequence(int ** resultTab, std::set<std::string>& results, std::string first, std::string second ,
		std::string result,int i, int j, Direction direction);
public:
	std::string getLCS (std::string first, std::string second, bool print);
	std::set<std::string> getAllLCS(std::string first, std::string second, bool print);
	LCS();
	~LCS();
	void printMatrix(std::string first, std::string second);
};