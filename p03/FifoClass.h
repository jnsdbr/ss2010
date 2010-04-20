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
				~FifoElement() { delete next; }
				inline FifoElement* next_element() {}
		};
		
		FifoElement *root;
		FifoClass& push(const string&);
		FifoClass& pop(string&);
		
	public:
		FifoClass() : root(NULL) {};
		FifoClass(const char*);
	 	~FifoClass() { if(!empty()) delete root; }
		inline bool empty() { return root==NULL; }
		inline FifoClass& operator <<(const string& v) { return push(v); }
	 	inline FifoClass& operator >>(string& v) { return pop(v); }
	 	inline operator string() { return pop() };
	 	operator int() const;
	 	const char* Error() const;
};
