#include "FifoClass.h"
using namespace std;

/* FifoClass */
FifoClass& FifoClass::push(const string v)
{
	top = new FifoElement(v, top);
	return *this;
}

FifoClass& FifoClass::pop(string& v)
{	
	if(empty()) throw "No elements in list";
	FifoElement *root = GetFirstElement();
	cout << "root: " << root << "\ttop: " << top << endl;
	v = root->getValue();
	
	delete root;
	return *this;
}

FifoClass::FifoElement* FifoClass::GetFirstElement() {
	FifoElement *temp;
	temp = top;

	while(temp->nextElement() != NULL) {
		temp = temp->nextElement();
	}

	return temp;
}
