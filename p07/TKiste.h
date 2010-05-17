// --------------------------------------------------------------
// TKiste.h:
//   Template-Klasse zum Speichern von Objekten vom Typ E
//   Prof. Dr.-Ing. Bernhard Lang
//   FH Osnabrück
// --------------------------------------------------------------
#ifndef _TKiste_h_
#define _TKiste_h_

template<class E>
class TKiste {
  class Huelle;
  ... ??? (Komponenten und Methoden deklarieren)
};

template<class E>
class TKiste<E>::Huelle {
  ... ??? (Komponenten und Methoden deklarieren)
};

// Methoden des Templates
template<class E> TKiste<E>::TKiste() ... (Template-Methode definieren)

... (Weitere Template-Methoden definieren)

#endif
