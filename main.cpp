#include <iostream>
#include "LCS.h"

int main()
{
	LCS lcs;
	lcs.getLCS("abcdefg", "abxdfg", true); // expecting: abdfg
	lcs.getAllLCS("abcdefg", "abxdfg", true); // expecting: abdfg
	lcs.printMatrix("abcdefg", "abxdfg");
	lcs.getAllLCS("bdcaba", "abcbdab", true); // expecting: bdab, bcba, bcab
	lcs.printMatrix("bdcaba", "abcbdab");
}



