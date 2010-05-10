//-------------------------------------------------------------------------------
// Beispielprogramm für die Klasse SimpleFont
//
// Prof. Dr.-Ing. B. Lang
// (c) FH Osnabrueck
// OOP-Praktikum
//-------------------------------------------------------------------------------
#include "image.h"
#include "bmpwrite.h"
#include "SimpleFont.h"

int main() {

  RGB_Pixel red(255,0,0);
  RGB_Pixel green(0,255,0);
  RGB_Pixel blue(0,0,255);

  Image I(80,80);

  // Zeichen 'a' an Position (X=30, Y=40) ausgeben
  int Ix=40, Iy=40;
  SimpleFont a('a');
  for (int y=0; y<SimpleFont::height(); y++) {
    for (int x=0; x<SimpleFont::width(); x++) {
      I[Iy+y][Ix+x]=((a[y][x]) ? red : green);
    }
  }
  // Zeichen 'b' rechts daneben ausgeben
  Ix+=SimpleFont::width();
  SimpleFont b('b');
  for (int y=0; y<SimpleFont::height(); y++) {
    for (int x=0; x<SimpleFont::width(); x++) {
      I[Iy+y][Ix+x]=((b[y][x]) ? green : blue);
    }
  }

  // Zeichen 'c' darunter ausgeben
  Iy-=SimpleFont::height();
  SimpleFont c('c');
  for (int y=0; y<SimpleFont::height(); y++) {
    for (int x=0; x<SimpleFont::width(); x++) {
      I[Iy+y][Ix+x]=((c[y][x]) ? blue : red);
    }
  }

  // Bild I in BMP-Datei wegschreiben
  { BmpWrite("test.bmp",I); }

  return 0;
}
