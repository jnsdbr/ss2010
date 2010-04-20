#include "FifoClass.h"

using namespace std;

int main()
{
	FifoClass s;
	s << "One";
	s << "Two";
	
	string peter = "Nicht geaendert!";
	s >> peter;
	cout << peter;
	s >> peter;
	cout << peter;
	s >> peter;
	cout << peter;
	return 0;
}
