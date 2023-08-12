/*
   CSCI 262 Data Structures, Fall 2019, Project 4 - Markov

   Author: Lucas Henke

   Modified: 10/24/2019

   Modified: 4/29/20 by Lauren Sherburne
*/
#ifndef _WORD_MODEL_H
#define _WORD_MODEL_H

#include "model.h"
#include <map>
#include <vector>

using namespace std;

class word_model : public markov_model {
public:
    virtual void initialize(string text, int order);

    virtual string generate(int size);

    // Add any helper methods you want here

protected:
    // Add any variables you may need here
    map < vector <string>, vector <string> > _model;
    vector <string> _data;
    int _order;
};

#endif
