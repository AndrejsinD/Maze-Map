/* TODO: 
Add header with authors names and other lab details 
Author: David Andrejsin
*/

#include <iostream> // for i/o
#include <fstream> // for file handling
#include <vector>
#include <string>
#include <stack>
#include "stdlib.h" // for the system command
#include "CTurtle.hpp"

namespace ct = cturtle;
using namespace std;

class Maze {
private:
	int rows = 0;
	int cols = 0;
	int start_row = 0;
	int start_column = 0;
	stack <vector <int>> forkstack;
	vector <vector <char>> mazeVect; // Matrix of chars

public: 
	Maze() {
		cout << "Default constructor called.\n" << endl;
	}

	void readMaze(string fileName) {
		string line;
		ifstream readFile (fileName);
		int lineCount = 0;
		if (!readFile.is_open()) {// Checking for errors opening the file
			cout << ("Error opening file.");
			return;
		}
		while (getline(readFile, line)) {// Reading file until the end is reached or an error occurs
			vector <char> thisLine;
			for (unsigned int i = 0; i < line.length(); ++i) {
				thisLine.push_back(line[i]);
			}
			mazeVect.push_back(thisLine);
			lineCount++;
		}

		if (readFile.bad()) { // More error checking
			cout << ("Error reading file.");
			return;
		}

		readFile.close();
		rows = mazeVect.size();			// Updating class attributes "rows" and "cols"
		cols = mazeVect[0].size();
		cout << "There are " << rows << " rows, and " << cols << " columns.\n\n";
		return;
	}

	void printMaze() {
		for (unsigned int i = 0; i < mazeVect.size(); i++) {
			for (unsigned int j = 0; j < mazeVect[i].size(); j++) {
				cout << mazeVect[i][j];
			}
			cout << endl;
		}
		cout << endl;
		return;
	}

	void checkStart() {
		// finds the starting position of the Turtle
		for (unsigned int i = 0; i < mazeVect.size(); i++) {
			for (unsigned int j = 0; j < mazeVect[i].size(); j++) {
				if (mazeVect[i][j] == 'S') {
					start_row = i;
					start_column = j;
				}
			}
			cout << endl;
		}
		cout << endl;
		return;
	}

	int count_paths() {
		// finds the number of possible ways to go when it wants to get out
		int counter = 0;

		if (mazeVect[start_row - 1][start_column] != *"+" && mazeVect[start_row - 1][start_column] != *".") {
			counter++;
		}
		if (mazeVect[start_row][start_column - 1] != *"+" && mazeVect[start_row][start_column - 1] != *".") {
			counter++;
		}
		if (mazeVect[start_row + 1][start_column] != *"+" && mazeVect[start_row + 1][start_column] != *".") {
			counter++;
		}
		if (mazeVect[start_row][start_column + 1] != *"+" && mazeVect[start_row][start_column + 1] != *".") {
			counter++;
		}
		return counter;
	}

	int count_paths_treasures() {
		// finds the number of possible ways to go when it wants to travel through the entire maze
		int counter = 0;
		if (start_row == 0 || start_row == mazeVect.size() - 1 || start_column == 0 || start_column == mazeVect[0].size() - 1) {
			return 0;
		}
		if (mazeVect[start_row - 1][start_column] != *"+" && mazeVect[start_row - 1][start_column] != *",") {
			counter++;
		}
		if (mazeVect[start_row][start_column - 1] != *"+" && mazeVect[start_row][start_column - 1] != *",") {
			counter++;
		}
		if (mazeVect[start_row + 1][start_column] != *"+" && mazeVect[start_row + 1][start_column] != *",") {
			counter++;
		}
		if (mazeVect[start_row][start_column + 1] != *"+" && mazeVect[start_row][start_column + 1] != *",") {
			counter++;
		}
		return counter;
	}

