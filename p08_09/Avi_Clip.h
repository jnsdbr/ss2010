#include <iostream>
#include "GrafikHuelle.h"
#include "Grafikklasse.h"
#include <vector>
using namespace std;

class Avi_Clip
{
	private:
		int breite;
		int hoehe;
		string bmp_name;
		vector<GrafikHuelle> GrafikHuellen;
		int laenge;
		//Ueberblendung ut;
		int ut_laenge;

	public:
		Avi_Clip(int b, int h, int l, string filename) : breite(b), hoehe(h), laenge(l), bmp_name(filename) {};
//		~Avi_Clip() { delete GrafikHuellen; };
		void Clip_erstellen() const;	
		
		string get_bmp_name() const
		{
			return this->bmp_name;
		}
		
		//void add_graphic(Grafikelement &g) { GrafikHuellen.push_back(&g); };
};