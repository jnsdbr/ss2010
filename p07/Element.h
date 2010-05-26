// --------------------------------------------------------------
// Element.h
//   Einfache Klassen zum Testen einer Container-Klasse
//   Prof. Dr.-Ing. Bernhard Lang
//   FH Osnabrück
// --------------------------------------------------------------
#ifndef _Element_h_
#define _Element_h_

#include <string>
using namespace std;

class Element {
 protected:
  string Zeichenkette; // Die Klasse kann eine Zeichenkette speichern
 public:
  Element(const Element& r): Zeichenkette(r.Zeichenkette){} // Kopierkonstruktor
Element(string s): Zeichenkette(s) {};          // Konstruktor speichert die übergebene Zeichenkette
  virtual Element* clone() const { return new Element(*this); } // clone-Methode, erzeugt eine Kopie des aktuellen Objekts
  operator const string&() const { return Zeichenkette; }       // Referenz auf die Zeichenkette nach aussen geben
};

class UnterElement : public Element {
 public:
  UnterElement(const UnterElement& r): Element(r){} // Kopierkonstruktor
  UnterElement(string s): Element(s) {};            // Konstruktor ruft Basis-Konstruktor auf
  virtual Element* clone() const { return new UnterElement(*this); } // clone-Methode, erzeugt eine Kopie des aktuellen Objekts
  operator const char*() const { return Zeichenkette.c_str(); } // Zeiger auf const char*-Zeichenkette nach aussen geben
};

#endif
