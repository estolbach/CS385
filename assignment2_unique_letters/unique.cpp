/*
 *      Name	        : unique.cpp
 *      Author      : Esther Stolbach
 *      Date        : 9/19/17
 *      Description : Unique
 *      Pledge      : I pledge my honor that I have abided by the Stevens honor system.
 */

#include <iostream>
#include <cctype>

using namespace std;

// this method checks that the string is all lower case
bool is_all_lowercase(const string &s) {
	// TODO: returns true if   all characters in   string are lowercase
	// letters in the English alphabet; false otherwise.
	for(auto it = s.cbegin(); it != s.cend(); ++it) {
		//checks if its uppercase
		if(isupper(*it)) {
			return false;
		}
		// checks if its a number
		else if(isdigit(*it)) {
			return false;
		}
	}
	return true;
}

//this method checks if all letters in the given string are unique - no duplicates
bool all_unique_letters(const string &s) {
// TODO: returns true if   all letters in string are unique, that is
	// no duplicates are found; false otherwise.
	// You may use only a  single int for storage and work with bitwise
	// and bitshifting operators.
	// No credit will be   given for other solutions.
	unsigned int setnum = 0;
	for(auto it = s.cbegin(); it != s.cend(); ++it) {
		if(((1 << (*it - 'a')) & setnum)) {
			return false;
		}
		setnum = (1 << (*it -'a')) | setnum;
			}
return true;
}

int main(int argc, char * const argv[]) {
// TODO: reads and parses command line arguments.
// Calls other functions to  produce correct output.
	//return error message if not correct number of arguements given
	if (argc != 2) {
			cerr << "Usage: ./unique <string>";
			return 1;

		}
	//return error message if not everything in string is lowercase
	if(is_all_lowercase(argv[1])==false) {
		cerr << "Error: String must contain only lowercase letters.";
		return 1;
	}

	if(all_unique_letters(argv[1])) {
		cout << "All letters are unique.";
	}else{
		cout << "Duplicate letters found.";
	}
return 0;

}

