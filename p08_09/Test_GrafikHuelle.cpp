//------------------------------------------------------------------------------------------
// Klasse "GrafikHuelle"
// (c) Prof. Dr.-Ing. Bernhard Lang
//     FH Osnabrück 
// 20. Mai 2005
//------------------------------------------------------------------------------------------
#include "Grafikklasse.h"
#include "Image.h"
#include "BmpRead.h"
#include "BmpWrite.h"
#include <vector>
#include <iostream>
using namespace std;

// ------------------------------------------------------------------------------------------------
// Klasse GrafikHuelle
//   Diese Klasse kapselt ein Objekt einer beliebigen Unterklasse der GrafikElement-Hierarchie,
//   ohne dass der Typ der Unterklasse bekannt sein muss.
//   Mit dieser Huelle koennen Objekte der GrafikElement-Klassenhierarchie mit unterschiedlichem
//   Datentyp gemeinsam in einen Container der Standardbibliothek eingeschrieben werden.
// ------------------------------------------------------------------------------------------------
class GrafikHuelle{
  GrafikElement* g;
 public:
  // Uebergaenge zwischen GrafikElement und GrafikHuelle
  GrafikHuelle(const GrafikElement& r) : g(r.clone())       { }
  operator const GrafikElement& () const                    { return *g; }
  // Kopierkonstruktor und Zuweisungsoperator werden benötigt, um "GrafikHuelle"-Objekte
  // in Container der Standardbibliothek einzuschreiben zu können.
  GrafikHuelle(const GrafikHuelle& r)  : g(r.g->clone())    { }
  GrafikHuelle& operator= (const GrafikHuelle& r)           { delete g; g=r.clone(); return *this; }
  // Destruktor
  virtual ~GrafikHuelle()                                   { delete g; }
  // Nachbildung der GrafikElement-Schnittstelle
  void add_offset(int x, int y)                             { g->add_offset(x,y); }
  void draw(Image& I)                                       { g->draw(I); }
  GrafikElement& operator= (const GrafikElement& r)         { *g = r; return *g; };
  GrafikElement* clone() const                              { return g->clone(); }
};

// ------------------------------------------------------------------------------------------------
// Tesprogramm für die Klasse.
// Dient auch als Beipiel fuer die Verwendung der Klasse.
// ------------------------------------------------------------------------------------------------
int main() {
  
  // BMP-Datei einlesen und in Bild speichern
  BmpRead b1("Bild1.bmp");
  Image I(b1.Width(),b1.Height());
  b1 >>I;
  
  // "GrafikElement"-Objekte erzeugen, in "GrafikHuelle"-Objekte einpacken
  // und diese in den Vektor "v" einschreiben.
  vector<GrafikHuelle> v;
  v.push_back(GrafikHuelle(Rechteck(10,10,30,30,RGB_Pixel(255,255,0)))); // Typ Rechteck
  v.push_back(GrafikHuelle(Punkt(17,23,RGB_Pixel(255,0,0))));            // Typ Punkt

  for (int i=0; i<v.size(); i++) {
    // Objekt in Bild zeichnen.
    //   Es werden die Methoden von "GrafikHuelle" augerufen, die dann die Methoden des in
    //   "GrafikHuelle" eingebetteten "GrafikElement"-Objekts aufrufen (siehe Klassendefinition
    //   von "GrafikHuelle").
    v[i].draw(I);
    v[i].add_offset(44,55);
    v[i].draw(I);
    // Wirklichen Objekttyp herausfinden
    // - Ueber die Operatormethode "GrafikHuelle::operator const GrafikElement& () const"
    //   wird eine Referenz auf das im "GrafikHuelle"-Objekt "v[i]" eingepackte
    //   "GrafikElement"-Objekt ermittelt und in "rge" gespeichert.
    // - Ueber den Adressoperator "&" wird die Adresse des von "rge" referenzierten
    //   Objekts ermittelt.
    // - Mit der Adresse laesst sich ueber den "dynamic_cast"-Operator der wirkliche
    //   Datentyp des "GrafikElement"-Objekts ermittelt.
    cout << "Es ist ein ";
    const GrafikElement& rge(v[i]);
    if (dynamic_cast<const Punkt*>(&rge)!=0)         { cout << "Punkt"; }
    else if (dynamic_cast<const Linie*>(&rge)!=0)    { cout << "Linie"; }
    else if (dynamic_cast<const Rechteck*>(&rge)!=0) { cout << "Rechteck"; }
    // ... und so weiter
    cout << "-Objekt" << endl;
  }
  
  // Bild in BMP-Datei schreiben
  BmpWrite("Test.bmp",I);
  return 0;
}
