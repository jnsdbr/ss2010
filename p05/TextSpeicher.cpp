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
TextSpeicher::TextSpeicher(string Filename): size(1000), lines(0)
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
			// Feld vergrößern um 500
			expand(500);
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
	TextSpeicher* KopieTS = new TextSpeicher();
	
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
			
			for(int i = 0; i <= lines; i++)
			{
				fout << t[i];
			}	
					
		}
		catch(...)
		{
			cerr << "Error opening File" << endl;
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
void TextSpeicher::SetFilename(string Filename)
{
	if(!Filename.empty())
	{
		filename = Filename;
	}
}
/**
 * 
 */
TextSpeicher::TextZeile& TextSpeicher::operator [] (int line)
{
	// Index < 0 => OutOfBounds
	if(line < 0)
	{
		OutOfBounds oob;
		throw oob;
	}
	
	// Index > lines => vergrößern
	if(line > lines)
	{
		// Wenn line größer als size dann expand
		if(line > size)
		{
			expand(100);
		}
		
		// Objekte erstellen
		while(lines <= line)
		{
			t[lines] = new TextZeile(string());
			lines++;
		}	
	}
	
	if(!t[line]){
    t[line] = new TextZeile();
  }
	
	return *t[line];
}
/**
 * Ermittelt den größten String?
 *
 * @return	int
 */
int TextSpeicher::MaxColumns () const
{

}
/* Bereits im Header implementiert. BS
TextSpeicher::TextZeile::TextZeile()
{
	
}
TextSpeicher::TextZeile::TextZeile(string tl)
{
}
TextSpeicher::TextZeile::TextZeile(TextZeile&)
{
}
TextSpeicher::TextZeile::~TextZeile()
{
}*/
TextSpeicher::TextZeile& TextSpeicher::TextZeile::operator= (const TextZeile& tl)
{
	l = static_cast<string>(tl);
}
char& TextSpeicher::TextZeile::operator [] (int column)
{
	if(column < 0) {
		OutOfBounds ThrowMeGently;
  /* Okay, I */	throw ThrowMeGently; /*! Are you satisfied now? */

	} else if (column > l.length()) { // the chance for an error
/*probl. sucks*/for(; column > l.length(); l += ' '); // is VERY high here
	}

	return l[column];

}
