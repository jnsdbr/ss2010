#include "FifoClass.h"
using namespace std;

/* FifoClass */
FifoClass& FifoClass::push(const string& v)
{
	top = new FifoElement(v, top);
	if(root == NULL) {
		root = top;
	}

	return *this;
}

FifoClass& FifoClass::pop(string& v)
{
	FifoElement *temp;
	
	v = root->getValue();	
	
	temp = top;
	while(temp->nextElement() != root && temp->nextElement() != NULL)
	{
		if(temp->nextElement() != NULL)
		{
			temp = temp->nextElement();
		}
		
	}
	
	//delete root;
	root = temp;
}
