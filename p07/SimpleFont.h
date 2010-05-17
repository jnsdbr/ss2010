//-------------------------------------------------------------------------------
// Klasse zur Umwandlung von ASCII-Zeichen in Rasterdarstellung
//
// Prof. Dr.-Ing. B. Lang
// (c) FH Osnabrueck
// OOP-Praktikum
//-------------------------------------------------------------------------------
#ifndef _SimpleFont_h_
#define _SimpleFont_h_

class SimpleFont {
  const static int FontHeight = 14;
  static unsigned char Generator[][FontHeight];
  int TheCharacter;
 public:
  class ChLine {
    friend class SimpleFont;
    static char Line;
    const static int FontWidth  = 8;
    ChLine() {}         // Defaultkonstruktor sperren
    ChLine(ChLine &) {} // Kopierkonstruktor sperren 
   public:
    bool operator [] (int i) const { return (Line>>(FontWidth-1-i))&1; }
  };
  SimpleFont(int i) : TheCharacter(i) {}
  ChLine &operator [] (int i) {
    if ((i<0)||(i>FontHeight)) {
      ChLine::Line = 0;
    } else {
      ChLine::Line = Generator[TheCharacter][FontHeight-1-i];
    }
    return *static_cast<ChLine*>(0);
  }
  static int height() { return FontHeight; }
  static int width()  { return ChLine::FontWidth; }
};


#endif
