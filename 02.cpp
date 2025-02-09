/*
Write a program that reads the following string:
“Munmun is the student of Computer Science & Engineering”.
a) Count the number of vowels and consonants.
b) Identify which vowels and consonants are in the string.
c) Split the string into two separate strings: 
   one with words that start with vowels, and the other with words that start with consonants.
*/

#include <iostream>   // Use basic libraries for simplicity
#include <fstream>    // For reading from a file
#include <cctype>     // For character functions

using namespace std;

bool checkIfVowel(char ch) {
    ch = tolower(ch);  // Convert to lowercase for comparison
    return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u';
}

int main() {
    // Open the input file and read the string
    ifstream inputFile("02.input.txt");
    string text;

    // Read the entire line from the file
    if (getline(inputFile, text)) {
        int vowelCount = 0, consonantCount = 0;
        string vowelLetters = "", consonantLetters = "", currentWord = "";
        string vowelStartingWords = "", consonantStartingWords = "";

        // Go through each character in the input
        for (char ch : text) {
            if (isalpha(ch)) {
                // Check if the character is a vowel or consonant
                if (checkIfVowel(ch)) {
                    vowelCount++;
                    vowelLetters += ch;  // Add vowel to the vowel list
                } else {
                    consonantCount++;
                    consonantLetters += ch;  // Add consonant to the consonant list
                }

                currentWord += ch;  // Build the current word
            } else if (ch == ' ') {
                // When we encounter a space, we check the word's first letter
                if (!currentWord.empty()) {
                    if (checkIfVowel(currentWord[0])) {
                        vowelStartingWords += currentWord + " ";
                    } else {
                        consonantStartingWords += currentWord + " ";
                    }
                    currentWord = "";  // Reset the current word
                }
            }
        }

        // Check the last word if it hasn't been processed
        if (!currentWord.empty()) {
            if (checkIfVowel(currentWord[0])) {
                vowelStartingWords += currentWord + " ";
            } else {
                consonantStartingWords += currentWord + " ";
            }
        }

        // Output the results
        cout << "\nTotal Vowels: " << vowelCount << endl;
        cout << "Vowels found: " << vowelLetters << endl;
        cout << "Total Consonants: " << consonantCount << endl;
        cout << "Consonants found: " << consonantLetters << endl;
        cout << "Words starting with a vowel: " << vowelStartingWords << endl;
        cout << "Words starting with a consonant: " << consonantStartingWords << endl;
    } else {
        cout << "Error: Could not open file." << endl;
    }

    inputFile.close();  // Close the file
    return 0;
}
