#include "huffman.h"

// Your implementations here

Huffman::Huffman()
{
	this->symbols = new int[256];
	this->probabilities = new long double[256];
	/*this->values = new int[256];
	this->codewords = new string[256];*/
	
	
}

int Huffman::arrayofsymbols(std::vector<int> arr, int*& u, long double*& pr, long double*& ipr)
{
	int sizeOfMsg = arr.size();
	long double* prob = new long double[sizeOfMsg];
	int* unique = new int[sizeOfMsg];

	for (int i = 0; i < sizeOfMsg; i++)
	{
		//initializng probabilities and uniques
		prob[i] = 0.0f;
		unique[i] = -1;
	}
	int temp;
	for (int i = 0; i < sizeOfMsg; i++)
	{
		temp = arr[i];
		if (unique[0] == -1)
		{
			unique[0] = temp;
			prob[0]++;
		}
		else
		{
			//iterate to find matches
			int k = 0;
			bool appended = false;
			while (unique[k] != -1)
			{
				if (unique[k] == temp)
				{
					//append that k's probability
					prob[k]++;
					appended = true;
					break;
				}
				k++;
			}
			if (!appended)
			{
				unique[k] = temp;
				prob[k] = 1;
			}
		}
	}
	int newCount = 0;

	while (unique[newCount] != -1)
	{
		newCount++;
	}

	int totalSize = sizeOfMsg;
	long double* invProb = new long double[sizeOfMsg];
	for (int i = 0; i < newCount; i++)
	{
		prob[i] = prob[i] / sizeOfMsg;
		invProb[i] = 1 / prob[i];
	}
	this->symbols = unique;
	this->probabilities = prob;
	u = unique;
	pr = prob;
	ipr = invProb;

	std::ofstream myfile("data.txt", std::ios::out);
	myfile << newCount << std::endl;
	for (int i = 0; i < newCount; i++)
	{
		myfile << unique[i] << std::endl;;
	}
	for (int i = 0; i < newCount; i++)
	{
		myfile << prob[i] << std::endl;;
	}
	myfile.close();
	return newCount;
}


long double Huffman::compute_entropy(std::vector<int> arr)
{
	int sizeOfMsg = arr.size();
	long double* prob = new long double[sizeOfMsg];
	int* unique = new int[sizeOfMsg];
	long double* invProb = new long double[sizeOfMsg];
	int newCount = arrayofsymbols(arr,unique,prob, invProb);
	//Compute The Entropy
	long double h = 0;
	for (int i = 0; i < newCount; i++)
	{
		long double logy = std::log2(invProb[i]);
		h += (logy*prob[i]);
	}

	return h;
}



// A utility function allocate a new 
// min heap node with given character 
// and frequency of the character 
struct MinHeapNode*  Huffman::newNode(int data, long double freq)
{
	struct MinHeapNode* temp
		= (struct MinHeapNode*)malloc
		(sizeof(struct MinHeapNode));

	temp->left = temp->right = NULL;
	temp->data = data;
	temp->freq = freq;

	return temp;
}


// A utility function to create 
// a min heap of given capacity 
struct MinHeap*  Huffman::createMinHeap(unsigned capacity)

{

	struct MinHeap* minHeap
		= (struct MinHeap*)malloc(sizeof(struct MinHeap));

	// current size is 0 
	minHeap->size = 0;

	minHeap->capacity = capacity;

	minHeap->array
		= (struct MinHeapNode**)malloc(minHeap->
			capacity * sizeof(struct MinHeapNode*));
	return minHeap;
}

// A utility function to 
// swap two min heap nodes 
void  Huffman::swapMinHeapNode(struct MinHeapNode** a,
	struct MinHeapNode** b)

{

	struct MinHeapNode* t = *a;
	*a = *b;
	*b = t;
}

// The standard minHeapify function. 
void  Huffman::minHeapify(struct MinHeap* minHeap, int idx)

{

	int smallest = idx;
	int left = 2 * idx + 1;
	int right = 2 * idx + 2;

	if (left < minHeap->size && minHeap->array[left]->
		freq < minHeap->array[smallest]->freq)
		smallest = left;

	if (right < minHeap->size && minHeap->array[right]->
		freq < minHeap->array[smallest]->freq)
		smallest = right;

	if (smallest != idx) {
		swapMinHeapNode(&minHeap->array[smallest],
			&minHeap->array[idx]);
		minHeapify(minHeap, smallest);
	}
}

// A utility function to check 
// if size of heap is 1 or not 
int  Huffman::isSizeOne(struct MinHeap* minHeap)
{

	return (minHeap->size == 1);
}

// A standard function to extract 
// minimum value node from heap 
struct MinHeapNode*  Huffman::extractMin(struct MinHeap* minHeap)

{

	struct MinHeapNode* temp = minHeap->array[0];
	minHeap->array[0]
		= minHeap->array[minHeap->size - 1];

	--minHeap->size;
	minHeapify(minHeap, 0);

	return temp;
}

// A utility function to insert 
// a new node to Min Heap 
void  Huffman::insertMinHeap(struct MinHeap* minHeap,
	struct MinHeapNode* minHeapNode)

{

	++minHeap->size;
	int i = minHeap->size - 1;

	while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {

		minHeap->array[i] = minHeap->array[(i - 1) / 2];
		i = (i - 1) / 2;
	}

	minHeap->array[i] = minHeapNode;
}

// A standard function to build min heap 
void  Huffman::buildMinHeap(struct MinHeap* minHeap)

{

	int n = minHeap->size - 1;
	int i;

	for (i = (n - 1) / 2; i >= 0; --i)
		minHeapify(minHeap, i);
}

