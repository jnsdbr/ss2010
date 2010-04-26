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
	if(chLevel <= 0 || empty())
	{
		error_str = "No elements in list";
		throw *this;
	} else {
	
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

		if(chLevel == 0) { top = NULL; }

	}
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

void FifoClass::mergesort()
{
	if(getLevel() > 1) {

		cout << "Sortiere... " << getLevel() << endl;

		FifoClass bigger;
		FifoClass smaller;

		string divider_str;
		pop(divider_str);
		cout << "Divider: " << divider_str << endl;

		string akt_str;
		while(getLevel() > 0) {
			cout << "getLevel: " << getLevel() << endl;
			pop(akt_str);
			if(akt_str >= divider_str) {
				cout << "bigger->push() : " << akt_str << endl;
				bigger.push(akt_str);
				
			} else {
				cout << "smaller->push() : " << akt_str << endl;
				smaller.push(akt_str);

			}
		}

		bigger.mergesort();
		smaller.mergesort();

		while(smaller.getLevel() > 0) {
			cout << "smaller:: level:" << smaller.getLevel();
			smaller.pop(akt_str);
			cout << " akt_str: " << akt_str << endl;
			push(akt_str);
		}
		cout << "divider:: " << divider_str << endl;
		push(divider_str);
		while(bigger.getLevel() > 0) {
			cout << "bigger:: level:" << bigger.getLevel();
			bigger.pop(akt_str);
			cout << " akt_str: " << akt_str << endl;
			push(akt_str);
		}
			
	}
}

FifoClass::FifoClass(const char* source) {
	chLevel = 0;
	top = NULL;
	error_str = "\n";
	string line;
	
	ifstream file;
	
	file.open(source);
	if(!file) {
		error_str = "Could not open file.";
		throw *this;
	} else {	
		while(!file.eof())
		{
			getline(file, line, '\n');
			if(line.length() > 0)
			{
				push(line);
			}
		}
		file.close();
	}

	
}


