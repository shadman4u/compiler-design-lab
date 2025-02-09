#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// Define lists for subjects, verbs, and nouns
vector<string> subjects = {"Sagor", "Selim", "Salma", "Nipu", "he", "she", "I", "we", "you", "they"};
vector<string> verbs = {"read", "eat", "take", "run", "write"};
vector<string> nouns = {"book", "cow", "dog", "home", "grass", "rice", "mango"};

int main()
{
    // Open input file
    freopen("09.input.txt", "r", stdin);
    string sentence;

    // Read each line from the input
    while (getline(cin, sentence))
    {
        // Split the sentence into words
        string currentWord;
        vector<string> wordList;
        
        for (char ch : sentence)
        {
            if (ch != ' ')
            {
                currentWord += ch; // Build the current word
            }
            else
            {
                if (!currentWord.empty()) // Avoid pushing empty strings
                {
                    wordList.push_back(currentWord);
                    currentWord = ""; // Reset for the next word
                }
            }
        }
        if (!currentWord.empty()) // Push the last word if exists
        {
            wordList.push_back(currentWord);
        }

        bool validSentence = true;

        // Check for valid number of words (2 or 3)
        if (wordList.size() < 2 || wordList.size() > 3)
        {
            validSentence = false;
        }
        else
        {
            // Validate subject
            if (find(subjects.begin(), subjects.end(), wordList[0]) == subjects.end())
                validSentence = false;

            // Validate verb
            if (find(verbs.begin(), verbs.end(), wordList[1]) == verbs.end())
                validSentence = false;

            // If there are three words, validate the noun
            if (wordList.size() == 3)
            {
                if (find(nouns.begin(), nouns.end(), wordList[2]) == nouns.end())
                    validSentence = false;
            }
        }

        // Output result
        if (validSentence)
            cout << sentence << " : This sentence is Valid!\n";
        else
            cout << sentence << " : Sorry, this sentence is Invalid.\n";
    }
    
    return 0;
}