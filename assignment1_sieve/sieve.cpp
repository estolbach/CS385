/*
 *      Name	        : sieve.cpp
 *      Author      : Esther Stolbach
 *      Date        : 9/12/17
 *      Description : Sieve of Eratosthenes
 *      Pledge      : I pledge my honor that I have abided by the Stevens honor system.
 */

#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
	PrimesSieve(int limit) :
			is_prime_ { new bool[limit + 1] }, limit_ { limit } {
		sieve();
		num_primes_ = count_num_primes();
	}
	~PrimesSieve() {
		delete[] is_prime_;
	}

	//Return number of primes found
	inline int num_primes() const {
		return num_primes_;
	}

	//displays all primes found
	void display_primes() const {
		//TODO: write code to display in the format specified in the
		// requirements document.
		int counter = 1;
		const int max_prime_width = num_digits(max_prime_),
				primes_per_row = 80 / (max_prime_width + 1);
		for (int i = 0; i <= limit_; i++) {
			if (is_prime_[i] == true) {
				if(primes_per_row < num_primes_){
				cout << setw(num_digits(max_prime_)) << i;
				} else {
					cout << i;
				}
				if(i == max_prime_) {
					break;
				}
				else if(counter % primes_per_row == 0) {
					cout << endl;
				} else {
					cout << " ";
				}
				counter++;
			}
		}
	}

private:
	bool * const is_prime_;
	const int limit_;
	int num_primes_, max_prime_;

	//counts the number of primes found
	int count_num_primes() const {
		// TODO: write code to   count the number of primes found
		int counter = 0;
		for (int i = 0; i <= limit_; i++) {
			if (is_prime_[i] == true) {
				counter++;
			}
		}
		return counter;
	}

	//This method determines how many digits are in an integer
	int num_digits(int num) const {
		// TODO: write code to   determine how many digits are in an integer
		// Hint: No   strings are needed. Keep dividing by   10.
		int counter = 0;
		while (num != 0) {
			num = num / 10;
			counter++;
		}
		return counter;
	}

	//sieve algorithm
	void sieve() {
		for (int i = 2; i <= limit_; i++) {
			is_prime_[i] = true;
		}
		for (int i = 2; i <= sqrt(limit_); i++) {

			if (is_prime_[i] == true) {
				for (int j = i * i; j <= limit_; j += i) {
					is_prime_[j] = false;
				}
			}
		}
		//find max_prime_
		for (int i = limit_; i >= 0; i--) {
			if (is_prime_[i] == true) {
				max_prime_ = i;
				break;
			}
		}
	}
};

int main() {

	cout <<   "**************************** " <<  "Sieve of Eratosthenes" <<
			" ****************************" <<   endl;
	cout << "Search for primes up to: ";
	string limit_str;
	cin >> limit_str;
	int limit;

	//   Use stringstream for conversion. Don't forget to #include <sstream>
	istringstream iss(limit_str);
	//   Check for error.
	if (!(iss >> limit)) {
		cerr << "Error: Input is not an integer." << endl;
		return 1;
	}
	if (limit < 2) {
		cerr << "Error: Input must be an integer >= 2." << endl;
		return 1;
	}
	//   TODO: write code that uses your class to produce the desired output.

	PrimesSieve ps(limit);
	cout << endl << "Number of primes found: " <<  ps.num_primes() << endl;
	cout << "Primes up to " << limit << ":" << endl;
	ps.display_primes();
	return 0;
}

