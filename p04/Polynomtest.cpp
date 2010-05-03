//-------------------------------------------------------------------------------
// Testprogramm zum OOP-Praktikum, Versuch 4
//
// Prof. Dr.-Ing. B. Lang
// (c) FH Osnabrueck
// OOP-Praktikum
//-------------------------------------------------------------------------------
#include "Polynom.h"
//#include "Image.h"
//#include "BmpWrite.h"
//#include "hline.h"
//#include "vline.h"

int main() {

  cout << "OOP-Praktikum, Versuch 4" << endl;
  //
  // Polynome spezifizieren, verknüpfen und ausgeben
  //
  Polynom P(X(4) - 3.0*X(3) + 2.0*X(5) + 1.0);
  cout << "P:   " << P << endl;
  Polynom Q;
  Q = 2.0*X(2) - 3.0*X(1) + 7.0;
  cout << "Q:   " << Q << endl;
  cout << "P+Q: " << P+Q << endl;
  Polynom PmQ(P-Q);
  cout << "P-Q: " << PmQ << endl;
  Polynom A(2.0*X(2)+3.0*X(1) + 4.0);
  cout << "A:   " << A << endl;
  Polynom B = X(1)+1.0;
  cout << "B:   " << B << endl;
  cout << "P-P: " << P-P << endl;
  cout << "P(0,75)=" << P(0.75) << endl;

  //
  // Koeffizienten eines Polynoms ermitteln
  //
  Polynom C = P+A;
  cout << "Koeffizienten von C=P+A:";
  for (int i=C;i>=0;i--) {
    cout << " " << C[i]; 
  }
  cout << endl;
/*
  //
  // Polynome in ein Image-Objekt einzeichnen  
  //
  Image I(400,300);
  HLine(20, 150, 360, RGB_Pixel(0,0,255)).draw(I);
  VLine(200, 20, 260, RGB_Pixel(0,0,255)).draw(I);
  // Im Intervall von x={-3..3} und y={-20..20} zeichnen und dies im
  // Pixelbereich x_i={20..380} und y_i={20..280} darstellen
  P.draw(I, 20,380,20,280, -3.0,3.0,-20.0,20.0, RGB_Pixel(0,255,255));
  Q.draw(I, 20,380,20,280, -3.0,3.0,-20.0,20.0, RGB_Pixel(255,255,0));

  //
  // Image-Objekt in BMP-Datei ausgeben
  //
  cout << "Datei P4.bmp wird geschrieben" << endl;
  BmpWrite("P4.bmp",I);
*/
  return 0;
}

