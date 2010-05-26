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
	Huelle *tmp = t;

	
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
	Huelle *tmp = t;
	
	t = new Huelle(*(v.clone()));
	t->set_next(tmp);
	
	count++;
	
	return *this;
}