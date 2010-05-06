#include "TextSpeicher.h"

using namespace std;

TextSpeicher::TextSpeicher()
{	
}
TextSpeicher::TextSpeicher(string Filename)
{
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
	filename = Filename;
}
TextSpeicher::TextZeile& TextSpeicher::operator [] (int line)
{	
}
int TextSpeicher::MaxColumns () const
{
}
TextSpeicher::TextZeile::TextZeile()
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
}
TextSpeicher::TextZeile& TextSpeicher::TextZeile::operator= (TextZeile&)
{
}
char& TextSpeicher::TextZeile::operator [] (int column)
{
}