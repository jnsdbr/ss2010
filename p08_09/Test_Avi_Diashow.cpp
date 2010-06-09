//------------------------------------------------------------------------------------------
// (c) Prof. Dr.-Ing. Bernhard Lang
//     FH Osnabrück    
//------------------------------------------------------------------------------------------

#include "AVI_Diashow.h"
#include <iostream>
using namespace std;

int main() {
  cout << "OOP-Praktikum" << endl;
  cout << "Avi_Diashow - Testprogramm" << endl;
  cout << "Prof. Dr.-Ing. B. Lang" << endl;
  const int Breite(300), Hoehe(225);
  #if 1
  AVI_Diashow MeineShow("test.avi",Breite,Hoehe);
  #else
  AVI_Diashow MeineShow("avi\\test.avi",Breite,Hoehe); // Bei XP-Bug: "test.avi" in Unterverzeichnis "avi" schreiben
  #endif
  
  // Clips spezifizieren  
  { int clip = MeineShow.Clip_hinzufuegen("Schwarz.bmp",30);
    MeineShow.Grafik_hinzufuegen(clip,TextZeile(Breite/4,Hoehe/2,"Meine Show",RGB_Pixel(255,255,255),RGB_Pixel(0,0,0)));
    MeineShow.Uebergang_hinzufuegen(clip,AVI_Diashow::Soft,25);
  }
  
  { int clip = MeineShow.Clip_hinzufuegen("Bild1.bmp",60);
    MeineShow.Grafik_hinzufuegen(clip,Rechteck(150,26,110,190,RGB_Pixel(255,255,0)));
    MeineShow.Uebergang_hinzufuegen(clip,AVI_Diashow::Soft,25);
  }
  
  { int clip = MeineShow.Clip_hinzufuegen("Bild2.bmp",30);
    MeineShow.Grafik_hinzufuegen(clip,Linie(0,0,Breite-1,Hoehe-1,RGB_Pixel(255,0,0)));
    MeineShow.Grafik_hinzufuegen(clip,Linie(Breite-1,0,0,Hoehe-1,RGB_Pixel(255,0,0)));
  }

  { int len=1;
    for (int i=0; i<3; i++) {
      MeineShow.Clip_hinzufuegen("Bild1.bmp",len);
      MeineShow.Clip_hinzufuegen("Bild2.bmp",len);
      MeineShow.Clip_hinzufuegen("Bild3.bmp",len);
      MeineShow.Clip_hinzufuegen("Bild4.bmp",len);
    }
  }
  { int len=2;
    for (int i=0; i<3; i++) {
      MeineShow.Clip_hinzufuegen("Bild1.bmp",len);
      MeineShow.Clip_hinzufuegen("Bild2.bmp",len);
      MeineShow.Clip_hinzufuegen("Bild3.bmp",len);
      MeineShow.Clip_hinzufuegen("Bild4.bmp",len);
    }
  }
  
  { int clip = MeineShow.Clip_hinzufuegen("Bild3.bmp",30);
    MeineShow.Grafik_hinzufuegen(clip,TextZeile(10,10,"Bild 3",RGB_Pixel(255,255,0),RGB_Pixel(0,0,0)));
    MeineShow.Uebergang_hinzufuegen(clip,AVI_Diashow::Schieben,25);
  }

  { int clip = MeineShow.Clip_hinzufuegen("Weiss.bmp",30);
    MeineShow.Grafik_hinzufuegen(clip,TextZeile(Breite/4,Hoehe/2,"Das wars",RGB_Pixel(0,0,0),RGB_Pixel(255,255,255)));
  }

  { int clip = MeineShow.Clip_hinzufuegen("Weiss.bmp",60);
    MeineShow.Grafik_hinzufuegen(clip,TextZeile(Breite/4,Hoehe/2,"Trauig, aber wahr.",RGB_Pixel(0,0,0),RGB_Pixel(255,255,255)));
  }
  { int clip = MeineShow.Clip_hinzufuegen("Schwarz.bmp",60);
    MeineShow.Grafik_hinzufuegen(clip,TextZeile(Breite/4,Hoehe/2,"Da habe ich mehr erwartet",RGB_Pixel(255,255,255),RGB_Pixel(0,0,0)));
  }
  { int clip = MeineShow.Clip_hinzufuegen("Weiss.bmp",60);
    MeineShow.Grafik_hinzufuegen(clip,TextZeile(Breite/4,Hoehe/2,"Ja, ich auch. :(",RGB_Pixel(0,0,0),RGB_Pixel(255,255,255)));
  }
  { int clip = MeineShow.Clip_hinzufuegen("Schwarz.bmp",60);
    MeineShow.Grafik_hinzufuegen(clip,TextZeile(Breite/4,Hoehe/2,"...",RGB_Pixel(255,255,255),RGB_Pixel(0,0,0)));
  }
  // Film erstellen  
  cout << "Laenge des Films: " << MeineShow.Laenge_des_Films() << " frames" << endl;
  MeineShow.Film_erstellen();
  return 0;
}
