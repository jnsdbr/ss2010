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
				FifoElement(string v) : value(v), next(NULL) {};
				~FifoElement() { delete next; }
		};

		FifoElement *root;
		FifoClass& push(string &v);
		FifoClass& pop(string &v);
	public:
		FifoClass() : root(NULL) {};
		FifoClass(const char*);
	 	~FifoClass() { if(!empty()) delete root; }
		inline bool empty() { return root==NULL; }
	 	inline FifoClass& operator << (string &v) { return push(&v); }
	 	inline FifoClass& operator >> (string &v) { return pop(&v); );
	 	operator string();
	 	operator int() const;
	 	const char* Error() const;
};
