/*************************************************************************
  RationaleZahl.cxx

  Rechnen mit rationalen Zahlen
  Impementierung und Testprogramm für benutzerdefinierten
  Datentyp "RationaleZahl"

  Dr. B. Lang, FH OS
  29.03.2001: Erste Version
  14.03.2003: Erweiterung fuer OOP-Praktikum SS2003
  09.03.2004: Angepasst an GNU 3.x Compiler
  09.03.2004: Zerlegt in 2 Dateien

  To Do:
  - Weitere Testproramme erstellen, so dass die Klasse RationaleZahl
    intensiv ausgetestet wird.
*************************************************************************///

#include <iostream>
#include "RationaleZahl.h"

using namespace std;

//
// Testprogramme
//
void test1() {
  // Test der Arithmetik
  cout << "Testprogramm 1:" << endl;
  RationaleZahl a = {'+',4,7}; // +4/7
  RationaleZahl b = {'-',1,4}; // -1/4
  RationaleZahl c = {'+',5,6}; // +5/6
  cout << b << '+' << b << '=' << b+b << endl;
  cout << b << '+' << c << '='<< b+c << endl;
  cout << c << '+' << b << '='<< c+b << endl;
  cout << b << '-' << c << '='<< b-c << endl;
  cout << "a*c = "<< a*c << endl;
  cout << "b/a = "<< b/a << endl;
}
void test2() {
  // Test unbekannte Ausnahme
  cout << "Testprogramm 2:"
       << "  int-Ausnahme. (Sollte als unbekannte Ausnahme gefangen werden)"
       << endl;
  throw int(10);
}
void test3() {
  // Test ...
  cout << "Testprogramm 3" << endl;
}
void test4() {
  // Test ...
  cout << "Testprogramm 4" << endl;
}
void test5() {
  // Test ...
  cout << "Testprogramm 5" << endl;
}
void test6() {
  // Test ...
  cout << "Testprogramm 6" << endl;
}
void test7() {
  // Test ...
  cout << "Testprogramm 7" << endl;
}
void test8() {
  // Test ...
  cout << "Testprogramm 8" << endl;
}
//
// ... falls nötig, weitere Testprogramme vereinbaren
//


//
// Hauptprogramm mit Fehlerbehandlung
//
int main() {
  void (*testfkts[])(void) = {test1, test2, test3, test4,
                              test5, test6, test7, test8};
  for (int i=0;i<sizeof(testfkts)/sizeof(void (*)(void));i++) {
    try {
      (*testfkts[i])();
    } catch (UnendlichDurchUnendlich) {
      cout << "--> Ausnahme: Unendlich durch Unendlich" << endl;
    } catch (NullDurchNull) {
      cout << "--> Ausnahme: 0 durch 0" << endl;
    } catch (NullMalUnendlich) {
      cout << "--> Ausnahme: 0 mal unendlich" << endl;
    } catch (MinusUnendlichUndPlusUnendlich) {
      cout << "--> Ausnahme: -unendlich + +unendlich" << endl;
    } catch (KeineZahl) {
      cout << "--> Ausnahme: Keine Zahl" << endl;
    } catch (FalschesVorzeichen) {
      cout << "--> Ausnahme: FalschesVorzeichen" << endl;
    } catch (...) {
      cout << "--> Ausnahme: Unbekannte Ausnahme" << endl;
    }
  }
}

