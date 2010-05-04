//-------------------------------------------------------------------------------
// Testprogramm 1 f"ur die Klasse TextSpeicher
//
// Prof. Dr.-Ing. B. Lang
// (c) FH Osnabrueck
// OOP-Praktikum
//-------------------------------------------------------------------------------
#include <iostream>
using namespace std;

#include "TextSpeicher.h"
#include "SimpleFont.h"

void BigPrint(TextSpeicher &t, int px, int py, TextSpeicher::TextZeile& s, char bg) {
  int Ix=px, Iy=py+SimpleFont::height()-1;
  for (int i=0; i<s; i++) {
    SimpleFont a(s[i]); // Objekt zum Auslesen der Rasterinformation von s[i]
    // Rasterinformation f"ur s[i] aus Zeichengenerator auslesen
    // und Zeichen verfgr"o"ssert in Textobjekt t einschreiben
    for (int y=0; y<SimpleFont::height(); y++) {
      for (int x=0; x<SimpleFont::width(); x++) {
        if (a[y][x]) {
          t[Iy-y][Ix+x] = s[i];
        } else {
          t[Iy-y][Ix+x] = bg;
        }
      }
    }
    Ix += SimpleFont::width();
  }
}

int main() {
  try {
    TextSpeicher src("Joachim_Ringelnatz.txt");
    src.SetFilename(""); // Nicht mehr abspeichern
    TextSpeicher dst;
    dst.SetFilename("Big.txt"); // Unter diesem Namen abspeichern
    for (int i=0; i<src; i++) { // src zeilenweise in dst einschreiben
      BigPrint(dst, 0, i*SimpleFont::height(), src[i], ' ');
    }
  } catch (TextSpeicher::OutOfBounds) {
    cerr << "Feldgrenzenverletzung" << endl;
  } catch (...) {
    cerr << "Unbekannte Ausnahme" << endl;
  }
}

