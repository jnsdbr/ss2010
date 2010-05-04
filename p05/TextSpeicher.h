//-------------------------------------------------------------------------------
// Klasse TextSpeicher zur Manipulation von Textdateien mittels
// zweidimensionalem Feldzugriff
//
// Prof. Dr.-Ing. B. Lang
// (c) FH Osnabrueck
// OOP-Praktikum
//-------------------------------------------------------------------------------
#ifndef _TextSpeicher_h_
#define _TextSpeicher_h_

class TextSpeicher {
 public:
  class TextZeile;
 private:
  TextZeile **t;
  int size;
  int lines;
  string filename;
  void expand(int s);
 public:
  class OutOfBounds {};
  TextSpeicher();
  TextSpeicher(string Filename);
  TextSpeicher(TextSpeicher&);
  ~TextSpeicher();
  TextSpeicher& operator= (TextSpeicher&);
  void SetFilename(string Filename);
  TextZeile& operator [] (int line);
  operator int () const { return lines; }
  int MaxColumns () const;
};
class TextSpeicher::TextZeile {
  string l;
 public:
  TextZeile();
  TextZeile(string tl);
  TextZeile(TextZeile&);
  ~TextZeile();
  TextZeile& operator= (TextZeile&);
  char& operator [] (int column);
  operator int () const { return l.size(); }
  operator const string () const { return l; }
};

#endif
