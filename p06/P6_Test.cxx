// --------------------------------------------------------------
// Testprogramm zu Aufgabe 1, Praktikumsübung 6
// Praktikum Objektorientierte Programmierung
// Fachhochschule Osnabrueck
// (c) Prof. Dr.-Ing. Bernhard Lang
// --------------------------------------------------------------
#include "rgb.h"             // Darstellung von Pixeln
#include "image.h"           // Zweidimensionales Bild
#include "bmpwrite.h"        // Schreiben von BMP-Dateien
#include "grafik.h"          // Grafik-Objekte
#include <iostream>
#include <math.h>
using namespace std;

int main() {
  try {
    // Vereinbarung einiger Farben
    RGB_Pixel red(255,0,0); RGB_Pixel green(0,255,0);
    RGB_Pixel blue(0,0,255); RGB_Pixel yellow(255,255,0);
    RGB_Pixel black;

    // Bild I vereinbaren
    const int height=200, width=150, iterations=100;
    Image I(width,height);

    //
    // Klassenhierarchie anwenden und überprüfen
    //
    // Einfache Objekte
    RechteckGefuellt(3,20, width-3, 25, green,blue).draw(I);
    Textzeile(38,11,"Testbild",red,black).draw(I);
    Rechteck(0,0,width-1,height-1,green).draw(I);

    // Objekte mittels GrafikElement-Referenz ansprechen
    Rechteck r1(8,height/2-2,130,height/2+15,yellow);
    Rechteck r2;
    GrafikElement &g1=r1; // Rechteck r1 mittels GrafikElement-Referenz ansprechen
    GrafikElement &g2=r2; // Rechteck r2 mittels GrafikElement-Referenz ansprechen
    g2=g1;                // r2=r1;
    g2.add_offset(15,30); // r2 verschieben
    g1.draw(I);           // r1 zeichnen
    g2.draw(I);           // r2 zeichnen
    // Objekte clonen und mittels GrafikElement-Zeiger ansprechen
    GrafikElement* pg(g2.clone()); // Clone-Objekt erstellen
    pg->add_offset(15,30);         // Bezugspunkt im Clone-Objekt verschieben
    pg->draw(I);                   // Clone-Objekt zeichnen
    delete pg;                     // Clone-Objekt freigeben
    // Fehlerfall überprüfen
    try {
      Linie l;
      l=g1;
    } catch(...) {
      cout << "Rechteck an Linie zuweisen ist nicht erlaubt" << endl;
    }
    // Objekte mittels GrafikElement-Zeiger ansprechen
    for (int k=0; k<iterations; k++) {
      int i=int(100.0*sin(3.0*k*2.0*M_PI/iterations))+height/2;
      GrafikElement* pl = new Linie(2*i/3,4*i/3,width-i,height-3*i,green);
      pl->draw(I);
      GrafikElement* pk = new Linie(0,0,0,0,black);
      *pk=*pl;
      pk->add_offset(40,30);
      pk->draw(I);
      delete pl;
      delete pk;
    }
    Kreis(75,100,50,red).draw(I);
    Kreis(75,100,40,red).draw(I);
    Textzeile(10,height/2,"OOP ist sch\x94n!",yellow,black).draw(I);

    // Bild schreiben
    BmpWrite("P6.bmp",I);
  } catch(...) { cout << "Ausnahme gefangen" << endl; }
}
