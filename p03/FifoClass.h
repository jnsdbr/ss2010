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
				FifoElement(string v, FifoElement* n) : value(v), next(n) {};
			//	~FifoElement() { if(next != NULL) delete next; }
				inline FifoElement* nextElement() { return next; }
				inline string getValue() { return value; }
		};
		
		FifoElement *root; // Stapelanfang -- das nächste zu poppende Element
		FifoElement *top;  // Stapelende -- das zuletzt hinzugefügt Element
		FifoClass& push(const string&);
		FifoClass& pop(string&);
		
	public:
		
		FifoClass() : root(NULL), top(NULL) {};
		FifoClass(const char*);
	 	~FifoClass() { if(!empty()) delete root; }
		inline bool empty() { return root==NULL; }
		inline FifoClass& operator <<(const string& v) { return push(v); }
	 	inline FifoClass& operator >>(string& v) { return pop(v); }
		operator string(); //??
	 	const char* Error() const;
};
