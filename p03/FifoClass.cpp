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
	FifoElement *prev = GetSecondElement();
	cout << "root: " << root << "\tprev: " << prev << "\ttop: " << top << endl;
	v = root->getValue();
	
	if(root != prev) {
		prev->setNext(NULL); // Der Speicher des letzten Elements wird befreit,
		delete root;	// wenn das Programm beendet wird (FifoClass::delete)
		// Deshalb werden alle außer das letzte Element free'd!
	}
	
	return *this;
}

FifoClass::FifoElement* FifoClass::GetFirstElement() {
	FifoElement *temp;
	temp = top;

	while(temp->nextElement() != NULL)
		temp = temp->nextElement();

	return temp;
}
FifoClass::FifoElement* FifoClass::GetSecondElement() {
	FifoElement *temp;
	FifoElement *root = GetFirstElement();
	temp = top;
	bool previousfound = false;

	while(!previousfound) {
		if(temp->nextElement() != root && temp->nextElement() != NULL) {
			temp = temp->nextElement();
		} else {
			previousfound = true;
		}
	}

	return temp;
}
