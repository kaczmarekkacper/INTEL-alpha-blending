#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

int main(int argc, char* argv[])
{
	if( argc < 3)
	{
		cout <<"Please insert a first or second input file name and output file name.\n";
		return 0;
	}
	// Opening first file
	fstream firstInput;
	fstream temporary1;
	temporary1.open(argv[1], ios::in | ios::binary);
	firstInput.open(argv[1], ios::in | ios::binary);
	if( !firstInput.good() || !temporary1.good())
	{
		cout <<"Something wrong with first input file.\n";
		return 0;
	};
	temporary1.seekg(0, ios::end);
	long length1 = temporary1.tellg();
	cout << "wszystko ok\n" << temporary1.tellg() << "\n";
	// Opening seocnd file
	fstream secondInput;
	fstream temporary2;
	temporary2.open(argv[2], ios::in | ios::binary);
	secondInput.open(argv[2], ios::in | ios::binary);
	if( !secondInput.good()|| !temporary2.good() )
	{
		cout <<"Something wrong with second input file.\n";
		return 0;
	}
	temporary2.seekg(0, ios::end);
	long length2 = temporary2.tellg();
	cout << "wszystko ok\n" << temporary2.tellg() << "\n";
	// Checking size of files
	if ( length1 != length2 )
	{
		cout << "Size of files must be equal.\n";
	}
	unsigned char output1[length1];
	if(firstInput.read((char*)output1, length1))
	{
		ofstream fout(argv[1], ios::binary);
		if(!fout.good())
			return 0;
		fout.write((char*)output1, length1);
	}
	return 0;
}
