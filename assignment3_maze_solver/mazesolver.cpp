/*******************************************************************************
 * Name        : mazesolver.cpp
 * Author      : Esther Stolbach
 * Date        :	 10/2/17
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 * Description : Uses recursive backtracking to solve a maze.
 ******************************************************************************/
#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>

using namespace std;

enum direction_t {
	NORTH, EAST, SOUTH, WEST
};

direction_t directions[] = { NORTH, EAST, SOUTH, WEST };

/**
 * Simple struct that represents a cell within the text-based maze.
 */
struct Cell {
	int row, col;

	/**
	 * No-args constructor.
	 */
	Cell() :
			row { 0 }, col { 0 } {
	}

	/**
	 * Constructor that takes in (row, col) coordinates.
	 */
	Cell(int _row, int _col) :
			row { _row }, col { _col } {
	}

	/**
	 * Checks if two cells are equal.
	 */
	bool operator==(const Cell &other) const {
		return row == other.row && col == other.col;
	}

	/**
	 * Returns that cell reached from the current cell when moving in the
	 * specified direction.
	 */
	Cell adjacent_cell(const direction_t direction) const {
		switch (direction) {
		case NORTH:
			return Cell(row - 1, col);
		case EAST:
			return Cell(row, col + 1);
		case SOUTH:
			return Cell(row + 1, col);
		case WEST:
			return Cell(row, col - 1);
		default:
			// Unknown direction -- just return a cell with the
			// coordinates of the current cell.
			return Cell(row, col);
		}
	}

	/**
	 * Allows for printing a cell from a cout statement.
	 */
	friend std::ostream& operator<<(std::ostream& os, const Cell &cell) {
		os << "(" << cell.row << ", " << cell.col << ")";
		os.flush();
		return os;
	}
};

class MazeSolver {
public:
	/**
	 * Constructor for creating a MazeSolver. Takes as argument a string
	 * representing the filename of the text file containing the maze.
	 */
	explicit MazeSolver(const string &filename) :
			filename_ { filename }, input_file_ { filename.c_str() } {
		if (!input_file_) {
			throw runtime_error("File '" + filename + "' not found.");
		}
		input_file_.exceptions(std::ifstream::badbit);
		parse_file();
	}

	/**
	 * Destructor. Used to free up memory allocated inside a MazeSolver.
	 */
	~MazeSolver() {
		// TODO
		for (int i = 0; i < num_rows_; i++) {
			delete[] maze_[i];
		}
		delete[] maze_;
	}

	/**
	 * Returns the path length of the solution.
	 */
	int path_length() const {
		// TODO
		return path_length_;
	}

	/**
	 * Attempts to solve the maze and returns whether or not a solution exists.
	 */
	bool solve() {
		return solve(start_);
	}

	/**
	 * Prints the ASCII maze on the screen with cout statements.
	 */
	void display_maze() const {
		// TODO
		for (int i = 0; i < num_rows_; i++) {
			for (int j = 0; j < num_cols_; j++) {
				cout << maze_[i][j];
			}
			cout << endl;
		}
	}

	static const int WALL_CHARACTER = '#', MARK_CHARACTER = '.',
			SPACE_CHARACTER = ' ';

private:
	string filename_;
	ifstream input_file_;
	char **maze_;
	int num_rows_, num_cols_, path_length_;
	Cell start_, end_;

	/**
	 * Parses the text file so that upon successful completion of this method,
	 * maze_ is a 2D array of characters, start_ and end_ represent the two
	 * open cells in the exterior of the maze, and path_length_ is initialized
	 * to 0.
	 */
	void parse_file() {
		vector<string> v;
		string line;
		while (getline(input_file_, line)) {
			v.push_back(line);
		}

		num_rows_ = v.size();
		if (num_rows_ == 0) {
			throw runtime_error("File '" + filename_ + "' is empty.");
		}
		num_cols_ = v[0].length();
		if (num_cols_ == 0) {
			throw runtime_error("File '" + filename_ + "' is empty.");
		}

		vector<Cell> points = start_and_end_points(v);

		maze_ = new char*[num_rows_];
		for (int row = 0; row < num_rows_; row++) {
			maze_[row] = new char[num_cols_];
			for (int col = 0; col < num_cols_; col++) {
				maze_[row][col] = v[row][col];
			}
		}
		start_ = points[0];
		end_ = points[1];
		path_length_ = 0;
	}

