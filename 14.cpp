#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <iomanip>
using namespace std;

// Using simpler names for variables and functions
map<char, vector<string>> grammar;
map<pair<char, char>, string> parsingTable;
map<char, set<char>> firstSet;
map<char, set<char>> followSet;
vector<char> nonTerminals;

// A function to calculate the FOLLOW set
void computeFollowSet() {
    // Start with the FOLLOW set of 'E' being { '$' }
    followSet[nonTerminals[0]].insert('$');

    // Iterate over all non-terminals
    for (char nonTerminal : nonTerminals) {
        for (char left : nonTerminals) {
            for (auto production : grammar[left]) {
                bool stop = false;
                int j = 0;
                for (int i = 0; i < production.size(); i++) {
                    if (production[i] == nonTerminal) {
                        for (j = i + 1; j < production.size(); j++) {
                            if (production[j] < 'A' || production[j] > 'Z') {
                                followSet[nonTerminal].insert(production[j]);
                                stop = true;
                                break;
                            } else {
                                for (char f : firstSet[production[j]]) {
                                    if (f != '@') followSet[nonTerminal].insert(f);
                                }
                                if (firstSet[production[j]].find('@') == firstSet[production[j]].end()) {
                                    stop = true;
                                    break;
                                }
                            }
                        }
                    }
                    if (stop) break;
                }

                if (j == production.size()) {
                    for (char f : followSet[left]) {
                        followSet[nonTerminal].insert(f);
                    }
                }
            }
        }
    }
}

int main() {
    // Define the grammar and FIRST sets
    nonTerminals = {'E', 'P', 'T', 'Q', 'F'};
    grammar['E'] = {"TP"};
    grammar['P'] = {"+TP", "@"};
    grammar['T'] = {"FQ"};
    grammar['Q'] = {"*FQ", "@"};
    grammar['F'] = {"(E)", "i"};

    firstSet['E'] = {'(', 'i'};
    firstSet['P'] = {'+', '@'};
    firstSet['T'] = {'(', 'i'};
    firstSet['Q'] = {'*', '@'};
    firstSet['F'] = {'(', 'i'};

    // Print Grammar
    cout << "Grammar:\n";
    for (char nt : nonTerminals) {
        cout << nt << " -> ";
        for (auto prod : grammar[nt]) {
            cout << prod << " | ";
        }
        cout << endl;
    }

    // Print FIRST sets
    cout << "\nFIRST sets:\n";
    for (char nt : nonTerminals) {
        cout << nt << " = { ";
        for (auto f : firstSet[nt]) {
            cout << f << " ";
        }
        cout << "}\n";
    }

    // Calculate FOLLOW sets
    computeFollowSet();

    // Print FOLLOW sets
    cout << "\nFOLLOW sets:\n";
    for (char nt : nonTerminals) {
        cout << nt << " = { ";
        for (auto f : followSet[nt]) {
            cout << f << " ";
        }
        cout << "}\n";
    }

    // Build the parsing table
    for (char row : nonTerminals) {
        for (char col : firstSet[row]) {
            if (col != '@') {
                bool found = false;
                for (auto prod : grammar[row]) {
                    if (prod[0] == col) {
                        parsingTable[{row, col}] = string(1, row) + "->" + prod;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    parsingTable[{row, col}] = string(1, row) + "->" + grammar[row][0];
                }
            }
        }
        if (firstSet[row].find('@') != firstSet[row].end()) {
            for (char col : followSet[row]) {
                parsingTable[{row, col}] = string(1, row) + "->@";
            }
        }
    }

    // Print the parsing table
    cout << "\nParsing Table:\n";
    vector<char> terminals = {'i', '+', '*', '(', ')', '$'};
    for (char t : terminals) cout << setw(8) << t; 
    cout << endl;

    for (char nt : nonTerminals) {
        cout << nt << "    ";
        for (char t : terminals) {
            if (!parsingTable[{nt, t}].empty())
                cout << left << setw(8) << parsingTable[{nt, t}];
            else
                cout << "        ";
        }
        cout << endl;
    }

    return 0;
}
