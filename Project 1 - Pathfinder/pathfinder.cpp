/*
    pathfinder.cpp
        
    Method implementations for the pathfinder class.
    
    assignment: CSCI 262 Project - Pathfinder        

    author: Lauren Sherburne
    date: 1/23/2000
*/

#include <iostream>
#include <fstream>
#include "pathfinder.h"
#include <cmath>
#include <algorithm>

using namespace std;

// constructor - optional, in case you need to initialize anything
pathfinder::pathfinder() { ; }

// public run() method - invokes private methods to do everything;
// returns the total elevation change cost of the best optimal path.
int pathfinder::run(string data_file_name, string save_file_name) {
    // suggested implementation - modify as desired!
    if (!_read_data(data_file_name)) {
        cout << "Error reading map data from \"" << data_file_name << "\"!" << endl;
	return -1;
    }

    _draw_map();
    
    int best_cost = _draw_paths();

    _save_image(save_file_name);

    return best_cost;
}

/*******************/
/* PRIVATE METHODS */
/*******************/

// _read_data - read and store width, height, and elevation data from the
// provided data file; return false if something goes wrong
bool pathfinder::_read_data(string data_file_name) {
    // open input file stream
    ifstream readData (data_file_name);
    if (readData.fail()) {
        return false;
    }

    // read in the width and height of the map
    string myString;
    int currentNum;
    readData >> myString >> _numCols;
    readData >> myString >> _numRows;
    
    // read in data to elevation data table
    _elevations = vector < vector <int> > (_numRows, vector <int> (_numCols));
    for (int i = 0; i < _numRows; i++) {
        for (int j = 0; j < _numCols; j++) {
            readData >> currentNum;
            _elevations[i][j] = currentNum;
            //cout << _elevations[i][j] << " ";     //Test the elevation data storage
        }
        //cout << endl;                             //Test the elevation data storage
    }

    // close input file stream
    readData.close();

    // if everything worked, return true
    return true;
}

// _draw_map - draw the elevation data as grayscale values on our Picture
// object.
void pathfinder::_draw_map() {
    // determine the minimum and maximum elevations in the data
    int minElev = _elevations[0][0], maxElev = minElev;

    for (int i = 0; i < _numRows; i++) {
        for (int j = 0; j < _numCols; j++) {
            if (_elevations[i][j] > maxElev) {
                maxElev =_elevations[i][j];
            } else if (_elevations[i][j] < minElev) {
                minElev = _elevations[i][j];
            }
        }
    }


    // calculate a scaling factor for the gray values on the map
    double scale = maxElev / 256;

    // determint the grayscale value for each point based on its elevation and draw the map
    vector <vector <int> > grayValues = vector < vector <int> > (_numRows, vector <int> (_numCols));
    int r, g, b;
    _image.set(_width - 1, _height - 1, 0, 0, 0);
    for (int i = 0; i < _numRows; i++) {
        for (int j = 0; j < _numCols; j++) {
            r = g = b = _elevations[i][j] / scale;
            _image.set(j, i, r, g, b);
        }
    }
}

