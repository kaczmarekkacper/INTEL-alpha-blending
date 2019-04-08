#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include "fun.h"

using namespace std;

int main(int argc, char* argv[])
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Alpha-Blending");
	//sf::RenderWindow window;
	if( argc < 3)
	{
		cout <<"Please insert a first or second input file name and output file name.\n";
		return 0;
	}
	// Opening first file
	fstream firstInput;
	firstInput.open(argv[1], ios::in | ios::binary);
	if( !firstInput.good() )
	{
		cout <<"Something wrong with first input file.\n";
		return 0;
	};
	firstInput.seekg(0, ios::end);
	long length1 = firstInput.tellg();
	cout << "wszystko ok\n" << firstInput.tellg() << "\n";
	firstInput.seekg(0, ios::beg);
	// Opening seocnd file
	fstream secondInput;
	secondInput.open(argv[2], ios::in | ios::binary);
	if( !secondInput.good() )
	{
		cout <<"Something wrong with second input file.\n";
		return 0;
	}
	secondInput.seekg(0, ios::end);
	long length2 = secondInput.tellg();
	cout << "wszystko ok\n" << secondInput.tellg() << "\n";
	secondInput.seekg(0, ios::beg);
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
	firstInput.seekg(0, ios::beg);
	char output2[length2];
	if(!secondInput.read(output2, length2))
	{
		cout << "Can't read second file to char array./n";
		return 0;
	}
	secondInput.seekg(0, ios::beg);
	sf::Image image;
	image.loadFromFile(argv[1]);
	sf::Texture texture1;
	if (!texture1.loadFromImage(image))
	{
		cout << "Cant load first file./n";
		return 0;
	}
	sf::Sprite sprite;
	sprite.setTexture(texture1);
	window.draw(sprite);
	window.display();
	while( window.isOpen())
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
    			sf::Vector2i localPosition = sf::Mouse::getPosition(window);
			cout << localPosition.x << " " << localPosition.y << "\n";
			while(sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				sleep(1);
			}
			//fun(output1, output2, localPosition.x, localPosition.y);
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
				cout << "Can't read first file to char array.\n";
				return 0;
			}
			firstInput.seekg(0, ios::beg);
			//ifstream out;
			//out.open("out.bmp", ios::binary | ios::in);
			sf::Image image2;
			image2.loadFromFile("out.bmp");
			if (!texture1.loadFromImage(image))
			{
				cout << "Cant display output file.\n";
				return 0;
			}
			sprite.setTexture(texture1);
			fout.close();
			//out.close();
			window.display();
		}
		
	}
	firstInput.close();
	secondInput.close();
	return 0;
}
