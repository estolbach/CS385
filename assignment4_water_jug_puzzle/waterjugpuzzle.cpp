/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : Esther Stolbach and Tim Barrett
 * Date        :	10/11/17
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 * 				~Esther and Tim
 * Description : Use a breadth first search to solve the famous water jug problem
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <queue>
#include <map>

using namespace std;

// Struct to represent state of water in the jugs.
struct State {
	int a, b, c;
	vector<string> directions;

	State(int _a, int _b, int _c) :
			a(_a), b(_b), c(_c) {
	}
	// String representation of state in tuple form.
	string to_string() {
		ostringstream oss;
		oss << "(" << a << ", " << b << ", " << c << ")";
		return oss.str();
	}
};

class Puzzle {

public:
	/**
	 * Constructor for creating a Puzzle
	 * It takes 6 int arguments for the goal and cap of each jug
	 */
	Puzzle(int jug_a, int jug_b, int jug_c, int goal_a, int goal_b, int goal_c) :
			jug_a_ { jug_a }, jug_b_ { jug_b }, jug_c_ { jug_c }, goal_a_ {
					goal_a }, goal_b_ { goal_b }, goal_c_ { goal_c } {
	}

	/**
	 * Attempts to solve the water jug puzzle and returns whether or not a solution exists.
	 */
	bool solve() {
		return solve(start_state_);
	}

private:
	int jug_a_, jug_b_, jug_c_, goal_a_, goal_b_, goal_c_;
	State start_state_ = { 0, 0, jug_c_ };

	/*
	 * This method attempts solves the water jug puzzle using a bfs
	 */
	bool solve(State p) {
		//2D array to check state has been visited
		bool **visit_arr_ = new bool*[jug_a_ + 1];
		for (int row = 0; row < jug_a_ + 1; row++) {
			visit_arr_[row] = new bool[jug_b_ + 1];
			fill(visit_arr_[row], visit_arr_[row] + jug_b_ + 1, false);
		}
		queue<State> q;
		q.push(p);
		while (!q.empty()) {
			State x = q.front();
			q.pop();
			if (x.a == goal_a_ && x.b == goal_b_ && x.c == goal_c_) {
				cout << "Initial state. " << p.to_string() << endl;
				for (unsigned int i = 0; i < x.directions.size(); ++i) {
					cout << x.directions[i];
				}
				return true;
			}
			ostringstream oss;
			//pour from c to a
			int fill_a, fill_b, fill_c, gallon;
			if (x.a != jug_a_ && x.c != 0) {
				fill_a = x.a + x.c;
				if (fill_a > jug_a_) {
					fill_c = fill_a - jug_a_;
					fill_a = jug_a_;
				} else {
					fill_c = 0;
				}
				gallon = x.c - fill_c;
				State s(fill_a, x.b, fill_c);
				//check if State s has been visited
				if (!(visit_arr_[s.a][s.b])) {
					visit_arr_[s.a][s.b] = true;
					oss << "Pour " << gallon << " " << gallon_s(gallon)
							<< " from C to A. " << s.to_string() << endl;
					s.directions = x.directions;
					s.directions.push_back(oss.str());
					q.push(s);
				}
			}
			oss.str("");

			//pour from b to a
			if (x.a != jug_a_ && x.b != 0) {
				fill_a = x.a + x.b;
				if (fill_a > jug_a_) {
					fill_b = fill_a - jug_a_;
					fill_a = jug_a_;
				} else {
					fill_b = 0;
				}
				gallon = x.b - fill_b;
				State s(fill_a, fill_b, x.c);
				//check if State s has been visited
				if (!(visit_arr_[s.a][s.b])) {
					visit_arr_[s.a][s.b] = true;
					oss << "Pour " << gallon << " " << gallon_s(gallon)
							<< " from B to A. " << s.to_string() << endl;
					s.directions = x.directions;
					s.directions.push_back(oss.str());
					q.push(s);
				}
			}
			oss.str("");

			//pour from c to b
			if (x.b != jug_b_ && x.c != 0) {
				fill_b = x.b + x.c;
				if (fill_b > jug_b_) {
					fill_c = fill_b - jug_b_;
					fill_b = jug_b_;
				} else {
					fill_c = 0;
				}
				gallon = x.c - fill_c;
				State s(x.a, fill_b, fill_c);
				//check if State s has been visited
				if (!(visit_arr_[s.a][s.b])) {
					visit_arr_[s.a][s.b] = true;
					oss << "Pour " << gallon << " " << gallon_s(gallon)
							<< " from C to B. " << s.to_string() << endl;
					s.directions = x.directions;
					s.directions.push_back(oss.str());
					q.push(s);
				}
			}
			oss.str("");

			//pour from a to b
			if (x.b != jug_b_ && x.a != 0) {
				fill_b = x.a + x.b;
				if (fill_b > jug_b_) {
					fill_a = fill_b - jug_b_;
					fill_b = jug_b_;
				} else {
					fill_a = 0;
				}
				gallon = x.a - fill_a;
				State s(fill_a, fill_b, x.c);
				//check if State s has been visited
				if (!(visit_arr_[s.a][s.b])) {
					visit_arr_[s.a][s.b] = true;
					oss << "Pour " << gallon << " " << gallon_s(gallon)
							<< " from A to B. " << s.to_string() << endl;
					s.directions = x.directions;
					s.directions.push_back(oss.str());
					q.push(s);
				}
			}
			oss.str("");

			//pour from b to c
			if (x.c != jug_c_ && x.b != 0) {
				fill_c = x.b + x.c;
				if (fill_c > jug_c_) {
					fill_b = fill_c - jug_c_;
					fill_c = jug_c_;
				} else {
					fill_b = 0;
				}
				gallon = x.b - fill_b;
				State s(x.a, fill_b, fill_c);
				//check if State s has been visited
				if (!(visit_arr_[s.a][s.b])) {
					visit_arr_[s.a][s.b] = true;
					oss << "Pour " << gallon << " " << gallon_s(gallon)
							<< " from B to C. " << s.to_string() << endl;
					s.directions = x.directions;
					s.directions.push_back(oss.str());
					q.push(s);
				}
			}
			oss.str("");

			//pour from a to c
			if (x.c != jug_c_ && x.a != 0) {
				fill_c = x.a + x.c;
				if (fill_c > jug_c_) {
					fill_a = fill_c - jug_c_;
					fill_b = jug_b_;
				} else {
					fill_a = 0;
				}
				gallon = x.a - fill_a;
				State s(fill_a, x.b, fill_c);
				//check if State s has been visited
				if (!(visit_arr_[s.a][s.b])) {
					visit_arr_[s.a][s.b] = true;
					oss << "Pour " << gallon << " " << gallon_s(gallon)
							<< " from A to C. " << s.to_string() << endl;
					s.directions = x.directions;
					s.directions.push_back(oss.str());
					q.push(s);
				}
			}
			oss.str("");
		}
		cout << "No solution.";
		return false;
	}

