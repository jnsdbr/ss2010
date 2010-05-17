// --------------------------------------------------------------
// AviWrite: Object for writing uncompressed AVI Files
//          Implementation of the methodes
// (c) Prof. Dr.-Ing. Bernhard Lang
//     May 2005
// --------------------------------------------------------------

#include "AviWrite.h"
#include "xa_avi.h"

//--------------------------------------------------------------------------------------
// Konstruktor
// Parameter:
//   FileName   - Name der AVI-Datei
//   w, h       - Bildbreite und Bildhöhe
//   rate       - Bildwiederholrate (in Bilder/sec)
//--------------------------------------------------------------------------------------
AviWrite::AviWrite(const char* FileName, long w, long h, int rate): FileOut(FileName) {
  long BufferSize;
  long MoviSize;
  long StrfSize;
  long StrhSize;
  long StrlSize;
  long AvihSize;
  long Idx1Size;
  long HdrlSize;
  long FileSize;
  long JunkSize;
  //
  width      = w;
  height     = h;
  //
  framenumber = 0;
  framerate  = rate;
  //
  BufferSize = Align32(width*3)*height;
  MoviSize   = 4 + (8 + BufferSize)*framenumber;
  StrfSize   = 40;
  StrhSize   = 56;
  StrlSize   = 4 + (8+StrhSize) + (8+StrfSize);
  AvihSize   = 56;
  Idx1Size   = framenumber*16;
  HdrlSize   = 4 + (8+AvihSize) + (8+StrlSize);
  JunkSize = 2048-HdrlSize-10*4;
  FileSize   = 4 + (8+HdrlSize) + (8+JunkSize) + (8+MoviSize)
                 + (8+Idx1Size);
  //
  WriteJunkHeader("RIFF",FileSize); WriteTag("AVI ");
  WriteJunkHeader("LIST",HdrlSize); WriteTag("hdrl");
  WriteJunkHeader("avih",AvihSize);
  write_long((1000000L/framerate)); // us_frame
  write_long(BufferSize*framerate); // Max. Bandwidth (Bytes/sec)
  write_long(0);             // pad_gran
  write_long(0x810);         // flags
  write_long(framenumber);    // total frames
  write_long(0);             // init frames
  write_long(1);             // streams
  write_long(BufferSize);    // suggested buffersize
  write_long(width);         // image width
  write_long(height);        // image height
  write_long(0);             // scale
  write_long(0);             // rate
  write_long(0);             // start
  write_long(0);             // length
  //
  WriteJunkHeader("LIST",StrlSize); WriteTag("strl");
  WriteJunkHeader("strh",StrhSize);
  WriteTag("vids");          // video stream identifier
  WriteTag("DIB ");          // video stream type
  write_long(0);             // flags
  write_short(0);            // prioritiy
  write_short(0);            // language
  write_long(0);             // init_frames
  write_long(1000000L/framerate); // scale (rate/scale = framerate)
  write_long(1000000L);      // rate
  write_long(0);             // start
  write_long(framenumber);    // length (total frames)
  write_long(BufferSize);    // suggested buffersize
  write_long(10000);         // quality (high)
  write_long(0);             // sample size
  write_short(0);            // rec_left
  write_short(0);            // rec_bottom
  write_short(width);        // rec_right
  write_short(height);       // rec_top
  //
  WriteJunkHeader("strf",StrfSize);
  write_long(40);            // format header size
  write_long(width);         // image width
  write_long(height);        // image height
  write_short(1);            // planes
  write_short(24);           // bits per pixel
  write_long(0);             // compression
  write_long(BufferSize);    // image size
  write_long(0);             // x-pel per meter
  write_long(0);             // y pel per meter
  write_long(0);             // lut size
  write_long(0);             // important colors
  //
  WriteJunkHeader("JUNK",JunkSize);
  for (;0<JunkSize;JunkSize--) {
    write_buffer(" ",1);
  }

  WriteJunkHeader("LIST",MoviSize); WriteTag("movi");
}