	/**
	 * Takes as input a vector of strings and returns a vector of exactly two
	 * cells, representing the starting and ending points in the exterior walls
	 * in the maze.
	 */
	vector<Cell> start_and_end_points(const vector<string> &v) const {
		vector<Cell> points;
		int last_row = num_rows_ - 1, last_col = num_cols_ - 1;

		// TODO - missing section

		Cell c = { 0, 0 };

		//top
		for (int i = 0; i <= last_col; i++) {
			if (v[0][i] == SPACE_CHARACTER) {
				c = {0, i};
				points.push_back(c);
			}
		}

		//bottom
		for (int i = 0; i <= last_col; i++) {
			if (v[last_row][i] == SPACE_CHARACTER) {
				c = {last_row, i};
				points.push_back(c);
			}
		}

		//left
		for (int i = 0; i <= last_row; i++) {
			if (v[i][0] == SPACE_CHARACTER) {
				c = {i, 0};
				points.push_back(c);
			}
		}

		//right
		for (int i = 0; i <= last_row; i++) {
			if (v[i][last_col] == SPACE_CHARACTER) {
				c = {i, last_col};
				points.push_back(c);
			}
		}

		size_t num_openings = points.size();
		if (num_openings == 0) {
			throw runtime_error("Maze has no openings.");
		} else if (num_openings == 1) {
			throw runtime_error("Maze has only 1 opening.");
		} else if (num_openings > 2) {
			throw runtime_error(
					"Ambiguous path. Maze has more than 2 openings.");
		}
		return points;
	}

	/**
	 * Attempts to solve the maze and mark the path from the starting cell to
	 * the ending cell. Uses recursive backtracking to mark the path.
	 */
	bool solve(Cell cell) {
		// TODO
		maze_[cell.row][cell.col] = MARK_CHARACTER;
		path_length_++;
		if (cell == end_) {
			return true;
			cout << end_;
		}
		if (move(cell, NORTH) && solve(cell.adjacent_cell(NORTH))) {
				return true;

		} else if (move(cell, EAST) && solve(cell.adjacent_cell(EAST))) {
				return true;

		} else if (move(cell, SOUTH) && solve(cell.adjacent_cell(SOUTH))) {
				return true;

		} else if (move(cell, WEST) && solve(cell.adjacent_cell(WEST))) {
				return true;
		}

		maze_[cell.row][cell.col] = SPACE_CHARACTER;
		path_length_--;
		return false;
	}

	/*
	 * helper function to check possible directions to move
	 */
	bool move(Cell cell, direction_t direction) {
		switch (direction) {
		case NORTH:
			if (cell.row - 1 < 0) {
				return false;
			}
			return maze_[cell.row - 1][cell.col] == SPACE_CHARACTER;
		case EAST:
			if (cell.col + 1 >= num_cols_) {
				return false;
			}
			return maze_[cell.row][cell.col + 1] == SPACE_CHARACTER;

		case SOUTH:
			if (cell.row + 1 >= num_rows_) {
				return false;
			}
			return maze_[cell.row + 1][cell.col] == SPACE_CHARACTER;
		case WEST:
			if (cell.col - 1 >= num_cols_) {
				return false;
			}
			return maze_[cell.row][cell.col - 1] == SPACE_CHARACTER;
		default:
			return false;
		}
	}
};

/**
 * Main function for reading the command line arguments and producing output.
 */
int main(int argc, char *argv[]) {
	if (argc != 2) {
		cerr << "Usage: " << argv[0] << " <maze file>" << endl;
		return 1;
	}
	MazeSolver *maze_solver = NULL;
	try {
		maze_solver = new MazeSolver(argv[1]);
		if (maze_solver->solve()) {
			cout << "Solution exists: YES" << endl << "Total moves:     "
					<< maze_solver->path_length() << endl << endl;
			maze_solver->display_maze();
		} else {
			cout << "Solution exists: NO" << endl;
		}
	} catch (const exception &e) {
		cerr << "Error: " << e.what() << endl;
		return 1;
	}

// Don't forget to delete the pointer to the maze solver.
	delete maze_solver;
	return 0;
}
