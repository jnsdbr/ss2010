#include "FifoClass.h"

using namespace std;

/* FifoClass */
FifoClass& FifoClass::push(const string& v)
{
	FifoElement *test;
	test = new FifoElement(v);
	return *this;
}
FifoClass& FifoClass::pop(string &v)
{
	cout << "Jens hat haarige Eier. Sehr haarig.";
}

/* FifoElement */
