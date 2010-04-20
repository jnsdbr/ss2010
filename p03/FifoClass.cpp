#include "FifoClass.h"
/* nic3r */
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
	
	
	
	/*
	v = *root;
	FifoElement *help = root;
	root = root->next_element();
	delete help;
	return *this;*/
}
