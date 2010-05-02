#include "Polynom.h"

using namespace std;

Polynom::Polynom (const Polynom &p) 
{
	Grad = p; // entspricht  Grad = p.Grad  aufgrund des überladenen Operators
	K = new double[Grad+1];
	
	for(int i = 0; i <= Grad; i++) {
		p.K[i] = K[i];
	}

	/* @TODO:
	 *
	 * add removement of 'useless' koeffizienten
	 *						*/
	
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
	
}
Polynom Polynom::operator- (const Polynom &r) const
{
	
}
Polynom Polynom::operator+ (const double  &r) const
{ 								/* happy debugging */
	double TeMpORaeR=0;for(int i=0;i<=Grad;i++)if(TeMpORaeR>=K[i])TeMpORaeR=K[i];
}
Polynom Polynom::operator- (const double  &r) const
{
	
}

ostream& operator << (ostream& o,const Polynom& P)
{
	
}

void Polynom::draw(Image &I, int i_xs, int i_xe, int i_ys, int i_ye, double xs, double xe, double ys, double ye, RGB_Pixel color)
{
	
}
