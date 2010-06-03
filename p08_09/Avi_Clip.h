class Avi_Clip
{
	private:
		int breite;
		int hoehe;
		string bmp_name;
		vector GrafikHuellen;
		int laenge;
		Ueberblendung ut;
		int ut_laenge;

	public:
		Avi_Clip(int b, int h, string filename) : breite(b), hoehe(h), bmp_name(filename) {};
		~Avi_Clip() { delete GrafikHuellen; };
		void Clip_erstellen() const;		
}