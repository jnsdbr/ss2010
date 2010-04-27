#include "Image.h"

class VLine
{
	private:
		int x_pos, y_pos, length;
		RGB_Pixel color;
	
	public:
		VLine(int x, int y, int l, RGB_Pixel c) : x_pos(x), y_pos(y), length(l), color(c) {};
		~VLine() {};
		void draw(Image &I)
		{
			for (int i = y_pos; i < (y_pos+length); i++) 
			{
				I[i][x_pos]=color;
			}
			
		}
}