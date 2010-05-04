//-------------------------------------------------------------------------------
// Testprogramm 0 für die Klasse TextObject
//
// Prof. Dr.-Ing. B. Lang
// (c) FH Osnabrueck
// OOP-Praktikum
//-------------------------------------------------------------------------------
#include <iostream>
using namespace std;
#include "TextSpeicher.h"

int main() {
  try {
    TextSpeicher t;
    t.SetFilename("P5_Test0.txt");

    // Kreuz in die Datei einschreiben
    for (int i=0;i<10;i++) {
      t[i][i] = '*';
    }
    for (int i=0;i<10;i++) {
      t[i][10-i-1] = '*';
    }

    // Parabeln in die Datei einschreiben
    for (int i=0;i<100;i++) {
      int j = i-50;
      t[j*j][i] = 'x';
      t[i][j*j] = 'o';
    }

    // Info zum Text
    cout << "Der Text besteht aus " << t << " Zeilen" << endl;
    for (int i=0; i<t; i++) {
      if (0 != int(t[i])) {
        cout << "  Zeile " << i << " besteht aus " << int(t[i]) << " Zeichen" << endl;
      }
    }

  } catch (TextSpeicher::OutOfBounds) {
    cerr << "Feldgrenzenverletzung" << endl;
  } catch (...) {
    cerr << "Unbekannte Ausnahme" << endl;
  }
}