	/*
	 * This method creates a string for gallon or gallons
	 */
	string gallon_s(int num) {
		string x;
		if (num == 1) {
			x = "gallon";
		} else {
			x = "gallons";
		}
		return x;
	}
};
/*
 * Main function for reading the command line arguments and producing output.
 */
int main(int argc, char *argv[]) {
	if (argc != 7) {
		cerr
				<< "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>";
		return 1;
	}
	int a, b, c, goal_a, goal_b, goal_c;
	istringstream iss;
	iss.str(argv[1]);
	if (!(iss >> a) || !(a > 0)) {
		cerr << "Error: Invalid capacity '" << argv[1] << "' for jug A.";
		return 1;
	}
	iss.clear();
	iss.str(argv[2]);
	if (!(iss >> b) || !(b > 0)) {
		cerr << "Error: Invalid capacity '" << argv[2] << "' for jug B.";
		return 1;
	}
	iss.clear();
	iss.str(argv[3]);
	if (!(iss >> c) || !(c > 0)) {
		cerr << "Error: Invalid capacity '" << argv[3] << "' for jug C.";
		return 1;
	}
	iss.clear();
	iss.str(argv[4]);
	if (!(iss >> goal_a) || !(goal_a >= 0)) {
		cerr << "Error: Invalid goal '" << argv[4] << "' for jug A.";
		return 1;
	}
	iss.clear();
	iss.str(argv[5]);
	if (!(iss >> goal_b) || !(goal_b >= 0)) {
		cerr << "Error: Invalid goal '" << argv[5] << "' for jug B.";
		return 1;
	}
	iss.clear();
	iss.str(argv[6]);

	if (!(iss >> goal_c) || !(goal_c >= 0)) {
		cerr << "Error: Invalid goal '" << argv[6] << "' for jug C.";
		return 1;
	}
	iss.clear();

	if (goal_a > a) {
		cerr << "Error: Goal cannot exceed capacity of jug A.";
		return 1;
	}

	if (goal_b > b) {
		cerr << "Error: Goal cannot exceed capacity of jug B.";
		return 1;
	}

	if (goal_c > c) {
		cerr << "Error: Goal cannot exceed capacity of jug C.";
		return 1;
	}

	if (goal_a + goal_b + goal_c != c) {
		cerr
				<< "Error: Total gallons in goal state must be equal to the capacity of jug C.";
		return 1;
	}

	Puzzle puzzle(a, b, c, goal_a, goal_b, goal_c);
	puzzle.solve();
	return 0;

}