	void travel_path() {
		// used for travelling out of the entire maze
		if (mazeVect[start_row - 1][start_column] != *"+" && mazeVect[start_row - 1][start_column] != *".") {
			mazeVect[start_row][start_column] = *".";
			mazeVect[start_row - 1][start_column] = *"S";
			start_row = start_row - 1;
		}
		else if (mazeVect[start_row][start_column - 1] != *"+" && mazeVect[start_row][start_column - 1] != *".") {
			mazeVect[start_row][start_column] = *".";
			mazeVect[start_row][start_column - 1] = *"S";
			start_column = start_column - 1;
		}
		else if (mazeVect[start_row + 1][start_column] != *"+" && mazeVect[start_row + 1][start_column] != *".") {
			mazeVect[start_row][start_column] = *".";
			mazeVect[start_row + 1][start_column] = *"S";
			start_row = start_row + 1;;
		}
		else if (mazeVect[start_row][start_column + 1] != *"+" && mazeVect[start_row][start_column + 1] != *".") {
			mazeVect[start_row][start_column] = *".";
			mazeVect[start_row][start_column + 1] = *"S";
			start_column = start_column + 1;
		}
	}

	void travel_treasures() {
		// used for travelling through the entire maze
		if (mazeVect[start_row - 1][start_column] != *"+" && mazeVect[start_row - 1][start_column] != *",") {
			mazeVect[start_row][start_column] = *",";
			mazeVect[start_row - 1][start_column] = *"S";
			start_row = start_row - 1;
		}
		else if (mazeVect[start_row][start_column - 1] != *"+" && mazeVect[start_row][start_column - 1] != *",") {
			mazeVect[start_row][start_column] = *",";
			mazeVect[start_row][start_column - 1] = *"S";
			start_column = start_column - 1;
		}
		else if (mazeVect[start_row + 1][start_column] != *"+" && mazeVect[start_row + 1][start_column] != *",") {
			mazeVect[start_row][start_column] = *",";
			mazeVect[start_row + 1][start_column] = *"S";
			start_row = start_row + 1;;
		}
		else if (mazeVect[start_row][start_column + 1] != *"+" && mazeVect[start_row][start_column + 1] != *",") {
			mazeVect[start_row][start_column] = *",";
			mazeVect[start_row][start_column + 1] = *"S";
			start_column = start_column + 1;
		}
	}

	void treasures() {
		// travels through the entire maze
		// recursive function
		system("cls");
		printMaze();

		int paths = count_paths_treasures();

		if (paths > 1) {
			forkstack.push({ start_row, start_column });
			travel_treasures();
			treasures();
		}
		else if (paths == 1) {
			travel_treasures();
			treasures();
		}
		else {
			mazeVect[start_row][start_column] = *",";
			if (forkstack.empty() != 1) {
				start_row = forkstack.top()[0];
				start_column = forkstack.top()[1];
				forkstack.pop();
				travel_treasures();
				treasures();
			}
			return;
		}
	}

	void travel() {
		// finds the way out
		// recursive function
		system("cls");
		printMaze();

		if (start_row == 0 || start_row == mazeVect.size() -1 || start_column == 0 || start_column == mazeVect[0].size() -1) {
			cout << "You found your way out!" << endl;
			return;
		}

		int paths = count_paths();

		if (paths > 1) {
			forkstack.push({ start_row, start_column });
			travel_path();
			travel();
		}
		else if (paths == 1) {
			travel_path();
			travel();
		}
		else {
			mazeVect[start_row][start_column] = *".";
			start_row = forkstack.top()[0];
			start_column = forkstack.top()[1];
			forkstack.pop();
			travel_path();
			travel();
		}
	}
};

int main() {
	Maze myMaze;
	myMaze.readMaze("mazemap5.txt"); // reads the map
	myMaze.checkStart(); // finds the position of the turtle at the beginning

	myMaze.treasures(); // travels through the entire maze
	myMaze.checkStart(); // finds the turtle again
	myMaze.travel(); // travels out of the maze

	cout << "Press Enter to exit...";
	getchar();
	return 0;
}