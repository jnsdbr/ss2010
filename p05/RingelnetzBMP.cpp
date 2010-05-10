#include "image.h"
#include "bmpwrite.h"
#include "SimpleFont.h"
#include "TextSpeicher.h"


int main()
{
	// Farben einstellen
	RGB_Pixel white(255,255,255);
	RGB_Pixel black(0,0,0);

	TextSpeicher ts("Joachim_Ringelnatz.txt");
	
	// Filename auf NULL gesetz damit die Datei im Destruktor nicht gespeichert wird.
	ts.SetFilename("");	
	
	int font_height = SimpleFont::height();
	int font_width = SimpleFont::width();
	int	max_width = ts.MaxColumns();
	int max_height = ts;
	
	int I_posX = 0;
	int I_posY = 0;
	
	// Image groesse berechnen
	Image I(max_width * font_width, max_height * font_height);

	
	for(int i = max_width - 1; i >= 0; i--)
	{		
		for(int j = 0; j < max_height; j++)
		{
			SimpleFont sf(ts[i][j]);
			
			for(int y = 0; y < font_height; y++)
			{
				for(int x = 0; x < font_width; x++)
				{
					//I[y + (max_width - (i + 1)) * font_height][x + j * font_width] = ((sf[y][x]) ? white : black);
				}
			}
		}
	}

	BmpWrite("test.bmp",I);

	return 0;	
}