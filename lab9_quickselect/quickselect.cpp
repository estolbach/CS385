/*******************************************************************************
 * Name          : quickselect.cpp
 * Author        : Esther Stolbach
 * Pledge        : I pledge my honor that I have abided by the Stevens honor system
 * Date          : 11/6/17
 * Description   : Implements the quickselect algorithm found on page 160 in
 *                 Algorithms, 3e by Anany Levitin.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;

/**
 * Swaps two values in an array
 */
static void swap(int array[], const int a, const int b) {
	int temp = array[a];
	array[a] = array[b];
	array[b] = temp;
}

/**
 * Implements the lomuto partition
 * everything to the left of p is <p
 * everything to the right of p is >p
 */
size_t lomuto_partition(int array[], size_t left, size_t right) {
	// TODO
	int p = array[left];
	size_t s = left;
	for (unsigned int i = left + 1; i <= right; i++) {
		if (array[i] < p) {
			s += 1;
			swap(array, s, i);
		}
	}
	swap(array, left, s);
	return s;
}

/**
 * finds the k smallest value by using lomuto partition
 */
int quick_select(int array[], size_t left, size_t right, size_t k) {
	// TODO
	size_t s = lomuto_partition(array, left, right);
	if (s == k - 1) {
		return array[s];
	} else if (s > k - 1) {
		return quick_select(array, left, s - 1, k);
	}
	return quick_select(array, s + 1, right, k);
}

int quick_select(int array[], const size_t length, size_t k) {
	return quick_select(array, 0, length - 1, k);
}

/**
 * Main function for reading the command line arguments and producing output.
 */
int main(int argc, char *argv[]) {
	if (argc != 2) {
		cerr << "Usage: " << argv[0] << " <k>" << endl;
		return 1;
	}

	int k;
	istringstream iss;
	iss.str(argv[1]);
	if (!(iss >> k) || k <= 0) {
		cerr << "Error: Invalid value '" << argv[1] << "' for k." << endl;
		return 1;
	}

	cout << "Enter sequence of integers, each followed by a space: " << flush;
	int value, index = 0;
	vector<int> values;
	string str;
	str.reserve(11);
	char c;
	iss.clear();
	while (true) {
		c = getchar();
		const bool eoln = c == '\r' || c == '\n';
		if (isspace(c) || eoln) {
			if (str.length() > 0) {
				iss.str(str);
				if (iss >> value) {
					values.push_back(value);
				} else {
					cerr << "Error: Non-integer value '" << str
							<< "' received at index " << index << "." << endl;
					return 1;
				}
				iss.clear();
				++index;
			}
			if (eoln) {
				break;
			}
			str.clear();
		} else {
			str += c;
		}
	}

	int num_values = values.size();
	if (num_values == 0) {
		cerr << "Error: Sequence of integers not received." << endl;
		return 1;
	}
	// TODO - error checking k against the size of the input
	unsigned int n = k;
	string x;
	if (values.size() == 1) {
		x = "value";
	} else {
		x = "values";
	}
	if (n > values.size()) {
		cerr << "Error: Cannot find smallest element " << k << " with only "
				<< values.size() << " " << x << ".";
		return 1;
	} else {

		// TODO - call the quick_select function and display the result
		cout << "Smallest element " << k << ": "
				<< quick_select(&values[0], values.size(), k);
	}
	return 0;
}
