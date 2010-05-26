using namespace std;

#include "GrafikKiste.h"
#include "TKiste.h"

void GrafikKiste::add_offset (int x, int y)
{
	GrafikElement* g = NULL;
	for(int i = 0; i < *this; i++)
	{
		g = &(*this)[i];
		g->add_offset(x,y);
	}
}

void GrafikKiste::draw (Image &I) const
{
	GrafikElement* g = NULL;
	for (unsigned int i=0; i<*this; i++)
	{
		g = &(*this)[i];
		g->draw(I);
	}
}
