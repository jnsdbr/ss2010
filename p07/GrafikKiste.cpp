using namespace std;

#include "GrafikKiste.h"
#include "TKiste.h"

void GrafikKiste::add_offset (int x, int y)
{
	GrafikElement* g = NULL;
	for(int i = 0; i < *this; i++) // *this liefert hier count zurück
	{
		g = &(*(this))[i];
		g->add_offset(x,y);
	}
}

void GrafikKiste::draw (Image &I) 
{
	GrafikElement* g = NULL;
	for (int i=0; i < *this; i++) // *this liefert hier count zurück
	{
		g = &(*(this))[i];
		g->draw(I);
	}
}
