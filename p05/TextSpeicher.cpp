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
	size += s;
	t = tmpArray;
}
/**
 * Überladener Konstruktor
 *
 * @param string Filename
 */
TextSpeicher::TextSpeicher(string Filename): size(1000), lines(0)
{
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
TextSpeicher::TextSpeicher(TextSpeicher& ts)
{

	TextSpeicher* KopieTS = new TextSpeicher();
	// Elemente löschen
	for(int i = 0; i < lines; i++)
	{
		delete t[i];
	}	
	delete [] t;

	for(int i=0;i<size;i++) {
		t[i] = ts.t[i];
	}
}
TextSpeicher::~TextSpeicher()
{
	
	if(filename.length() > 0) {
		ofstream fout(filename.c_str());
		for(int i = 0; i <= lines; i++)
			fout << t[i];		// exception missing
	}

	delete [] t; // may not work

}
TextSpeicher& TextSpeicher::TextSpeicher::operator= (TextSpeicher& JensFailed)
{ // nicht getestet, könnte absoluter quatsch sein.
	TextSpeicher* magic = new TextSpeicher(JensFailed);
	return *magic; // O_o ich hab kp von referenzen
}
void TextSpeicher::SetFilename(string Filename)
{
	if(!Filename.empty())
	{
		filename = Filename;
	}
}
TextSpeicher::TextZeile& TextSpeicher::operator [] (int line)
{	
}
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
