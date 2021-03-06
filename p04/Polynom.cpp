#include "Polynom.h"

using namespace std;

Polynom::Polynom (const Polynom &p)
{
    Grad = p;

    while(p.K[Grad] == 0.0)
	{
        Grad--;
    }
    K = new double[Grad+1];

    for(int i = Grad; i >= 0; i--)
	{
        K[i] = p.K[i];
    }
}

Polynom::Polynom(const int g, const double v)
{	
    Grad = g;

    K = new double[g + 1];
    for(int i = 1; i < g; i++)
	{
		K[i] = 0.0;
    }

    K[Grad] = v;
}
Polynom::~Polynom()
{
	delete[] K;
}
Polynom Polynom::operator= (const Polynom& r)
{
	delete [] K;
	Grad = r;
	K = new double[Grad+1];
	for(int i=0; i <= Grad;i++)
	{
		K[i] = r[i];
	}
	
	return *this;
}
Polynom::operator int () const
{
	return Grad;
}
double Polynom::operator[] (const int i) const
{
    return K[i];	
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
				o << "+";
			}
			o << P[i];
			
			if(i > 0)
			{
				o << "*X("<< i <<")";
			}
		}
	}
	
	o << ')';
	
	return o;
}

void Polynom::draw(Image &I, int i_xs, int i_xe, int i_ys, int i_ye, double xs, double xe, double ys, double ye, RGB_Pixel color)
{
	int x_Bereich = i_xe - i_xs;
	int y_Bereich = i_ye - i_ys;
	
	double x_Intervall = xe - xs;
	double y_Intervall = ye - ys;

	double x_schrittweite = x_Intervall / x_Bereich;
	double y_schrittweite = y_Intervall / y_Bereich;

	double funktionswert = 0.0;

	for(int i = i_xs; i<=i_xe; i++)
	{
		funktionswert = (*this)(xs+(i-i_xs)*x_schrittweite);

		if(funktionswert >= ys && funktionswert <= ye)
		{
			int y_position = static_cast<int>(((funktionswert-ys)/y_Intervall)*y_Bereich+0.5);

			y_position += i_ys;	
																																						 //ausgerechnetes Pixel einfaerben
			I[y_position][i] = RGB_Pixel(color.Red(), color.Green(), color.Blue());
		}
	}
}