// A utility function to print an array of size n 
void  Huffman::printArr(int arr[], int n)
{
	int i;
	std::string code = "";
	for (i = 0; i < n; ++i)
	{
		std::cout << arr[i];
		std::string str = std::to_string(arr[i]);
		code += str;
	}
	this->codeWords.push_back(code);
	std::cout << "\n";
	
}

// Utility function to check if this node is leaf 
int  Huffman::isLeaf(struct MinHeapNode* root)

{

	return !(root->left) && !(root->right);
}

// Creates a min heap of capacity 
// equal to size and inserts all character of 
// data[] in min heap. Initially size of 
// min heap is equal to capacity 
struct MinHeap*  Huffman::createAndBuildMinHeap(int* data, long double freq[], int size)

{

	struct MinHeap* minHeap = createMinHeap(size);

	for (int i = 0; i < size; ++i)
		minHeap->array[i] = newNode(data[i], freq[i]);

	minHeap->size = size;
	buildMinHeap(minHeap);

	return minHeap;
}

// The main function that builds Huffman tree 
struct MinHeapNode*  Huffman::buildHuffmanTree(int* data, long double freq[], int size)

{
	struct MinHeapNode *left, *right, *top;

	// Step 1: Create a min heap of capacity 
	// equal to size. Initially, there are 
	// modes equal to size. 
	struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);

	// Iterate while size of heap doesn't become 1 
	while (!isSizeOne(minHeap)) {

		// Step 2: Extract the two minimum 
		// freq items from min heap 
		left = extractMin(minHeap);
		right = extractMin(minHeap);

		// Step 3: Create a new internal 
		// node with frequency equal to the 
		// sum of the two nodes frequencies. 
		// Make the two extracted node as 
		// left and right children of this new node. 
		// Add this node to the min heap 
		// '$' is a special value for internal nodes, not used 
		top = newNode('$', left->freq + right->freq);

		top->left = left;
		top->right = right;

		insertMinHeap(minHeap, top);
	}

	// Step 4: The remaining node is the 
	// root node and the tree is complete. 
	return extractMin(minHeap);
}

// Prints huffman codes from the root of Huffman Tree. 
// It uses arr[] to store codes 
void  Huffman::printCodes(struct MinHeapNode* root, int arr[], int top)

{
	
	// Assign 0 to left edge and recur 
	if (root->left) {

		arr[top] = 0;
		printCodes(root->left, arr, top + 1);
	}

	// Assign 1 to right edge and recur 
	if (root->right) {

		arr[top] = 1;
		printCodes(root->right, arr, top + 1);
	}

	// If this is a leaf node, then 
	// it contains one of the input 
	// characters, print the character 
	// and its code from arr[] 
	if (isLeaf(root)) {

		std::cout << root->data << ": ";
		//codeWords << root->data << " ";
		values.push_back(root->data);
		printArr(arr, top);
		
	}
}

//// The main function that builds a 
//// Huffman Tree and print codes by traversing 
//// the built Huffman Tree 
//void HuffmanCodes(int* data, long double freq[], int size)
//
//{
//	// Construct Huffman Tree 
//	struct MinHeapNode* root
//		= buildHuffmanTree(data, freq, size);
//
//	// Print Huffman codes using 
//	// the Huffman tree built above 
//	int arr[MAX_TREE_HT], top = 0;
//
//	printCodes(root, arr, top);
//}


void Huffman::build_tree(std::vector<int> arr)
{
	//initialize some parameters
	//call array of symbols
	//create tree
	//print it out
	int sizeOfMsg = arr.size();
	long double* prob = new long double[sizeOfMsg];
	int* unique = new int[sizeOfMsg];
	long double* invProb = new long double[sizeOfMsg];
	int newCount = arrayofsymbols(arr, unique, prob, invProb);
	struct MinHeapNode* tree;
	
	tree = buildHuffmanTree(unique, prob, newCount);

	// Print Huffman codes using 
	// the Huffman tree built above 
	int ar[MAX_TREE_HT], top = 0;
	printCodes(tree, ar, top);
	printInFile();
	return;

}
void Huffman::printInFile()
{
	
	std::ofstream file;
	file.open("codewords.txt", std::ios::out);
	int size = this->values.size();
	for (int i = 0; i < size; i++)
	{
		file << this->values[i]<< " ";
		file << this->codeWords[i] << std::endl;

	}

}
//build huffman tree for these words
//replace each number in the origianl photo with the new codeword
int Huffman::encode(std::vector<int> dataofthefile)
{
	this->build_tree(dataofthefile);
	std::ifstream original("org.txt");
	std::ofstream input("decoded.txt");
	char temp[255];
	original.getline(temp, 255);
	int xres;
	int yres;
	original >> xres;
	original >> yres;
	int totalMessage = xres*yres;
	int intensity;
	original >> intensity;
	input << temp << std::endl;
	input << xres <<" "<<yres << std::endl;
	input << intensity << std::endl;
	int numberOfBits = 0;
	for (int i = 0; i<totalMessage; i++)
	{
		char* num = new char[256];
		original >> num;

		if (num[0] == '0' || num[0] == '1' || num[0] == '2' || num[0] == '3' || num[0] == '4' || num[0] == '5' || num[0] == '6' || num[0] == '7' || num[0] == '8' || num[0] == '9')
		{
			int number = std::stoi(num);
			//check on that integer
			int i = 0;
			while (values[i]!= number)
			{
				i++;
			}
			std::string cw = codeWords[i];
			numberOfBits = numberOfBits + cw.size();
			std::bitset<128>bs(cw);
			int ev = (int)(bs.to_ulong());
			input <<ev << " ";
		}
	}
	std::cout << numberOfBits <<" Bits   "<< numberOfBits/8 <<" bytes"<< std::endl;
	return numberOfBits;
}
