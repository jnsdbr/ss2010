#include "TextSpeicher.h"

using namespace std;

/**
 * Vergrößert das t um die Größe s
 * 
 * @param int	s	size + s
 * @return void
 */
void TextSpeicher::expand(int s)
{	
	int _s = s + size;
	
	// Array von Zeigern größe + expand größe	
	TextZeile **tmpArray = new TextZeile*[_s];
	
	// Pointer von TextZeilen Element zwischenspeichern	und alte Elemente auf NULL setzen
	for(int i = 0; i < lines; i++)
	{
		tmpArray[i] = t[i];
		t[i] = NULL;	
	} 	
	// Die unverbrauchten Felder mit NULL füllen
	for(int i = lines; i < _s; i++)
	{
		tmpArray[i] = NULL;	
	}
	
	// Pointer Liste löschen
	delete [] t;

	// Size vergrößern
	size = _s;
	t = tmpArray;
}
/**
 * Überladener Konstruktor
 *
 * @param string Filename
 */
TextSpeicher::TextSpeicher(string Filename): size(10), lines(0)
{
	// Dateinamen setzen und Stream Objekt erstellen.
	filename = Filename;
	ifstream file(filename.c_str());
	
	if(!file)
	{
		cerr << "Error while opening file" << endl;
		throw *this;
	}
	
	try
	{
		// Array von Pointern anlegen
		t = new TextZeile*[size];
	}
	catch(bad_alloc)
	{
		cerr << "BAD_ALLOC: Memory error" << endl;
		throw *this;
	}
	
	for(int i = 0; i < size; i++)
	{
		// Array mit NULL füllen
		t[i] = NULL;
	}

	// Einlesen der Datei
	string zeile;
	
	// Solange Dateiende nicht erreicht ist
	while(!file.eof())
	{
		if(lines >= size)
		{
			// Feld vergrößern um 10
			expand(10);
		}
		
		// Zeile einlesen
		getline(file, zeile, '\n');
		
		try
		{
			// Speicher alloziieren
			t[lines] = new TextZeile(zeile);			
		}
		catch(bad_alloc)
		{
			cerr << "BAD_ALLOC: Memory error" << endl;
			throw *this;
		}											    
		
		lines++;
	}
		
	file.close();
}
/**
 * Überladener Konstruktor
 *
 * @param TextSpeicher ts
 */
TextSpeicher::TextSpeicher(TextSpeicher& ts)
{	
	// Elemente löschen
	for(int i = 0; i < lines; i++)
	{
		t[i] = NULL;
	}
	
	delete [] t;

	// Neue Elemente speichern
	for(int i = 0; i < size; i++)
	{
		t[i] = ts.t[i];
	}
}
/**
 * Destruktor
 */
TextSpeicher::~TextSpeicher()
{	
	if(filename.length() > 0)
	{
		try
		{
			// Stream öffnen und in Datei schreiben
			ofstream fout(filename.c_str());
			
			for(int i = 0; i < lines; i++)
			{
				if(t[i]) {
					fout << static_cast<string>(*t[i]) << endl;
				} else {
					fout << endl;
				}
			}	
					
		}
		catch(...)
		{
			cerr << "Error handling File" << endl;
		}
	}
	
	
	try
	{
		// Elemente löschen
		for(int i = 0; i < lines; i++)
		{
			t[i] = NULL;
		}
				
		delete [] t;	
	}
	catch(...)
	{
		cerr << "Error while closing program" << endl;
	}
}

/**
 *
 */
TextSpeicher& TextSpeicher::TextSpeicher::operator= (TextSpeicher& JensFailed)
{ // nicht getestet, könnte absoluter quatsch sein.
	TextSpeicher* magic = new TextSpeicher(JensFailed);
	return *magic; // O_o ich hab kp von referenzen
}
/**
 * Speichert den Dateinamen
 *
 * @param string	Filename
 * @return void
 */
void TextSpeicher::SetFilename(string Filename) {
	if(!Filename.empty()) filename = Filename;
}
/**
 * 
 */
TextSpeicher::TextZeile& TextSpeicher::operator [] (int line)
{
	if(line < 0) {
		OutOfBounds error;
    	throw error;
  	}
	/* Wir benötigen mehr Zeilen_zeiger_ um die neuen Daten unterzubekommen!
	   Deshalb legen wir 10 neue an und hoffen, dass es reicht.
	   Ansonsten werden später nochmal 10 angelegt.
	   Hier hätte man auch gut mit einer Konstanten arbeiten können...
						ist mir nun aber auch egal */
  	if(line+1 > lines) {
    		expand(10);
    		lines = line+1;
  	}
	/* Nachdem wir den Array mit den Zeigern erweitert haben, legen wir
	   schlussendlich ein neues TextZeilen-Objekt für die neue Zeile an */
  	if(!t[line]){
    		t[line] = new TextZeile();
  	}

	// fin
  	return *t[line];
}
/**
 * Alle Zeilen durchgehen und längste Spalte finden
 *
 * @return	int
 */
int TextSpeicher::MaxColumns () const
{
	int max_columns = 0;
	for(int i=0; i<lines; i++) {
		if(*t[i] > max_columns) {
			max_columns = *t[i];
		}
	}
	return max_columns;
}
TextSpeicher::TextZeile& TextSpeicher::TextZeile::operator= (const TextZeile& tl)
{
	l = static_cast<string>(tl);
}
char& TextSpeicher::TextZeile::operator [] (int column)
{
	// Sicherheitsabfrage - negative Spalten gibbet net
	if(column < 0) {
		OutOfBounds ThrowMeGently;
  		throw ThrowMeGently; 
	} else if (column >= l.length()) {
		/* Wir greifen auf eine Spalte zu, die noch nicht "angelegt" wurde
			 Dies holen wir nun nach und füllen den Zwischenraum mit Leerzeichen */
		l.resize(column+1, ' '); 
	} 

	return l[column];
}

