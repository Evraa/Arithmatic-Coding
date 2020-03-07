#include "lz77.h"

//
int main(int argc, char* argv[]) {
	char* ev = argv[1];
	if (ev[1] == 'e')
	{
		LZ77 lz;
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
		lz.setx(xres);
		lz.sety(yres);
		lz.setinten(intensity);
		lz.setChar(temp);
		std::vector<Triplet>* encoded_msg = new std::vector<Triplet>;
		std::vector<unsigned char> decoded_msg;
		int numOfBits = 0;
		std::string s, t, a;

		a = argv[2];
		int A = std::stoi(a);
		s = argv[3];
		int S = std::stoi(s);
		t = argv[4];
		int T = std::stoi(t);


		std::string tempo;
		std::vector<int> vec;

		if (totalMessage > 0)
		{
			int iterate = totalMessage;
			while (iterate > 0)
			{
				char* num = new char[3];
				std::cin >> num;
				if (num[0] == '0' || num[0] == '1' || num[0] == '2' || num[0] == '3' || num[0] == '4' || num[0] == '5' || num[0] == '6' || num[0] == '7' || num[0] == '8' || num[0] == '9')
				{
					int number = std::stoi(num);
					vec.push_back(number);
				}

				iterate--;
			}
		}
		
			int bits = lz.encode(vec, S, T, A, encoded_msg);
			std::cout << "Number of bits used: " << bits << std::endl;
			return 0;
	}
		if (ev[1] == 'd')
		{
			std::cout << "Decoding" << std::endl;
			LZ77 lz;
			char temp[255];
			std::cin >> temp;
			std::cout << temp << std::endl;
			char* ev2 = argv[2];
			char* ev3 = argv[3];
			int xres = std::stoi(ev2);
			int yres = std::stoi(ev3);
			//int tot = xres*yres;
			int tot;
			std::cin >> tot;
			std::cout << "Msg size: "<<tot << std::endl;
			std::vector<Triplet>* encoded_msg = new std::vector<Triplet>;
			std::vector<unsigned char> decoded_msg;
			lz.decode(*encoded_msg, &decoded_msg,tot,xres);
			return 0;
		}
		//stands for testing different values of STA
		if (ev[1] == 't')
		{
			LZ77 lz;
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
			lz.setx(xres);
			lz.sety(yres);
			lz.setinten(intensity);
			lz.setChar(temp);
			std::vector<Triplet>* encoded_msg = new std::vector<Triplet>;
			std::vector<unsigned char> decoded_msg;
			int numOfBits = 0;
			std::vector<int> vec;

			if (totalMessage > 0)
			{
				int iterate = totalMessage;
				while (iterate > 0)
				{
					char* num = new char[3];
					std::cin >> num;
					if (num[0] == '0' || num[0] == '1' || num[0] == '2' || num[0] == '3' || num[0] == '4' || num[0] == '5' || num[0] == '6' || num[0] == '7' || num[0] == '8' || num[0] == '9')
					{
						int number = std::stoi(num);
						vec.push_back(number);
					}

					iterate--;
				}
			}

			int i = 1;
			int S = 1;
			int A = 256;
			int arr[400];
			int ind = 0;
			while (i <= 20)
			{
				int T = 1;
				int j = 1;
				while (j <= 20) {
					arr[ind++] = lz.encode(vec, S, T, A, encoded_msg, i, j);
					j++;
					T = T + 1;
				}
				i++;
				S = S + 1;
			}
			int min = 0;
			for (int i = 1; i < 400; i++)
			{
				if (arr[i] < arr[min])
					min = i;
			}
			std::cout << min << std::endl;
			std::cout << arr[min] << std::endl;
			std::cout << 524288.0 / arr[min] << std::endl;
			return 0;
		}
		//stands for decoroleation
		if (ev[1] == 'r')
		{
			LZ77 lz;
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
			lz.setx(xres);
			lz.sety(yres);
			lz.setinten(intensity);
			lz.setChar(temp);
			std::vector<Triplet>* encoded_msg = new std::vector<Triplet>;
			std::vector<unsigned char> decoded_msg;
			int numOfBits = 0;
			std::vector<int> vec;

			if (totalMessage > 0)
			{
				int iterate = totalMessage;
				while (iterate > 0)
				{
					char* num = new char[3];
					std::cin >> num;
					if (num[0] == '0' || num[0] == '1' || num[0] == '2' || num[0] == '3' || num[0] == '4' || num[0] == '5' || num[0] == '6' || num[0] == '7' || num[0] == '8' || num[0] == '9')
					{
						int number = std::stoi(num);
						vec.push_back(number);
					}

					iterate--;
				}
			}
			int newl = 0;
			for (int i = xres; (vec[i] && i < totalMessage); i++)
			{
				vec[i] = vec[i] - vec[i - xres];
				std::cout << vec[i] << std::endl;
			}
			int bits = lz.encode(vec, 2, 4, 256, encoded_msg);
			std::cout << "Compression ratio : " << 524288.0 / bits << std::endl;
		}
		std::cout << "You may enter one of these commands: " << std::endl;
		std::cout << "./hw1_p3.exe -encode A S T < msgX.pgm" << std::endl;
		std::cout << "./hw1_p3.exe -encode A S T <msgX.pgm | ./hw1_p3.exe -decode xres yres intensity" << std::endl;
		std::cout << "./hw1_p3.exe -rdecorrelalate <msgX.pgm" << std::endl;
		std::cout << "Thank you." << std::endl;
		
		return 0;
}