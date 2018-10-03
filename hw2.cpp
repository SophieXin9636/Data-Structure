#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::ostream;
using std::istream;

#include <cstring>
#include <string>
using std::string;

#define Size 256

using namespace std;

class TSet {
	private:
		string set_name;

		/* if the element is True, then the element is in the set, and vice versa.*/
		bool set[Size]; // set of all ASCII character element

	public:
		/* Default constructer */
		TSet(){}

		/* constructor */
		TSet(string input_name){
			set_name = input_name;
			memset(set, false, sizeof(set)); // initialize set to false
		}

		/* Union */
		TSet operator+ (const TSet input_set){
			/* A Temporary object that store the result of logic operation */
			TSet TempSet(set_name+"+"+input_set.set_name);

			/* Union : use OR logic operation */
			for(int i = 0; i < Size; i++){
				TempSet.set[i] = set[i] | input_set.set[i];
			}
			return TempSet;
		}

		/* Intersection */
		TSet operator* (const TSet input_set){
			/* A Temporary object that store the result of logic operation */
			TSet TempSet(set_name+"*"+input_set.set_name);

			/* Intersection : use AND logic operation */
			for(int i = 0; i < Size; i++){
				TempSet.set[i] = set[i] & input_set.set[i];
			}
			return TempSet;
		}

		/* Difference */
		TSet operator- (const TSet input_set){
			/* A Temporary object that store the result of logic operation */
			TSet TempSet(set_name+"-"+input_set.set_name);

			/* Difference : use AND and NOT logic operation */
			for(int i = 0; i < Size; i++){
				TempSet.set[i] = set[i] & (~input_set.set[i]);
			}
			return TempSet;
		}

		/* Contain */
		string operator>= (const TSet input_set){
			/* A Temporary object that store the result of logic operation */
			TSet TempSet(set_name+">="+input_set.set_name);

			/* check setA equal setB */
			int check1 = 0, check2 = 0;
			/* Contain : use Intersection(AND) operation */
			for(int i = 0; i < Size; i++){
				TempSet.set[i] = set[i] & input_set.set[i];

				if(TempSet.set[i]==true &&  input_set.set[i]==true)	check1++;
				if(input_set.set[i] == true)	check2++;
			}
			if(check1 == check2)
				return set_name + " contains " + input_set.set_name;
			else return set_name +" does not contain " + input_set.set_name;
		}

		/* Belong to : check whether character is in the set */
		string in(char input_char){
			// create a char array, and cast to string type
			char c_array[2] = {input_char};
			string c(c_array);

			if(set[(int)input_char] == true){
				return "\'" + c + "\' is in " + set_name;
			}
			else return "\'" + c + "\' is not in " + set_name;
		}

		/* user self-defined and overloaded istream operator>> */
		friend istream& operator>>(istream& in, TSet &input_set){
	        string input_str; // defined input of string type
		    getline(in, input_str);
		    for(int i=0; i < input_str.length(); i++){
		    	// the character is in the set
                input_set.set[(int)input_str[i]] = true;
		    }
			return in;
	    }

		/* user self-defined and overloaded ostream operator<< */
	    friend ostream& operator<<(ostream& out, const TSet &input_set){
	        out << input_set.set_name << ": {" << input_set.print_set_element(input_set.set) << "}";
	        return out;
	    }

	    // print set
	    string print_set_element(const bool p_set[]) const {
	    	string print_set("");

			// if the element in the set, then append to print_set
	    	for(int i = 0; i < Size; i++){
	    		if(p_set[i] == true){
	    			print_set.push_back((char)i);
	    		}
	    	}
	    	return print_set;
	    }
};

int main(){
    int N = 0;
    cin >> N;
    for(int i=0; i<N; i++){
    	char x;

    	TSet A("A"), B("B");

    	cin.ignore();
    	cin >> A >> B;
    	cin.get(x);

    	TSet C, D;
    	C = A + B; // union
    	D = A * B; // intersection

    	cout << "Test Case " << (i+1) << ":" << endl;
    	cout << A << endl;
    	cout << B << endl;
    	cout << C << endl;
    	cout << D << endl;
    	cout << (A-B) << endl;
    	cout << (B-A) << endl;
    	cout << (A>=B) << endl;
    	cout << (B>=A) << endl;
    	cout << A.in(x) << endl;
    	cout << B.in(x) << endl;
    	cout << endl;
    }
    return 0;
}
