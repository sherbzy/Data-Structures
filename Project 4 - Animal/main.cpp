/*
animal.cpp

author: L. Henke and C. Painter-Wakefield
date: 04 November 2019


Animal/20 questions program for CSCI 262, starter code.

Name: Lauren Sherburne
Date: 4/2/2020
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <queue>
using namespace std;

class node {
public:
    string data;
    node* left;
    node* right;
};

node* read_game_tree(ifstream &input);
bool play_game(node* root, string&);
void write_game_tree(node* root, ofstream &output);
void write_DOT_file(node* root, ofstream &output);
void add_to_game_tree(node* root, const string);

int main() {
    //open file stream and check for error
    ifstream readTree ("animal_game_tree.txt");
    if (readTree.fail()) {
        cerr << "Error opening file to read game tree." << endl;
        return -1;
    }

    //read in the game tree and ensure that the root is not nullptr
    node* root = read_game_tree(readTree);
    if (root == nullptr) {
        return -1;
    }

    //close file stream
    readTree.close();

    while (true) {
        string tmp;
        int choice;

        cout << "Welcome to 20 questions!" << endl;
        cout << "  1) Play the game" << endl;
        cout << "  2) Save the game file" << endl;
        cout << "  3) Quit" << endl;
        cout << "Please make your selection: ";
        getline(cin, tmp);
        choice = atoi(tmp.c_str());

        bool gameWon = true;
        string gameString = "";
        if (choice == 1) {
            //play the game
            gameWon = play_game(root, gameString);
        } else if (choice == 2) {
            //write the animal game tree to a file
            //open file stream, check for error, and erase previous contents of the file
            ofstream shit("animalTree.txt");
            if (shit.fail()) {
                cerr << "Error opening animal text file to write tree." << endl;
                return -1;
            }
            shit.trunc;

            //use a recursive function to write the information to the file
            write_game_tree(root, shit);

            //close file stream
            shit.close();
            cout << "Game file saved in 'animalTree.txt'" << endl;

            //save the animal game tree to a separate file in DOT format
            //open file stream, check for error, and erase previous contents of the file
            ofstream crap("animalGameTree.txt");
            if (crap.fail()) {
                cerr << "Error opening animal text file to write tree." << endl;
                return -1;
            }
            crap.trunc;

            //output the beginning line to the file...
            crap << "digraph G {" << endl;

            //use a recursive function to write the information to the file
            write_DOT_file(root, crap);

            //output the ending line of the file...
            crap << "}" << endl;

            //close file stream
            crap.close();
            cout << "Additional DOT format file saved in 'animalGameTree.txt'" << endl << endl;

        } else if (choice == 3) {
            break;
        } else {
            cout << "Sorry, I don't understand." << endl << endl;
        }

        //if the user won the game, prompt them to expand the game tree if desired until they answer with either
        //"y" for yes and "n" for no
        string userChoice;
        if (!gameWon) {
            cout << "Would you like to expand the game tree (y/n): ";
            getline(cin, userChoice);

            while ((userChoice != "y") && (userChoice != "n")) {
                cout << "I'm sorry, but I did not understand your answer." << endl;
                cout << "Please answer with either \"y\" for yes or \"n\" for no:" << endl;
                cout << "Would you like to expand the game tree (y/n): ";
                getline(cin, userChoice);
            }
        }



        //if the user chooses to expand the game tree, print out what questions were asked along with the user's
        //answers, then prompt the user to enter: 1. the question which would have caused the game to win and 2. a
        //question that distinguishes the first animal from the old animal
        if (userChoice == "y") {
            cout << endl << endl << "I asked the following:" << endl;
            add_to_game_tree(root, gameString);
        }
    }

    //return 0 signals the operating system that the program ended ok
    return 0;
}



// recursively uses a file stream parameter to read in an existing game tree from file and return
// the root node of the tree
node* read_game_tree(ifstream &input) {
    //read in one line of the file and store it as a string
    string inputLine;
    getline(input, inputLine);

    //determine if the input is a question (true) or an answer (false)
    bool isQuestion;
    isQuestion = inputLine.substr(0, 3).find('Q') != string::npos;

    //delete the first 3 characters in the string which contain #, the letter A or Q, and a space
    inputLine.erase(0, 3);

    //create a node with the data from the string
    node* myNode = new node;
    myNode->data = inputLine;

    //if the input was a question, then recursively read in the next input as a left child of the current node
    if (isQuestion) {
        myNode->left = read_game_tree(input);
    }

    //if the input was an answer, return the node
    if (!isQuestion) {
        return myNode;
    }

    //read in a right child if necessary
    myNode->right = read_game_tree(input);

    //return the node
    return myNode;
}

//implement a function to play the game of 20 questions
bool play_game(node* root, string &gameData) {
    //continue the game using a while loop until
    while (root != nullptr) {
        //print the next question and do not move on until the user answers with either y or n
        cout << root->data << " (y/n): ";
        string userChoice = "y";
        getline(cin, userChoice);

        while ((userChoice != "y") && (userChoice != "n")) {
            cout << endl << "I'm sorry, but I did not understand your answer." << endl;
            cout << "Please answer with either \"y\" for yes or \"n\" for no:" << endl;
            cout << root->data << " (y/n): ";
            getline(cin, userChoice);
        }

        //if the user answers yes to the question continue to the left child
        //otherwise, continue on to the right child
        if (userChoice == "y") {
            gameData += "y";
            root = root->left;
        } else if (userChoice == "n") {
            gameData += "n";
            root = root->right;
        }

        //if there are no more questions in the game tree, display if the computer won and return true for a win or
        //return false for a loss
        if (root == nullptr) {
            if (userChoice == "y") {
                cout << "YAY! I guessed your animal :)" << endl;
                return true;
            } else if (userChoice == "n") {
                cout << "BOO! I am out of questions! I give up :(" <<  endl;
                return false;
            }
        }
    }
}

//recursively writes the game tree's contents to a separate storage file
void write_game_tree(node* root, ofstream &output) {
    //if the next line is a leaf, indicate that it is an answer, and print the data before returning
    if ((root->left == nullptr) && (root->right == nullptr)) {
        output << "#A " << root->data << endl;
        return;
    }

    //indicate that the data is a question and print the next line
    output << "#Q " << root->data << endl;

    //recursively print the left branch of the tree first
    if (root->left != nullptr) {
        write_game_tree(root->left, output);
    }

    //recursively print the right branches of the tree next
    if (root->left != nullptr) {
        write_game_tree(root->right, output);
    }
}

//EXTRA CREDIT FUNCTION
//recursively writes the game tree to a separate file in DOT formatting
void write_DOT_file(node* root, ofstream &output) {
    if ((root->left != nullptr) || (root->right != nullptr)) {
        output << "\"" << root->data << "\" -> {";
        if (root->left != nullptr) {
            output << "\"" << root->left->data << "\" ";
        }
        if (root->right != nullptr) {
            output << "\"" << root->right->data << "\"";
        }
        output << "};" << endl;
        write_DOT_file(root->left, output);
        write_DOT_file(root->right, output);
    }
}

//takes the user through the process of adding to the game tree
void add_to_game_tree(node* root, const string gameData) {
    //first print the questions and the user's answers back to them
    int i;
    for (i = 0; i < gameData.size() - 1; i++) {
        cout << root->data << " ";
        if (gameData.at(i) == 'y') {
            cout << "YES" << endl;
            if (root->left->left != nullptr) {
                root = root->left;
            }
        } else {
            cout << "NO" << endl;
            if (root->right->left != nullptr) {
                root = root->right;
            }
        }
    }
    node* myNode = new node;
    myNode = root;

    if (gameData.at(i) == 'y') {
        root = root->left;
        cout << root->data << " NO" << endl;
    } else {
        root = root->right;
        cout << root->data << " NO" << endl;
    }
    root = myNode;

    //prompt the user to enter a question that would have caused the game to win
    cout << endl << "Enter a new animal in the form of a question, e.g., 'Is it a whale?':" << endl;
    string newAnimal;
    getline(cin, newAnimal);

    //prompt the user to enter a new question that distinguishes the new animal from the others
    cout << endl << "Now enter a question for which the answer is 'yes' for your new animal";
    cout << "and which does not contradict your previous answers:" << endl;
    string animalDistinctionQuestion;
    getline(cin, animalDistinctionQuestion);

    //first store the old 'answer' node
    node* answer = new node;
    if (gameData.at(i) == 'y') {
        answer = root->left;
    } else {
        answer = root->right;
    }

    //add the new question to the tree in place of the old answer
    node* newQuestionNode = new node;
    newQuestionNode->data = animalDistinctionQuestion;
    if (gameData.at(i) == 'y') {
        root->left = newQuestionNode;
    } else {
        root->right = newQuestionNode;
    }

    //add the new answer to the left node...
    node* newAnimalNode = new node;
    newAnimalNode->data = newAnimal;
    newQuestionNode->left = newAnimalNode;

    //add the old answer to the right node...
    newQuestionNode->right = answer;
}