#include "GrafikHuelle.h"
#include "Grafikklasse.h"

#include <iostream>
#include <vector>
using namespace std;

class Avi_Clip
{
	private:
  		enum Ueberblendung { None, Soft, Schieben };		
		int breite;
		int hoehe;
		string bmp_name;
		vector<GrafikHuelle> GrafikHuellen;
		int laenge;
		Ueberblendung ut;
		int ut_laenge;

	public:
		Avi_Clip(int b, int h, int l, string filename) : breite(b), hoehe(h), bmp_name(filename), laenge(l), ut_laenge(-1) { ut = None; };
		~Avi_Clip() {};
		void Clip_erstellen() const;	
		
		string get_bmp_name() const { return this->bmp_name; }
		int get_length() const { return this->laenge; }
		int get_ut_length() const { return this->ut_laenge; }
		Ueberblendung get_ut_type() const { return this->ut; }
		
		int get_num_elements() const { return this->GrafikHuellen.size(); }
		vector<GrafikHuelle>& get_elements() { return GrafikHuellen; }
		
		void add_graphic(const GrafikElement& g) { GrafikHuellen.push_back(g); }
		void set_ut(int UT, int UT_LAENGE) { ut = static_cast<Ueberblendung>(UT); ut_laenge = UT_LAENGE; }
};
