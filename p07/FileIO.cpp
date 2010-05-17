//------------------------------------------------------------------------------------------
// (c) Prof. Dr.-Ing. Bernhard Lang
//     FH Osnabrück    
//------------------------------------------------------------------------------------------
#include "FileIO.h"

//-----------------------------------------------------------------------
// class FileIn
//-----------------------------------------------------------------------

FileIn::FileIn(const char* FileName) {
  f = fopen(FileName, "rb");
  if (!f) throw "FileIn::FileIn(char* FileName): Cannot open file";
  InFilePosition = 0;
}

FileIn::~FileIn() {
   if (NULL!=f) {
      fclose(f);
   }
}

long FileIn::get_long() {
  long value;
  unsigned char buffer[sizeof(long)];
  fread((char*)&buffer, 1, 4 , f);
  value = ((buffer[3]*256L+buffer[2])*256L+buffer[1])*256L+buffer[0];
  InFilePosition += 4;
  return value;
}

short FileIn::get_short() {
  short value;
  unsigned char buffer[sizeof(short)];
  fread((char*)&buffer, 1, 2 , f);
  value = buffer[1]*256+buffer[0];
  InFilePosition += 2;
  return value;
}

unsigned char FileIn::get_char() {
  unsigned char value;
  fread((unsigned char*)&value, 1, 1 , f);
  InFilePosition += 1;
  return value;
}

int FileIn::read_buffer(char* buffer, int N) {
  InFilePosition += N;
  return fread(buffer, 1, N, f);
}

//-----------------------------------------------------------------------
// class FileOut
//-----------------------------------------------------------------------

FileOut::FileOut(const char* FileName) {
   f      = NULL;
   f      = fopen(FileName,"wb");
   if (!f) throw "FileOut::FileOut(char* FileName): Cannot open file";
}

FileOut::~FileOut() {
   if (NULL!=f) {
      fclose(f);
   }
}

void FileOut::write_long(long value) {
  unsigned char buffer[sizeof(long)];
  for (int i=0;i<sizeof(long);i++) {
    buffer[i]=value&0xff;
    value >>=8;
  }
  fwrite((char*)buffer, 1, 4 , f);
}

void FileOut::write_short(short value) {
  unsigned char buffer[sizeof(short)];
  for (int i=0;i<sizeof(short);i++) {
    buffer[i]=value&0xff;
    value >>=8;
  }
  fwrite((char*)&buffer, 1, 2 , f);
}

void FileOut::write_char(char value) {
  fwrite((char*)&value, 1, 1 , f);
}

int FileOut::write_buffer(char* buffer, int N) {
  return fwrite(buffer, 1, N , f);
}

int FileOut::seek(long pos) {
	return fseek(f, pos, SEEK_SET);
}

//-----------------------------------------------------------------------
// class Align
//-----------------------------------------------------------------------

long Align::Align16(long value) {
   if (value&1L) return value+1; // align to 16Bit
   else return value;
}

long Align::Align32(long value) {
   if (value&3L) return (value&(0xfffffffc))+4; // align to 32Bit
   else return value;
}
