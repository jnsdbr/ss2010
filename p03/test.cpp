#include "FifoClass.h"

using namespace std;

int main()
{
	FifoClass s;
	//FifoClass s("test.txt");
	
	string peter;
	s << "c";
	s << "b";
	s << "a";
	s << "f";
	s << "e";
	s << "d";
	s.mergesort();
	
	while(s.getLevel() > 0) {
		cout << static_cast<string>(s) << endl;
	}


	/*s << "One";
	s << "Two";
	s << "Three";
	int plubb;

	string peter = "Nicht geaendert!";
	plubb = s;
	cout << "Fuellstand: " << plubb << endl;
	peter = static_cast<string>(s); // cast neccessary, can't explain why :/
	cout << peter << endl;
	s >> peter;
	plubb = s;
	cout << "Fuellstand: " << plubb << endl;
	cout << peter << endl;
	s >> peter;
	plubb = s;
	cout << "Fuellstand: " << plubb << endl;
	cout << peter << endl;*/
	return 0;
}
