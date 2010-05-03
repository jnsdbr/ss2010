#include "Image.h"

class HLine
{
	private:
		int x_pos, y_pos, length;
		RGB_Pixel color;
	
	public:
		HLine(int x, int y, int l, RGB_Pixel c) : x_pos(x), y_pos(y), length(l), color(c) {};
		~HLine() {};
		void draw(Image &I)
		{
			for (int i = x_pos; i < (x_pos+length); i++) 
			{
				I[i][y_pos]=color;
			}	
		}
};