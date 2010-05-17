// --------------------------------------------------------------
// Testprogramm zur Praktikumsübung 7
// Praktikum Objektorientierte Programmierung
// Fachhochschule Osnabrueck
// (c) Prof. Dr.-Ing. Bernhard Lang
// --------------------------------------------------------------
#include <iostream>
using namespace std;
#include "Kiste.h"
#include "Element.h"


int main() {
  Kiste c1;
  Kiste c2;

  // Kiste c1 fuellen und ausgeben
  c1 << Element("Eins")<< Element("Zwei") << Element("Drei");
  for (int i=0; i<c1; i++) {
    cout << static_cast<const string>(c1[i]) << " ";
  }
  cout << endl;

  // Kiste c2 fuellen und ausgeben
  c2 << UnterElement("One")<< UnterElement("Two") << UnterElement("Three");
  for (int i=0; i<c2; i++) {
    cout << dynamic_cast<UnterElement&>(c2[i]) << " ";
  }
  cout << endl;

  // Kiste c2 zweimal in c1 kopieren und c1 ausgeben
  c1 << c2 << c2; // c1 enthaelt nun Element- und UnterElement-Objekte
  for (int i=0; i<c1; i++) {
    try {
      UnterElement& rue(dynamic_cast<UnterElement&>(c1[i]));
      cout << "UnterElement-Objekt:" << rue << endl;
    } catch (bad_cast) {
      cout << "Element-Objekt:" << static_cast<const string>(c1[i]) << endl;
    }
  }
  return 0;
}
