#include "arithmetic.h"

// Your includes here

// Your implementations here

double Arithmetic::binary_to_decimal(const bitset<32>& fraction)
{
	//initiallize the double with zero
	double dec = 0;
	//initiallize the power with 1
	int powr = 1;
	//loop upon the full decimal number to check on each bit
	for (int i = 0; i < 32; i++)
	{
		//read the ith bit
		int bit = fraction[i];
		//if one, add its power value
		if (bit == 1)
		{
			dec = dec + (pow(2,-powr));
		}
		//increment the power with each iteration
		powr++;
	}
	//return the decimal converted value
	return dec;

}



void Arithmetic::printOutMessage(int k , vector<string>* encoded_msg)
{
	ofstream outfile;
	outfile.open("test.txt", ios::out);
	outfile << k << endl;
	int n = encoded_msg->size();
	vector<string> encoded_msg2;
	for (int i = 0; i < n; i++)
	{
	string ev2 = encoded_msg->back();
	encoded_msg->pop_back();
	encoded_msg2.push_back(ev2);
	}
	for (int i = 0; i < n; i++)
	{
		string ev2 = encoded_msg2.back();
		encoded_msg2.pop_back();
		outfile << ev2 << endl;
		
	}
	
	
}

// Function to convert decimal to binary upto 
// k-precision after decimal point 
bitset<32> Arithmetic::decimal_to_binary(double fraction,int k)
{
	//problem here!
	bitset<32> binary;
	int n = k;
	while (k>0)
	{
		// Find next bit in fraction 
		fraction *= 2;
		//if last bit, assert and exit
		if (fraction == 1)
		{
			binary[n - k] = 1;
			break;
		}
		//get its value
		int fract_bit = fraction;

		//if 1, assign one and decrement the fraction
		if (fract_bit == 1)
		{
			fraction -= fract_bit;
			binary[n- k] = 1;
		}
		//if zero, assign zero, and keep the loop
		else
			binary[n - k] = 0;
		k--;
	}

	return binary;
}

int Arithmetic::encode(const vector<unsigned char>& msg, int num_symbols_per_block, vector<string>* encoded_msg)
{
	//for testing
	ofstream outfile;
	outfile.open("test.txt", ios::out);
	int m = num_symbols_per_block;
	int numverOfBitsinTotal = 0;
	encoded_msg = new vector<string>;
	int oldsizeOfMsg = msg.size();
	int* arr = new int[oldsizeOfMsg];
	string numb;
	int three = 3;
	int it = 0;
	int sizeOfMsg = 0;
	for (int i = 0; i < oldsizeOfMsg; i++)
	{
		if (msg[it] != 'x')
		{
			numb.push_back(msg[it]);
			it++;
			oldsizeOfMsg--;
		}
		if (msg[it] != 'x')
		{
			numb.push_back(msg[it]);
			it++;
			oldsizeOfMsg--;
		}
		if (msg[it] != 'x')
		{
			numb.push_back(msg[it]);
			it++;
			oldsizeOfMsg--;
		}
		it++;
		
		//now numb, has the right number, ie: 50
		 arr[i] = std::stoi(numb);
		 numb = "";
		 sizeOfMsg++;
	}

	int maximumM = m ;
	/////////////
	float* prob = new float[sizeOfMsg];
	int* unique = new int[sizeOfMsg];
	for (int i = 0; i < sizeOfMsg; i++)
	{
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
	float totalSize = sizeOfMsg;
	float* accProb = new float[newCount];
	for (int i = 0; i < newCount; i++)
	{
		accProb[i] = 1;
	}

	accProb[0] = 0.0f;
	for (int i = 0; i < newCount; i++)
	{
		prob[i] = prob[i] / totalSize;
		accProb[i + 1] = accProb[i] + prob[i];
	}
	accProb[newCount] = 1;
	//////////
	//NOW arry has the numbers we need in integers
	//lets assign their probablities and frequinceies
	//
	int cycle = 0;
	
	int division = sizeOfMsg / m;
	int remain = sizeOfMsg%m;
	for (int hi = 0; hi < division + 1; hi++)
	{
		if (hi == division)
		{
			if (remain > 0)
			{
				m = remain;
			}
			else
				break;
		}
		
		
		int tempo = arr[0+ (maximumM*cycle)];
		float upper = 0.0f;
		float lower = 0.0f;

		for (int i = 0; i < newCount; i++)
		{
			if (tempo == unique[i])
			{
				lower = accProb[i];
				upper = accProb[i + 1];
				break;
			}
		}
		//Now uniques and probabilities are ready
		for (int i = 1; i < m; i++)
		{
			//Arithmetic coding starts here
			tempo = arr[i+(maximumM*cycle)];
			float diff = upper - lower;
			for (int l = 0; l < newCount; l++)
			{
				if (tempo == unique[l])
				{
					float fxnow = accProb[l + 1];
					float fxminus1 = accProb[l];
					upper = lower + (diff*fxnow);
					lower = lower + (diff * fxminus1);
					break;
				}
			}
		}
		//now upper and lower are correct, not so accurate, but correct
		float tag = (upper + lower) / 2.0f;
		float diff = (upper - lower);
		int k = 0;
		if (diff == 0 || isnan(diff))
		{
			k = 32;
		}
		else
		{
			 k = ceil(log2(1 / diff)) + 1;
		}
		if (k > 32)
			k = 32;
		bitset<32> ev = decimal_to_binary(tag, k);
		string printed = ev.to_string();
		int j = printed.length() - 1;
		
		for (int l = 0; l < j; l++, j--)
		{
			char temp = printed[l];
			printed[l] = printed[j];
			printed[j] = temp;
		}
		
		printed.resize(k);
		encoded_msg->push_back(printed);
		numverOfBitsinTotal += k;
		
		cycle++;
		
		
	}
	//Print out the encoded message
	printOutMessage(numverOfBitsinTotal, encoded_msg);
	return numverOfBitsinTotal;
}

void Arithmetic::decode(const vector<bitset<32>>& encoded_msg, int num_symbols_per_block, vector<unsigned char>* decoded_msg)
{

}

