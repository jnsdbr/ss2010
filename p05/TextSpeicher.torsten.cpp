#include <iostream>
#include <fstream>

using namespace std;

#include "TextSpeicher.h"

#define NUM_EXP 10

//---Methoden Klasse TextSpeicher---

// Private

void TextSpeicher::expand(int s) {
  TextZeile **temp;
  int i;
  if ((lines + s) < size) {
    return;
  }
  
  temp = t;

  // neues größeres Array erstellen
  t = new TextZeile*[size + s];

  // Zeiger aus altem Array in neues kopieren
  for(i=0;i<size;i++) {
    t[i] = temp[i];
    temp[i] = NULL;
  }

  // size auf neue Größe setzen
  size += s;

  // Ungenutzte Zeiger mit NULL initialisieren
  for(;i<size;i++) {
    t[i] = NULL;
  }

  // Altes Array löschen
  delete [] temp;
}

// Public

TextSpeicher::TextSpeicher() {
  // Variablen des Objektes initialisieren
  t = NULL;
  size = 0;
  lines = 0;
  filename.clear();
}

TextSpeicher::TextSpeicher(string Filename) {
  // Variablen des Objektes initialisieren
  t = NULL;
  size = 0;
  lines = 0;
  
  string line;
  ifstream datei;
  
  // filename im Objekt setzen
  filename = Filename;
  
  // Datei öffnen
  datei.open(filename.c_str());
  if(!datei) {
    throw "Datei kann nicht geöffnet werden";
  }

  // Datei zeilenweise auslesen
  while(getline(datei,line))  {
    expand(NUM_EXP);
    t[lines] = new TextZeile(line);
    lines++;
  }

  // Datei schließen
  datei.close();
}

TextSpeicher::TextSpeicher(TextSpeicher &ts) {
  size = ts.size;
  lines = ts.lines;
  filename.clear();
  
  t = new TextZeile*[ts.size];

  for(int i=0;i<size;i++) {
    t[i] = ts.t[i];
  }
}

TextSpeicher::~TextSpeicher() {
  if(!filename.empty()) {
    ofstream datei;
    datei.open(filename.c_str());

    for(int i=0;i<lines;i++) {
      if(t[i]) {
	datei << static_cast<string>(*t[i]) << endl;
      }
      else {
	datei << endl;
      }
      delete t[i];
    }

    datei.close();
  }
  
  delete [] t;
}

TextSpeicher& TextSpeicher::operator= (TextSpeicher &ts) {
  static TextSpeicher neu(ts);
  return neu;
}

void TextSpeicher::SetFilename(string Filename) {
  filename = Filename;
}

TextSpeicher::TextZeile& TextSpeicher::operator [] (int line) {
  if(line < 0) {
    OutOfBounds error;
    throw error;
  }
  if(line+1 > lines) {
    expand(line+1 - lines + NUM_EXP);
    lines = line+1;
  }
  if(!t[line]){
    t[line] = new TextZeile();
  }
  return *t[line];
}

int TextSpeicher::MaxColumns () const {
  int max_columns = 0;
  for(int i=0;i<lines;i++) {
    if(*t[i] > max_columns) {
      max_columns = *t[i];
    }
  }
  return max_columns;
}


//---Methoden Klasse TextSpeicher::TextZeile---

// Public
TextSpeicher::TextZeile::TextZeile() {
  l.clear();
}

TextSpeicher::TextZeile::TextZeile(string tl) {
  l = tl;
}

TextSpeicher::TextZeile::TextZeile(TextZeile &tz) {
  l = tz.l;
}

TextSpeicher::TextZeile::~TextZeile() {
  
}

TextSpeicher::TextZeile& TextSpeicher::TextZeile::operator= (TextZeile &tz) {
  static TextZeile neu(tz);
  return neu;
}

char& TextSpeicher::TextZeile::operator [] (int column) {
  if(column < 0) {
    OutOfBounds error;
    throw error;
  }
  
  if(l.empty() || l.length() <= column) {
    l.resize(column+1, ' ');
  }
  return l.at(column);
}
