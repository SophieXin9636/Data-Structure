#include <iostream>
using namespace std;

/* Polynomial Term using linked list implementation */
struct Term {
	double coef; // coefficient
	int expo; // exponent
	struct Term *pre, *next; // double link that point to previous term and next term
	Term(double c = 0, int e = 0, Term *p = 0, Term *n = 0) :coef(c), expo(e), pre(p), next(n) {}
};

class Polynomial {
public:
	/* default constructor */
	//Polynomial(){
		//Term *Poly = new Term;
	//}

	/* constructor */
	Polynomial(double c = 0, int e = 0, Term *ptr1 = 0, Term *ptr2 = 0) {
		Poly = new Term(c, e, ptr1, ptr2);
	}

	/* insert a single term(node) to current Polynomial */
	void insert_term(double c, int e) {
		Term *head = Poly; // temporary first node
		// Polynomial is not empty, then create Term node
		if (Poly) {
			// insert term following exponential order
			if (e < (Poly->expo)) {
				// insert to term between two node or tail node
				while (e < (Poly->expo)) {
					if (Poly->next == nullptr) {
						Term *newTerm = new struct Term(c, e, Poly);
						Poly->next = newTerm;
						newTerm->pre = Poly;
						return;
					}
					Poly = Poly->next;
					if (e == Poly->expo) {
						Poly->coef += c; // add coefficient
						Poly = head;
						return;
					}
					
				}
				Term *temp = Poly;
				Poly = Poly->pre;
				Term *newTerm = new struct Term(c, e, Poly, temp);
				Poly = newTerm;
				temp->pre = Poly->next;
				Poly = head; // back and point to first term(node)
			}
			else if (e > (Poly->expo)) {
				// insert to first node
				Poly->pre = new struct Term(c, e, Poly->pre, Poly);
				Poly = Poly->pre;
			}
			else Poly->coef += c; // add two coefficient of term due to the same exponent
		}
		// Polynomial is empty, then create first node
		else {
			struct Term *newTerm = new struct Term(c, e); // add new term(node)
			Poly = newTerm;
		}
	}
	/* delete term(node) of Polynomial that coefficient is 0 */
	void delete_zeroTerm() {
		for(Term *current = Poly; current; current = current->next){
			if(current->coef == 0){
				Term *deleteTerm = current;
				deleteTerm->pre->next = deleteTerm->next;
				deleteTerm->next->pre = deleteTerm->pre;
				delete deleteTerm;
			}
		}
	}

	/* operator overloading of Add */
	Polynomial operator+ (const Polynomial &obj) {
		Polynomial add_Polynomial;
		Term *Aptr = Poly;
		Term *Bptr = obj.Poly;
		
		while(Aptr || Bptr){ // Aptr & Bptr is not nullptr, then execuat loop
			if(Aptr->expo > Bptr->expo){ // A > B
				add_Polynomial.insert_term(Aptr->coef, Aptr->expo);
				Aptr = Aptr->next;
			}
			else if(Aptr->expo < Bptr->expo){ // A < B
				add_Polynomial.insert_term(Bptr->coef, Bptr->expo);
				Bptr = Bptr->next;
			}
			else add_Polynomial.insert_term(Aptr->coef + Bptr->coef, Aptr->expo); // A=B
		}
		return add_Polynomial;
	}
	
	/* operator overloading of Multiply */
	Polynomial operator* (const Polynomial &obj) {
		Polynomial multiplyPolynomial;

		for(Term *Aptr = Poly; Aptr; Aptr = Aptr->next){
			for(Term *Bptr = obj.Poly; Bptr; Bptr = Bptr->next){
				multiplyPolynomial.insert_term(Aptr->coef * Bptr->coef, Aptr->coef + Bptr->coef);
			}
		}
		return multiplyPolynomial;
	}
	
	void print_Polynomial(){
		for(Term *current = Poly; current; current = current->next){
			cout << current->coef << " " << current->expo << endl;
		}
	}
	
private:
	Term *Poly; // declare a pointer that point to Term object
};

int main() {
	int P; // number of term of Polynomial A
	int Q; // number of term of Polynomial B
	int c, e; // input. c is coefficient, and e is exponent
	int caseCount = 1;

	while (cin >> P) {
		Polynomial A, B, C, D;
		for (int i = 0; i < P; i++) {
			cin >> c >> e;
			A.insert_term(c, e);
		}
		cin >> Q;
		if (P == 0 && Q == 0) {
			cout << "End!!" << endl;
			return 0;
		}
		for (int i = 0; i < Q; i++) {
			cin >> c >> e;
			B.insert_term(c, e);
		}
		
		C = A + B;
		D = A * B;
		cout << "Case" << caseCount++ <<":"<< endl;
		cout << "ADD" << endl;
		C.delete_zeroTerm();
		C.print_Polynomial();
		cout << "MULTIPLY" << endl;
		D.delete_zeroTerm();
		D.print_Polynomial();
	}
	return 0;
}
