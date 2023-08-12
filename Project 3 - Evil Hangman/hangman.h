#ifndef _HANGMAN_H
#define _HANGMAN_H

/*
    hangman.h
        
    Class definition for the hangman class.

    assignment: CSCI 262 Project - Evil Hangman        

    author: Lauren Sherburne

    last modified: 3/9/2020
*/

#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <fstream>
#include <ctime>
#include <map>
#include <algorithm>

using namespace std;

/******************************************************************************
   class hangman

   Maintains game state for a game of hangman.

******************************************************************************/

class hangman {
public:
    hangman();

    //start a new game where player gets num_guesses unsuccessful tries to guess a word with letters number of letters
	void start_new_game(int num_guesses, int letters);

    //player guesses letter c; return whether or not char is in word
    bool process_guess(char c);

    //set the chosen word
    void setWord (int numLetters);

    //display current state of word with all guessed characters or dashes
    string get_display_word();

    //setters and getters for the number of guesses remaining
    void setNumGuesses (int numGuesses);
    int get_guesses_remaining();

    //setters and getters for the string of letters the user has guessed
    string get_guessed_chars();

    // Has this character already been guessed?
    bool was_char_guessed(char c);

    // Has the game been won/lost?  (Else, it continues.)
    bool is_won();
    bool is_lost();

    // Return the true hidden word.
    string get_hidden_word();

    // setters and getters for the word family
    void printNumWordFamily ();

    // creates a map filled with all possible word families then chooses the largest family
    void updateWordFamily (char c);


private:
    //vector of strings that contains a current list of possible words
    vector <string> _words;

    // store the number of guesses that the user has remaining
    int _userGuesses;

    // store the letters that the user has already guessed
    string _userLettersGuessed;

    // string to hold the "word" that the user sees
    string _theWord;
};

#endif
