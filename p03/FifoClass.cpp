#include "FifoClass.h"
using namespace std;

/* FifoClass */

const char* FifoClass::Error() const {
	return error_str.c_str(); // ändern
}

void FifoClass::ChangeLevel(bool updown) {
	//cout << "chLevel:: old: " << chLevel;
	//try {
		if(updown) {
			chLevel++;
		} else {
			if(chLevel>0) chLevel--;
			else throw "Charge level underflow";
		}
	//} throw "Changing charge level failed.";
	//cout << " new: " << chLevel << endl;
}

FifoClass& FifoClass::push(const string v)
{
	top = new FifoElement(v, top);
	ChangeLevel(true);
	return *this;
}

FifoClass& FifoClass::pop(string& v)
{
	if(empty()) throw "No elements in list";
	FifoElement *root = GetFirstElement();
	FifoElement *prev = GetSecondElement();
	//cout << "root: " << root << "\tprev: " << prev << "\ttop: " << top << endl;
	v = root->getValue();

	if(root != prev) {
		prev->setNext(NULL); // Der Speicher des letzten Elements wird befreit,
		delete root;	// wenn das Programm beendet wird (FifoClass::delete)
		// Deshalb werden alle außer das letzte Element free'd!
	}

	ChangeLevel(false);

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

FifoClass::FifoClass(const char* source) {
	chLevel = 0;
	top = NULL;
	error_str = '\0';
	string line;
	ifstream file;
	// try

	file.open(source);
	while(!file.eof()) {
		getline(file, line, '\n');
		if(line.length() > 0) {
			push(line);
		}
	}

	file.close();
}
