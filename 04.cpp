/*
Build a lexical analyzer implementing the following rules:
Integer variable = (i-nI-N)(a-zA-Z0-9)*
ShortInt Number = (1-9)|(1-9)(0-9)|(1-9)(0-9)(0-9)|(1-9)(0-9)(0-9)(0-9)
LongInt Number = (1-9)(0-9)(0-9)(0-9)(0-9)+
Invalid Input or Undefined = Otherwise
*/

#include <iostream>  // Use iostream for basic input/output
#include <cctype>    // For character checking functions
#include <fstream>   // For file handling

using namespace std;

int main() {
    ifstream inputFile("04.input.txt");  // Open the file
    string inputWord;

    while (getline(inputFile, inputWord)) {  // Read each line from file
        bool valid = true;

        // Check for Integer Variable (starts with 'i' to 'n' and is alphanumeric)
        if (tolower(inputWord[0]) >= 'i' && tolower(inputWord[0]) <= 'n') {
            for (int j = 1; j < inputWord.size(); j++) {
                if (!isalnum(inputWord[j])) {  // Check if character is not alphanumeric
                    valid = false;
                    break;
                }
            }
            if (valid) {
                cout << inputWord << " : Integer variable" << endl;
                continue;
            }
        }

        // Check for ShortInt and LongInt Numbers
        valid = true;  // Reset validity check for number
        if (inputWord[0] >= '1' && inputWord[0] <= '9') {
            for (int j = 1; j < inputWord.size(); j++) {
                if (!isdigit(inputWord[j])) {  // Check if character is not a digit
                    valid = false;
                    break;
                }
            }
            if (valid) {
                if (inputWord.size() < 5) {
                    cout << inputWord << " : ShortInt Number" << endl;
                } else {
                    cout << inputWord << " : LongInt Number" << endl;
                }
                continue;
            }
        }

        // If none of the above conditions are met, input is invalid
        cout << inputWord << " : Invalid Input or Undefined" << endl;
    }

    inputFile.close();  // Close the file
    return 0;
}
