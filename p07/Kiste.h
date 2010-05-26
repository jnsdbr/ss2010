// --------------------------------------------------------------
// Kiste.h:
//   Klasse zum Speichern von Element-Objekten
//   Prof. Dr.-Ing. Bernhard Lang
//   FH Osnabr�ck
// --------------------------------------------------------------
#ifndef _Kiste_h_
#define _Kiste_h_

#include "Element.h"
#include <new>
#include <typeinfo>


class Kiste
{
	// Der private Teil kann Ihren Anforderungen entsprechend ver�ndert werden
	private:
		class Huelle;
		Huelle*  t;
		const char* error;
		unsigned int count; 
		Kiste& operator= (const Kiste&) { return *this; } // Zuweisungsoperator sperren
		Kiste(const Kiste&) {}						// Kopierkonstruktor sperren
	
	// Dieses oeffentliche Interface ist obligatorisch und darf nicht ver�ndert werden
	public:
		Kiste() : t(NULL), error(0), count(0) {}	// Konstruktor
		virtual ~Kiste() {};							// Destruktor
		operator int() const { return count; };		// Gibt Anzahl der eingeschriebenen Elemente zur�ck
		Kiste& operator<< (const Element &v);		// Elemente am Ende anf�gen
		Kiste& operator<< (const Kiste& r);			// Inhalt der �bergebenen Kiste r am Ende anf�gen
		Element& operator[] (unsigned int i);		// Zugriff auf i-tes Element in der Kiste
		const char* get_error() { return error; }	// Fehlertext zur�ckgeben
};

// Die Klasse Kiste::Huelle ist privat in Kiste und darf daher Ihren Anforderungen entsprechend gestaltet werden.
// Folgende Definition ist als Beispiel zu verstehen:
class Kiste::Huelle
{
	private:
		Huelle*  next;
		Element* val;
	
	public:
		Huelle(const Element& e) {};
		~Huelle() {};
		operator Element&() { return *val; };						// Gibt Referenz auf aktuelles Element-Objekt zur�ck
		void add(const Element &e);					// F�gt ein Huelle-Objekt am Ende der Liste an.
		Huelle* get_next() const { return next; }
		void set_next(Huelle *x) { next = x; }
};

#endif
