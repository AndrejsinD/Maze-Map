/* TODO: 
Add header with authors names and other lab details 
Author: David Andrejsin
*/

#include <iostream> // for i/o
#include <fstream> // for file handling
#include <vector>
#include <string>
#include "stdlib.h" // for the system command
#include "CTurtle.hpp"
namespace ct = cturtle;
using namespace std;

class Maze {
private:
	int rows = 0;
	int cols = 0;
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
	
	void search_from() {
		//Here I will tranlate the python code from the textbook into C++
	}
};

int main() {
	Maze myMaze;
	myMaze.readMaze("mazemap2.txt");

	system("cls"); // this clears the console, but is not really needed.

	myMaze.printMaze();



	cout << "Press Enter to exit...";
	getchar();
	return 0;
};