/**************************************************************************
  RationaleZahl.h

  Rechnen mit rationalen Zahlen (Deklarationen)

  Dr. B. Lang, FH OS
  29.03.2001: Erste Version
  14.03.2003: Erweiterung fuer OOP-Praktikum SS2003

  To Do:
  - nichts bekannt
/*************************************************************************/

//
// Ausnahmen
//
struct UnendlichDurchUnendlich{};
struct NullDurchNull{};
struct NullMalUnendlich{};
struct MinusUnendlichUndPlusUnendlich{};
struct KeineZahl{};
struct FalschesVorzeichen{};
struct UeberlaufImZaehler{};           // Freiwillig
struct UeberlaufImNenner{};            // Freiwillig
struct UeberlaufImZaehlerUndNenner{};  // Freiwillig

//
// Vereinbarung des Benutzerdefinierten Datentyps "Rationale Zahl"
//
struct RationaleZahl {
  char Vorzeichen;
  unsigned int  Zaehler, Nenner;
};

//
// Operatoren
//
RationaleZahl &operator +(const RationaleZahl &l, const RationaleZahl &r);
RationaleZahl &operator -(const RationaleZahl &l, const RationaleZahl &r);
RationaleZahl &operator *(const RationaleZahl &l, const RationaleZahl &r);
RationaleZahl &operator /(const RationaleZahl &l, const RationaleZahl &r);

using namespace std;
ostream &operator << (ostream & o, const RationaleZahl &r); // benoetigt <iostream>