//--------------------------------------------------------------------------------------
// Destruktor
//--------------------------------------------------------------------------------------
AviWrite::~AviWrite() {
  
  // AVI-Datei abschliessen
  long BufferSize = Align32(width*3)*height;
  long Idx1Size = framenumber*16;

  long Position   = 4;
  WriteJunkHeader("idx1",Idx1Size);
  for (int i=0;i<framenumber;i++) {
     WriteTag("00db");
     write_long(10L);
     write_long(Position);
     write_long(BufferSize);
     Position += BufferSize+8;
  }

  // Header mit der Anzahl tatsächlich geschriebener Frames neu schreiben
  seek(0);
  long MoviSize   = 4 + (8 + BufferSize)*framenumber;
  long StrfSize = 40;
  long StrhSize = 56;
  long StrlSize = 4 + (8+StrhSize) + (8+StrfSize);
  long AvihSize = 56;
  long HdrlSize = 4 + (8+AvihSize) + (8+StrlSize);
  long JunkSize = 2048-HdrlSize-10*4;
  long FileSize      = 4 + (8+HdrlSize) + (8+JunkSize) + (8+MoviSize) + (8+Idx1Size);

  WriteJunkHeader("RIFF",FileSize); WriteTag("AVI ");
  WriteJunkHeader("LIST",HdrlSize); WriteTag("hdrl");
  WriteJunkHeader("avih",AvihSize);
  write_long((1000000L/framerate));         // us_frame
  write_long(BufferSize*framerate); // Max. Bandwidth (Bytes/sec)
  write_long(0);             // pad_gran
  write_long(0x810);         // flags
  write_long(framenumber);    // total frames
  write_long(0);             // init frames
  write_long(1);             // streams
  write_long(BufferSize);    // suggested buffersize
  write_long(width);         // image width
  write_long(height);        // image height
  write_long(0);             // scale
  write_long(0);             // rate
  write_long(0);             // start
  write_long(0);             // length
  //
  WriteJunkHeader("LIST",StrlSize); WriteTag("strl");
  WriteJunkHeader("strh",StrhSize);
  WriteTag("vids");          // video stream identifier
  WriteTag("DIB ");          // video stream type
  write_long(0);             // flags
  write_short(0);            // prioritiy
  write_short(0);            // language
  write_long(0);             // init_frames
  write_long((1000000L/framerate));         // scale (rate/scale = 25)
  write_long(1000000L);      // rate
  write_long(0);             // start
  write_long(framenumber);    // length (total frames)
  write_long(BufferSize);    // suggested buffersize
  write_long(10000);         // quality (high)
  write_long(0);             // sample size
  write_short(0);            // rec_left
  write_short(0);            // rec_bottom
  write_short(width);        // rec_right
  write_short(height);       // rec_top
}

//--------------------------------------------------------------------------------------
// Bild in AVI-Datei einschreiben
//--------------------------------------------------------------------------------------
AviWrite& AviWrite::operator<<(const Image& img) {
  if ((width!=img.Width())||(height!= img.Height())) {
    ErrorText = "int AviWrite::operator=(Image& img): Falsche Bildgröße übergeben";
    throw this;
  }
  long BufferSize = Align32(width*3)*height;
  long LineBufferSize = Align32(width*3);
  char* LineBuffer=new char[LineBufferSize];
  int x,y;
  LineBuffer[LineBufferSize-1]=0;
  LineBuffer[LineBufferSize-2]=0;
  LineBuffer[LineBufferSize-3]=0;
  LineBuffer[LineBufferSize-4]=0;
  WriteJunkHeader("00db",BufferSize);
  for (y=0;y<height;y++) {
    for (x=0;x<width;x++) {
      // img[y][x] wird nur auf der rechten Seite der Zuweisungen
      // verwendet. Daher ist der "const_cast" sinnvoll und ohne Schaden.
      RGB_Pixel& p = const_cast<Image&>(img)[y][x];
      LineBuffer[3*x]   = p.Blue();
      LineBuffer[3*x+1] = p.Green();
      LineBuffer[3*x+2] = p.Red();
    }
    write_buffer(LineBuffer,LineBufferSize);
  }
  framenumber++;
  delete [] LineBuffer;
  return *this;
}

void AviWrite::WriteJunkHeader(char* buffer, long size){
  if (4 != write_buffer(buffer, 4)) {
    error = 1;
    ErrorText = "Error in: void AviWrite::WriteJunkHeader(char* buffer, long size)";
    throw this;
  }
  write_long(size);
}

void AviWrite::WriteTag(char* buffer){
  if (4 != write_buffer(buffer, 4)) {
    error = 1;
    ErrorText = "Error in: void AviWrite::WriteTag(char* buffer)";
    throw this;
  }
}

