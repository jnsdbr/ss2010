#include "AVI_Diashow.h"
using namespace std;

int AVI_Diashow::Clip_hinzufuegen(const string& name, int Laenge)
{
	try
	{
		this->clipContainer.push_back(Avi_Clip(this->get_height(), this->get_width(), Laenge , name));
	}
	catch(...) {}

	return this->clipContainer.size() - 1;
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

void AVI_Diashow::Film_erstellen() const
{
	cout << "Erstelle Datei: " << this->avi_name << endl;

	try
	{
		// Avi Objekt anlegen
		AviWrite avi(this->avi_name.c_str(), this->avi_breite, this->avi_hoehe);

		// Container durchgehen
		for(unsigned int i = 0; i < clipContainer.size(); i++)
		{
			// Bitmap einlesen
			BmpRead bmp_reader(clipContainer[i].get_bmp_name().c_str());
			
			// Image erstellen
			Image img(this->avi_breite, this->avi_hoehe);

			// Eingelesene Bitmap in das img "schieben"
			bmp_reader >> img;
		
			// Grafikelemente hinzufuegen
			if(clipContainer[i].get_num_elements() > 0)
			{
				cout << clipContainer[i].get_num_elements() << endl;
				vector<GrafikHuelle>& tmp = clipContainer[i].get_elements();
			}
		
		
			// Clip in Avi schreiben
			for(int j = 0; j < clipContainer[i].get_length(); j++)
			{
				avi << img;
			}
		}
	}
	catch(...) {}
	
	cout << "Finished" << endl;
}

int AVI_Diashow::Laenge_des_Films() const
{
	int laenge = 0;

	// Container durchgehen
	for(unsigned int i = 0; i < this->clipContainer.size(); i++)
	{
		// Clip laenge und Clip Ueberblendung addieren
		laenge += this->clipContainer[i].get_length();
		laenge += this->clipContainer[i].get_ut_length();
	}
	
	return laenge;
}


bool AVI_Diashow::Uebergang_hinzufuegen(int Clip, Ueberblendung ue, int Laenge)
{
	return true; // Der Rückgabewert gibt an, ob die Information dem Clip hinzugefügt werden konnte
}
