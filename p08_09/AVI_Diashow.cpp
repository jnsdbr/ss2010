#include "AVI_Diashow.h"
using namespace std;

int AVI_Diashow::Clip_hinzufuegen(const string& name, int Laenge)
{
	cout << "blubb";
	try
	{
		clipContainer.push_back(new Avi_Clip(this->get_hoehe(), this->get_breite(), Laenge , name));
	}
	catch(...) {}

	return clipContainer.size();
}

bool AVI_Diashow::Grafik_hinzufuegen(int Clip, const GrafikElement& g)
{
	try
	{
		clipContainer[Clip].add_graphic(g);
		
		return true;
	}
	catch(...)
	{
		return false;
	}
}


/*
bool Uebergang_hinzufuegen(int Clip, Ueberblendung ue, int Laenge);
void Film_erstellen() const;
int  Laenge_des_Films() const;
*/