#include "FifoClass.h"

using namespace std;

/* FifoClass */
FifoClass& FifoClass::push(const string& v)
{
	root = new FifoElement(v, root);
	return *this;
}

FifoClass& FifoClass::pop (string& v)
{
	if (empty()) throw "Stack underflow";
	
	// bori5
	
	/*
	v = *root;
	FifoElement *help = root;
	root = root->next_element();
	delete help;
	return *this;*/
}
