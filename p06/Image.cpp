//-------------------------------------------------------------------------------
// Klasse zur Behandlung von Bildern, Implementierung der Methoden
//
// Prof. Dr.-Ing. B. Lang
// (c) FH Osnabrueck
// OOP-Praktikum
//-------------------------------------------------------------------------------
#include "Image.h"

RGB_Pixel& Image::Line::operator [] (int i) {
  if ((i>=0)&&(i<width)) return linebuffer[i];
  else return OutsidePixel;
}

Image::Image(int width, int height): height(height),width(width),
    imagebuffer(new Line*[height]),OutsideLine(width) {
  for (int i=0;i<height;i++) {
    imagebuffer[i] = new Line(width);
  }
}
Image::~Image() {
  for (int i=0;i<height;i++) {
    delete imagebuffer[i];
  }
  delete [] imagebuffer;
}
Image::Line& Image::operator [] (int i) {
  if ((i>=0)&&(i<height)) return *imagebuffer[i];
  else return OutsideLine;
}

