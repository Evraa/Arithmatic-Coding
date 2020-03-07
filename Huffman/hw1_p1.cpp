#include "huffman.h"

int main(int argc, char* argv[]) {


	char* func = argv[1];
	//stands for -entropy
	if (func[1] == 'e'&&func[2] == 'n'&&func[3] == 't'&&func[4] == 'r')
	{
		Huffman huff;
		char temp[255];
		std::cin >> temp;
		std::cout << temp << std::endl;
		int xres;
		int yres;
		std::cin >> xres;
		std::cin >> yres;
		int totalMessage = xres*yres;
		std::cout << totalMessage << std::endl;
		int intensity;
		std::cin >> intensity;
		int numOfBits = 0;
		std::vector<int> vec;
		int i = totalMessage;
		while (i > 0)
		{
			char* num = new char[3];
			std::cin >> num;

			if (num[0] == '0' || num[0] == '1' || num[0] == '2' || num[0] == '3' || num[0] == '4' || num[0] == '5' || num[0] == '6' || num[0] == '7' || num[0] == '8' || num[0] == '9')
			{
				int number = std::stoi(num);
				vec.push_back(number);
			}
			i--;
		}


		return(huff.compute_entropy(vec));
	}

	if (func[1] == 't' && func[2] == 'r')
	{
		Huffman huff;
		char temp[255];
		std::cin >> temp;
		std::cout << temp << std::endl;
		int xres;
		int yres;
		std::cin >> xres;
		std::cin >> yres;
		int totalMessage = xres*yres;
		int intensity;
		std::cin >> intensity;
		int numOfBits = 0;
		std::vector<int> vec;
		int i = totalMessage;
		while (i > 0)
		{
			char* num = new char[3];
			std::cin >> num;

			if (num[0] == '0' || num[0] == '1' || num[0] == '2' || num[0] == '3' || num[0] == '4' || num[0] == '5' || num[0] == '6' || num[0] == '7' || num[0] == '8' || num[0] == '9')
			{
				int number = std::stoi(num);
				vec.push_back(number);
			}
			i--;
		}

		huff.build_tree(vec);
		return 0;
	}
	if(argv[2])
		//char* ev2 = argv[2];
	//if (func[1] == 'e' && func[2] == 'n'&&func[3] == 'c'&&func[4] == 'o')
	{

		Huffman huff;
		char temp[255];
		std::cin >> temp;
		std::cout << temp << std::endl;
		int xres;
		int yres;
		std::cin >> xres;
		std::cin >> yres;
		int totalMessage = xres*yres;
		int intensity;
		std::cin >> intensity;
		int numOfBits = 0;
		std::vector<int> vec;
		std::ofstream orgFile("org.txt", std::ios::out);
		orgFile << temp << std::endl;
		orgFile << xres << " " << yres << std::endl;
		orgFile << intensity << std::endl;
		for (int i = 0; i < totalMessage; i++)
		{
			char* num = new char[3];
			std::cin >> num;
			if (num[0] == '0' || num[0] == '1' || num[0] == '2' || num[0] == '3' || num[0] == '4' || num[0] == '5' || num[0] == '6' || num[0] == '7' || num[0] == '8' || num[0] == '9')
			{
				int number = std::stoi(num);
				vec.push_back(number);
				orgFile << number << " ";
			}

		}
		orgFile.close();

		for (int i = xres; (vec[i] && i < totalMessage); i++)
		{
			vec[i] = vec[i] - vec[i - xres];
			std::cout << vec[i] << std::endl;
		}

		huff.encode(vec);
		std::cout << "evram" << std::endl;
		return 0;
	}


	//stands for -encode
	if (func[1] == 'e' && func[2] == 'n'&&func[3] == 'c'&&func[4] == 'o' )
	{
		Huffman huff;
		char temp[255];
		std::cin >> temp;
		std::cout << temp << std::endl;
		int xres;
		int yres;
		std::cin >> xres;
		std::cin >> yres;
		int totalMessage = xres*yres;
		std::cout << totalMessage << std::endl;
		int intensity;
		std::cin >> intensity;
		int numOfBits = 0;
		std::vector<int> vec;
		std::ofstream orgFile("org.txt", std::ios::out);
		orgFile << temp << std::endl;
		orgFile << xres << " " << yres << std::endl;
		orgFile << intensity << std::endl;
		for (int i = 0; i < totalMessage; i++)
		{
			char* num = new char[3];
			std::cin >> num;
			if (num[0] == '0' || num[0] == '1' || num[0] == '2' || num[0] == '3' || num[0] == '4' || num[0] == '5' || num[0] == '6' || num[0] == '7' || num[0] == '8' || num[0] == '9')
			{
				int number = std::stoi(num);
				vec.push_back(number);
				orgFile << number << " ";
			}

		}
		orgFile.close();
		huff.encode(vec);
		return 0;
	}


}