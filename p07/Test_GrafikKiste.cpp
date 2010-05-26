// --------------------------------------------------------------
// Testprogramm zur Praktikumsübung 7
// Praktikum Objektorientierte Programmierung
// Fachhochschule Osnabrueck
// (c) Prof. Dr.-Ing. Bernhard Lang
// --------------------------------------------------------------
#include "RGB_Pixel.h"          // Darstellung von Pixeln
#include "Image.h"        // Zweidimensionales Bild
#include "AviWrite.h"     // Schreiben von AVI-Dateien
#include "Grafikklasse.h"       // Grafik-Objekte
#include "GrafikKiste.h"   // Fifo von Grafik-Objekten
#include <iostream>
#include <math.h>
int main() {
  try {
    // Vereinbarung einiger Farben
    RGB_Pixel red(255,0,0); RGB_Pixel green(0,255,0);
    RGB_Pixel blue(0,0,255); RGB_Pixel yellow(255,255,0);
    RGB_Pixel transparent;

    // Vereinbarung eines AVI-Objekts
    #if 1
    const int height=240, width=320, frames=200; // (Erzeugt Video von ca. 45 MB)
    #else
    const int height=180, width=120, frames=60; // (Erzeugt Video von ca. 3,8 MB)
    #endif
    AviWrite video("P7.avi",width,height);

    // Erstes Fifo für Grafikelemente vereinbaren und füllen
    GrafikKiste f1;
    f1 << TextZeile(10,height/2,"OOP ist sch\x94n!",yellow,transparent);
    f1 << Rechteck(8,height/2-2,130,height/2+15,yellow);

    for (int k=0;k<frames;k++) { // Generierung der Frames
      cout << '.' << flush;

      // Zweites Fifo für Grafikelemente vereinbaren und füllen
      GrafikKiste f;
      int i=int(100.0*sin(3.0*k*2.0*M_PI/frames))+height/2;
      int j=int(10.0*sin(10.0*k*2.0*M_PI/frames))+width/2;
      f << Linie(2*i/3,4*i/3,width-i,height-3*i,green);
      f << RechteckGefuellt(3,i-2, width-3, i/2+15,green,blue);
      f << TextZeile(+j-30,i,"Testbild",red,transparent);
      f << Rechteck(0,0,width-1,height-1,green);

      // Bei erstem Fifo den Bezugspunkt aller Grafikelemente verschieben
      // und Inhalt des ersten Fifos in das zweite Fifo kopieren
      f1.add_offset(static_cast<int>(10*sin(10.0*k*2.0*M_PI/frames)),
                    static_cast<int>(10*cos(10.0*k*2.0*M_PI/frames)));
      f << f1;

      // Bild I vereinbaren und zweites Fifo in das Bild zeichnen
      Image I(width,height);
      f.draw(I);

      // Bild in AVI-Video schreiben
      video << I;
    }
  } catch(...) { cout << "Ausnahme gefangen" << endl; }
}
