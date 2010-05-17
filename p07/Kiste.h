// --------------------------------------------------------------
// Kiste.h:
//   Klasse zum Speichern von Element-Objekten
//   Prof. Dr.-Ing. Bernhard Lang
//   FH Osnabrück
// --------------------------------------------------------------
#ifndef _Kiste_h_
#define _Kiste_h_

#include "Element.h"

class Kiste {
  // Der private Teil kann Ihren Anforderungen entsprechend verändert werden
  class Huelle;
  Huelle*  t;
  const char*    error;
  Kiste& operator= (const Kiste&) { return *this; } // Zuweisungsoperator sperren
  Kiste(const Kiste&) {}             // Kopierkonstruktor sperren
 public: 
  // Dieses oeffentliche Interface ist obligatorisch und darf nicht verändert werden
  Kiste() : t(0), error(0) {} // Konstruktor
  virtual ~Kiste();           // Destruktor
  operator int() const;       // Gibt Anzahl der eingeschriebenen Elemente zurück
  Kiste& operator<< (const Element &v);     // Elemente am Ende anfügen
  Kiste& operator<< (const Kiste& r);       // Inhalt der übergebenen Kiste r am Ende anfügen
  Element& operator[] (unsigned int i);     // Zugriff auf i-tes Element in der Kiste
  const char* get_error() { return error; } // Fehlertext zurückgeben
};

// Die Klasse Kiste::Huelle ist privat in Kiste und darf daher Ihren Anforderungen entsprechend gestaltet werden.
// Folgende Definition ist als Beispiel zu verstehen:
class Kiste::Huelle {
  Huelle*  next;
  Element* val;
 public:
  Huelle(const Element& e);
  ~Huelle();
  operator Element&();        // Gibt Referenz auf aktuelles Element-Objekt zurück
  void add(const Element &e); // Fügt ein Huelle-Objekt am Ende der Liste an.
  Huelle* get_next() const { return next; }
};

#endif
