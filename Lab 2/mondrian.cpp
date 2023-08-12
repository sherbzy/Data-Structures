/*
 * mondrian.cpp
 *
 * Author: Lauren Sherburne
 *
 * Generate recursive pictures inspired by the art of Piet Mondrian.
 */

#include <cstdlib>
#include <ctime>
#include <iostream>

#include "mondrian.h"

using namespace std;

//declare constants and rgb values for colors
const int MIN_PAINT = 35000;


void Mondrian::_paint_recursive(Picture &picture, int left, int top, int right, int bottom) {

    // base case 1 - in case we made a zero width or height rectangle
    int width = right - left;
    int height = bottom - top;
    if ((width == 0) || (height == 0)) {
        return;
    }

    // base case 2 - rectangle is now "small enough"
    if ((width * height) < MIN_PAINT) {
        // Fill with a color (or not) using _color_fill()
        _color_fill(picture, left, top, right, bottom);
    } else  {
        // otherwise, split the rectangle in two at random, and paint the
        // two rectangles recursively; make sure not to paint over the
        // dividing lines!
        if (width > height) {
            int x = (rand() % (right - left + 1)) + left;
            _paint_recursive(picture, x + 1, top, right, bottom);
            _paint_recursive(picture, left, top, x - 1, bottom);
            _draw_vertical_line(picture, x, top, bottom);

        } else {
            int y = (rand() % (bottom - top + 1)) + top;
            _draw_horizontal_line(picture, y, left, right);
            _paint_recursive(picture, left, top, right, y - 1);
            _paint_recursive(picture, left, y + 1, right, bottom);
        }
      }
}

void Mondrian::_color_fill(Picture &picture, int left, int top, int right, int bottom) {
    int r, g, b;

    // Choose a color at random from a palette;
    // for traditional Mondrian colors, a good palette is:


    int c = rand() % 4 + 1;
    cout << c << endl;

    if (c == 1) {
        r = 255;
        g = 0;
        b = 0;
    } else if (c == 2) {
        r = 0;
        g = 0;
        b = 128;
    } else if (c == 3) {
        r = 255;
        g = 215;
        b = 0;
    } else if (c == 4) {
        r = 255;
        g = 255;
        b = 255;
    }

    for (int x = left; x <= right; x++) {
        for (int y = top; y <= bottom; y++) {
            picture.set(x, y, r, g, b);
        }
    }
}

// These are done for you to save time in lab
void Mondrian::_draw_horizontal_line(Picture &picture, int y, int left, int right) {
    for (int x = left; x <= right; x++) {
        picture.set(x, y, 0, 0, 0);
    }
}

void Mondrian::_draw_vertical_line(Picture &picture, int x, int top, int bottom) {
    for (int y = top; y <= bottom; y++) {
        picture.set(x, y, 0, 0, 0);
    }
}

void Mondrian::paint(string output_filename, int width, int height) {
    // get a new random seed each time
    //srand(time(nullptr));

    // create a white picture
    Picture picture(width, height, 255, 255, 255);

    // put a frame around it
    _draw_horizontal_line(picture, 0, 0, width - 1);
    _draw_horizontal_line(picture, height - 1, 0, width - 1);
    _draw_vertical_line(picture, 0, 0, height - 1);
    _draw_vertical_line(picture, width - 1, 0, height - 1);

    // invoke our computer artist!
    _paint_recursive(picture, 1, 1, width - 2, height - 2);

    // save result
    picture.save(output_filename);
}
