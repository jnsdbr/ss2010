#ifndef _BmpRead_h_
#define _BmpRead_h_
//------------------------------------------------------------------------------------------
// (c) Prof. Dr.-Ing. Bernhard Lang
//     FH Osnabrück    
//------------------------------------------------------------------------------------------

#define DEBUG_BMP_READ 0

//#include <stdio.h>
#include "FileIO.h"
#include "Image.h"
#include "RGB_Pixel.h"

class BmpRead: public FileIn, public Align {
private:
  int width;
  int height;
  Image* i;
public:
  BmpRead(const char* FileName);
  ~BmpRead() { delete i; }
  operator Image& () {  return (*i); }
  int Width()  { return width;  }
  int Height() { return height; }
  BmpRead& operator>> (Image& img);
};
#endif

