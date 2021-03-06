//------------------------------------------------------------------------------
// Klasse Grafikobjekte zur Erzeugung von Grafikelementen
// 
//
// Jens de Boer
// Boris Spinner
//------------------------------------------------------------------------------
#ifndef _Grafikklasse_h_
#define _Grafikklasse_h_
#include <string>
#include "BmpWrite.h"
#include "SimpleFont.h"
#include <typeinfo> // bad_cast

using namespace std;

class GrafikElement {
	protected: /* damit auch innerhalb der objekte darauf einfach zugegriffen werden kann */
		int xs, ys;	// Bezugspunkt
	public:
		GrafikElement(): xs(0), ys(0) {};
		GrafikElement(int XS, int YS): xs(XS), ys(YS) {};
		virtual ~GrafikElement() {};

		int get_xs() const { return xs; }
		int get_ys() const { return ys; }

		virtual void draw(Image&) {} const = 0;
		virtual void add_offset(int x_offset, int y_offset) const = 0;
		virtual GrafikElement* clone() const = 0; 

		virtual GrafikElement& operator=(const GrafikElement& r);
};

class Punkt: public GrafikElement {
	private:
		RGB_Pixel c;	// Farbe
	public:
		Punkt(): GrafikElement(), c(0,0,0) {};
		Punkt(int XS, int YS, RGB_Pixel C): GrafikElement(XS, YS), c(C) {};
		virtual ~Punkt() {};

		RGB_Pixel get_color() const { return c; }

		virtual void draw(Image&);
		virtual void add_offset(int x_offset, int y_offset) { xs += x_offset; ys += y_offset; }
		virtual GrafikElement* clone() const { return new Punkt(*this); }
		
		virtual GrafikElement& operator=(const GrafikElement& r);
};

class Linie: public GrafikElement {
	private:
		int xe, ye;	// Endpunkt
		RGB_Pixel c;	// Farbe
	public:
		Linie(): GrafikElement(), c(0,0,0) {};
		Linie(int XS, int YS, int XE, int YE, RGB_Pixel C): GrafikElement(XS, YS), xe(XE), ye(YE), c(C) {};
		virtual ~Linie() {};

		int get_xe() const { return xe; }
		int get_ye() const { return ye; }
		RGB_Pixel get_color() const { return c; }

		virtual void draw(Image&);
		virtual void add_offset(int x_offset, int y_offset) { xs += x_offset; ys += y_offset; xe += x_offset; ye += y_offset; }
		virtual GrafikElement* clone() const { return new Linie(*this); }

		virtual GrafikElement& operator=(const GrafikElement& r);
};
class Kreis: public GrafikElement {
	private:
		int radius;	// Make an educated guess
		RGB_Pixel c;	// Farbe
	public:
		Kreis(): GrafikElement(), c(0,0,0), radius(0) {};
		Kreis(int XS, int YS, int R, RGB_Pixel C): GrafikElement(XS, YS), radius(R), c(C) {};
		virtual ~Kreis() {};

		int get_radius() const { return radius; }
		RGB_Pixel get_color() const { return c; }

		virtual void draw(Image&);
		virtual void add_offset(int x_offset, int y_offset) { xs += x_offset; ys += y_offset; }
		virtual GrafikElement* clone() const { return new Kreis(*this); }

		virtual GrafikElement& operator=(const GrafikElement& r);
};
class Rechteck: public GrafikElement {
	protected:
		int xe, ye;	// Endpunkt
		RGB_Pixel c;	// Farbe
	public:
		Rechteck(): GrafikElement(), xe(0), ye(0), c(0,0,0) {};
		Rechteck(int XS, int YS, int XE, int YE, RGB_Pixel C): GrafikElement(XS, YS), xe(XE), ye(YE), c(C) {};
		virtual ~Rechteck() {};

		int get_xe() const { return xe; }
		int get_ye() const { return ye; }
		RGB_Pixel get_color() const { return c; }

		virtual void draw(Image&);
		virtual void add_offset(int x_offset, int y_offset) { xs += x_offset; ys += y_offset; xe += x_offset; ye += y_offset; }
		virtual GrafikElement* clone() const { return new Rechteck(*this); }

		virtual GrafikElement& operator=(const GrafikElement& r);
};
class RechteckGefuellt: public Rechteck {
	private:
		RGB_Pixel f;	// Fuellfarbe
	public:
		RechteckGefuellt(): Rechteck(), f(0,0,0) {};
		RechteckGefuellt(int XS, int YS, int XE, int YE, RGB_Pixel C, RGB_Pixel F): Rechteck(XS, YS, XE, YE, C), f(F) {};
		virtual ~RechteckGefuellt() {};
		
		RGB_Pixel get_fcolor() const { return f; }

		virtual void draw(Image&);
		virtual GrafikElement* clone() const { return new RechteckGefuellt(*this); }

		virtual GrafikElement& operator=(const GrafikElement& r);
};
class Zeichen: public GrafikElement {
	private:
		unsigned char ch;	// Code des Zeichens
		RGB_Pixel fg, bg;	// Vorder- und Hintergrundfarbe
	public:
		Zeichen(): GrafikElement(), ch('\0'), fg(0,0,0), bg(0,0,0) {};
		Zeichen(int XS, int YS, unsigned char CH, RGB_Pixel FG, RGB_Pixel BG): GrafikElement(XS, YS), ch(CH), fg(FG), bg(BG) {};
		virtual ~Zeichen() {};

		unsigned char get_char() const { return ch; }
		RGB_Pixel get_fg() const { return fg; }
		RGB_Pixel get_bg() const { return bg; }

		virtual void draw(Image&);
		virtual void add_offset(int x_offset, int y_offset) { xs += x_offset; ys += y_offset; }
		virtual GrafikElement* clone() const { return new Zeichen(*this); }

		virtual GrafikElement& operator=(const GrafikElement& r);		
};
class TextZeile: public GrafikElement {
	private:
		string s;		// Zeichenkette
		RGB_Pixel fg, bg;	// Vorder- und Hintergrundfarbe
	public:
		TextZeile(): GrafikElement(), s('\0'), fg(0,0,0), bg(0,0,0) {};
		TextZeile(int XS, int YS, string STR, RGB_Pixel FG, RGB_Pixel BG): GrafikElement(XS, YS), s(STR), fg(FG), bg(BG) {};
		virtual ~TextZeile() {};

		string get_string() const { return s; }
		RGB_Pixel get_fg() const { return fg; }
		RGB_Pixel get_bg() const { return bg; }

		virtual void draw(Image&);
		virtual void add_offset(int x_offset, int y_offset) { xs += x_offset; ys += y_offset; }
		virtual GrafikElement* clone() const { return new TextZeile(*this); }

		virtual GrafikElement& operator=(const GrafikElement& r);
};

#endif
