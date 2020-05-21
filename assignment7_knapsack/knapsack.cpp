/*
 *      Name	        : knapsack.cpp
 *      Author      : Esther Stolbach
 *      Date        : 12/06/17
 *      Description : Program that uses dynamic programming to solve the 0-1 knapsack problem
 *      Pledge      : I pledge my honor that I have abided by the Stevens honor system.
 */

#include <iostream>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

struct Item {
	unsigned int item_number, weight, value;
	string description;

	explicit Item(const unsigned int item_number, const unsigned int weight,
			const unsigned int value, const string &description) :
			item_number(item_number), weight(weight), value(value), description(
					description) {
	}

	friend std::ostream& operator<<(std::ostream& os, const Item &item) {
		os << "Item " << item.item_number << ": " << item.description << " ("
				<< item.weight << (item.weight == 1 ? " pound" : " pounds")
				<< ", $" << item.value << ")";
		os.flush();
		return os;
	}
};

/*
 * Methog to print a vector of Item
 */
void print(vector<Item> item) {
	for (unsigned int i = 0; i < item.size(); i++) {
		cout << "   " << item[i];
		cout << endl;
	}
}

/*
 * Method to find the highest value you can have in your 'knapsack'
 */
int solve(unsigned int num, unsigned int cap, vector<Item> item,
		vector<vector<int>>& table) {
	unsigned int total_val = 0;
	for (unsigned int i = 1; i <= num; i++) {
		for (unsigned int j = 1; j <= cap; j++) {
			//amount of weight you have left
			int rem = j-item[i-1].weight;
			if (rem < 0 ) {
				table[i][j] = table[i - 1][j];
			} else {
				table[i][j] = max(
						(unsigned int) (table[i - 1][rem]
								+ (unsigned int) item[i-1].value),
						(unsigned int) table[i - 1][j]);

			}
			total_val = table[i][j];
		}
	}
	return total_val;
}

/*
 * Method to backtrack through the table to find all items placed in 'knapsack'
 * returns the total weight in the 'knapsack'
 */
int answer(unsigned int num, unsigned int cap, vector<vector<int>> table,
		vector<Item> item, vector<Item>& add) {
	int total_weight =0;
	while(num && cap){
		//if current item's value is greater then previous items value do:
		if(table[num][cap]>table[num-1][cap]){
				//add current item to a new vector - add
				add.push_back(item[num-1]);
				//subtract current item's weight from the capacity
				cap = cap-item[num-1].weight;
				//calculate the total weight
				total_weight+=item[num-1].weight;
			}
			//go up to previous item
			num--;
		}
	return total_weight;
	}


int main(int argc, char *argv[]) {
	if (argc != 3) {
		cerr << "Usage: " << argv[0] << " <capacity> <filename>" << endl;
		return 1;
	}

	istringstream iss;
	int cap;
	iss.str(argv[1]);
	if (!(iss >> cap) || !(cap >= 0)) {
		cerr << "Error: Bad value '" << argv[1] << "' for capacity.";
		return 1;

	}
	iss.clear();

	ifstream input_file_(argv[2]);
	if (!input_file_.is_open()) {
		cerr << "Error: Cannot open file '" << argv[2] << "'.";
		return 1;
	}
	vector<Item> item_vec;
	int counter;
	int line_num = 0;
	string line, weight, value, name;
	int w, v;
	while (getline(input_file_, line)) {
		line_num++;
		counter = 0;
		//check for number of commas
		for (unsigned int i = 0; i < line.length(); i++) {
			if (line[i] == ',') {
				counter++;
			}
		}
		//if commas != 2 do:
		if (counter != 2) {
			cerr << "Error: Line number " << line_num
					<< " does not contain 3 fields.";
			return 1;
		}
		//set words in file to the right value,separate by commas
		name = line.substr(0, line.find(","));
		line = line.substr(line.find(",") + 1);
		weight = line.substr(0, line.find(","));
		iss.str(weight);
		//check if weight is an int >=0
		if (!(iss >> w) || !(w > 0)) {
			cerr << "Error: Invalid weight '" << weight << "' on line number "
					<< line_num << ".";
			return 1;
		}
		iss.clear();
		value = line.substr(line.find(",") + 1, line.size());
		iss.str(value);
		//check if value is an int >=0
		if (!(iss >> v) || !(v > 0)) {
			cerr << "Error: Invalid value '" << value << "' on line number "
					<< line_num << ".";
			return 1;
		}
		iss.clear();
		//add item to the vector
		Item item(line_num, w, v, name);
		item_vec.push_back(item);
	}
	cout << "Candidate items to place in knapsack:" << endl;
	vector<Item> add;
	print(item_vec);
	//set 2d vector to all 0's
	vector<vector<int>> table(line_num + 1, vector<int>(cap + 1, 0));

	solve(line_num, cap, item_vec, table);
	answer(line_num, cap, table, item_vec, add);
	cout << "Capacity: " << cap << (cap == 1 ? " pound" : " pounds") << endl;
	cout << "Items to place in knapsack:";
	if (add.empty()) {
		cout << " None" << endl;
	} else {
		cout << endl;
		//sort the vector by reversing it to the right order
		reverse(add.begin(),add.end());
		print(add);
	}
	cout << "Total weight: " << answer(line_num, cap, table, item_vec, add) << (answer(line_num, cap, table, item_vec, add) == 1 ? " pound" : " pounds")
			<< endl;
	cout << "Total value : $" << solve(line_num, cap, item_vec, table);
	return 0;
}

