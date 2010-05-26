#include "Kiste.h"
#include <iostream>

using namespace std;

/**
 * Überladener Shift Operator - hängt eine Kiste an eine andere an
 * 
 * @param Kiste& r	Objekt von Typ Kiste
 * @return *this
 */
Kiste& Kiste::operator<< (const Kiste& r)
{
	for(unsigned int i = 0; i < r; i++)
	{
		*this << const_cast<Kiste&>(r)[i];
	}
	return *this;
}

/**
 * Überladener Klammer Operator
 *
 * @param unsigned int	i	Index
 * @return *tmp				Referenz von Huelle
 */
Element& Kiste::operator [](unsigned int i)
{
	Huelle *tmp = first;

	if(i > count)
	{
		throw;
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
 * @param const Element	&v	Objekt vom Typ ELement
 * @return *this
 */
Kiste& Kiste::operator<< (const Element &v)
{
	if(!first)
	{
		first = new Huelle(v);
		last = first;
	}
	else
	{
		Huelle *tmp = last;
		
		last = new Huelle(v); // new Huelle(*(v.clone()))
		tmp->set_next(last);
	}
	
	count++;
	
	return *this;
}
