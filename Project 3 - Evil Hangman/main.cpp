/*
    main.cpp
        
    Implements the user interface for hangman.
    
    assignment: CSCI 262 Project - Evil Hangman        

    author: Lauren Sherburne

    last modified: 3/9/2020
*/

#include <iostream>
#include <set>
#include <string>
#include <cstdlib>
#include <cctype>

#include "hangman.h"

using namespace std;

// helper function prototypes
int get_integer(string msg);                     // return a positive integer
char get_letter(string msg);                     // return a valid lowercase letter
bool get_yesno(string msg);                      // return true == yes / false == no
string trim(string s);                              // remove leading/trailing whitespace
// returns the user-chosen positive integer indicating the number of letters in the hangman word
int get_word_length(set <int> lengths);


int main() {
    //seed the random number generator with time
    srand (time(0));
    rand();

    //generate a list of all possible word lengths in the dictionary by reading the lengths into a set
    //
    // read the file dictionary.txt and determine the word lengths
    ifstream readDict("dictionary.txt");

    if (readDict.fail()) {
        cerr << "Error opening dictionary file to read." << endl;
    }

    set <int> dictionaryWordLengths;
    string word;
    while (!readDict.eof()) {
        readDict >> word;
        dictionaryWordLengths.insert(word.size());
    }
    readDict.close();


    //welcome user to hangman
    cout << "Welcome to Hangman!" << endl;
    cout << "===================" << endl << endl;

    // get the hangman object
    hangman game;

    //loop through and continue playing games of hangman until the user chooses to exit at the end of a game
    while (true) {
        //determine the number of guesses that the user would like
        int num_guesses = get_integer("How many guesses would you like?");
        cout << endl;

        //prompt the user for a valid word length
        int wordLength = get_word_length(dictionaryWordLengths);

        //prompt the user to decide if they want to see how many possible words remain
        bool showNumWords = get_yesno("Show running total of words? (y/n)");

        //start a new game with the user-chosen number of guesses and length of word
        game.start_new_game(num_guesses, wordLength);

        //loop through each turn until the game is either won or lost
        while (!game.is_won() && !game.is_lost()) {
            //display the word so far with the letters that the user got correct and dashes in the spaces that have
            //not been guessed
            cout << "Your word is: " << game.get_display_word() << endl;

            //print the characters that the user already guessed
            string already_guessed = game.get_guessed_chars();
            if (already_guessed.size() == 0) {
                cout << "You have not yet guessed any letters." << endl;
            } else {
                cout << "You have already guessed these letters: ";
                cout << already_guessed << endl;
            }

            //print the number of guesses that the user has left
            cout << "You have " << game.get_guesses_remaining();
            cout << " guesses remaining." << endl << endl;

            //prompt the user to guess a new letter that has not yet been guessed
            char guess = get_letter("What is your next guess?");

            //print the number of possible words remaining in the word family if that option was chosen
            if (showNumWords) {
                game.printNumWordFamily();
            }

            while (game.was_char_guessed(guess)) {
                cout << endl << "You already guessed that!" << endl;
                guess = get_letter("What is your next guess?");
            }
            cout << endl;

            //
            bool good_guess = game.process_guess(guess);
            if (good_guess) {
                cout << "Good guess!" << endl;
            } else {
                cout << "Sorry, that letter isn't in the word." << endl;
            }

            if (game.is_won()) {
                cout << "Congratulations! You won the game!" << endl;
            }

            if (game.is_lost()) {
                cout << "Oh no! You lost!!!" << endl;
                cout << "My secret word was: " << game.get_hidden_word() << endl;
            }
        }

        cout << endl;
        if (!get_yesno("Would you like to play again (y/n)?")) break;
    }

    cout << endl << "Thank you for playing Hangman." << endl;

    return 0;
}

// Prompt for a positive integer response, re-prompting if invalid
// input is given. This is not super-robust - it really should work
// harder to filter out responses like "123foo", but oh well.
int get_integer(string msg) {
    while (true) {
        string input;    
        int result = 0;

        cout << msg << endl;
        getline(cin, input);

        result = atoi(input.c_str());
        if (result > 0) return result;

        cout << "I didn't understand that. Please enter a positive integer.";
        cout << endl;
    }
}
    
// Prompt for a letter of the alphabet, re-prompting if invalid
// input is given.
char get_letter(string msg) {
    while (true) {
        string input;    
 
        cout << msg << endl;
        getline(cin, input);

        input = trim(input);

        if (input.size() == 1) {
            char result = tolower(input[0]);
            if (result >= 'a' && result <= 'z') return result;
        }
        
        cout << "I didn't understand that. ";
        cout << "Please enter a letter of the alphabet.";
        cout << endl;
    }
}


// Prompt for a yes/no response, re-prompting if invalid
// input is given.
bool get_yesno(string msg) {
    while (true) {
        string input;    
 
        cout << msg << endl;
        getline(cin, input);

        input = trim(input);
        for (int i = 0; i < input.size(); i++) {
            input[i] = tolower(input[i]);
        }

        if (input == "y" || input == "yes") return true;
        if (input == "n" || input == "no") return false;
        
        cout << "I didn't understand that. ";
        cout << "Please enter y(es) or n(o).";
        cout << endl;
    }
}

string trim(string s) {
    int a, b;

    for (a = 0; a < s.size() && isspace(s[a]); a++);
    for (b = s.size() - 1; b >= a && isspace(s[b]); b--);
    
    return s.substr(a, b - a + 1);
}

// prompt the user for a word length, repeating as necessary until the number is positive and there is at least one word
// in the given dictionary that has the same number of letters
int get_word_length (set <int> lengths) {
    cout << "How long of a word would you like?" << endl;
    int userInput, element;
    do {
        cin >> userInput;
        element = distance (lengths.begin(), lengths.find(userInput));
        if (element > (lengths.size() - 1)) {
            cout << "Invalid input: There are no words in our dictionary that are length " << userInput << "." << endl;
            cout << "Please try again..." << endl;
        } else {
            return userInput;
        }
    } while (true);
}