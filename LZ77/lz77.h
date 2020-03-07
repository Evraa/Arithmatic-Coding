#ifndef _LZ77_H
#define _LZ77_H


#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include <bitset>
#include <cmath>
#include <math.h>   
// Struct to hold the triplet for each entry
struct Triplet {
	// Starting position of the longest match in the previous string
	// i.e. number of symbols to look back.
	unsigned int j;

	// Length of the longest match i.e. number of symbols to copy
	// starting at the match position.
	unsigned int k;

	// Uncompressed code of the symbol following the match. The number
	// of bits here will depend on the size of the alphabet in use.
	unsigned char c;
};

class LZ77 {
public:
	// Constructor and destructor
	LZ77();
	int encode(const std::vector<int>& msg, int S, int T, int A, std::vector<Triplet>* encoded_msg, int i =0, int j=0);
	// A function to encode the input message using LZ77.
	// 
	// Inputs:
	// - the input message
	// - S the size of the match buffer i.e. the maximum distance to look
	//   backward for a match
	// - T the size of the lookahead buffer   
	// - A the size of the alphabet
	//
	// The encoded message contains the triplets output from the input msg.
	//
	// The function should return the number of bits in the encoded 
	// message.
	

	void decode(const std::vector<Triplet>& encoded_msg, std::vector<unsigned char>* decoded_msg, int totalSize, int xRes);


	// A function to decode a message encoded using LZ77.
	/*void decode(const std::vector<Triplet>& encoded_msg,
		std::vector<unsigned char>* decoded_msg);
*/
	void setx(int x) { this->x = x; }
	void sety(int y) { this->y = y; }
	void setinten(int inten) { this->inten = inten;}
	void setChar(char* temp) { this->prob = temp; }
private:
	// Any data members here ... 
	int totalSize;
	int x;
	int y;
	int inten;
	char* prob;
};

#endif