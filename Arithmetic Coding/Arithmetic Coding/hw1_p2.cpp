#include "arithmetic.h"


int main(int argc, char* argv[]) {
	// read parameters here ...
	//What do I need?
	//first, read message by blocks
	int m = 5;
	ifstream myfile;

	Arithmetic arth;
	vector<unsigned char> vec;
	char temp[255];
	myfile.open("./data/earth.pgm");
	//freeing the first three lines
	for (int i=0; i<3; i++)
		myfile.getline(temp, 255);

//	vector<bitset<32>>* encoded_message = NULL;
	vector<string>* encoded_message = NULL;

	//encoded_message->push_back(0);
	int numOfBits = 0;
	if (myfile.is_open())
	{
		while (!myfile.eof())
		{
			//Our main encoding code lies here
			myfile.getline(temp, 255, ' ');

				char* ev = temp;
				if (ev[0] == '0' || ev[0] == '1' || ev[0] == '2' || ev[0] == '3' || ev[0] == '4' || ev[0] == '5' || ev[0] == '6' || ev[0] == '7' || ev[0] == '8' || ev[0] == '9' )
				{
					if (ev[0])
						vec.push_back(ev[0]);
					if (ev[1])
						vec.push_back(ev[1]);
					if (ev[2])
						vec.push_back(ev[2]);
					//to know where the string stopped when encoding
					vec.push_back('x');
				}
		}
		//for sure vec is ready with x seperated strings
		numOfBits = arth.encode(vec, m, encoded_message);

	}

	


	
	// perform the required operation ...

	// write output ...
	
	return 0;
}