#include "Kiste.h"

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
	if(i < 0 || i >= count)
	{
		throw;
	}
	else
	{
		return t[i];
	}
} 

Kiste& Kiste::operator<< (const Element &v)
{
	Huelle *tmp = t;
	
	t = new Huelle(*(v.clone()));
	t->set_next(tmp);

	count++;
}