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

	if((r.Zaehler > 0 && r.Nenner == 0) && (l.Zaehler > 0 && l.Nenner == 0)){
		MinusUnendlichUndPlusUnendlich error;
		throw error;
	}

	if((r.Zaehler == 0 && r.Nenner == 0) || (l.Zaehler == 0 && l.Nenner == 0)){
		KeineZahl error;
		throw error;
	}

	int n1, n2;
	int akt_ggT;
	static RationaleZahl ergebnis;

	akt_ggT = ggT(l.Nenner, r.Nenner);

	n1 = l.Nenner/akt_ggT;
	n2 = r.Nenner/akt_ggT;

	int ZaehlerLinks = l.Zaehler;
	int ZaehlerRechts = r.Zaehler;

	if(l.Vorzeichen == '-')	ZaehlerLinks = ZaehlerLinks*(-1);
	if(r.Vorzeichen == '-')	ZaehlerRechts = ZaehlerRechts*(-1);

	int ErgebnisMitVorzeichen = 0;
	ErgebnisMitVorzeichen = (ZaehlerLinks * n2) + (ZaehlerRechts * n1);
	if(ErgebnisMitVorzeichen<0) {
		ergebnis.Vorzeichen = '-'; // Das Vorzeichen wird in der Struct eingefügt
		ergebnis.Zaehler = ErgebnisMitVorzeichen * (-1); // und von der Zahl entfernt
	} else
	{
		ergebnis.Vorzeichen = '+';
		ergebnis.Zaehler = ErgebnisMitVorzeichen;
	}

	// ergebnis.Zaehler = (l.Zaehler * n2) + (r.Zaehler * n1);
	ergebnis.Nenner = n1 * n2 * akt_ggT;

	// kürzen

	akt_ggT = ggT(ergebnis.Zaehler, ergebnis.Nenner);
	ergebnis.Zaehler = ergebnis.Zaehler/akt_ggT;
	ergebnis.Nenner = ergebnis.Nenner/akt_ggT;

	return ergebnis;

}
RationaleZahl &operator -(const RationaleZahl &l, const RationaleZahl &r) {

	RationaleZahl rNeu = r;

	if(rNeu.Vorzeichen == '-') rNeu.Vorzeichen = '+';
	else rNeu.Vorzeichen = '-';

	return l + rNeu;

}
RationaleZahl &operator *(const RationaleZahl &l, const RationaleZahl &r) {

	if((l.Zaehler == 0 && l.Nenner > 0 && r.Zaehler > 0 && r.Nenner == 0) ||
	   (l.Zaehler > 0 && l.Nenner == 0 && r.Zaehler == 0 && r.Nenner > 0)){
		NullMalUnendlich error;
		throw error;
	}

	if((r.Zaehler == 0 && r.Nenner == 0) || (l.Zaehler == 0 && l.Nenner == 0)) {
		KeineZahl error;
		throw error;
	}

	int n1 = 0,
		n2 = 0,
		z1 = 0,
		z2 = 0;

	z1 = l.Zaehler / ggT(l.Zaehler, r.Nenner);
	z2 = r.Zaehler / ggT(r.Zaehler, l.Nenner);
	n1 = l.Nenner / ggT(r.Zaehler, l.Nenner);
	n2 = r.Nenner / ggT(l.Zaehler, r.Nenner);

	static RationaleZahl ergebnis;
	ergebnis.Zaehler = z1 * z2;
	ergebnis.Nenner = n1 * n2;
	if(((l.Vorzeichen == '-') || (r.Vorzeichen == '-'))&&!((l.Vorzeichen == '-') && (r.Vorzeichen == '-')))
	{
			ergebnis.Vorzeichen = '-';
	} else ergebnis.Vorzeichen = '+';

	return ergebnis;

}
RationaleZahl &operator /(const RationaleZahl &l, const RationaleZahl &r) {

	if(l.Zaehler > 0 && l.Nenner == 0 && r.Zaehler > 0 && r.Nenner == 0){
		UnendlichDurchUnendlich error;
		throw error;
	}

	if(l.Zaehler == 0 && l.Nenner > 0 && r.Zaehler == 0 && r.Nenner > 0){
		NullDurchNull error;
		throw error;
	}

	RationaleZahl rNeu;
	rNeu.Nenner = r.Zaehler;
	rNeu.Zaehler = r.Nenner;
	rNeu.Vorzeichen = r.Vorzeichen;

	return l * rNeu;
}

//
// Ausgabeoperator: <<
//
ostream &operator << (ostream & o, const RationaleZahl &r) {
  	o << '(';
  	if(r.Zaehler == 0 && r.Nenner > 0){
  	  o << "0";
  	}
  	else if(r.Zaehler > 0 && r.Nenner == 0){
  	  o << r.Vorzeichen << "unendlich";
  	}
  	else if(r.Zaehler == 0 && r.Nenner == 0){
  	  o << "NaN";
  	}
  	else{
  	  o << r.Vorzeichen << r.Zaehler << '/' << r.Nenner ;
  	}
  	o << ')';
  	return o;
}

int ggT(int a, int b)
{
	int d=0, r=0;
	if(b != 0)
	{
		r = a % b;
		d = ggT(b, r);

		return d;
	}
	else
	{
		return a;
	}
}