/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Esther Stolbach
 * Version     : 1.0
 * Date        : 10/29/17
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens honor system
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
	// TODO
	long count = 0;
	for (int p = 0; p < length; p++) {
		for (int q = p + 1; q < length; q++) {
			if (array[p] > array[q]) {
				count++;
			}
		}
	}
	return count;
}

/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
	// TODO
	// Hint: Use mergesort!
	int *scratch = new int[length];
	long answer = mergesort(array, scratch, 0, length - 1);
	delete[] scratch;
	return answer;

}

/**
 * Sorts the array using mergesort
 */
static long mergesort(int array[], int scratch[], int low, int high) {
	// TODO
	long count = 0;
	if (low < high) {
		int mid = low + (high - low) / 2;
		count += mergesort(array, scratch, low, mid);
		count += mergesort(array, scratch, mid + 1, high);
		int l = low, h = mid + 1;
		for (int k = low; k <= high; k++) {
			if (l <= mid && (h > high || array[l] <= array[h])) {
				scratch[k] = array[l++];
			} else {

				count += mid - l + 1;
				scratch[k] = array[h++];
			}
		}
		for (int k = low; k <= high; k++) {
			array[k] = scratch[k];
		}
	}
	return count;
}

int main(int argc, char *argv[]) {
	// TODO: parse command-line argument

	if (argc > 2) {
		cerr << "Usage: ./inversioncounter [slow]";
		return 1;
	}

	if (argc > 1 && strncmp(argv[1], "slow", 4) != 0) {
		cerr << "Error: Unrecognized option '" << argv[1] << "'.";
		return 1;
	}

	cout << "Enter sequence of integers, each followed by a space: " << flush;

	istringstream iss;
	int value, index = 0;
	vector<int> values;
	string str;
	str.reserve(11);
	char c;
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

	// TODO: produce output
	//If user only enters spaces
	if (str.empty()) {
		cerr << "Error: Sequence of integers not received.";
		return 1;
	}
	//slow version using nested loops
	if (argc == 2) {
		cout << "Number of inversions: "
				<< count_inversions_slow(&values[0], values.size()) << endl;
	} else {
		//fast version using merge sort
		cout << "Number of inversions: "
				<< count_inversions_fast(&values[0], values.size());

	}

	return 0;
}
