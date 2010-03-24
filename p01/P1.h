//---------------------------------------------------
// P1.h
//---------------------------------------------------
// OOP-Praktikum, Termin 1: Anmeldung zum Praktikum
// (Headerdatei)
// Erfasst die Anmeldungen zu einem Praktikum und
// erstellt daraus eine Komma-separierte Liste.
//---------------------------------------------------
// B. Lang, FH OS
// 11.03.2005: Erste Version
//---------------------------------------------------
// To Do: 
// - nichts bekannt
//---------------------------------------------------
#ifndef _P1_h_
#define _P1_h_

#include <string>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

//
// Datenstruktur zum Aufbau einer verzeigerten Liste
// und zum Speichern von Anmeldedaten
//
struct Anmeldung {
  Anmeldung* next;
  string   Nachname;
  string   Vorname;
  string   Email;
  string   Matrikelnummer;
  string   Studienrichtung;
  string   Semester;
  string   G1name;
  string   G1vorname;
  string   Anmerkung;
};

//
// Prototypen
//
namespace file
{
	bool check_file(string& filename);
	bool write_xml(Anmeldung* list, string destination);
	int read_file(string& source);
}

namespace list
{
	Anmeldung* create();
	bool insert(string item[]);
	int pop(Anmeldung* element, Anmeldung* previous);
	int remove_duplicates();
	void show();
	Anmeldung* get_root();
	bool destroy(Anmeldung*);
	
	static Anmeldung* root = NULL;
	static Anmeldung* current = NULL;	
}

#endif

