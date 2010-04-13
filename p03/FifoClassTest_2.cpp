/**************************************************************************
  FifoClassTest_2.h

  Testen der Container-Klasse mit Fifo-Eigenschaften

  Dr. B. Lang, FH OS
  12.04.2001: Erste Version
  24.03.2003: Ueberarbeitung fuer OOP-Praktikum SS2003
  19.03.2004: Angepasst an GNU 3.xx Compiler
  23.03.2005: Ueberarbeitung fuer OOP-Praktikum SS2005
  31.03.2006: Nun werden Referenzen von FifoClass gefangen
  
  To Do:
  - nichts bekannt
/*************************************************************************/
#include<iostream>
using namespace std;
#include "FifoClass.h"

//
// Testprogramm für Methode "mergesort": Textdatei bitte als Argument übergeben
//
int main(int argc, char *argv[]) {

  //
  // Sortieren
  //
  try {
    cout << ">Fifo aus Textdatei fuellen" << endl;
    FifoClass s( (argc>1) ? argv[1] : "FifoClass.h" ); // Fifo einrichten und aus Datei füllen
    cout << ">Fifo sortieren" << endl;
    s.mergesort();                          // Elemente im Fifo sortieren
    cout << ">Fifo ausgeben" << endl;
    while (s>0) {                           // Elemente ausgeben
      cout << static_cast<string>(s) << endl;
    }
  } catch (FifoClass& f) {
    cout << "> Failure: Fifo Objekt sollte hier keine Ausnahme werfen:" << endl;
    cout << " >>> " << f.Error() << endl;
    return 3;
  } catch (...) {
    cout << "> Failure: Unbekannte Ausnahme" << endl;
    return 3;
  }
  return 0;
}
