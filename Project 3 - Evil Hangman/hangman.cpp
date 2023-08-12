/*
    hangman.cpp
        
    Method implementations for the hangman class.
    
    assignment: CSCI 262 Project - Evil Hangman        

    author: Lauren Sherburne

    last modified: 3/9/2020
*/

#include "hangman.h"

using namespace std;


// constructor
hangman::hangman() {

}


//setup a new game of hangman using a given number of guesses and number of letters
void hangman::start_new_game(int num_guesses, int letters) {
    setNumGuesses(num_guesses);
    setWord(letters);

    // read the file dictionary.txt and determine the word lengths
    ifstream readDict("dictionary.txt");

    if (readDict.fail()) {
        cerr << "Error opening dictionary file to read." << endl;
    }

    //read in all of the words of the proper size to the list of possible words
    string word;
    while (!readDict.eof()) {
        readDict >> word;
        if (word.size() == letters) {
            _words.push_back(word);
        }
    }
    readDict.close();
}


//process a player's guess: return true or false depending on whether or not the guess was in the hidden word then
//decrease the number of guesses remaining if necessary
bool hangman::process_guess(char c) {
    string word = _theWord;
    updateWordFamily(c);
    if (_theWord != word) {
        return true;
    }

    _userGuesses -= 1;
    return false;
}

//set the chosen word to a string of dashes based on the number of letters specified
void hangman::setWord (int numLetters) {
    for (int i = 0; i < numLetters; i++) {
        _theWord += '-';
    }
}


//return a representation of the hidden word, with unguessed letters masked by dashes
string hangman::get_display_word() {
    return _theWord;
}


//set the number of guesses that the user has
void hangman::setNumGuesses (int numGuesses) {
    _userGuesses = numGuesses;
}


//return the number of guesses that the user has remaining
int hangman::get_guesses_remaining() {
    return _userGuesses;
}


//return the alphabetical string that lists all letters that the user has already guessed
string hangman::get_guessed_chars() {
    return _userLettersGuessed;
}


//returns true if letter was already guessed.
bool hangman::was_char_guessed(char c) {
    //if the user has not guessed any letters, add their guess and return false
    if (_userLettersGuessed.size() == 0) {
        _userLettersGuessed += c;
        return false;
    }

    //loop through the letters that the user has already guessed and return true if c matches any chars in the string
    for (int i = 0; i < _userLettersGuessed.size(); i++) {
        if (_userLettersGuessed[i] == c) {
            return true;
        }
    }

    //loop through the string of guessed letters and add c based on alphabetical order
    //return false since c was not already guessed
    for (string::iterator i = _userLettersGuessed.begin(); i != _userLettersGuessed.end(); i++) {
        if (*i > c) {
            _userLettersGuessed.insert(i, c);
            return false;
        }
    }
    _userLettersGuessed += c;
    return false;
}


//return true if the game has been won by the player.
bool hangman::is_won() {
    if ((*_words.begin() == _theWord) && (_words.size() == 1)) {
        return true;
    }
    return false;
}


//return true if the game has been lost.
bool hangman::is_lost() {
    if ((!is_won()) && (_userGuesses == 0)) {
        return true;
    }
    return false;
}


//return the true hidden word to show the player.
string hangman::get_hidden_word() {
    // return a random word from the list of possible words
    int index = rand() % _words.size();
    vector <string>::iterator iterator = _words.begin();
    for (int i = 0; i <= index; i++) {
        iterator++;
    }
    return *iterator;
}

//print the number of words in the current list of possible words
void hangman::printNumWordFamily () {
    cout << "Words in chosen family: " << _words.size() << endl << endl;
}


//based on the user's guess, c, create all possible word families and update the member variables to match the largest
//word family
void hangman::updateWordFamily (char c) {
    //create a map to hold all possible word families
    map <string, vector <string> > map;

    //fill one key of the map with the current list of possible words
    string currentList = "currentList";
    for (int i = 0; i < _words.size(); i++) {
        map[currentList].push_back(_words.at(i));
    }

    //use for loops to create all possible word families
    //loop through the map first...
    for (auto s: map) {
        //then loop through the list of possible words in the map...
        for (string word: s.second) {
            //create a string to use as a key for each word in the possible words list
            string newWord = _theWord;

            //loop through the letters of each possible word
            for (int i = 0; i < word.size(); i++) {
                //find out if the word contains one or more of the letters that the user guessed and update the key
                if (word[i] == c) {
                    newWord[i] = c;
                }
                else {
                    newWord[i] = '-';
                }
            }
            //add the word to the vector in the map using the key newWord
            map[newWord].push_back(word);
        }
    }

    //clear the original list of possible words from the map
    map.erase(currentList);

    //determine the largest word family and its key by looping through the map and comparing the sizes of the vectors
    //at each key
    int max(0);
    string maxWord;
    for (auto s: map) {
        if (s.second.size() > max) {
            max = s.second.size();
            maxWord = s.first;
        }
    }

    //update the current list of possible words using the chosen list from the map
    _words.clear();
    _words = map[maxWord];

    //add any letters from the key that points to the list of possible words in the map to _theWord
    for (int i = 0; i < maxWord.size(); i++) {
        if (maxWord.at(i) != '-') {
            _theWord.at(i) = maxWord.at(i);
        }
    }
}

