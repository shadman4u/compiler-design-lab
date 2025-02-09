#include <bits/stdc++.h>
using namespace std;

// Function to check precedence of operators
int getPrecedence(char op);
string infixToPostfix(string expression);
string processExpression(string expression);

int main() {
    // Open the file for reading input
    freopen("17.input.txt", "r", stdin);
    string inputExpr;
    getline(cin, inputExpr);  // Read the entire line from the file
    cout << processExpression(inputExpr);  // Process and output the result
    return 0;
}

string processExpression(string expression) {
    string currentWord = "", postfixResult = "";
    stack<string> operators;
    
    for (char c : expression) {
        if (c != ' ') {
            currentWord += c; // Forming a word or operator
        } else {
            if (currentWord == "then") { 
                currentWord = ""; 
                continue;
            }
            if (currentWord == "if") {
                operators.push(currentWord); // Push "if" to stack
            }
            else if (currentWord == "else") {
                operators.push(currentWord); // Push "else" to stack
            }
            else {
                // Convert any valid infix to postfix and append to result
                postfixResult += infixToPostfix(currentWord);
                while (!operators.empty() && operators.top() == "else") {
                    postfixResult += "?";
                    operators.pop();
                    operators.pop(); // Remove the matching "if"
                }
            }
            currentWord = "";
        }
    }
    return postfixResult;
}

string infixToPostfix(string expr) {
    string postfix = "";
    stack<char> operatorStack;
    
    for (char c : expr) {
        if (isalnum(c)) {
            postfix += c; // Add operands (letters) directly to postfix
        } else if (c == '(') {
            operatorStack.push(c); // Open parenthesis goes to stack
        } else if (c == ')') {
            // Pop from stack until matching open parenthesis
            while (!operatorStack.empty() && operatorStack.top() != '(') {
                postfix += operatorStack.top();
                operatorStack.pop();
            }
            operatorStack.pop(); // Remove '('
        } else if (!isspace(c)) { 
            // Handle operators: pop higher or same precedence operators to postfix
            while (!operatorStack.empty() && getPrecedence(c) <= getPrecedence(operatorStack.top())) {
                postfix += operatorStack.top();
                operatorStack.pop();
            }
            operatorStack.push(c); // Push current operator to stack
        }
    }
    
    // Pop remaining operators from stack
    while (!operatorStack.empty()) {
        postfix += operatorStack.top();
        operatorStack.pop();
    }
    
    return postfix;
}

int getPrecedence(char op) {
    switch (op) {
        case '^':
            return 3;
        case '/':
        case '*':
            return 2;
        case '+':
        case '-':
            return 1;
        default:
            return 0;
    }
}
