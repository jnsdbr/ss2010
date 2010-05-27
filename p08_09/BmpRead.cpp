//------------------------------------------------------------------------------------------
// (c) Prof. Dr.-Ing. Bernhard Lang
//     FH Osnabrück    
//------------------------------------------------------------------------------------------
#include <stdio.h>
#include "BmpRead.h"
#include "RGB_Pixel.h"

#define HOHE_BMP_FORMAT_TOLERANZ 1

BmpRead::BmpRead(const char* FileName): FileIn(FileName) {
   // Variablendeklarationen 
   int LUT_used = 0;        // Schaltervariable
   int GrayLUT  = 0;        // Schaltervariable
   // Daten aus Dateikopf
   unsigned long FileSize              = 0;
   unsigned long ImageOffset           = 0;
   // Daten aus Bitmap-Kopf
   unsigned long  ImageHeaderSize      = 0;
   unsigned short ImageBitCount        = 0;
   unsigned long  ImageCompression     = 0;
   unsigned long  ImageSize            = 0;
   unsigned long  ImageXPelsPerMeter   = 0;
   unsigned long  ImageYPelsPerMeter   = 0;
   unsigned long  ImageColorsUsed      = 0;
   unsigned long  ImageColorsImportant = 0;
   unsigned char LUT[256][3];
   
   // ----------------------------------------------------------------
   // Eingabedatei oeffnen
   // ----------------------------------------------------------------
//   in = fopen(FileName, "rb");

   // --------------------------------------
   // Analysiere Dateikopf
   // --------------------------------------
   { short id;
     // Kennung "BM"
     id = get_short();
     if ( id != 0x4d42 ) { // ASCII-Zeichen "BM" müssen hier stehen
       throw "BmpRead::BmpRead(char*): Error: Not a BMP-File\n";
     }
     // Dateigröße
     FileSize = get_long();
     // Zwei reservierte Worte, müssen 0 enthalten
     if ((get_short()!=0)) {
#ifndef HOHE_BMP_FORMAT_TOLERANZ
       // Auskommentiert, da nicht alle Dateien diese Bedingung erfüllen.
       // Wenn der Rest stimmt, ist es auch nicht so schlimm.
       throw "BmpRead::BmpRead(char*): Error: Reserved words must be 0\n";
#endif
     }
     if ((get_short()!=0)) {
#ifndef HOHE_BMP_FORMAT_TOLERANZ
       // Auskommentiert, da nicht alle Dateien diese Bedingung erfüllen.
       // Wenn der Rest stimmt, ist es auch nicht so schlimm.
       throw "BmpRead::BmpRead(char*): Error: Reserved words must be 0\n";
#endif
     }
     // Offset der Pixeldaten
     ImageOffset = get_long();
   }
#if DEBUG_BMP_READ 
   printf("\nDateikopf von Datei %s:\n", FileName);
   printf("  Dateigroesse:             %li\n",  FileSize);
   printf("  Offset der Pixeldaten:    %li\n",  ImageOffset);
#endif

   // --------------------------------------
   // Analysiere Info-Kopf
   // --------------------------------------
   ImageHeaderSize = get_long();
   switch(ImageHeaderSize) {
     case 12:
       // old OS/2-Type Bitmap
       width    = get_short();
       height   = get_short();
       if (get_short()!=1) { // Anzahl der Planes muß 1 sein!
         throw "BmpRead::BmpRead(char*): Error: Wrong number of planes defined\n";
       }
       ImageBitCount = get_short();
       switch(ImageBitCount) {
         case 1: // monochrome Bitmap
         case 4: // 16 Farben Bitmap
         case 8: // 256 Farben Bitmap
           ImageColorsUsed = 1<<ImageBitCount;
           LUT_used = 1; // LUT notwendig
           break;
         case 24: // True Color Bitmap
           LUT_used = 0;
           break;
         default:
           throw "BmpRead::BmpRead(char*): Error: Illegal Bitmap Bit Count\n";
       }
#if DEBUG_BMP_READ 
       printf("Infokopf von Datei %s:", FileName);
       printf("  Dateityp:                 OS/2 Bitmap\n");
       printf("  Bildbreite:               %li\n", width);
       printf("  Bildhoehe:                %li\n", height);
       printf("  Bits pro Pixel:           %i\n",  ImageBitCount);
#endif
       break;
     case 40:
       // Windows-Type Bitmap;
       width           = get_long();
       height          = get_long();
       if (get_short()!=1) { // Anzahl der Planes muá 1 sein!
         throw "BmpRead::BmpRead(char*): Error: Wrong number of planes defined\n";
       }
       ImageBitCount        = get_short();
       ImageCompression     = get_long();
       ImageSize            = get_long();
       ImageXPelsPerMeter   = get_long();
       ImageYPelsPerMeter   = get_long();
       ImageColorsUsed      = get_long();
       ImageColorsImportant = get_long();
       switch(ImageBitCount) {
         case 1: // monochrome Bitmap
         case 4: // 16 Farben Bitmap
         case 8: // 256 Farben Bitmap
           if (ImageColorsUsed==0) {
             ImageColorsUsed = 1<<ImageBitCount;
           } else if (ImageColorsUsed > (1U<<ImageBitCount)) {
             throw "BmpRead::BmpRead(char*): Error: Wrong LUT size in File\n";
           }
           LUT_used = 1; // LUT notwendig
           break;
         case 16: // True Color Bitmap
         case 24: // True Color Bitmap
         case 32: // True Color Bitmap
           LUT_used = 0;
           break;
         default:
           throw "BmpRead::BmpRead(char*): Error: Illegal Bitmap Bit Count\n";
       }
#if DEBUG_BMP_READ 
       printf("Infokopf von Datei %s:\n", FileName);
       printf("  Dateityp:                 Windows Bitmap\n");
       printf("  Bildbreite:               %li\n", width);
       printf("  Bildhoehe:                %li\n", height);
       printf("  Bits pro Pixel:           %i\n",  ImageBitCount);
       printf("  Kompression:              %li\n", ImageCompression);
       printf("  Bildgroesse:              %li\n", ImageSize);
       printf("  x Pixel pro Meter:        %li\n", ImageXPelsPerMeter);
       printf("  y Pixel pro Meter:        %li\n", ImageYPelsPerMeter);
       printf("  LUT-Größe:                %li\n", ImageColorsUsed);
       printf("  Verwendete LUT Eintraege: %li\n", ImageColorsImportant);
#endif
       if (ImageCompression) {
         throw "BmpRead::BmpRead(char*): Bildkompression noch nicht unterstuetzt\n";
       }
       break;
     case 120:
       throw "BmpRead::BmpRead(char*): WindowsV4-Type Bitmap (not yet supported)\n";
       break;
     case 136:
       throw "BmpRead::BmpRead(char*): WindowsV5-Type Bitmap (not yet supported)\n";
       break;
     default:
       throw "BmpRead::BmpRead(char*): Error: Unknown Bitmap type\n";
   }

   // --------------------------------------
   // LUT auslesen
   // --------------------------------------
   if (LUT_used) {
     // LUT used, read LUT
     unsigned int i;
     int ch;
     int LUT_Byte4 = 0;
     for (i=0;i<ImageColorsUsed;i++) {
       ch = LUT[i][2] = get_char(); // blue
       ch = LUT[i][1] = get_char(); // green
       ch = LUT[i][0] = get_char(); // red
       switch(ImageHeaderSize) {
         case 12:
           break;
         case 40:
         case 120:
         case 136:
           ch = get_char();
           if (ch!=0) {
             LUT_Byte4 = 1;
           }
           break;
       }
     }
     if (LUT_Byte4) {
       printf("Warnung: Viertes LUT Byte nicht immer 0!\n");
     }
     // LUT überprüfen, ob sie eine Grauwert-LUT ist
     GrayLUT = 1;
     for (i=0;i<ImageColorsUsed;i++) {
       if (LUT[i][2] != i) { GrayLUT=0; break; }
       if (LUT[i][1] != i) { GrayLUT=0; break; }
       if (LUT[i][0] != i) { GrayLUT=0; break; }
     }
   } // else LUT not used
   // --------------------------
   // Konsistenzüberprüfung
   // --------------------------
   // Ermittelte (InFilePosition) und aus Datei gelesene (ImageOffest)
   // Position der Pixeldaten vergleichen.
   if (ImageOffset!=InFilePosition) {
     // Hier stimmt was nicht, beide Zeiger sollten gleich sein
     throw "BmpRead::BmpRead(char*): Error: Inconsitency, Image Offset wrong\n";
   }

   // Bild allozieren 
   i = new Image(width, height);

   // --------------------------------------
   // Pixeldaten auslesen
   // --------------------------------------
   { long x,y;
     int PixelsInBuffer;
     unsigned long PixelBuffer;
     unsigned int  value;
     unsigned char red,green,blue;
     int ReadAlign;
     
     // Zeilenalignement auf 32-Bit Worte bestimmen
     ReadAlign = ( 4 * ((width*ImageBitCount+31) >> 5) // Word32 Align
                     - ((width*ImageBitCount+7)  >> 3) // Byte Align
                 );
                 
     // Bild auslesen und verarbeiten
     for (y=0;y<height;y++) {
       // printf("Line %i\n",y);
       PixelsInBuffer=0;
       for (x=0;x<width;x++) {
         // Pixel aus Datei auslesen
         switch(ImageBitCount) {
           case 1:
             // Monochrome Bilder 
             if (!PixelsInBuffer) {
               PixelBuffer = get_char();
               PixelsInBuffer = 8;
             }
             value = (PixelBuffer>>7) & 1;
             PixelBuffer <<= 1;
             red   = LUT[value][0];
             green = LUT[value][1];
             blue  = LUT[value][2];
             PixelsInBuffer--;
             break;
           case 4:
             // 4-Bit Bilder 
             if (!PixelsInBuffer) {
               PixelBuffer = get_char();
               PixelsInBuffer = 2;
             }
             value = (PixelBuffer>>4) & 0xF;
             PixelBuffer <<= 4;
             red   = LUT[value][0];
             green = LUT[value][1];
             blue  = LUT[value][2];
             PixelsInBuffer--;
             break;
           case 8:
             // 8-Bit Bilder 
             value = get_char();
             if (GrayLUT) {
               red = green = blue = value;
             } else {
               red   = LUT[value][0];
               green = LUT[value][1];
               blue  = LUT[value][2];
             }
             break;
           case 16:
             // 16-Bit Bilder 
             PixelBuffer  = get_char();
             PixelBuffer |= (get_char() << 8);
             blue  = (PixelBuffer       & 0x1f)<<3;
             green = ((PixelBuffer>>5)  & 0x1f)<<3;
             red   = ((PixelBuffer>>10) & 0x1f)<<3;
             break;
           case 24:
             // 24-Bit Bilder 
             blue  = get_char();
             green = get_char();
             red   = get_char();
             break;
         }
         // Pixel in Bildspeicher wegschreiben
         (*i)[y][x] = RGB_Pixel(red,green,blue);
       }
       // Read Alignment of this line
       for (x=0;x<ReadAlign;x++) {
         get_char();
       }
     }
   }

   // ------------------------------------
   // Konsistenzüberprüfung
   // ------------------------------------
   if (InFilePosition != FileSize) {
#if DEBUG_BMP_READ 
     printf("Warnung: Falsche Dateigroesse in Datei gespeichert\n");
#endif
   }
}

BmpRead& BmpRead::operator>> (Image& img) {
  for (int x(0); x<img.Width(); x++ ) {
    for (int y(0); y<img.Height(); y++ ) {
      img[y][x] = (*i)[y][x];
    }
  }
  return *this;
}

