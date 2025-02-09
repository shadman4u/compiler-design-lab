#include <iostream>
#include <map>
#include <string>
#include <iomanip>

using namespace std;

// The map holds production rules like {"E+E" : "E"} where key is right-hand side and value is left-hand side
map<string, string> productionRules;
string stackContent = "", inputStr;

// This function will attempt to reduce the stack content based on the production rules
void tryReduce() {
    for (auto rule : productionRules) {
        // Check if the current stack contains any of the right-hand side of the production rule
        if (stackContent.find(rule.first) != string::npos) {
            int position = stackContent.find(rule.first);  // Find position of rule
            stackContent.erase(position);  // Remove the matched part from the stack
            stackContent += rule.second;  // Add the left-hand side of the production to the stack
            // Print the current stack and input
            cout << left << setw(13) << "$" + stackContent << right << setw(13) << inputStr + "$" << right
                 << "         Reduced " << rule.second << " --> " << rule.first << endl;
            tryReduce();  // Recursively try to reduce further
            return;  // Exit after reducing once
        }
    }
}

int main() {
    freopen("10.input.txt", "r", stdin);  // Redirecting input to read from a file
    string production;
    int ruleCount;  // Number of rules
    cin >> ruleCount;
    cin.ignore();  // To ignore the newline after reading integer

    // Read production rules and store in the map
    for (int i = 0; i < ruleCount; i++) {
        getline(cin, production);  // Read the rule as a string
        productionRules[production.substr(3)] = production[0];  // Substring after "X->" is right-hand side, before it is left-hand side
    }

    cin >> inputStr;  // Input expression to be parsed
    cout << "Stack              " << "Input            " << "Action\n";
    cout << left << setw(13) << "$" + stackContent << right << setw(13) << inputStr + "$" << endl;

    // Parsing begins: shift and reduce operations
    while (!inputStr.empty()) {
        // Perform shift operation: move one character from input to stack
        stackContent += inputStr[0];
        inputStr.erase(0, 1);
        cout << left << setw(13) << "$" + stackContent << right << setw(13) << inputStr + "$" << right << "         Shift " << stackContent.back() << endl;

        tryReduce();  // Try to reduce the stack after each shift
    }

    // Final check for acceptance
    if (stackContent == "E") {
        cout << "Accepted\n";  // If stack has "E", the input is accepted
    } else {
        cout << "Rejected\n";  // Otherwise, it's rejected
    }

    return 0;
}
