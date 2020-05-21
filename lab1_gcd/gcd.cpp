#include <iostream>
#include <sstream>
#include <cmath>
/*
 * Esther Stolbach
 * I pledge my honor that I have abided by the Stevens honor system.
 */

using namespace std;

// std::cout to wrap all the defaults in a namespace like R

/*This method is used to find the gcd of two numbers
 *using recursion
 */
int gcd(int num1, int num2) {
	num1 = abs(num1);
	num2 = abs(num2);
	if (num1 == 0) {
		return num2;
	}
	if (num2 == 0) {
		return num1;
	}
	if (num1 == num2) {
		return num1;
	}
	if (num1 > num2) {
		return gcd(num1 - num2, num2);
	} else {
		return gcd(num1, num2 - num1);
	}
}

/*This method is used to find the gcd of two numbers
 *using iteration
 */
int gcdI(int num1, int num2) {
	num1 = abs(num1);
	num2 = abs(num2);
	if (num1 == 0) {
		return num2;
	}
	if (num2 == 0) {
		return num1;
	}
	while (num1 != num2) {
		while (num1 > num2) {
			num1 = num1 - num2;
		}
		while (num2 > num1) {
			num2 = num2 - num1;
		}
	}
	return num1;
}

//main function
int main(int argc, char* const argv[]) {
	int m, n;
	istringstream iss;
	if (argc != 3) {
		cerr << "Usage: " << argv[0] << " <integer m> <integer n>" << endl;
		return 1;
	}

	iss.str(argv[1]);
	if (!(iss >> m)) {
		cerr << "Error: The first argument is not a valid integer." << endl;
		return 1;
	}

	iss.clear(); //Clears out the error code
	iss.str(argv[2]);
	if (!(iss >> n)) {
		cerr << "Error: The second argument is not a valid integer." << endl;
		return 1;
	}

	cout << "Iterative: gcd(" << m << ", " << n << ") = " << gcdI(n, m) << endl;
	cout	 <<	"Recursive: gcd(" << m << ", " << n << ") = " << gcd(n, m) << endl;
	return 0;

}

