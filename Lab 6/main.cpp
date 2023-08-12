/* CSCI 262 Lab 06 - Ancient Algorithms
 *
 * Author: Lauren Sherburne
 * Date: 2/14/20
 */

#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;

//this function uses egyptian multiplication to find the product of two numbers
int egyptianMult () {
    //first prompt the user to enter 2 positive integers to be multiplied together
    int numOne, numTwo;
    cout << "Please enter two positive integers: ";
    cin >> numOne >> numTwo;
    cout << endl;

    //create two vectors to hold the two lists of numbers
    vector <int> vecOne;
    vector <int> vecTwo;
    int nextNumOne, nextNumTwo;

    //the smaller of the user's numbers goes in the first vector while the larger goes in the second
    if (numOne < numTwo) {
        nextNumOne = numOne;
        vecOne.push_back(numOne);
        nextNumTwo = numTwo;
        vecTwo.push_back(numTwo);
    } else {
        nextNumOne = numTwo;
        vecOne.push_back(numTwo);
        nextNumTwo = numOne;
        vecTwo.push_back(numOne);
    }

    //fill the first vector by halving the number (integer division) before it each time until you reach 1
    //fill the second vector by doubling the number before it until it has the same number of elements as the
    //first vector
    while (nextNumOne != 1) {
        nextNumOne /= 2;
        vecOne.push_back(nextNumOne);
        nextNumTwo *= 2;
        vecTwo.push_back(nextNumTwo);
    }

    //print the two vectors in columns side by side
    for (int i = 0; i < vecOne.size(); i++) {
        cout << setw(3) << vecOne[i];
        cout << setw(5) << vecTwo[i] << endl;
    }
    cout << endl;

    //calculate the answer by adding all the numbers in the second vector whose corresponding element in the first
    //vector are not even then return the answer
    int answer(0);
    for (int i = 0; i < vecOne.size(); i++) {
        if ((vecOne[i] % 2) != 0) {
            answer += vecTwo[i];
        }
    }

    return answer;
}

//the following function uses the babylonian method to determine an accurate estimate of a number's square root
void babylonianMethod () {
    //prompt the user to input the number the wish to know the square root of and their guess of it's square root
    double userNum, userGuess;
    cout << "Enter a number: ";
    cin >> userNum;
    cout << "What is your guess?";
    cin >> userGuess;

    //estimate and print the square root by finding the average of the user's number and the user's guess until
    //the change in estimates is less than 1e-8
    double lastNum(userGuess), nextNum, difference;
    do {
        nextNum = (lastNum + (userNum/lastNum)) / 2;
        cout << setprecision(10) << nextNum << endl;
        difference = abs(nextNum - lastNum);
        lastNum = nextNum;
    } while (difference > 1e-8);

    cout << endl;
}

//the sieve of eratosthenes function finds all prime numbers that are less than a given maximum
void sieveOfEratosthenes () {
    //prompt the user to specify the maximum number
    int maxNum;
    cout << "Input a maximum number: ";
    cin >> maxNum;

    //use a vector of boolian values that is the size of the maximum number to determine which numbers are prime
    vector <bool> primes(maxNum + 1);

    //set index 0, 1, to false
    primes[0] = primes[1] = false;

    //set index 2 to true, but set all indexes that are multiples of 2 to false
    primes[2] = primes [3] = primes [5] = primes[7] = primes[11] = true;
    for (int i = 4; i < primes.size(); i++) {
        if ((i % 2 == 0) || (i % 3 == 0) || (i % 5 == 0) || (i % 7 == 0) || (i % 11 == 0)) {
            if (primes[i] != true) {
                primes[i] = false;
            }
        } else {
            primes[i] = true;
        }
    }

    //print all indexes in the prime vector that are true
    for (int i = 0; i < primes.size(); i++) {
        if (primes[i]) {
            cout << i << " ";
        }
    }
    cout << endl << endl;
}

//this function uses a method developed by Archimedes to estimate pi
void approxPi () {
    //intiaialize a double for pi's estimate, the apothem, the hypotenuse, and both old and new triangle side lengths
    double oldEstimate, newEstimate, apothem, hypotenuse, sideLength;

    //begin with a regular hexagon inscribed inside a circle of radius 1
    int numSides(6);
    double perimeter;
    const double RADIUS = 1.0;

    //compute and print the first estimate
    perimeter = double(numSides) * RADIUS;
    oldEstimate = perimeter / (2 * RADIUS);
    cout << "Number of Sides: " << setw(2) << numSides << " -> pi: " << oldEstimate << endl;
    sideLength = RADIUS;

    //continue printing estimates until the change in values is less than 1e-12
    double difference;
    do {
        //Compute the apothem
        apothem = sqrt(RADIUS - (pow(sideLength, 2) / 4));

        //Double the number of sides and compute both the new side length and the hypotenuse
        numSides *= 2;
        sideLength /= 2;
        hypotenuse = sqrt(pow((RADIUS - apothem), 2) + (pow(sideLength, 2)));

        //compute the perimeter and estimate pi
        perimeter = double(numSides) * hypotenuse;
        newEstimate = perimeter / (2.0 * RADIUS);

        //print the new estimate
        cout << "Number of Sides: " << setw(2) << numSides << " -> pi: " << setprecision(14) << newEstimate << endl;

        //determine the difference between the old and new estimates
        difference = newEstimate - oldEstimate;

        //swap new and old values
        sideLength = hypotenuse;
        oldEstimate = newEstimate;
    } while (difference > 1e-12);

    cout << endl;
}

int main() {
    //create an integer to hold the user's choice
    int userChoice;

    //the do-while loop ensures that the program repeats until the user quits
    do {
        //prompt the user to choose an algorithm: Egyptian multiplication, the Babylonian method, the sieve of
        // eratosthenes or archimedes' approximation of pi
        cout << "Which algorithm would you like to use?" << endl;
        cout << "(1) Egyptian multiplication" << endl;
        cout << "(2) The Babylonian Method" << endl;
        cout << "(3) The Sieve of Eratosthenes" << endl;
        cout << "(4) Archimedes' Approximation of Pi" << endl;
        cout << "Enter \"0\" to quit" << endl;
        cin >> userChoice;

        switch (userChoice) {
            case 0:         //if the user chooses 0 to quit, end the program
                return 0;
            case 1:         //if the user chooses 1, use egyptian multiplication
                cout << "Answer: " << egyptianMult() << endl;
                break;
            case 2:         //if the user chooses 2, use the babylonian method
                babylonianMethod();
                break;
            case 3:         //if the user chooses 3, use the sieve of eratosthenes
                sieveOfEratosthenes();
                break;
            case 4:         //if the user chooses 4, use archimedes' approximation of pi
                approxPi();
                break;
            default:
                cout << "You're choice was invalid, please enter the integer next to the algorithm you wish to use" << endl;
        }

    } while (true);
}