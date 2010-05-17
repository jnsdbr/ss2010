#include <iostream>
#include <string>
#include "Grafikklasse.h"
#include "Image.h"

using namespace std;

int main()
{
	RGB_Pixel red(255,0,0);
	RGB_Pixel green(0,255,0);
	RGB_Pixel blue(0,0,255);
	RGB_Pixel yellow(255,255,0);
	RGB_Pixel white(255,255,255);
	RGB_Pixel black;
	
	const int height=300, width=300, iterations=100;
	
	Image I(width,height);
	
	Punkt TestPunkt(270,270,red);
	Rechteck r1(8,height/2-2,130,height/2+15,yellow);
	GrafikElement &g1=r1;

	try {
		TestPunkt.draw(I);	
		Rechteck(200,200,230,230,yellow).draw(I);
		RechteckGefuellt(50,50,100,100,red,blue).draw(I);
		Zeichen(20,20,'Y',green,yellow).draw(I);
		TextZeile(10,10,"Bo5 > JdB", white, black).draw(I);

		Linie(8, 17, 80, 17, red).draw(I);
		Kreis(150,150, yellow, 30).draw(I);	

	     	Linie l;
	      	l=g1;	
	}
	catch (bad_cast) {
		cout << "bad_cast";
	}
	catch (...) {
		cout << "fail";
	}
	BmpWrite("test.bmp",I);

	return 0;
}
