#include "FifoClass.h"

using namespace std;

int main()
{
	FifoClass s;
	s << "One";
	s << "Two";
	s << "Three";	

	string peter = "Nicht geaendert!";
	s >> peter;
	cout << peter << endl;
	s >> peter;
	cout << peter << endl;
	s >> peter;
	cout << peter << endl;
	return 0;
}
