// --------------------------------------------------------------
// AviWrite: Object for writing uncompressed AVI Files
//          class definition
// (c) Prof. Dr.-Ing. Bernhard Lang
//     May 2005
// --------------------------------------------------------------
#ifndef _AviWrite_h_
#define _AviWrite_h_

// #include <stdio.h>
#include "FileIO.h"
#include "Image.h"
#include "RGB_Pixel.h"

class AviWrite: public FileOut, public Align {
 private:
  int  width;         // Bildbreite
  int  height;        // Bildhöhe
  int  framenumber;   // Aktuelle Frame-Nummer
  int  framerate;     // Bilder pro Sekunde
  int  error;
  char* ErrorText;
  void WriteJunkHeader(char* buffer, long size);
  void WriteTag(char* buffer);
 public:
  AviWrite(const char* FileName, long w, long h, int rate=25);
  ~AviWrite();
  AviWrite& operator<<(const Image&);

  const char* get_Error() const { return ErrorText; }

};

#endif

