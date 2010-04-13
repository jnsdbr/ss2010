/**************************************************************************
  FifoClassTest_1.h

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
// Testprogramm: Textdatei bitte als Argument übergeben
//
int main(int argc, char *argv[]) {

  //
  // Normaler Betrieb
  //
  cout << "*** Zunaechst wird der normale Betrieb der Fifo-Klasse abgetestet ***" << endl;
  try {
    cout << "> Fifo aus Textdatei fuellen" << endl;
    FifoClass s( (argc>1) ? argv[1] : "test.txt" ); // Fifo einrichten und aus Textdatei füllen
    cout << "> Fifo ausgeben" << endl;
    while (s>0) {                           // Elemente ausgeben
      cout << static_cast<string>(s) << endl;
    }
    cout << "> Fifo mittels Ein- und Ausgabeoperator fuellen" << endl;
    s << "One"; s << "Two"; s << "Three";
    cout << "> Fifo ausgeben" << endl;
    string help;
    s >> help; cout << help << endl;
    s >> help; cout << help << endl;
    s >> help; cout << help << endl;
  } catch (FifoClass& f) {
    cout << "> Failure: Fifo Objekt sollte hier keine Ausnahme werfen:" << endl;
    cout << " >>> " << f.Error() << endl;
    return 3;
  } catch (...) {
    cout << "> Failure: Unbekannte Ausnahme" << endl;
    return 3;
  }

  //
  // Fifo Unterlauf testen
  //
  cout << "*** Es werden nun Fifo-Unterlaeufe passieren ***" << endl;
  { FifoClass s; // Leeres Fifo einrichten
    try {
      cout << static_cast<string>(s) << endl;
    } catch (FifoClass& f) {
      cout << "> Erwartete Ausnahme wegen Fifo-Unterlauf:" << endl;
      cout << " >>> " << f.Error() << endl;
    } catch (...) {
      cout << "> Failure: Unbekannte Ausnahme" << endl;
      return 3;
    }
    try {
      string help;
      cout << "> Fifo mittels Ein- und Ausgabeoperator fuellen" << endl;
      s << "Eins"; s << "Zwei"; s << "Drei";
      cout << "> Fifo ausgeben und Unterlauf herbeifuehren" << endl;
      s >> help; cout << help << endl;
      s >> help; cout << help << endl;
      s >> help; cout << help << endl;
      s >> help; cout << help << endl; // Hier muss ein Unterlauf passieren
    } catch (FifoClass& f) {
      cout << "> Erwartete Ausnahme wegen Fifo-Unterlauf:" << endl;
      cout << " >>> " << f.Error() << endl;
    } catch (...) {
      cout << "> Failure: Unbekannte Ausnahme" << endl;
      return 3;
    }
  }

  //
  // Test auf Fehler beim Datei-oeffnen 
  //
  cout << "*** Es wird nun eine Ausnahme wegen nicht existierender Datei passieren ***" << endl;
  try {
    FifoClass s( "DieDateiGibtsNicht" ); // Fifo einrichten und aus Datei füllen
  } catch (FifoClass& f) {
    cout << "> Erwartete Ausnahme wegen nicht existierender Datei:" << endl;
    cout << " >>> " << f.Error() << endl;
  } catch (...) {
    cout << "> Failure: Unbekannte Ausnahme" << endl;
    return 3;
  }
  return 0;
}
