// --------------------------------------------------------------
// TKiste.h:
//   Template-Klasse zum Speichern von Objekten vom Typ E
//   Prof. Dr.-Ing. Bernhard Lang
//   FH Osnabrück
// --------------------------------------------------------------
#ifndef _TKiste_h_
#define _TKiste_h_
#include <cstddef>	// so we can use NULL
#include <typeinfo>	// bad_cast

/**
 * TKiste
 */
template<class E>
class TKiste
{
	private:
		class Huelle;
		Huelle* first;
		Huelle* last;
		const char* error;
		unsigned int count; 
		TKiste& operator= (const TKiste&) { return *this; } // Zuweisungsoperator sperren
		TKiste(const TKiste&) {}						// Kopierkonstruktor sperren
		
	public:
		TKiste() : first(NULL), last(NULL), error(0), count(0) {}	// Konstruktor
		virtual ~TKiste() { delete first; };							// Destruktor
		operator int() const { return count; };		// Gibt Anzahl der eingeschriebenen Elemente zurück
		TKiste& operator<< (const E &v);		// Elemente am Ende anfügen
		TKiste& operator<< (const TKiste& r);			// Inhalt der übergebenen Kiste r am Ende anfügen
		E& operator[] (unsigned int i);		// Zugriff auf i-tes Element in der Kiste
		const char* get_error() { return error; }	// Fehlertext zurückgeben
};

/**
 * Huelle
 */
template<class E>
class TKiste<E>::Huelle
{
	private:
		Huelle*  next;
		E* val;
	
	public:
		Huelle(const E& e);
		~Huelle() { delete val; delete next; };
		operator E&() { return *val; };						// Gibt Referenz auf aktuelles Element-Objekt zurück
		Huelle* get_next() const { return next; }
		void set_next(Huelle *x) { next = x; }
};

/**
 * Überladener Shift Operator - hängt eine TKiste an eine andere an
 * 
 * @param TKiste<E>& r	Objekt von Typ E
 * @return *this
 */
template<class E>
TKiste<E>& TKiste<E>::operator<< (const TKiste<E>& r)
{
	for(int i = 0; i < r; i++)
	{
		try
		{
			*this << const_cast<TKiste<E>&>(r)[i];
		}
		catch(bad_cast)
		{
			throw "Fehler";
		}
	}
	
	return *this;
}
/**
 * Überladener Klammer Operator
 *
 * @param unsigned int	i	Index
 * @return *tmp				Referenz von Huelle
 */
template<class E>
E& TKiste<E>::operator [](unsigned int i)
{
	Huelle *tmp = first;

	if(i > count)
	{
		throw "Ausserhalb des Bereichs!";
	}
	
	if(i != 0)
	{
		for(unsigned int j = 1; j <= i; j++)
		{
			tmp = tmp->get_next();
		}
	}
	
	return *tmp;	
} 

/**
 * Überladener Shift Operator - fügt eine Huelle zur Liste hinzu
 *
 * @param const E	&v	Konstante Variable vom Typ E
 * @return *this
 */
template<class E>
TKiste<E>& TKiste<E>::operator<< (const E &v)
{
	if(!first)
	{
		try
		{
			first = new Huelle(v);
			last = first;
		}
		catch(...)
		{
			throw "Fehler beim allozieren des Speichers!";
		}
	}
	else
	{
		Huelle *tmp = last;
		
		try
		{
			last = new Huelle(v);
			tmp->set_next(last);
		}
		catch(...)
		{
			throw "Fehler beim allozieren des Speichers!";
		}
	}
	
	count++;
	
	return *this;
}

/**
 * Default Konstruktor Huelle
 *
 * @param const E& e	Element vom Typ E
 */
template<class E>
TKiste<E>::Huelle::Huelle(const E& e)
{
	try
	{
		E *tmp = dynamic_cast<E*>(e.clone());
		
		// Überprüfen ob tmp gesetzt wurde
		if(tmp)
		{
	    	val = tmp;
		}		
	}
	catch(bad_cast)
	{
		throw "Fehler";
	}
	
	next = NULL;
}

#endif
