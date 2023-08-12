/*
   CSCI 262 Data Structures, Fall 2019, Project 4 - Markov

   Author: Lucas Henke

   Modified: 10/24/2019

   Modified: 4/29/20 by Lauren Sherburne
*/

#include "map_model.h"

void map_model::initialize(string text, int order) {

    //use variables to hold text and order values; copy first order characters to back to simulate wrap-around
    _data = text + text.substr(0, order);
    _order = order;

    //loop through the characters in the string
    for (int i = 0; i < text.size(); i++) {
        //create a substring of the next sequence
        string nextSequence = _data.substr(i, order);

        //if the next sequence is not equal to a map key, make it into a new map key
        //otherwise, add the next letter in the string to the map's vector
        _model[nextSequence].push_back(_data.at(i + order));
    }
}

string map_model::generate(int size) {
    //pick a random k-char substring from the training text as the initial seed
    int start = rand() % (_data.length() - _order);
    string seed = _data.substr(start, _order);

    string answer;

    //repeat the generation size times to produce the correct number of characters
    for (int i = 0; i < size; i++) {
        //use the seed as a key to find the vector value in the map
        //choose a random character from the vector
        int pos = rand() % (_model[seed].size());
        char nextChar = _model[seed].at(pos);

        //add the next character to the answer string and update the seed
        answer += nextChar;
        seed = seed.substr(1) + nextChar;
    }

    return answer;
}
