/*************************************************************************



 *************************************************************************/

#include <iostream>
#include <string>
#include <new>

#include <fstream>

using namespace std;

class FifoClass {
	private:
		class FifoElement {
			private:
				string value;
				FifoElement* next;
			public:
				FifoElement(string v, FifoElement* n) : value(v), next(n) {
					cout << "value: " << v << "\tnext: " << n << endl;
				};
				~FifoElement() { delete next; }
				inline FifoElement* nextElement() { return next; }
				inline string getValue() { return value; }
				inline void setNext(FifoElement* n) { next = n; };
		};

		FifoElement *top;  // List's End -- latest added element
		FifoClass& push(const string);
		FifoClass& pop(string&);
		inline string pop() { string v; pop(v); return v;}
		unsigned int chLevel; // Charge Level -- number of elements in list
		unsigned char errorNo;

	public:

		FifoClass() : top(0), chLevel(0), errorNo(0) {};
		FifoClass(const char*);
	 	~FifoClass() { if(!empty()) delete top; }
		inline bool empty() { return top==0; }
		inline FifoClass& operator <<(const string v) { return push(v); }
	 	inline FifoClass& operator >>(string& v) { return pop(v); }
		FifoElement* GetFirstElement();
		FifoElement* GetSecondElement();
		void ChangeLevel(bool updown);
		inline unsigned int getLevel() { return chLevel; }
		inline operator int() const { return chLevel; }
		inline operator string() { return pop(); };
	 	const char* Error() const;
};
