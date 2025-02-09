/*
Write a C program that reads the following string:
“Md. Tareq Zaman, Part-3, 2011”
a) Count the number of words, letters, digits, and other characters.
b) Separate letters, digits, and other characters.
*/

#include <iostream>  // Using iostream instead of bits/stdc++.h
#include <fstream>   // For file handling
#include <cctype>    // For character functions like tolower()

using namespace std;

int main() {
    // Open the input file
    ifstream inputFile("01.input.txt");
    string textLine;

    // Read the line from the file
    if (getline(inputFile, textLine)) {
        int wordCount = 1; // Start with 1 assuming there’s at least one word
        int letterCount = 0, digitCount = 0, specialCount = 0;
        
        string letterPart = "", digitPart = "", specialPart = "";

        // Loop over each character in the string
        for (char ch : textLine) {
            if (ch == ' ') {
                wordCount++;  // Increment word count if a space is found
            } else if (isalpha(ch)) {
                letterCount++;     // Count letters
                letterPart += ch;  // Store letters in string
            } else if (isdigit(ch)) {
                digitCount++;      // Count digits
                digitPart += ch;   // Store digits in string
            } else {
                specialCount++;       // Count other characters
                specialPart += ch;    // Store other characters in string
            }
        }

        // Display counts
        cout << "Total words: " << wordCount << endl;
        cout << "Total letters: " << letterCount << endl;
        cout << "Total digits: " << digitCount << endl;
        cout << "Total special characters: " << specialCount << endl;

        // Display separated characters
        cout << "\nLetters: " << letterPart << endl;
        cout << "Digits: " << digitPart << endl;
        cout << "Special Characters: " << specialPart << endl;
    } else {
        cout << "Could not read from file." << endl;
    }

    inputFile.close(); // Close the file
    return 0;
}
