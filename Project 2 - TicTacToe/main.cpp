/* CSCI 262 Project 2 - Tic-Tac-Toe
 *
 * Author: Lauren Sherburne
 * Date: 2/10/2020
 *
*/


//include iostream, vector, string, fstream, algorithm, and set libraries
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <set>

//using namespace standard
using namespace std;

//check if a specific player won on a certain board
bool checkWin (const char piece, const string board) {
    //if the piece wins, return true
    if (board[0] == piece) {
        if ((board[1] == piece) && (board[2] == piece)) {
            return true;
        }
        if ((board[3] == piece) && (board[6] == piece)) {
            return true;
        }
        if ((board[4] == piece) && (board[8] == piece)) {
            return true;
        }
    }
    if (board[4] == piece) {
        if ((board[3] == piece) && (board[5] == piece)) {
            return true;
        }
        if ((board[1] == piece) && (board[7] == piece)) {
            return true;
        }
        if ((board[2] == piece) && (board[6] == piece)) {
            return true;
        }
    }
    if (board[8] == piece) {
        if ((board[6] == piece) && (board[7] == piece)) {
            return true;
        }
        if ((board[2] == piece) && (board[5] == piece)) {
            return true;
        }
    }

    //otherwise return false
    return false;
}

//determine if the current board results in a tie or that it has no spaces
bool checkTie (string board) {
    for (int i = 0; i < 9; i++) {
        if (board[i] == ' ') {
            return false;
        }
    }
    return true;
}


//count the wins by x, wins by o, and ties and the total number of boards
void countBoards (int &xWins, int &oWins, int &ties, int &totalBoards, const set <string> totalBoardsList) {
    //the total number of possible boards is equal to the number inside totalBoardsList
    totalBoards = totalBoardsList.size();

    //iterate through the set of boards and count the x wins, o wins, and ties
    for (auto board : totalBoardsList) {
        if (checkWin('X', board)) {
            xWins += 1;
        }
        else if (checkWin('O', board)) {
            oWins += 1;
        } else if (checkTie(board)) {
            ties += 1;
        }
    }
}


//this recursive function generates all permutations of a tic tac toe board
void findAllBoards (string board, bool player, vector <string> &allBoards) {
    //first add the string board to the vector of boards
    allBoards.push_back(board);

    //function base cases: when x wins, o wins, or there is a tie
    if ((checkWin ('X', board)) || ((checkWin('O', board)))) {
        return;
    } else if (checkTie(board)) {
        return;
    }

    //loop through each position on the board
    for (int i = 0; i < 9; i++) {
        string b = board;
        //if the board contains a space, then fill it with an x or o and recurse
        if (b[i] == ' ') {
            if (player) {
                b[i] = 'X';
                findAllBoards(b, !player, allBoards);
            } else {
                b[i] = 'O';
                findAllBoards(b, !player, allBoards);
            }
        }
    }
}

int main() {
    //declare and initialize variables to hold the total number of boards, the number of o's wins, the number of x's
    //wins, and the number of ties
    int totalNumBoards = 0, xNumWins= 0, oNumWins = 0, totalNumTies = 0;

    //initialize the first board: a string with 9 spaces
    string firstBoard = "         ";

    //create a vector of strings to hold all the tic tac toe boards and use recursion to fill it with all possible
    //board combinations
    vector <string> allBoards;
    findAllBoards(firstBoard, true, allBoards);

    //add the elements of allBoards vector to a set; this sorts the data and eliminates all duplicates
    set<string> uniqueBoards;
    for (string s : allBoards){
        uniqueBoards.insert(s);
    }

    //determine the number of x wins boards, o wins boards, ties, and the total number of boards
    countBoards(xNumWins, oNumWins, totalNumTies, totalNumBoards, uniqueBoards);

    //test the above by printing uniqueBoards to a separate file
    //open file stream and check for error
    ofstream writeFile ("TicTacToe Boards.txt");
    if (writeFile.fail()) {
        cerr << "Unable to write to file." << endl;
        return -1;
    }

    //iterate through uniqueBoards and write to file
    set<string>::iterator it = uniqueBoards.begin();
    while (it != uniqueBoards.end()) {
        writeFile << (*it) << endl;
        it++;
    }

    //close file stream
    writeFile.close();

    //print uniqueBoards data to the screen
    cout << "total boards: " << totalNumBoards << ", wins for 'O': " << oNumWins;
    cout << ", wins for 'X': " << xNumWins << ", ties: " << totalNumTies;

    //return 0 signals the operating system that the program ended ok
    return 0;
}