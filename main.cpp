#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <math.h>
#include <cstdint>
#include <cstring>

extern "C" void f(char*,char*, int, int, int, int);

using namespace std;

int main(int argc, char* argv[])
{
	
	char temporary[4];
	
	
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
	firstInput.seekg(0, ios::beg);
	
	//reading offset
	firstInput.seekg( 10, ios::beg );
	firstInput.read(temporary, 4);
	uint16_t offset1;
	memcpy(&offset1, temporary, sizeof(offset1));

	//reading width
	firstInput.seekg( 18, ios::beg );
	firstInput.read(temporary, 4);
	int width1;
	memcpy(&width1, temporary, sizeof(width1));

	//reading height
	firstInput.seekg( 22, ios::beg );
	firstInput.read(temporary, 4);
	int height1;
	memcpy(&height1, temporary, sizeof(height1));
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
	secondInput.seekg(0, ios::beg);
	
	//reading offset
	secondInput.seekg( 10, ios::beg );
	secondInput.read(temporary, 4);
	uint16_t offset2;
	memcpy(&offset2, temporary, sizeof(offset2));
	cout << offset2 << endl;
	//reading width
	secondInput.seekg( 18, ios::beg );
	secondInput.read(temporary, 4);
	int width2;
	memcpy(&width2, temporary, sizeof(width2));

	//reading height
	secondInput.seekg( 22, ios::beg );
	secondInput.read(temporary, 4);
	int height2;
	memcpy(&height2, temporary, sizeof(height2));
	secondInput.seekg(0, ios::beg);	
	
	// Checking size of files
	if ( length1 != length2 )
	{
		cout << "Size of files must be equal.\n";
	}
	cout << length1 << " " << length2 << " rozmiary " << endl;
	// Checking width
	if ( width1 != width2 )
	{
		cout << "Width of bmps must be equal.\n";
	}
	
	// Checking width
	if ( height1 != height2 )
	{
		cout << "Height of bmps must be equal.\n";
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
	
	sf::RenderWindow window(sf::VideoMode(width1, height1), "Alpha-Blending");
	
	sf::Image image1;
	image1.loadFromFile(argv[1]);
	sf::Texture texture1;
	if (!texture1.loadFromImage(image1))
	{
		cout << "Cant load first image./n";
		return 0;
	}
	sf::Sprite sprite1;
	sprite1.setTexture(texture1);
	window.draw(sprite1);
	
	sf::Image image2;
	image2.loadFromFile(argv[2]);
	sf::Texture texture2;
	if (!texture2.loadFromImage(image2))
	{
		cout << "Cant load second image./n";
		return 0;
	}
	sf::Sprite white;
	white.setTexture(texture2);
	sf::Sprite sprite2;
	sprite2.setTexture(texture2);
	window.draw(sprite2);
	window.display();
	firstInput.close();
	secondInput.close();
	while( window.isOpen())
	{	
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
    			sf::Vector2i localPosition = sf::Mouse::getPosition(window);
			if ( localPosition.x <= 0 || localPosition.y <= 0 || localPosition.x >= width1 || localPosition.y >= height1)
				continue;
			while(sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
			}
			firstInput.open(argv[1], ios::in | ios::binary);
			secondInput.open(argv[2], ios::in | ios::binary);
			cout << localPosition.x << " " << height1-localPosition.y << "\n";
			f(output1, output2, localPosition.x, height1-localPosition.y, width1, height1);
			// Writing to file
			ofstream fout1("out1.bmp", ios::binary);
			ofstream fout2("out2.bmp", ios::binary);
			if(!fout1.good())
			{
				cout << "Cant create a first output file.\n";
				return 0;
			}
			
			if(!fout2.good())
			{
				cout << "Cant create a second output file.\n";
				return 0;
			}
			
			fout1.write(output1, length1);
			fout1.close();
			fout2.write(output2, length2);
			fout2.close();
			firstInput.seekg(0, ios::beg);
			secondInput.seekg(0, ios::beg);
			if(!firstInput.read(output1, length1))
			{
				cout << "Can't read first file to char array.\n";
				return 0;
			}
			if(!secondInput.read(output2, length2))
			{
				cout << "Can't read second file to char array.\n";
				return 0;
			}
			firstInput.close();
			secondInput.close();
			sf::Image image3;
			image3.loadFromFile("out1.bmp");
			if (!texture1.loadFromImage(image3))
			{
				cout << "Cant display a first output file.\n";
				return 0;
			}
			window.clear();
			window.draw(white);
			sprite1.setTexture(texture1);
			
			
			window.draw(sprite1);
			sf::Image image4;
			image4.loadFromFile("out2.bmp");
			if (!texture2.loadFromImage(image4))
			{
				cout << "Cant display a second output file.\n";
				return 0;
			}
			sprite2.setTexture(texture2);
			
			
			window.draw(sprite2);
			window.display();
			
		}
		
	}
	return 0;
}
