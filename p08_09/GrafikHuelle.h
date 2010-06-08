#include <iostream>
#include "Grafikklasse.h"
using namespace std;

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