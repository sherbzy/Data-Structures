/*
   CSCI 262 Data Structures, Fall 2019, Project 4 - Markov

   Author: Lucas Henke

   Modified: 10/24/2019

   Modified: 4/29/20 by Lauren Sherburne
*/
#ifndef _MAP_MODEL_H
#define _MAP_MODEL_H

#include <string>
#include <map>
#include <vector>

#include "model.h"

using namespace std;

class map_model : public markov_model {
public:
    virtual void initialize(string text, int order);

    virtual string generate(int size);

    string to_string();

protected:
    // Add any variables you may need here
    map <string, vector <char> > _model;
    string _data;
    int _order;
};

#endif
