#include "AVI_Diashow.h"
using namespace std;

int AVI_Diashow::Clip_hinzufuegen(const string& name, int Laenge)
{
	try
	{
		clipContainer.push_back(Avi_Clip(this->get_hoehe(), this->get_breite(), Laenge , name));
	}
	catch(...) {}

	return clipContainer.size();
}

bool AVI_Diashow::Grafik_hinzufuegen(int Clip, const GrafikElement& g)
{
	try
	{
		//clipContainer[Clip].add_graphic(g);
		
		return true;
	}
	catch(...)
	{
		return false;
	}
}

void AVI_Diashow::Film_erstellen() const
{
	
}

int AVI_Diashow::Laenge_des_Films() const
{
	
}

/*
bool Uebergang_hinzufuegen(int Clip, Ueberblendung ue, int Laenge);
*/