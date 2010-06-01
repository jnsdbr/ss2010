//------------------------------------------------------------------------------------------
// (c) Prof. Dr.-Ing. Bernhard Lang
//     FH Osnabrück    
//------------------------------------------------------------------------------------------

#ifndef _AVI_Diashow_h_
#define _AVI_Diashow_h_

#include "grafik.h"
#include "image.h"
#include "BmpRead.h"
#include "AviWrite.h"
#include "Ueberblendungen.h"
#include "GrafikHuelle.h"
#include <vector>
#include <map>
#include <iostream>
using namespace std;

class AVI_Diashow {
  int hoehe, breite;
  string aviname;
 public:
  enum Ueberblendung { Soft, Schieben };
  AVI_Diashow(const string& AviName, int Breite, int Hoehe): hoehe(Hoehe), breite(Breite), aviname(AviName) {};
  virtual ~AVI_Diashow() {};
  int  Clip_hinzufuegen(const string& name, int Laenge);
  bool Grafik_hinzufuegen(int Clip, const GrafikElement& g);
  bool Uebergang_hinzufuegen(int Clip, Ueberblendung ue, int Laenge);
  void Film_erstellen() const;
  int  Laenge_des_Films() const;
};

#endif
