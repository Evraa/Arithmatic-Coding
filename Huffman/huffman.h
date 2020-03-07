#ifndef _HUFFMAN_H
#define _HUFFMAN_H

#include <vector>
#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include <bitset>
#include <cmath>
#include <math.h>   
//using namespace std;
// Define the tree node struct here ...
struct Node {
	// ...
};

// Define a symbol struct here to hold the symbol (grayscale value)
// and its probability/frequency
struct Symbol {
	// Grayscale value of the symbol
	unsigned char val;
	// ...
};
// A Min Heap: Collection of 
// min-heap (or Huffman tree) nodes 
struct MinHeap {

	// Current size of min heap 
	unsigned size;

	// capacity of min heap 
	unsigned capacity;

	// Attay of minheap node pointers 
	struct MinHeapNode** array;
};

struct MinHeapNode {

	// One of the input characters 
	int  data;

	// Frequency of the character 
	long double freq;

	// Left and right child of this node 
	struct MinHeapNode *left, *right;
};
#define MAX_TREE_HT 100 

class Huffman {
public:
	// Constructor and destructor
	Huffman();
	int arrayofsymbols(std::vector<int> arr, int *& u, long double *& pr, long double *& ipr);
	
	// A function to compute the entropy of the input message and
	// stores the probabilities of the different symbols in
	// the input array.
	long double compute_entropy(std::vector<int> vec);

	MinHeapNode * newNode(int data, long double freq);

	MinHeap * createMinHeap(unsigned capacity);

	void swapMinHeapNode(MinHeapNode ** a, MinHeapNode ** b);

	void minHeapify(MinHeap * minHeap, int idx);

	int isSizeOne(MinHeap * minHeap);

	MinHeapNode * extractMin(MinHeap * minHeap);

	void insertMinHeap(MinHeap * minHeap, MinHeapNode * minHeapNode);

	void buildMinHeap(MinHeap * minHeap);

	void printArr(int arr[], int n);

	

	int isLeaf(MinHeapNode * root);

	MinHeap * createAndBuildMinHeap(int * data, long double freq[], int size);

	MinHeapNode * buildHuffmanTree(int * data, long double freq[], int size);

	void printCodes(MinHeapNode * root, int arr[], int top);

	// A function to build the Huffman tree given the computed
	// symbol probabilities.
	void build_tree(std::vector<int> arr);

	void printInFile();

	int encode(std::vector<int> dataofthefile);


	// A function to print the code table computed from the build_tree above.
	void print_code_table();

	// A function to encode the input message using the computed tree 
	// and store the output in the output array, where each entry
	// corresponds to the codeword for an input symbol in the message.
	//
	// The function should return the number of bits in the encoded 
	// message.
	//int encode(vector<int> arr);

private:
	// Data members here ... for example to store the tree and the codeword 
	// hash table
	Node* tree;
	// ...
	int* symbols ;
	long double* probabilities;
	std::vector<int> values;
	std::vector<std::string> codeWords;
	
};

#endif