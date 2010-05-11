#include "Image.h"
#include "BmpWrite.h"
#include "SimpleFont.h"
#include "TextSpeicher.h"

using namespace std;

int main()
{
	// Farben einstellen
	RGB_Pixel white(255,255,255);
	RGB_Pixel black(0,0,0);

	TextSpeicher ts("Joachim_Ringelnatz.txt");
	
	// Filename auf NULL gesetz damit die Datei im Destruktor nicht gespeichert wird.
	ts.SetFilename("no_write");	
		
	int font_height = SimpleFont::height();
	int font_width = SimpleFont::width();
	int max_width = ts.MaxColumns()*font_width;
	int max_height = (ts)*font_height;
	
	// Image groesse berechnen
	Image I(max_width+(2*font_width), max_height+font_height);

	// Von oben nach unten
	for(int Iy = max_height - font_height; Iy >= 0; Iy -= font_height)
	{
		// Von links nach rechts
		for(int Ix = font_width; Ix < max_width; Ix += font_width)
		{	
			// Positionierung
			SimpleFont a(ts[ts - 1 - (Iy / font_height)][(Ix - font_width) / font_width]);

			// Tabs abfangen
			if(ts[ts - 1 - (Iy / font_height)][(Ix - font_width) / font_width] != '\t')
			{
				// Pixel zeichnen
				for(int y = 0; y < font_height; y++)
				{
					for(int x = 0; x < font_width; x++)
					{
						I[Iy + y][Ix + x] = ((a[y][x]) ? white : black);
			    	}	
			  	}
			}
		}
	}

	BmpWrite("test.bmp",I);

	return 0;	
}
