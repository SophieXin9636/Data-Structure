#include <iostream>
using namespace std;

/* Polynomial Term using linked list implementation */
class Term{
	public:
		double coef; // coefficient
		int expo; // exponent
		Term *link; // link that point to next term or null
};

class Polynomial: public Term{
	friend class Term;
	public:
		/* default constructor */
		Polynomial():coef(0),expo(0),next(0){}
		
		/* constructor */
		Polynomial(double c=0, int e=0, Term *ptr=0):coef(c),expo(e),next(ptr){}
		
		/* insert a single term(node) to current Polynomial */
		void insert_term(double c, int e){
			// Polynomial is empty, then create first node
			if(!Poly) Term *first = new Term(c, e); // add new term(node)
			else Term Poly->link = new Term(c, e, Poly->link);
		}
		
		/* delete term(node) of Polynomial that coefficient is 0 */
		void delete_term(){
			
		}
		
		/* operator overloading */
		Polynomial operator+ (const Polynomial &obj){
			
		}
		Polynomial operator* (const Polynomial &obj){
			
		}
	private:
		Term *Poly; // declare a pointer that point to Term object
};

int main() {
	int P; // number of term of Polynomial A
	int Q; // number of term of Polynomial B
	int c, e; // c:coefficient, e:exponent
	
	Polynomial A, B, C, D;
	
	while(cin >> P){
		for(int i=0; i<P; i++){
			cin >> c >> e;
			A.insert_term(c, e);
		}
		if(P == 0 && Q == 0){
			cout << "End!!" <<endl;
			return 0;
		}
		for(int i=0; i<Q; i++){
			cin >> c >> e;
		}
	}

	C = A + B;
	D = A * B;

	return 0;
}
