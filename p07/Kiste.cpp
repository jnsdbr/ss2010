Kiste& Kiste::operator<< (const Kiste& r)
{
	for(int i = 0; i< r; i++)
	{
		*this << const_cast<Container&>(r)[i];
	}
	return *this;
}

Element& Kiste::operator [](unsigned int i)
{
	if(i < 0 || i >= Anzahl)
	{
		throw;
	}
	else
	{
		return *(t[i]);
	}
}