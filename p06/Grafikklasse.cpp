#include <iostream>
#include "Grafikklasse.h"

using namespace std;

/**
 * Zechnet einen Punkt an Position x,y
 */
inline void Punkt::draw(Image& I) {
	I[xs][ys] = c;
}
/**
 * Bresenham-Linien-Algorithmus
 *
 * @param	Image&		I
 */
inline void Linie::draw(Image& I) 
{
	int x = xs;
	int y = ys;
	int D = 0;
	int HX = xe - xs;
	int HY = ye - ys;
	int xInc = 1;
	int yInc = 1;
	
	if(HX < 0) { xInc = -1; HX = -HX; }
	if(HY < 0) { yInc = -1; HY = -HY; }
  
	if(HY <= HX)
	{
		// ?
		const int _c = 2 * HX, M = 2 * HY;
		while(true)
		{
			Punkt(y, x, c).draw(I);
			if(x == xe) { break; }
			x += xInc;
			D += M;
			if(D > HX) { y += yInc; D -= _c; }
		}
	} 
	else
	{
		// ?
		const int _c = 2 * HY, M = 2 * HX;
		while(true)
		{
			Punkt(y, x, c).draw(I);
			if(y == ye) { break; }
			y += yInc;
			D += M;
			if(D > HY) { x += xInc; D -= _c; }
		} 
	}
}
/**
 * Zeichnet ein Rechteck von xs,ys nach xe,ye
 */
inline void Rechteck::draw(Image& I) {
	
	// Sauberer?
	Linie(xs, ys, xs, ye, c).draw(I);
	Linie(xs, ys, xe, ys, c).draw(I);
	Linie(xs, ye, xe, ye, c).draw(I);
	Linie(xe, ye, xe, ys, c).draw(I);
	
	/*
	for (int i=xs; i<=xe; i++) {	// Vertikal zeichnen
		I[i][ys] = c;
		I[i][ye] = c;
	}
	for (int i=ys; i<=ye; i++) {	// Horziontal zeichnen
		I[xs][i] = c;
		I[xe][i] = c;
	}
	*/
}
/**
 * Zeichnet ein gefuelltes Rechteck
 */
inline void RechteckGefuellt::draw(Image& I) {	
	for(int i = 0; i <= (xe-xs)/2; i++)
		Rechteck(xs+i,ys+i,xe-i,ye-i, (i==0)?c:f).draw(I);
}
/**
 * Bresenham-Kreis-Algorithmus
 *
 * @param	Image&		I
 */
inline void Kreis::draw(Image& I)
{
	int f = 1 - radius;
	int ddF_x = 0;
	int ddF_y = -2 * radius;
	int x = 0;
	int y = radius;

	Punkt(xs, ys + radius, c).draw(I);
	Punkt(xs, ys - radius, c).draw(I);
	Punkt(xs + radius, ys, c).draw(I);
	Punkt(xs - radius, ys, c).draw(I);
	
	while(x < y)
	{
		if(f >= 0)
		{
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		
		x++;
		ddF_x += 2;
		f += ddF_x + 1;

		Punkt(xs + x, ys + y, c).draw(I);
		Punkt(xs - x, ys + y, c).draw(I);
		Punkt(xs + x, ys - y, c).draw(I);
		Punkt(xs - x, ys - y, c).draw(I);
		Punkt(xs + y, ys + x, c).draw(I);
		Punkt(xs - y, ys + x, c).draw(I);
		Punkt(xs + y, ys - x, c).draw(I);
		Punkt(xs - y, ys - x, c).draw(I);		
	}
}
/**
 * Zeichnet ein farbiges Zeichen an der Position x,y
 */
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
/**
 * Zeichnet eine farbige Textzeile an der Position x,y
 */
inline void TextZeile::draw(Image& I) {
	int font_height = SimpleFont::height();
	int font_width = SimpleFont::width();
	for(int i=0; i<s.length(); i++)
		Zeichen(xs+i*font_width,ys,s[i],fg,bg).draw(I);
}


