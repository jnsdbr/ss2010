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
  cout << b << '+' << b << '=' << b+b << endl << endl;
  cout << b << '+' << c << '=' << b+c << endl << endl;
  cout << c << '+' << b << '=' << c+b << endl << endl;
  cout << b << '-' << c << '=' << b-c << endl << endl;
  cout << a << '*' << c << '=' << a*c << endl << endl;
  cout << a << '*' << b << '=' << a*b << endl << endl;
  cout << b << '*' << a << '=' << b*a << endl << endl;
  cout << b << '*' << b << '=' << b*b << endl << endl;
  cout << a << '/' << c << '=' << a/c << endl << endl;
  cout << a << '/' << b << '=' << a/b << endl << endl;
  cout << b << '/' << a << '=' << b/a << endl << endl;
  cout << b << '/' << b << '=' << b/b << endl << endl;
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
  RationaleZahl a = {'-',10,2};
  RationaleZahl b = {'+',12,4};
  cout << a << '+' << b << '=' << a+b << endl;
  cout << b << '+' << a << '=' << b+a << endl;
  cout << a << '-' << b << '=' << a-b << endl;
  cout << b << '-' << a << '=' << b-a << endl;
}
void test4() {
  cout << "Testprogramm 4" << endl;
  // Unendlich durch Unendlich
  RationaleZahl a = {'+',4,0};
  cout << a << '/' << a << '=' << a/a << endl;
}
void test5() {
  cout << "Testprogramm 5" << endl;
  // NullDurchNull
  RationaleZahl b = {'+',0,999};
  cout << b << '/' << b << '=' << b/b << endl;
}
void test6() {
  cout << "Testprogramm 6" << endl;
  // NullMalUnendlich
  RationaleZahl a = {'+',3,0};
  RationaleZahl b = {'+',0,3};
    cout << b << '*' << a << '=' << b*a << endl;
}
void test7() {
  cout << "Testprogramm 7" << endl;
  // MinusUnendlichUndPlusUnendlich
  RationaleZahl c = {'+',3,0};
  RationaleZahl d = {'-',5,0};
  cout << c << '+' << d << '=' << c+d << endl;
}
void test8() {
  cout << "Testprogramm 8" << endl;
  // Keine Zahl
  RationaleZahl a = {'+',0,0};
  cout << a << '*' << a << '=' << a*a << endl;
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

