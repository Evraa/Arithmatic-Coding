#include "lz77.h"
// Your includes here

// Your implementations here

LZ77::LZ77()
{}

int LZ77::encode(const std::vector<int>& msg, int S, int T, int A, std::vector<Triplet>* encoded_msg,int first,int second)
{
	//return number of total bits, easy as they are standard
	long double newS = ceil(log2(S));
	long double newT = ceil(log2(T + S));
	long double newA = ceil(log2(A));
	//getting size of the whole vector
	int size = msg.size();
	this->totalSize = size;
	//creating an array to deal with, as it's more comfortable to me :D5
	int* arr = new int[size+2];
	arr[0] = -1; //starting point
	for (int i = 0; i < size; i++)
	{
		arr[i+1] = msg[i];
	}
	arr[size + 1] = -1;//ending point
	std::string s = std::to_string(first);
	std::string s2 = std::to_string(second);
	std::string file = "Triplet";
	file += s;
	file += s2;
	file += ".txt";
	std::ofstream outFile(file, std::ios::out);
	
	//first I'll read uniques and type zeros and their values
	std::cout << "(0,0," << arr[1] << ")" << std::endl;
	outFile << 0 << " " << 0 << " " << arr[1] << std::endl;
	int* ptrl = &arr[1];
	int* ptrr = &arr[2];
	int triplets = 0;
	int itsRange = 0;
	bool con = true;
	while (con)
	{
		//int* lookAhead = new int[T];
		//int* search = new int[S];
		int s = S;
		int t = T;
		int* arrayOfInd = new int[s];
		int itsRange = 0;
		int i = 0;
		int* search = ptrl;
		//getting all the matches
		while (i<s && *search != -1)
		{
			//50 100 50 100 150 50 150 200 250
			if (*ptrr == *search)
			{
				arrayOfInd[itsRange] = i;
				search--;
				itsRange++;
			}
			else 
			{
				search--;
			}
			i++;
			
		}
		//if no matches
		if (itsRange == 0)
		{
			//no matches found
			std::cout << "(0,0," << *ptrr << ")" << std::endl;
			outFile << 0 << " " << 0 << " " << *ptrr << std::endl;
			ptrl = ptrr;
			ptrr++;
		}
		//if there exist only one match
		if (itsRange == 1)
		{
			//Keep track of that match untill
				//1- non-matching character is found
				//2- ptrr is null
		//	search++;
			ptrl = ptrl - arrayOfInd[0];
			int pos = arrayOfInd[0];
			pos++;
			int length = 1;
			ptrr++;
			ptrl++;
			while (*ptrr == *ptrl && length < t)
			{
				ptrr++;
				ptrl++;
				length++;
			}
			std::cout << "(" <<pos<<","<<length<<"," << *ptrr << ")" << std::endl;
			outFile << pos << " "<< length<<" "<< *ptrr<< std::endl;

			ptrr++;
			ptrl = ptrr - 1;
		}
		//if the range is greater than one, it means, there exists more than one matching color, hence we need to dig further
		if (itsRange > 1)
		{
			//1- you need array of pointers, each assigned to one of the matching characters
			//2- keep looping untill they die and only one of them is alive
			//3- while looping, keep track of their positions, and length
			//4- with one survivor left (all are dead and no matching) take the least one of them
			int** arrayOfPointers = new int*[itsRange];
			int* pos = new int[itsRange];
			for (int r = 0; r < itsRange; r++)
			{
				arrayOfPointers[r] = ptrl - (arrayOfInd[r]) ;
				pos[r] = arrayOfInd[r];
			}
			bool Alive = true;
			int num = itsRange;
			int howlong = 1;
			int lastAlive = 0 ;
			while (Alive)
			{
				for (int l = 0; l < num; l++)
				{
					if (arrayOfPointers[l])
						arrayOfPointers[l]++;
				}
				ptrr++;
				for (int i = 0; i < num; i++)
				{
					int value = *(ptrr);
					if (arrayOfPointers[i] != NULL && value != *arrayOfPointers[i] )
					{
						arrayOfPointers[i] = NULL;
					}
				}
				
				int c = 0;
				
				for (int i = num-1; i >= 0; i--)
				{
					if (arrayOfPointers[i] == NULL)
						c++;
					else
						lastAlive = i;
				}
				if (c == itsRange || howlong == t)
				{
					//find that one
					//end of file?
					if (*ptrr == -1)
					{
						std::cout << "(" << pos[lastAlive] + 1 << "," << howlong << ",NULL)" << std::endl;
						outFile << pos[lastAlive] + 1 << " " << howlong  << " "<< -1 << std::endl;
						con = false;
					}

					else {
						std::cout << "(" << pos[lastAlive] + 1 << "," << howlong << "," << *(ptrr) << ")" << std::endl;
						outFile << pos[lastAlive] + 1 << " " << howlong << " " << *(ptrr) << std::endl;
					}
					ptrr++;
					
					ptrl = ptrr - 1;
					Alive = false;
				}
				
				howlong++;
			}




		}
		triplets++;
		//end of array?
		if (*ptrr == -1)
			con = false;
	}
	outFile.close();
	int bitsPerSymbol = triplets * (newS + newT + newA);
	outFile << "Total number of bits used " << bitsPerSymbol << std::endl;
	long double ratio = 524288.0 / bitsPerSymbol;
	outFile << "Compression ratio: " << ratio << std::endl;

	return bitsPerSymbol;
	
}

void LZ77::decode(const std::vector<Triplet>& encoded_msg, std::vector<unsigned char>* decoded_msg,int totalSize , int xRes)
{
	std::ifstream inFile("Triplet00.txt");
	/*std::string str;
	inFile >> str;
*/
	int* mainArr = new int[totalSize];
	int index = 0;
	int trip;
	int ind = 0;
	int len = 0;
	int ch = 0;
	int charNum = 0;
	while (!inFile.eof() && charNum < totalSize) {
		inFile >> ind;
		inFile >> len;
		inFile >> ch;
		std::cout << ind <<" "<<len<<" "<<ch<< std::endl;
		if (ind == 0)
		{
			mainArr[index] = ch;
			index++;
			charNum++;
		}
		else
		{
			int space = index - ind;
			for (int i = 0; i < len; i++)
			{
				mainArr[index++] = mainArr[space++];
				charNum++;
			}
			mainArr[index++] = ch;
			charNum++;
		}
	}
	inFile.close();
	std::ofstream* outFile;
	outFile = new std::ofstream("orig.txt");
	int newLine = 0;
	std::cout << "Here is the original message after being encoded with the above triplets, and then decoded" << std::endl;
	if (outFile->is_open()) {
		for (int i = 0; i < totalSize; i++)
		{
			*outFile << mainArr[i] << " ";
			newLine++;
			if (newLine == xRes)
			{
				*outFile << std::endl;
				newLine = 0;
			}
		}
	}
	outFile->close();

	return;
}
