//-------------------------------------------------------------------------------
// Klasse zum Schreiben von BMP-Dateien, Implementierung der Methoden
//
// Prof. Dr.-Ing. B. Lang
// (c) FH Osnabrueck
// OOP-Praktikum
//-------------------------------------------------------------------------------
#include "BmpWrite.h"

BmpWrite::BmpWrite(const char* FileName,Image& img) {
   width  = 0;
   height = 0;
   f      = NULL;
   f      = fopen(FileName,"wb");
   if (!f) throw FileOpenError(__FILE__,__LINE__);
   *this = img;
}

BmpWrite::~BmpWrite() {
   if (NULL!=f) {
      fclose(f);
   }
}

int BmpWrite::operator=(Image& img) {
   long BytesPerLine;
   long BufferSize;
   int x,y;
   unsigned char* buffer;
   if (NULL !=f ) {
      width  = img.Width();
      height = img.Height();
      BytesPerLine = Align32(width*3);
      BufferSize = BytesPerLine*height;
      // Bitmap File Header
      fwrite("BM",1,2,f);
      write_long(14+40+BufferSize);
      write_short(0);
      write_short(0);
      write_long(14+40);
      // DIB Header
      write_long(40);
      write_long(width);
      write_long(height);
      write_short(1);
      write_short(24);
      write_long(0);
      write_long(BufferSize);
      write_long(0);
      write_long(0);
      write_long(0);
      write_long(0);
      // no LUT
      ;
      // write pixel data
      for (y=0;y<height;y++) {
         for (x=0;x<width;x++) {
            write_char(img[y][x].Blue());
            write_char(img[y][x].Green());
            write_char(img[y][x].Red());
            buffer +=3;
         }
         for (int i=BytesPerLine-3*x;i>0;i--) {
            write_char(0);
         }
      }
      fclose(f);
      f = NULL;
      return 0;
   } else {
      return 1;
   }
}

long BmpWrite::Align16(long value) {
   if (value&1L) return value+1; // align to 16Bit
   else return value;
}

long BmpWrite::Align32(long value) {
   if (value&3L) return (value&(0xfffffffc))+4; // align to 32Bit
   else return value;
}

#if 0

long BmpWrite::get_long() {
  long value;
  char buffer[sizeof(long)];
  fread((char*)&buffer, 1, 4 , f);
  value = ((buffer[3]*256L+buffer[2])*256L+buffer[1])*256L+buffer[0];
}

short BmpWrite::get_short() {
  short value;
  char buffer[sizeof(short)];
  fread((char*)&value, 1, 2 , f);
  value = buffer[1]*256+buffer[0];
}

char BmpWrite::get_char() {
  char value;
  fread((char*)&value, 1, 1 , f);
}

#endif

void BmpWrite::write_long(long value) {
  char buffer[sizeof(long)];
  for (unsigned int i=0;i<sizeof(long);i++) {
    buffer[i]=value&0xff;
    value >>=8;
  }
  fwrite((char*)buffer, 1, 4 , f);
}

void BmpWrite::write_short(short value) {
  char buffer[sizeof(short)];
  for (unsigned int i=0;i<sizeof(short);i++) {
    buffer[i]=value&0xff;
    value >>=8;
  }
  fwrite((char*)&buffer, 1, 2 , f);
}

void BmpWrite::write_char(char value) {
  fwrite((char*)&value, 1, 1 , f);
}

