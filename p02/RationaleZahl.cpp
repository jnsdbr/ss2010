/*************************************************************************
  RationaleZahl.cxx

  Rechnen mit rationalen Zahlen
  Impementierung und Testprogramm für benutzerdefinierten
  Datentyp "RationaleZahl"

  Dr. B. Lang, FH OS
  29.03.2001: Erste Version
  14.03.2003: Erweiterung fuer OOP-Praktikum SS2003
  09.03.2004: Angepasst an GNU 3.x Compiler
  09.03.2004: Zerlegt in 2 Dateien

  To Do:
  - Operatoren nach Vorgabe implementieren
*************************************************************************///

#include <iostream>
#include "RationaleZahl.h"

using namespace std;

//
// Operatoren: + - * /
//
RationaleZahl &operator +(const RationaleZahl &l, const RationaleZahl &r) {
  cout << '(' << l.Zaehler << '/' << l.Nenner << ')' << "plus"
       << '(' << r.Zaehler << '/' << r.Nenner << ')'
       << "ist noch nicht implementiert" << endl;
//  return ???;
}
RationaleZahl &operator -(const RationaleZahl &l, const RationaleZahl &r) {
  cout << '(' << l.Zaehler << '/' << l.Nenner << ')' << "minus"
       << '(' << r.Zaehler << '/' << r.Nenner << ')'
       << "ist noch nicht implementiert" << endl;
//  return ???;
}
RationaleZahl &operator *(const RationaleZahl &l, const RationaleZahl &r) {
  cout << '(' << l.Zaehler << '/' << l.Nenner << ')' << "mal"
       << '(' << r.Zaehler << '/' << r.Nenner << ')'
       << "ist noch nicht implementiert" << endl;
//  return ???;
}
RationaleZahl &operator /(const RationaleZahl &l, const RationaleZahl &r) {
  cout << '(' << l.Zaehler << '/' << l.Nenner << ')' << "durch"
       << '(' << r.Zaehler << '/' << r.Nenner << ')'
       << "ist noch nicht implementiert" << endl;
//  return ???;
}

//
// Ausgabeoperator: <<
//
ostream &operator << (ostream & o, const RationaleZahl &r) {
  o << "ostream &operator << (ostream & o, RationaleZahl r)"
    << " noch nicht implementiert" << endl;
  return o;
}

