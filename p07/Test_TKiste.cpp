// --------------------------------------------------------------
// Testprogramm zur Praktikumsübung 7
// Praktikum Objektorientierte Programmierung
// Fachhochschule Osnabrueck
// (c) Prof. Dr.-Ing. Bernhard Lang
// --------------------------------------------------------------
#include <iostream>
#include <cmath>
using namespace std;

#include "TKiste.h"

#include "Element.h"

#include "image.h"           // Zweidimensionales Bild
#include "bmpwrite.h"        // Schreiben von BMP-Dateien
#include "grafik.h"          // Grafik-Objekte


int main() {
  TKiste<Element> c1;
  TKiste<UnterElement> c2;

  // Container c1 fuellen und ausgeben
  c1 << Element("Eins")<< Element("Zwei") << Element("Drei");
  for (int i=0; i<c1; i++) {
    cout << static_cast<const string>(c1[i]) << " ";
  }
  cout << endl;

  // Container c2 fuellen und ausgeben
  c2 << UnterElement("One")<< UnterElement("Two") << UnterElement("Three");
  for (int i=0; i<c2; i++) {
    cout << c2[i] << " ";
  }

  // Grafik-Element Klasse mit Container verwenden
  try {

    // Container fuer Grafik-Elemente vereinbaren
    TKiste<GrafikElement> gc;

    // Vereinbarung einiger Farben
    RGB_Pixel red(255,0,0); RGB_Pixel green(0,255,0);
    RGB_Pixel blue(0,0,255); RGB_Pixel yellow(255,255,0);
    RGB_Pixel black;

    // Bildgroesse vereinbaren
    const int height=200, width=150, iterations=100;

    // Grafik-Elemente in Container schieben
    gc << RechteckGefuellt(3,20, width-3, 25, green,blue);
    gc << Textzeile(38,11,"Testbild",red,black);
    gc << Rechteck(0,0,width-1,height-1,green);
    Rechteck r1(8,height/2-2,130,height/2+15,yellow);
    Rechteck r2;
    GrafikElement &g1=r1;
    GrafikElement &g2=r2;
    g2=g1; // r2=r1;
    g2.add_offset(15,30);
    gc << g1;
    gc << g2;
    for (int k=0; k<iterations; k++) {
      int i=int(100.0*sin(3.0*k*2.0*M_PI/iterations))+height/2;
      GrafikElement* pl = new Linie(2*i/3,4*i/3,width-i,height-3*i,green);
      gc << *pl;
      GrafikElement* pk = new Linie(0,0,0,0,black);
      *pk=*pl;
      pk->add_offset(40,30);
      gc << *pk;
      delete pl;
      delete pk;
    }
    gc << Textzeile(10,height/2,"OOP ist sch\x94n!",yellow,black);

    // Bild I vereinbaren
    Image I(width,height);

    // Grafik-Elemente in Bild einzeichnen
    for (int i=0; i<gc; i++) {
      gc[i].draw(I);
    }

    // Bild schreiben
    BmpWrite video("P7.bmp",I);
  } catch(...) { cout << "Ausnahme gefangen" << endl; }

  cout << endl;

  return 0;
}
