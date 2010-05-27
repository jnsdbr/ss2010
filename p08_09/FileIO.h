//------------------------------------------------------------------------------------------
// (c) Prof. Dr.-Ing. Bernhard Lang
//     FH Osnabrück    
//------------------------------------------------------------------------------------------
#ifndef _FileIO_h_
#define _FileIO_h_

#include <stdio.h>

class FileOpenError {
 public:
  FileOpenError(char* filename, int linenumber):
    filename(filename),linenumber(linenumber){}
  char* filename;
  int   linenumber;
};

class Align {
 public:
  long Align16(long value);
  long Align32(long value);
};

class FileIn {
 private:
  // Komponenten
  unsigned char* buffer;
  FILE* f;
protected:
  FileIn() {};
  unsigned long InFilePosition;
public:
  FileIn(const char*);
  ~FileIn();
  long get_long();
  short get_short();
  unsigned char get_char();
  int read_buffer(char*, int);
};

class FileOut {
 private:
  // Komponenten
  unsigned char* buffer;
  FILE* f;
protected:
  FileOut() {}; 
public:
  FileOut(const char*);
  ~FileOut();
  void write_long(long value);
  void write_short(short value);
  void write_char(char value);
  int  write_buffer(char*, int);
  int  seek(long pos);
};

#endif