// _draw_paths() - find and draw optimal paths from west to east using 
// dynamic programming; return the best optimal path cost
int pathfinder::_draw_paths() {
    //create a table that keeps track of the minimum cost for each point on the map and the direction needed to travel
    //at each point
    _minCosts = vector <vector <int> > (_numRows, vector <int> (_numCols));
    _direction = vector <vector <char> > (_numRows, vector <char> (_numCols));

    //set the values in the last column of the min values table to zero
    for (int i = 0; i < _numRows; i++) {
        _minCosts[i][_numCols - 1] = 0;
    }

    //set the values in the last column of the directions table to 'e'
    for (int i = 0; i < _numRows; i++) {
        _direction[i][_numCols - 1] = 'e';
    }

    //determine the minimum "cost" to travel one step east and use the information to fill out the cost and direction tables
    int s, e, n;
    for (int i = _numCols - 2; i >= 0; i--) {
        for (int j = 0; j < _numRows; j++) {
            if (j == _numRows - 1) {
                s = -1;
                e = _minCosts[j][i + 1] + abs(_elevations [j][i] - _elevations [j][i + 1]);
                n = _minCosts[j - 1][i + 1] + abs(_elevations[j][i] - _elevations[j - 1][i + 1]);
                //cout << s << " " << e << " " << n << endl;
            } else if (j == 0) {
                s = _minCosts[j + 1][i + 1] + abs(_elevations[j][i] - _elevations[j + 1][i + 1]);
                e = _minCosts[j][i + 1] + abs(_elevations [j][i] - _elevations [j][i + 1]);
                n = -1;
                //cout << s << " " << e << " " << n << endl;
            } else {
                s = _minCosts[j + 1][i + 1] + abs(_elevations[j][i] - _elevations[j + 1][i + 1]);
                e = _minCosts[j][i + 1] + abs(_elevations [j][i] - _elevations [j][i + 1]);
                n = _minCosts[j - 1][i + 1] + abs(_elevations[j][i] - _elevations[j - 1][i + 1]);
                //cout << s << " " << e << " " << n << endl;
            }
            if (s == -1) {
                if (e <= n) {
                    _minCosts[j][i] = e;
                    _direction[j][i] = 'e';
                    //cout << "e is " << e << endl;
                } else {
                    _minCosts[j][i] = n;
                    _direction[j][i] = 'n';
                    //cout << "n is " << n << endl;
                }
            } else if (n == -1) {
                if (e <= s) {
                    _minCosts[j][i] = e;
                    _direction[j][i] = 'e';
                    //cout << "e is " << e << endl;
                } else {
                    _minCosts[j][i] = s;
                    _direction[j][i] = 's';
                    //cout << "s is " << s << endl;
                }
            } else {
                if ((e <= n) && (e <= s)) {
                    _minCosts[j][i] = e;
                    _direction[j][i] = 'e';
                    //cout << "e is " << e << endl;
                } else if (s <= n) {
                    _minCosts[j][i] = s;
                    _direction[j][i] = 's';
                    //cout << "s is " << s << endl;
                } else {
                    _minCosts[j][i] = n;
                    _direction[j][i] = 'n';
                    //cout << "n is " << n << endl;
                }
            }
        }
    }

    //test the information in the cost and direction tables
//    for (int i = 0; i < _numRows; i++) {
//        for (int j = 0; j < _numCols; j++) {
//            cout << _minCosts[i][j] << " ";
//        }
//        cout << endl;
//    }
//
//    cout << endl << endl;
//
//    for (int i = 0; i < _numRows; i++) {
//        for (int j = 0; j < _numCols; j++) {
//            cout << _direction[i][j] << " ";
//        }
//        cout << endl;
//    }

    // using blue lines, draw the best optimal paths from west to east
    for (int i = 0; i < _numRows; i++) {
        int yCount = i;
        for (int j = 0; j < _numCols; j++) {
            if (_direction [yCount][j] == 'n') {
                yCount -= 1;
            } else if (_direction[yCount][j] == 's') {
                yCount += 1;
            }
            _image.set(j, yCount, 0, 0, 255);
        }
    }

    //create a vector with total cost of each path from west to east
    vector <int> pathCost;
    pathCost = vector <int> (_numRows);

    vector <int> copyCosts;
    copyCosts = vector <int> (_numRows);

    //fill the vector with the values in the first column of minCosts
    for (int i = 0; i < _numRows; i++) {
        pathCost.at(i) = _minCosts[i][0];
        copyCosts.at(i) = pathCost.at(i);
    }

    //then sort the vector to find the path with the least cost
    sort(pathCost.begin(), pathCost.end());
    int totalCost = pathCost.at(0);

    //draw the optimal path in yellow and return its cost
    vector <int>::iterator it = find(copyCosts.begin(), copyCosts.end(), totalCost);
    int currentRow = distance(copyCosts.begin(), it);

    for (int i = 0; i < _numCols - 1; i++) {
        if (_direction[currentRow][i] == 'n') {
            currentRow -= 1;
        } else if (_direction[currentRow][i] == 's') {
            currentRow += 1;
        }
        _image.set(i, currentRow, 255, 255, 0);
    }

    // return totalCost
    return totalCost;

}

// _save_image - we'll do this one for you :)
void pathfinder::_save_image(string save_file_name) {
    _image.save(save_file_name);
}

