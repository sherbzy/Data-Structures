/*
   CSCI 262 Data Structures, Fall 2019, Project 4 - Markov

   Author: Lucas Henke

   Modified: 10/24/2019

   Modified: 4/29/20 by Lauren Sherburne
*/

#include "word_model.h"
#include <sstream>
#include <iostream>

void word_model::initialize(string text, int order) {
    //use variables to hold text and order values; copy first order words to back to simulate wrap-around
    istringstream sin(text);
    while (!sin.eof()) {
        string word;
        sin >> word;
        _data.push_back(word);
    }

    for (int i = 0; i < order; i++) {
        _data.push_back(_data[i]);
    }
    _order = order;

    //loop through the words in the vector
    vector <string> nextSequence;
    for (int i = order; i < _data.size(); i++) {
        //create a string of the next sequence of words
        nextSequence.clear();
        for (int j = 0; j < order; j++) {
            nextSequence.push_back(_data[i - order + j]);
        }

        //if the next sequence is not equal to a map key, make it into a new map key
        //otherwise, add the next word to the string to the map's vector
        _model[nextSequence].push_back(_data[i]);
    }
}


string word_model::generate(int size) {
    //pick a random word from the training text as the initial seed
    vector <string> seed;
    int start = rand() % (_data.size() - _order);
    for (int i = 0; i < _order; i++ ) {
        seed.push_back(_data[start + i]);
    }

    string answer, nextWord;
    //repeat the generation size times to produce the correct number of words
    for (int i = 0; i < size; i++) {
        //use the seed as a key and find the vector value in the map
        //choose a random word from the vector
        int pos = rand() % (_model[seed].size());
        if (_model.count(seed)) {
            cout << "yes" << endl;
        }
        nextWord = _model[seed].at(pos);

        //add the next word to the answer string and update the seed
        answer += nextWord + " ";
        start++;
        seed.clear();
        for (int j = 0; j < _order; j++) {
            seed.push_back(_data[start + j]);
        }
    }
    return answer;
}
