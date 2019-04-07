#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "f.h"

using namespace std;

int main(int argc, char* argv[])
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Alpha-Blending");
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
	temporary1.close();
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
	temporary2.close();
	// Checking size of files
	if ( length1 != length2 )
	{
		cout << "Size of files must be equal.\n";
	}
	// Copy files to char arrays
	char output1[length1];
	if(!firstInput.read(output1, length1))
	{
		cout << "Can't read first file to char array./n";
		return 0;
	}
	char output2[length2];
	if(!secondInput.read(output2, length2))
	{
		cout << "Can't read second file to char array./n";
		return 0;
	}
	sf::Texture texture1;
	if (!texture1.loadFromFile(argv[1]))
	{
		cout << "Cant load first file./n";
		return 0;
	}
	sf::Sprite sprite;
	sprite.setTexture(texture1);
	while( window.isOpen())
	{
		window.display();
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
    			sf::Vector2i localPosition = sf::Mouse::getPosition(window);
			cout << localPosition.x << " " << localPosition.y << "\n";
			while(sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				// waiting
			}
			f(output1, output2, localPosition.x, localPosition.y);
			// Writing to file
			ofstream fout("out.bmp", ios::binary);
			if(!fout.good())
			{
				cout << "Cant create a output file.\n";
				return 0;
			}
			fout.write(output1, length1);
			if(!firstInput.read(output1, length1))
			{
				cout << "Can't read first file to char array./n";
				return 0;
			}
			//ifstream out;
			//out.open("out.bmp", ios::binary | ios::in);
			if (!texture1.loadFromMemory(output1, length1))
			{
				cout << "Cant display output file./n";
				return 0;
			}
			sprite.setTexture(texture1);
			fout.close();
			//out.close();
		}
		
	}
	firstInput.close();
	secondInput.close();
	return 0;
}
