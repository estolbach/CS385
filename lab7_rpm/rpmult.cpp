/*******************************************************************************
 * Name        : rpmult.cpp
 * Author      : Esther Stolbach
 * Date        :	 10/22/17
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 * Description : Uses bit shift to solve Russian Peasant Multiplication.
 ******************************************************************************/

#include <iostream>
#include <sstream>
#include <climits>

using namespace std;
/*
 * This method is to use Russian peasant multiplication on two numbers
 */
unsigned long russian_peasant_multiplication(unsigned int m, unsigned int n) {
	unsigned long add_m = 0;
	long lm = (long) m;
	long ln = (long) n;
	//if n is greater than m, swap them
	if (ln > lm) {
		unsigned long temp = ln;
		ln = lm;
		lm = temp;

	}
	while (ln >= 1) {
		//if n is even do this
		if ((ln & 1)==0) {
			ln >>= 1;
			lm <<= 1;
			//if n is odd do this
		} else {
			ln = (ln - 1) >> 1;
			add_m += lm;
			lm <<= 1;
		}
	}

	return add_m;
}

/*
 * Main function for reading the command line arguments and producing output.
 */
int main(int argc, char* const argv[]) {
	if (argc != 3) {
		cerr << "Usage: " << argv[0] << " <integer m> <integer n>" << endl;
		return 1;
	}

	unsigned int m, n;
	istringstream iss;

	iss.str(argv[1]);
	if (!(iss >> m) || m > INT_MAX) {
		cerr << "Error: The first argument is not a valid nonnegative integer."
				<< endl;
		return 1;
	}
	iss.clear();
	iss.str(argv[2]);
	if (!(iss >> n) || n > INT_MAX) {
		cerr << "Error: The second argument is not a valid nonnegative integer."
				<< endl;
		return 1;
	}

	cout << m << " x " << n << " = " << russian_peasant_multiplication(m, n);
	return 0;
}
