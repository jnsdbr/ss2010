#include "Kiste.h"
#include <iostream>

using namespace std;

Kiste& Kiste::operator<< (const Kiste& r)
{
	for(int i = 0; i < r; i++)
	{
		*this << const_cast<Kiste&>(r)[i];
	}
	return *this;
}

Element& Kiste::operator [](unsigned int i)
{
	Huelle *tmp = first;

	// Fehler abfragen
	if(i > count)
	{
		throw;
	}
	
	if(i != 0)
	{
		for(int j = 1; j <= i; j++)
		{
			tmp = tmp->get_next();
		}
	}
	
	return *tmp;	
} 

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