#include <bits/stdc++.h>

using namespace std;

// Parsing table for predictive parsing
map<pair<char, char>, string> parseTable;

// Function that processes the input string
bool processInput(string expr);

int main()
{
    // Open file and read the expression
    freopen("15.input.txt", "r", stdin);
    string expression;
    getline(cin, expression);

    // Filling the parsing table with production rules
    parseTable[make_pair('E', 'i')] = "TX";
    parseTable[make_pair('E', '(')] = "TX";
    parseTable[make_pair('X', '+')] = "+TX";
    parseTable[make_pair('X', ')')] = "@";
    parseTable[make_pair('X', '$')] = "@";
    parseTable[make_pair('T', 'i')] = "FY";
    parseTable[make_pair('T', '(')] = "FY";
    parseTable[make_pair('Y', '+')] = "@";
    parseTable[make_pair('Y', ')')] = "@";
    parseTable[make_pair('Y', '$')] = "@";
    parseTable[make_pair('Y', '*')] = "*FY";
    parseTable[make_pair('F', 'i')] = "i";
    parseTable[make_pair('F', '(')] = "(E)";

    cout << "Expression to parse: " << expression << endl;

    if(processInput(expression)) 
        cout << "String accepted!" << endl;
    else 
        cout << "String rejected!" << endl;

    return 0;
}

// Function to simulate the parsing process
bool processInput(string expr) {
    stack<pair<int, char>> parserStack;
    parserStack.push({0, 'E'});  // Starting symbol
    
    int indentation = 0;  // Indentation for displaying parsing steps
    for (int i = 0; i < expr.size(); i++) {
        while (parserStack.top().second != expr[i] && parserStack.top().second != '@') {
            pair<int, char> current = parserStack.top();
            // If no rule is found, reject the string
            if (parseTable[{current.second, expr[i]}] == "") {
                return false;
            }
            
            // Print the production being applied
            for (int j = 0; j < current.first; j++) cout << " ";
            cout << current.second << " ---> " << parseTable[{current.second, expr[i]}] << endl;
            
            indentation = current.first + 5;
            parserStack.pop();
            string rule = parseTable[{current.second, expr[i]}];
            reverse(rule.begin(), rule.end());  // Reverse the production for stack processing

            // Push the right-hand side of the production in reverse order
            for (char c : rule) {
                parserStack.push({indentation, c});
            }
        }
        
        // If the top of the stack matches the current symbol in the string
        if (parserStack.top().second == expr[i]) {
            parserStack.pop();
        }
        
        // Handle the epsilon ('@') case
        if (parserStack.top().second == '@') {
            parserStack.pop();
            i--;  // Stay at the same character in the string for further processing
        }
    }
    
    // Empty the stack and print the remaining derivation steps
    while (!parserStack.empty()) {
        for (int i = 0; i < parserStack.top().first; i++) cout << " ";
        cout << parserStack.top().second << " ---> @" << endl;
        parserStack.pop();
    }
    
    return true;
}
