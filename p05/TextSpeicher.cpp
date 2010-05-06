#include "TextSpeicher.h"

using namespace std;

void TextSpeicher::expand(int s)
{
	
	if(s > lines)
	{
		TextZeile **tmpArray = new *TextZeile [size + s];
		
		for(int i = 0; i < s; i++)
		{
			tmpArray[i] = (t[i] != NULL) ? t[i] : NULL;
		}
		
		delete [] t;
		
		t = tmpArray;		
		
		lines = s;
	}
}
TextSpeicher::TextSpeicher()
{
	size = 0;
	lines = 0;
	t = NULL;
	filename = static_cast<string>(NULL);
}
TextSpeicher::TextSpeicher(string Filename)
{
	size = 0;
	lines = 0;
	t = NULL;
	
	ifstream in(Filename.c_str());
	
	try
	{
		if(in)
		{
			while(!in.eof())
			{
				//getline(in, ,'\n');
			}
			in.close();
		}	
	}
	catch(...)
	{
		
	}
}
TextSpeicher::TextSpeicher(TextSpeicher&)
{
}
TextSpeicher::~TextSpeicher()
{
}
TextSpeicher& TextSpeicher::TextSpeicher::operator= (TextSpeicher&)
{
}
void TextSpeicher::SetFilename(string Filename)
{
	if(!Filename.empty())
	{
		filename = Filename;
	}
}
TextSpeicher::TextZeile& TextSpeicher::operator [] (int line)
{	
}
int TextSpeicher::MaxColumns () const
{
}
/*TextSpeicher::TextZeile::TextZeile()
{
	
}
TextSpeicher::TextZeile::TextZeile(string tl)
{
}
TextSpeicher::TextZeile::TextZeile(TextZeile&)
{
}
TextSpeicher::TextZeile::~TextZeile()
{
}*/
TextSpeicher::TextZeile& TextSpeicher::TextZeile::operator= (const TextZeile& tl)
{
	l = static_cast<string>(tl);
}
char& TextSpeicher::TextZeile::operator [] (int column)
{
	if(column < 0) {
		OutOfBounds ThrowMeGently;
  /* Okay, I */	throw ThrowMeGently; /*! Are you satisfied now? */

	} else if (column > l.length()) { // the chance for an error
/*probl. sucks*/for(; column > l.length(); l += ' '); // is VERY high here
	}

	return l[column];

}
