#include "Polynom.h"

using namespace std;

Polynom::Polynom (const Polynom &p) 
{
	Grad = p; // entspricht  Grad = p.Grad  aufgrund des überladenen Operators
	
	while(p(Grad) == 0.0)
	{
		Grad--;
	}
	
	K = new double[Grad+1];
	
	for(int i = 0; i <= Grad; i++) {
		p.K[i] = K[i];
	}

	/* @TODO:
	 *
	 * add removement of 'useless' koeffizienten
	 *
	 */
}
Polynom::Polynom (const int g, const double v)
{
	Grad = g;
	int i;
	
	K = new double[Grad + 1];
	K[Grad] = v;
	
	for (i = 0; i < Grad; i++) 
	{
		K[i] = 0.0;
	}
}
Polynom::~Polynom()
{
	delete[] K;
}
Polynom Polynom::operator= (const Polynom& r)
{
	return Polynom(r);
}
Polynom::operator int () const
{
	return Grad;
}
double Polynom::operator[] (const int i) const
{
	
}
/**
 * @return Wert an Stelle x
 */
double Polynom::operator() (const double &x) const
{
	int i;
	double result = K[Grad];
	
	for(i = Grad - 1; i >= 0; i--) 
	{
		result *= x;
		result += K[i];
	}
	
	return result;
}
Polynom Polynom::operator+ (const Polynom &r) const
{
	int i;
	
	if(r.Grad > Grad) 
	{
		Polynom result(r.Grad);
		
		for(i = r.Grad; i > Grad; i--) 
		{
			result.K[i] = r.K[i];
		}
		for (i = Grad; i >= 0; i--) 
		{
			result.K[i] = r.K[i] + K[i];
		}
		return Polynom(result);
	}
	else 
	{
		Polynom result(Grad);
		
		for (i = Grad; i > r.Grad; i--) 
		{
			result.K[i] = K[i];
		}
		for (i = r.Grad; i >= 0; i--) 
		{
			result.K[i] = r.K[i] + K[i];
		}
		return Polynom(result);
	}
}
Polynom Polynom::operator- (const Polynom &r) const
{
	int i;
	if(r.Grad > Grad) 
	{
		Polynom result(r.Grad);
    
		for(i = r.Grad; i > Grad; i--) 
		{
			result.K[i] = -(r.K[i]);
		}
		for(i = Grad; i >= 0; i--) 
		{
			result.K[i] = K[i] - r.K[i];
		}
		
		return Polynom(result);
	}
	else 
	{
		Polynom result(Grad);
    
		for(i = Grad; i > r.Grad; i--) 
		{
			result.K[i] = K[i];
		}
		for(i = r.Grad; i >= 0; i--)
		{
			result.K[i] = K[i] - r.K[i];
		}
		
		return Polynom(result);
	}	
}
Polynom Polynom::operator+ (const double  &r) const
{
	Polynom result(*this);
	result.K[0] += r;
	
	return result;	
}
Polynom Polynom::operator- (const double  &r) const
{
	Polynom result(*this);
	result.K[0] -= r;
	
	return result;	
}

ostream& operator << (ostream& o, const Polynom& P)
{	
	o << '(';
	
	for(int i = P; i >= 0; i--)
	{
		if(P[i] != 0)
		{
			if((P[i] >= 0) && (i < static_cast<int>(P)))
			{
				o<<"+";
			}
			o << P[i];
			
			if(i > 0 && i != P)
			{
				o << "* x("<< i <<")";
			}
		}
	}
	
	o << ')';
	
	return o;
}

void Polynom::draw(Image &I, int i_xs, int i_xe, int i_ys, int i_ye, double xs, double xe, double ys, double ye, RGB_Pixel color)
{
}
