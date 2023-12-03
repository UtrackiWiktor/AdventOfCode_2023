// AoC_day1_task1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>

using namespace std;

void calcTask1();
void calcTask2();
vector<string> getSubstrings(string);

int main()
{
    cout << "Calculating solution for Task1." << endl;
    calcTask1();
    cout << endl << "Calculating solution for Task2" << endl;
    calcTask2();
}

void calcTask1() {
    fstream input;
    input.open("input.txt");

    int sum = 0;

    while (input.good()) {
        string line;
        while (getline(input, line)) {
            istringstream ss(line);
            char x;
            int number = -1;
            int lastDigit = 0;
            while (ss >> x) {
                int digit = x - '0';
                if (digit >= 0 && digit <= 9) {
                    if (number == -1) {
                        number = digit * 10;
                    }
                    lastDigit = digit;
                }
            }
            number += lastDigit;
            sum += number;
            cout << number << endl;
        }
    }
    cout << "Sum is: " << sum << endl;
}

void calcTask2() {
    map<string, int> digits;
    digits["zero"] = 0;
    digits["one"] = 1;
    digits["two"] = 2;
    digits["three"] = 3;
    digits["four"] = 4;
    digits["five"] = 5;
    digits["six"] = 6;
    digits["seven"] = 7;
    digits["eight"] = 8;
    digits["nine"] = 9;

    fstream input;
    input.open("input.txt");

    int sum = 0;

    while (input.good()) {
        string line;
        while (getline(input, line)) {
            istringstream ss(line);
            char x;
            string letterSequence = "";
            int number = -1;
            int lastDigit = -1;
            int digitFromLetters = -1;
            while (ss >> x) {
                int digit = x - '0';
                //if is a proper digit
                if (digit >= 0 && digit <= 9) {
                    if (number == -1) {
                        number = digit * 10;
                    }
                    lastDigit = digit;
                    letterSequence = "";
                }
                else { //if its a letter, it might be a part of a digit in word form
                    letterSequence += x;
                    if (letterSequence.size() == 3) {
                        try { //check if sequence can be translated into a digit
                            digitFromLetters = digits.at(letterSequence);
                            if (number == -1) {
                                number = digitFromLetters * 10;
                            }
                            lastDigit = digitFromLetters;
                            char lastChar = letterSequence[letterSequence.size() - 1];
                            letterSequence = lastChar;
                        }
                        catch (out_of_range e) {}
                    }
                    else if (letterSequence.size() > 3) {
                        vector<string> substrings = getSubstrings(letterSequence);
                        for (string s : substrings) {
                            try { //check if subsequence can be translated into a digit
                                digitFromLetters = digits.at(s);
                                if (number == -1) {
                                    number = digitFromLetters * 10;
                                }
                                lastDigit = digitFromLetters;
                                char lastChar = letterSequence[letterSequence.size() - 1];
                                letterSequence = lastChar;
                            }
                            catch (out_of_range e) {}
                        }
                    }
                }
            }
            number += lastDigit;
            sum += number;
            cout << number << endl;
        }
    }
    cout << "Sum is: " << sum << endl;
}

vector<string> getSubstrings(string stringDigits) {
    vector<string> substrings;
    int size = stringDigits.size();
    if (size == 4) {
        substrings.push_back(stringDigits);
        substrings.push_back(stringDigits.substr(1, 3));   
    }
    else if (size == 5) {
        substrings.push_back(stringDigits.substr(2, 3));
        substrings.push_back(stringDigits.substr(1, 4));
        substrings.push_back(stringDigits);
    }
    else if (size > 5) {
        substrings.push_back(stringDigits.substr(size - 3, 3));
        substrings.push_back(stringDigits.substr(size - 4, 4));
        substrings.push_back(stringDigits.substr(size - 5, 5));
    }
    return substrings;
}
