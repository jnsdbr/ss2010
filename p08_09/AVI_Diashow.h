//------------------------------------------------------------------------------------------
// (c) Prof. Dr.-Ing. Bernhard Lang
//     FH Osnabr�ck    
//------------------------------------------------------------------------------------------

#ifndef _AVI_Diashow_h_
#define _AVI_Diashow_h_

#include "Grafikklasse.h"
#include "GrafikHuelle.h"
#include "Image.h"
#include "BmpRead.h"
#include "AviWrite.h"
//#include "Ueberblendungen.h"
#include "Avi_Clip.h"
#include <vector>
#include <iostream>
#include <string>
using namespace std;

class AVI_Diashow {
	private:
		int avi_hoehe, avi_breite;
		string avi_name;
		vector<Avi_Clip> clipContainer;
	public:
		enum Ueberblendung { None, Soft, Schieben };
		AVI_Diashow(const string& AviName, int Breite, int Hoehe): avi_hoehe(Hoehe), avi_breite(Breite), avi_name(AviName), clipContainer() {};
		virtual ~AVI_Diashow() {};
		int Clip_hinzufuegen(const string& name, int Laenge);
		bool Grafik_hinzufuegen(int Clip, const GrafikElement& g);
		bool Uebergang_hinzufuegen(int Clip, Ueberblendung ue, int Laenge);
		void Film_erstellen() const;
		int  Laenge_des_Films() const;

		int get_height() const { return this->avi_hoehe; }
		int get_width() const { return this->avi_breite; }
};

#endif
