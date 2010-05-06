#include <iostream>
#include <string>

using namespace std;

int main() {
	string test;
	test = "Hallo Welt!";

	cout << test << endl << test.length() << "=" << test[test.length()-1] << endl;

	int p=1;
	cout << "p " << static_cast<string>((p == 1)?"ist 1":"ist nicht 1") << endl;

	cout << "test hat " << test.length() << " Zeichen. Versuche auf das " << test.length()*2 << "te zuzugreifen und füge Text hinzu!"<< endl;
	cout << "test: " << test << endl;

	for(int i = (test.length()-1)*2; test.length()-1 < i; test += ' ');
	test += "Hallo zurück!";
	cout << test;

	return 0;
}
