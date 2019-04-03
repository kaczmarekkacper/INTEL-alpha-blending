#include <iostream>
#include <fstream>
int main(int argc, char* argv[])
{
	if( argc < 4)
	{
		printf("Please insert a first and second input file name and output file name.");
		return 0;
	}
	std::ifstream DataFile(argv[1], std::ios::binary);
	if(!DataFile.good())
	{
		printf("Something wrong with first input file.");
		return 0;
	}
	DataFile.seekg(0, std::ios::end);
	size_t filesize = (int)DataFile.tellg();
	DataFile.seekg(0);
	unsigned char output[filesize];
	if(DataFile.read((char*)output, filesize))
	{
		if(!fout.good())
			return 0;
		fout.write((char*)output, filesize);
	}
	std::ifstream DataFile(argv[2], std::ios::binary);
	if(!DataFile.good())
	{
		printf("Something wrong with second input file.");
		return 0;
	}
	DataFile.seekg(0, std::ios::end);
	size_t filesize2 = (int)DataFile.tellg();
	DataFile.seekg(0);
	unsigned char output2[filesize2];
	if(DataFile.read((char*)output2, filesize2))
	{
		if(!fout.good())
			return 0;
		fout.write((char*)output2, filesize2);
	}
	
	return 0;
}
