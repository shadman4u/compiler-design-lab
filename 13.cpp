/*
Program to compute FIRST and FOLLOW sets for a given Context-Free Grammar (CFG)
*/
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

map<char, vector<string>> prodRules;
map<char, set<char>> firstSet;
map<char, set<char>> followSet;
vector<char> nonTerminals;

int main() {
    ifstream inputFile("13.input.txt");
    string line;
    while (getline(inputFile, line)) {
        prodRules[line[0]].push_back(line.substr(3));
        if(find(nonTerminals.begin(), nonTerminals.end(), line[0]) == nonTerminals.end())
            nonTerminals.push_back(line[0]);
    }

    // Display grammar rules
    cout << "_____Grammar_____\n";
    for(char symbol : nonTerminals) {
        cout << symbol << " -> ";
        for(const auto& rule : prodRules[symbol]) {
            cout << rule << " | ";
        }
        cout << "\n";
    }

    // Calculate FIRST sets
    for(int i = nonTerminals.size() - 1; i >= 0; i--) {
        for(const auto& rule : prodRules[nonTerminals[i]]) {
            for(size_t j = 0; j < rule.size(); j++) {
                if(rule[j] < 'A' || rule[j] > 'Z') { // Terminal character
                    firstSet[nonTerminals[i]].insert(rule[j]);
                    break;
                } else {
                    for(char f : firstSet[rule[j]]) {
                        firstSet[nonTerminals[i]].insert(f);
                    }
                    if(firstSet[rule[j]].find('@') == firstSet[rule[j]].end()) break;
                }
            }
        }
    }

    // Display FIRST sets
    cout << "_____FIRST_____\n";
    for(char symbol : nonTerminals) {
        cout << symbol << " = {";
        for(auto f : firstSet[symbol]) {
            cout << f << ", ";
        }
        cout << "}\n";
    }

    // Initialize FOLLOW set with end marker
    followSet[nonTerminals[0]].insert('$');
    for(char target : nonTerminals) {
        for(char left : nonTerminals) {
            for(const auto& rule : prodRules[left]) {
                bool done = false;
                size_t j = 0;
                for(size_t i = 0; i < rule.size(); i++) {
                    if(rule[i] == target) {
                        for(j = i + 1; j < rule.size(); j++) {
                            if(rule[j] < 'A' || rule[j] > 'Z') {
                                followSet[target].insert(rule[j]);
                                done = true;
                                break;
                            } else {
                                for(char f : firstSet[rule[j]]) {
                                    if(f != '@') followSet[target].insert(f);
                                }
                                if(firstSet[rule[j]].find('@') == firstSet[rule[j]].end()) {
                                    done = true;
                                    break;
                                }
                            }
                        }
                    }
                    if(done) break;
                }
                if(j == rule.size()) {
                    for(char f : followSet[left]) {
                        followSet[target].insert(f);
                    }
                }
            }
        }
    }

    // Display FOLLOW sets
    cout << "_____FOLLOW_____\n";
    for(char symbol : nonTerminals) {
        cout << symbol << " = {";
        for(auto f : followSet[symbol]) {
            cout << f << ", ";
        }
        cout << "}\n";
    }
}
