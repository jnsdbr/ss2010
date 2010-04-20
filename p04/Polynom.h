//-------------------------------------------------------------------------------
// Klasse zur Verwaltung von Polygonen
//
// Prof. Dr.-Ing. B. Lang
// (c) FH Osnabrueck
// OOP-Praktikum
//-------------------------------------------------------------------------------
#include <iostream>
using namespace std;
#include "Image.h"

class Polynom {
  int Grad;
  double *K;
 public:
  Polynom (const Polynom &p);                   // Kopierkonstruktor
  Polynom (const int g=0,const double v=0.0);   // Konstruktor für Polynom mit Grad g
  ~Polynom();
  Polynom operator= (const Polynom& r);         // Zuweisungsoperator (tiefe Kopie)
  operator int () const;                        // Konversion: Grad des Polynoms auslesen
  double  operator[] (const int i) const;       // Zugriff auf die Koeffizienten
  double  operator() (const double &x) const;   // Berechnung des Funktionswerts
  // Operatoren und Funktionen
  Polynom operator+ (const Polynom &r) const;   // Polynomaddition
  Polynom operator- (const Polynom &r) const;   // Polynomsubtraktion
  //Polynom operator* (const Polynom &r) const; // Polynommultiplikation (optional)
  //Polynom operator/ (const Polynom &r) const; // Polynomdivision (optional)
  //Polynom operator% (const Polynom &r) const; // Polynom-Modulo-Operation (optional)
  //Polynom Ableitung() const;                  // Ableitung des Polynoms bilden (optional)
  // Hilfsmethoden zur Polynomeingabe
  Polynom operator+ (const double  &r) const;
  Polynom operator- (const double  &r) const;
  // Zeichnen eines Polynoms in ein Image-Objekt // (siehe Aufgabe 4)
  void draw( Image &I, int i_xs, int i_xe, int i_ys, int i_ye,
             double xs, double xe, double ys, double ye,
             RGB_Pixel color );
};

// Überladener Ausgabeoperator
ostream& operator << (ostream& o,const Polynom& P);

// Hilfsklasse zur Polynom-Eingabe
class X {
  int power;
 public:
  X(const int i):power(i) {}
  int get_power () const { return power; }
  operator Polynom () const { return Polynom(power,1.0);}
  Polynom operator+ (const Polynom &r) const { return Polynom(*this) + r; }
  Polynom operator- (const Polynom &r) const { return Polynom(*this) - r; }
  Polynom operator+ (const double &r) const  { return Polynom(*this) + r; }
  Polynom operator- (const double &r) const  { return Polynom(*this) - r; }
};
// Hilfsfunktion zur Polynomeingabe
inline Polynom operator *(const double l, const X &r) {return Polynom(r.get_power(),l);}

