//------------------------------------------------------------------------------------------
// (c) Prof. Dr.-Ing. Bernhard Lang
//     FH Osnabrück    
//------------------------------------------------------------------------------------------

#ifndef _AVI_Diashow_h_
#define _AVI_Diashow_h_

#include "Grafikklasse.h"
#include "Image.h"
#include "BmpRead.h"
#include "AviWrite.h"
//#include "Ueberblendungen.h"
#include "Avi_Clip.h"
#include <vector>
#include <map>
#include <iostream>
#include <new>
using namespace std;

class AVI_Diashow {
	private:
		int hoehe, breite;
		string aviname;
		vector<Avi_Clip> clipContainer;
	public:
		enum Ueberblendung { Soft, Schieben };
		AVI_Diashow(const string& AviName, int Breite, int Hoehe): hoehe(Hoehe), breite(Breite), aviname(AviName) {};
		virtual ~AVI_Diashow() {};
		int Clip_hinzufuegen(const string& name, int Laenge);
		bool Grafik_hinzufuegen(int Clip, const GrafikElement& g);
		bool Uebergang_hinzufuegen(int Clip, Ueberblendung ue, int Laenge);
		void Film_erstellen() const;
		int  Laenge_des_Films() const;

		int get_hoehe() const { return this->hoehe; }
		int get_breite() const { return this->breite; }
};

#endif
