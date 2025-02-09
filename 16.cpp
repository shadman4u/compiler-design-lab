#include <iostream>
#include <stack>
#include <fstream>
#include <string>
using namespace std;

int getPrecedence(char c);
string convertToPostfix(string exp);

int main() {
    ifstream inputFile("16.input.txt");
    if (!inputFile) {
        cout << "Error opening file!" << endl;
        return 1; // Exit if file can't be opened
    }

    string infix;
    getline(inputFile, infix);  // Read the entire line from the file
    inputFile.close(); // Close the file after reading

    string result = convertToPostfix(infix);
    cout << "Postfix expression: " << result << endl;

    return 0;
}

string convertToPostfix(string exp) {
    string postfix = "";
    stack<char> operators;

    for (int i = 0; i < exp.length(); i++) {
        char current = exp[i];

        // If the character is an operand (a letter)
        if ((current >= 'a' && current <= 'z') || (current >= 'A' && current <= 'Z')) {
            postfix += current;
        } 
        // If it's an opening parenthesis, push it onto the stack
        else if (current == '(') {
            operators.push(current);
        } 
        // If it's a closing parenthesis, pop until we find the matching opening parenthesis
        else if (current == ')') {
            while (!operators.empty() && operators.top() != '(') {
                postfix += operators.top();
                operators.pop();
            }
            operators.pop(); // Remove '('
        } 
        // If it's an operator, pop from the stack while the precedence is higher or equal
        else {
            while (!operators.empty() && getPrecedence(current) <= getPrecedence(operators.top())) {
                postfix += operators.top();
                operators.pop();
            }
            operators.push(current); // Push the current operator
        }
    }

    // Pop all remaining operators from the stack
    while (!operators.empty()) {
        postfix += operators.top();
        operators.pop();
    }

    return postfix;
}

int getPrecedence(char c) {
    if (c == '^') return 3;
    if (c == '*' || c == '/') return 2;
    if (c == '+' || c == '-') return 1;
    return 0; // Default precedence for invalid operators
}
