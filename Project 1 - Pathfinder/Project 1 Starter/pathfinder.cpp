/*
    pathfinder.cpp
        
    Method implementations for the pathfinder class.
    
    assignment: CSCI 262 Project - Pathfinder        

    author: <your name here>
*/

#include <iostream>
#include "pathfinder.h"

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
    // TODO: open input file

    // TODO: read in and store width and height
    
    // TODO: read in and store elevation data

    // TODO: close input file

    // TODO: return true if everything worked
    return true;
}

// _draw_map - draw the elevation data as grayscale values on our Picture
// object.
void pathfinder::_draw_map() {
    // TODO: determine min/max elevation values in map
    // TODO: from min, max, determine a scaling factor for data to shift
    //       elevations into 0 - 255 range
    // TODO: for each elevation point, determine its grayscale value
    // TODO: for each elevation point, set the corresponding Picture point

    // example of using Picture object: delete this code
    for (int x = 0; x < 255; x++) {
        for (int y = 0; y < 100; y++) {
            int r, g, b;
            r = g = b = x; // gray value equal to x coordinate
            _image.set(x, y, r, g, b);
        }
    }
}

// _draw_paths() - find and draw optimal paths from west to east using 
// dynamic programming; return the best optimal path cost
int pathfinder::_draw_paths() {
    // TODO: compute minimum cost for every point on map, keeping track
    // of next move necessary to attain min cost (this will require
    // additional data structures!)

    // TODO: plot optimal paths from every westmost point, in blue

    // TODO: find and plot best optimal path in yellow

    // TODO: return total cost of best cost

    // TODO: consider breaking this method up using additional helper methods
    return 0;
}

// _save_image - we'll do this one for you :)
void pathfinder::_save_image(string save_file_name) {
    _image.save(save_file_name);
}

