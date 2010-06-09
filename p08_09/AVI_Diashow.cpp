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

void AVI_Diashow::Film_erstellen()
{
	cout << "Erstelle Datei: " << this->avi_name << endl;

	try
	{
		// Avi Objekt anlegen
		AviWrite avi(this->avi_name.c_str(), this->avi_breite, this->avi_hoehe);
		Image prev_img(this->avi_breite, this->avi_hoehe); // Nötig für Überblendungen
		
		// Container durchgehen
		for(unsigned int i = 0; i < clipContainer.size(); i++)
		{
			cout << "Verarbeite Clip " << i << "..." << endl;
			// Bitmap einlesen
			BmpRead bmp_reader(clipContainer[i].get_bmp_name().c_str());
			
			// Images erstellen
			Image img(this->avi_breite, this->avi_hoehe);

			// Eingelesene Bitmap in das img "schieben"
			bmp_reader >> img;
		
			// Grafikelemente hinzufuegen
			if(clipContainer[i].get_num_elements() > 0)
			{
				int anzGE = clipContainer[i].get_num_elements();
				cout << "Anz. GrafikElemente: " << anzGE << endl;

				vector<GrafikHuelle>& tmp = clipContainer[i].get_elements();

				// GrafikElemente einzeichnen
				for(; anzGE > 0; anzGE--) {
					cout << "Lege GrafikElement " << anzGE << " auf Clip..." << endl;
					tmp[anzGE-1].draw(img);
				}

			}

			// Überblendung vorhanden?
			if(static_cast<Ueberblendung>(clipContainer[i].get_ut_type()) == None)
			{
				// Clip in Avi schreiben
				for(int j = 0; j < clipContainer[i].get_length(); j++)
				{
					avi << img;
				}
			}
			else if(static_cast<Ueberblendung>(clipContainer[i].get_ut_type()) == Schieben) {
				// Überblendung Schieben ist vorhanden!
				int clip_length = clipContainer[i].get_length();
				int ut_length = clipContainer[i].get_ut_length();

				cout << "Überblendung (Schieben) berechnen..." << endl;
				cout << "\tCliplänge: " << clip_length << endl;
				cout << "\tÜbergangslänge: " << ut_length << endl;

				double step_x; // Pixel per Frame
				step_x = this->avi_breite / ut_length;

				cout << "\t" << step_x << " x-Pixel pro Frame schieben" << endl;

				/* Überblendung einfügen (ggf. eiskalt länger als Cliplänge)
				   img: Arbeits-Image. Hierauf wird die Überblendung durchgeführt. Dieses Image wird in die Avi geknallt.
					Bisher befindet sich hier der letzte Frame des aktuellen Clips.
				   prev_img: Das (letzte) Image vom vorherigen Clip. Von hier werden die Daten für die Überblendung geholt.
				   new_img: Das letzte Image vom aktuellen Clip, auf dessen Basis gerendert wird. */

				// Aktuelles Image sichern und damit zum Arbeitsimage 'degradieren'
				Image new_img(this->avi_breite, this->avi_hoehe);
				for(int yy=0; yy <= avi_hoehe; yy++) {
					for(int xx=0; xx <= avi_breite; xx++) {
						new_img[yy][xx] = img[yy][xx];
						img[yy][xx] = RGB_Pixel(0,255,0);
					}
				}

				// Frames mit Überblendung erzeugen
				cout << "\tÜberblendung (" << ut_length << " Frames) wird eingefügt..." << endl;
				for(int frame_i=0; frame_i < ut_length; frame_i++) {

					// Aktuellen Clip einfügen
					// frame_i*step_x  := Pixel, die in diesem Frame gezeichnet werden müssen

					for(int yy=0; yy <= avi_hoehe; yy++) { // funktioniert auch nur so lange, wie avi_hoehe = clip=hoehe
						for(int xx=0; xx <= frame_i*step_x; xx++) {
							img[yy][xx] = new_img[yy][avi_breite-(frame_i*step_x)+xx];
						}
					}		

					// Alten clip dahinter hängen
					for(int yy=0; yy <= avi_hoehe; yy++) {
						for(int xx=0; xx <= avi_breite-(frame_i*step_x); xx++) {
							img[yy][xx+frame_i*step_x] = prev_img[yy][xx];
						}
					}
	
					avi << img;				
				}
				// Standbilder einfügen, falls Clip länger als Überblendung
				if(clip_length > ut_length) {
					cout << "\tStandbilder (" << clip_length-ut_length << " Frames) werden eingefügt..." << endl;
					for(int j = 0; j < (clip_length-ut_length); j++)
					{
						avi << new_img;
					}
				}				
			}
			else if(static_cast<Ueberblendung>(clipContainer[i].get_ut_type()) == Soft) {
				// Überblendung Soft ist vorhanden!
				int clip_length = clipContainer[i].get_length();
				int ut_length = clipContainer[i].get_ut_length();

				cout << "Überblendung (Soft) berechnen..." << endl;
				cout << "\tCliplänge: " << clip_length << endl;
				cout << "\tÜbergangslänge: " << ut_length << endl;

				/* Überblendung einfügen (ggf. eiskalt länger als Cliplänge)
				   img: Arbeits-Image. Hierauf wird die Überblendung durchgeführt. Dieses Image wird in die Avi geknallt.
					Bisher befindet sich hier der letzte Frame des aktuellen Clips.
				   prev_img: Das (letzte) Image vom vorherigen Clip. Von hier werden die Daten für die Überblendung geholt.
				   new_img: Das letzte Image vom aktuellen Clip, auf dessen Basis gerendert wird. */

				// Aktuelles Image sichern und damit zum Arbeitsimage 'degradieren'
				Image new_img(this->avi_breite, this->avi_hoehe);
				for(int yy=0; yy <= avi_hoehe; yy++) {
					for(int xx=0; xx <= avi_breite; xx++) {
						new_img[yy][xx] = img[yy][xx];
						img[yy][xx] = RGB_Pixel(0,255,0);
					}
				}
				// Frames mit Überblendung erzeugen
				cout << "\tÜberblendung (" << ut_length << " Frames) wird eingefügt..." << endl;
				for(int frame_i=0; frame_i < ut_length; frame_i++) {

					for(int yy=0; yy <= avi_hoehe; yy++) {
						for(int xx=0; xx <= avi_breite; xx++) {
							img[yy][xx] = RGB_Pixel(							
							(prev_img[yy][xx].Red()*(ut_length-frame_i)+(new_img[yy][xx].Red()*frame_i))/ut_length,
							(prev_img[yy][xx].Green()*(ut_length-frame_i)+(new_img[yy][xx].Green()*frame_i))/ut_length,
							(prev_img[yy][xx].Blue()*(ut_length-frame_i)+(new_img[yy][xx].Blue()*frame_i))/ut_length);
						}
					}

					avi << img;				
				}
				// Standbilder einfügen, falls Clip länger als Überblendung
				if(clip_length > ut_length) {
					cout << "\tStandbilder (" << clip_length-ut_length << " Frames) werden eingefügt..." << endl;
					for(int j = 0; j < (clip_length-ut_length); j++)
					{
						avi << new_img;
					}
				}				
			}
			else { cout << "Unbekannte Überblendung :(" << endl; }

			// Image sichern, damit es für eine eventuelle Überblendung nicht neu berechnet werden muss
			// Es existiert weder operator=, noch ein Kopierkonstruktor für Images :(
			for(int yy=0; yy <= avi_hoehe; yy++) {
				for(int xx=0; xx <= avi_breite; xx++) {
					prev_img[yy][xx] = img[yy][xx];
				}
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
		if(clipContainer[i].get_length() > clipContainer[i].get_ut_length()) {
			laenge += this->clipContainer[i].get_length();
		} else {
			laenge += this->clipContainer[i].get_ut_length();
		}
	}
	
	return laenge;
}


bool AVI_Diashow::Uebergang_hinzufuegen(int Clip, Ueberblendung ue, int Laenge)
{
	if(ue == Schieben || ue == Soft) {
		clipContainer[Clip].set_ut(static_cast<int>(ue), Laenge); // static_cast<Avi_Clip::Ueberblendung>(ue) geht nicht, da private
		return true;
	} else {
		cout << "Fehler: Überblendung nicht vollständig Implementiert!" << endl;
		return false;
	}
	


/*	cout << "Clip 1 ist kürzer als die Überblendung. Soll dieser verlängert werden? (j/n): ";
	string test;
	cin >> test;
	cout << "Antwort: " << test << endl;*/
}
