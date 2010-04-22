#include "FifoClass.h"
using namespace std;

/* FifoClass */

const char* FifoClass::Error() const
{
	return error_str.c_str();
}

void FifoClass::ChangeLevel(bool updown)
{
	if(updown)
	{
		chLevel++;
	}
	else
	{
		if(chLevel>0) chLevel--;
		else throw "Charge level underflow";
	}
}

FifoClass& FifoClass::push(const string v)
{
	try
	{
		top = new FifoElement(v, top);
		ChangeLevel(true);
	}
	catch(bad_alloc)
	{
		error_str = "Bad Alloc.";
		throw *this;
	}
	return *this;
}

FifoClass& FifoClass::pop(string& v)
{
	if(chLevel == 0)
	{
		error_str = "bla";
		throw *this;
	}
	
	if(empty())
	{
		error_str = "No elements in list";
		throw *this;
	}
	
	
	FifoElement *root = GetFirstElement();
	FifoElement *prev = GetSecondElement();
	
	
	v = root->getValue();

	if(root != prev)
	{
		prev->setNext(NULL); // Der Speicher des letzten Elements wird befreit,
		delete root;	// wenn das Programm beendet wird (FifoClass::delete)
		// Deshalb werden alle außer das letzte Element free'd!
	}

	ChangeLevel(false);

	return *this;
}

FifoClass::FifoElement* FifoClass::GetFirstElement()
{
	FifoElement *temp;
	temp = top;

	while(temp->nextElement() != NULL)
		temp = temp->nextElement();

	return temp;
}

FifoClass::FifoElement* FifoClass::GetSecondElement()
{
	FifoElement *temp;
	FifoElement *root = GetFirstElement();
	temp = top;
	bool previousfound = false;

	while(!previousfound)
	{
		if(temp->nextElement() != root && temp->nextElement() != NULL)
		{
			temp = temp->nextElement();
		}
		else
		{
			previousfound = true;
		}
	}

	return temp;
}

FifoClass::FifoClass(const char* source) {
	chLevel = 0;
	top = NULL;
	error_str = "\n";
	string line;
	
	ifstream file;
	
	try
	{
		file.open(source);
		
		while(!file.eof())
		{
			getline(file, line, '\n');
			if(line.length() > 0)
			{
				push(line);
			}
		}
	}
	catch(...)
	{
		error_str = "Could not open file.";
		throw *this;
	}

	file.close();
}
