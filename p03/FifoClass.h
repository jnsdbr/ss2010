/*************************************************************************



 *************************************************************************/

#include <iostream>
#include <string>
#include <new>

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
		};
		
		FifoElement *top;  // Stapelende -- das zuletzt hinzugefügt Element
		FifoClass& push(const string);
		FifoClass& pop(string&);
		
	public:
		
		FifoClass() : top(0) {};
		FifoClass(const char*);
	 	~FifoClass() { if(!empty()) delete top; }
		inline bool empty() { return top==0; }
		inline FifoClass& operator <<(const string v) { return push(v); }
	 	inline FifoClass& operator >>(string& v) { return pop(v); }
		FifoElement* GetFirstElement();
		operator string(); //??
	 	const char* Error() const;
};
