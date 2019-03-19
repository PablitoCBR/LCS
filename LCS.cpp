#include "LCS.h"
#include <string>
#include <vector>
#include <iostream>

LCS::LCS() {};
LCS::~LCS() {};

int LCS::max(int a, int b) {
	return (a > b) ? a : b;
}

int ** LCS::LCSMatrix(std::string first, std::string second){
	int firstLength = first.length(), secondLength = second.length();


	int ** resultTab = new int*[firstLength + 1];
	for (int i = 0; i < firstLength + 1; i++)
		resultTab[i] = new int[secondLength + 1];

	for (int i = 0; i < firstLength + 1; i++) {
		for (int j = 0; j < secondLength + 1; j++) {
			if (i == 0 || j == 0)
				resultTab[i][j] = 0;
			else if (first[i - 1] == second[j - 1])
				resultTab[i][j] = resultTab[i - 1][j - 1] + 1;
			else resultTab[i][j] = max(resultTab[i - 1][j], resultTab[i][j - 1]);
		}
	}

	return resultTab;
}

void LCS::printMatrix(std::string first, std::string second) {
	int XLength = first.length() + 1, YLength = second.length() + 1;
	int ** matrix = LCSMatrix(first, second);

	for (int i = 0; i < XLength; i++) {
		for (int j = 0; j < YLength; j++) {
			std::cout << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

std::string LCS::getLCS(std::string first, std::string second, bool print){
	// declare length of given strings
	int firstLength = first.length(), secondLength = second.length();
	std::string lcs = ""; // longest common subsequence of given strings

	// declare dynamic 2D array and fill it
	int ** resultTab = LCSMatrix(first, second);

	// Search LCS from array
	int pX = firstLength;
	int	pY = secondLength;
	while (resultTab[pX][pY] > 0) {
		int maxValue = max(resultTab[pX - 1][pY], resultTab[pX][pY - 1]);
		if (maxValue == resultTab[pX][pY])
			if(resultTab[pX-1][pY] <= resultTab[pX][pY-1])
				pY -= 1;
			else pX -= 1;
		else {
			lcs = first[pX - 1] + lcs;
			pY -= 1;
			pX -= 1;
		}
	}

	// clean up array
	for (int i = 0; i < firstLength; i++)
		delete[] resultTab[i];
	delete[] resultTab;

	// print if want
	if (print)
		std::cout << lcs << std::endl;

	return lcs;
}

void LCS::getSubsequence(int ** resultTab, std::set<std::string>& results, std::string first, std::string second,
	std::string result,int i, int j, Direction direction) {
	
	while (resultTab[i][j] > 0) {
		int maxValue = max(resultTab[i - 1][j], resultTab[i][j - 1]);
		if (maxValue == resultTab[i][j])
			if (resultTab[i - 1][j] <= resultTab[i][j - 1]) {
				if(resultTab[i - 1][j] < resultTab[i][j - 1])
					j -= 1;
				else {
					Direction newDirection;
					int newI = i, newJ = j;
					if (direction == UP) {
						newDirection = LEFT;
						newJ -= 1;
					}
					else {
						newDirection = UP;
						newI -= 1;
					}
					// found crossroad so this go still on his direction and call new with opposite direction
					getSubsequence(resultTab, results, first, second, result, newI, newJ, newDirection);
					if (direction == UP)
						i -= 1;
					else j -= 1;
				}
			}
			else  i -= 1;
		else {
			result = first[i - 1] + result;
			j -= 1;
			i -= 1;
		}
	}
	results.insert(result);
}

std::set<std::string> LCS::getAllLCS(std::string first, std::string second, bool print) {
	 std::set<std::string> results;
	 int firstLength = first.length(), secondLength = second.length();

	 // declare dynamic 2D array
	 int ** resultTab = LCSMatrix(first, second);
	 int lengthLCS = resultTab[firstLength][secondLength];

	 // search for all longest subsequences and add them to passed Set
	 getSubsequence(resultTab, results, first, second, "", firstLength, secondLength, UP);

	 // clean up array
	 for (int i = 0; i < firstLength; i++)
		 delete[] resultTab[i];
	 delete[] resultTab;
	 
	 // print if want
	 if (print) {
		 for (std::string lcs : results)
			 std::cout << lcs << std::endl;
	 }

	 return results;
}

