//-------------------------------------------------------------------------------
// Klasse zum Schreiben von BMP-Dateien
//
// Prof. Dr.-Ing. B. Lang
// (c) FH Osnabrueck
// OOP-Praktikum
//-------------------------------------------------------------------------------
#ifndef _bmpwrite_h_
#define _bmpwrite_h_

#include <stdio.h>
#include "Image.h"

class BmpWrite {
 public:
  class FileOpenError {
   public:
    FileOpenError(char* filename, int linenumber):
      filename(filename),linenumber(linenumber){}
    char* filename;
    int   linenumber;
  };
 private:
  // Private Methoden
  long Align16(long value);
  long Align32(long value);
  void write_long(long value);
  void write_short(short value);
  void write_char(char value);
  // Komponenten
  int width;
  int height;
  unsigned char* buffer;
  FILE* f;
  int operator=(Image&);
  BmpWrite() { throw "BmpWrite: Defaultkonstruktor gesperrt";} 
  BmpWrite(BmpWrite&)   { throw "Kopierkonstruktor gesperrt";}
 public:
  BmpWrite(const char*, Image&);
  ~BmpWrite();
};

#endif

