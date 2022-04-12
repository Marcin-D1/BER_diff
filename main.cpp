#include <iostream>
#include<fstream>
#include <bitset>
#include <chrono>
#include<ctime>

using namespace std::chrono;
uint8_t hammingDistance(uint8_t n1, uint8_t n2);

int main(int argc, char * argv[])
{
    auto start = high_resolution_clock::now();
    std::ifstream inFile;
    std::ofstream out("log2.txt", std::ios_base::app);
	size_t size = 0;
	inFile.open(argv[1], std::ios::binary);

    char* oData = 0;
	if(inFile.is_open()) {
		inFile.seekg(0, std::ios::end);
		size = inFile.tellg();
		inFile.seekg(0, std::ios::beg);

		oData = new char[size+1];
		inFile.read(oData, size);
		oData[size] = '\0';
	}

    std::ifstream inFile2;
	size_t size2 = 0;
	inFile2.open(argv[2], std::ios::binary);

    char* oData2 = 0;
	if(inFile2.is_open()) {
		inFile2.seekg(0, std::ios::end);
		size2 = inFile2.tellg();
		inFile2.seekg(0, std::ios::beg);

		oData2 = new char[size+1];
		inFile2.read(oData2, size2);
		oData2[size] = '\0';
	}

    std::string str(oData);
    std::string str2(oData2);
    int diffCounter = 0;
    int allCounter = 0;
    for (std::size_t i = 0; i < str.size(); ++i)
    {
        uint8_t a = uint8_t(str.c_str()[i]);
        uint8_t b= uint8_t(str2.c_str()[i]);
        diffCounter  +=(int)hammingDistance(a,b);
        allCounter++;
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::time_t t = std::time(0);
    out << "Pliki: " << argv[1]<< " " << argv[2]<<std::endl;
    out << "Timestamp: "<<t << std::endl;
    out << "Czas trwania: " << duration.count() <<" microseconds"<< std::endl;
    out << "Ilość porównanych bitów: "<<allCounter<<std::endl;
    out << "BER "<<diffCounter<<std::endl<<std::endl<<std::endl<<std::endl;


    return 0;
}

uint8_t hammingDistance(uint8_t n1, uint8_t n2)
{
    uint8_t x = n1 ^ n2; // XOR
    uint8_t setBits = 0;
    while (x > 0)
    {
        setBits += x & 1;
        x >>= 1;
    }
    return setBits;
}
