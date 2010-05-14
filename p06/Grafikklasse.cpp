#include <iostream>
#include "Grafikklasse.h"

using namespace std;

inline void Punkt::draw(Image& I) {
	I[xs][ys] = c;
}

inline void Rechteck::draw(Image& I) {
	for (int i=xs; i<=xe; i++) {	// Vertikal zeichnen
		I[i][ys] = c;
		I[i][ye] = c;
	}
	for (int i=ys; i<=ye; i++) {	// Horziontal zeichnen
		I[xs][i] = c;
		I[xe][i] = c;
	}
}

inline void RechteckGefuellt::draw(Image& I) {
	for(int i = 0; i <= (xe-xs)/2; i++)
		Rechteck(xs+i,ys+i,xe-i,ye-i, (i==0)?c:f).draw(I);
}

void Zeichen::draw(Image& I) {
	int font_height = SimpleFont::height();
	int font_width = SimpleFont::width();
	SimpleFont DasZuZeichnendeZeichen(ch);
	// Pixel zeichnen
	for(int y = 0; y < font_height; y++)
	{
		for(int x = 0; x < font_width; x++)
		{
			I[ys + y][xs + x] = ((DasZuZeichnendeZeichen[y][x]) ? fg : bg);
	   	}	
	}
}

inline void TextZeile::draw(Image& I) {
	int font_height = SimpleFont::height();
	int font_width = SimpleFont::width();
	for(int i=0; i<s.length(); i++) {
		Zeichen(xs+i*font_width,ys,s[i],fg,bg).draw(I);
		cout << s[i] << endl;
	}
}


