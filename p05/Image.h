//-------------------------------------------------------------------------------
// Klasse zur Behandlung von Bildern
//
// Prof. Dr.-Ing. B. Lang
// (c) FH Osnabrueck
// OOP-Praktikum
//-------------------------------------------------------------------------------
#ifndef _image_h_
#define _image_h_

#include "RGB_Pixel.h"

class Image {
  Image(Image& c):OutsideLine(0) { throw "class Image: Kopierkonstruktor gesperrt"; }
  Image& operator= (Image& c) { throw "class Image: Zuweisungsoperator gesperrt"; }
 public:
  class Line {
    Line(Line& c) {}
    Line& operator= (Line& c) { return *this; }
    int width;
    RGB_Pixel* linebuffer;  // Zeiger auf ein Feld von Pixeln
    RGB_Pixel OutsidePixel; // Pixel für Zugriffe außerhalb der Zeile
   public:
    Line(int width):width(width),linebuffer(new RGB_Pixel[width]){}
    ~Line() { delete [] linebuffer; }
    RGB_Pixel& operator [] (int i);
  };
 private:
  int height, width;
  Line** imagebuffer; // Zeiger auf ein Feld von Zeilen
  Line OutsideLine;   // Zeile für Zugriffe außerhalb des Bildes
 public:
  Image(int width, int height);
  ~Image();
  Line& operator [] (int i);
  int Width()  const { return width;  }
  int Height() const { return height; }
};

#endif
