/*
Program to build a simple lexical analyzer that evaluates expressions
based on these grammar rules:
E -> E A E | (E) | ID
A -> + | - | * | /
ID -> any valid identifier | any valid integer
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <cctype>

using namespace std;
string lineInput;

bool checkIdentifier(string token) {
    if (token.empty() || !(isalpha(token[0]) || token[0] == '_')) {
        return false;
    }

    // Check each character
    for (char ch : token) {
        if (!(isalnum(ch) || ch == '_')) {
            return false;
        }
    }

    // List of reserved keywords in C++
    static const string reservedWords[] = {
        "alignas", "alignof", "and", "and_eq", "asm", "auto", "bitand", "bitor",
        "bool", "break", "case", "catch", "char", "char8_t", "char16_t", "char32_t",
        "class", "compl", "concept", "const", "consteval", "constexpr", "const_cast",
        "continue", "co_await", "co_return", "co_yield", "decltype", "default", "delete",
        "do", "double", "dynamic_cast", "else", "enum", "explicit", "export", "extern",
        "false", "float", "for", "friend", "goto", "if", "inline", "int", "long",
        "mutable", "namespace", "new", "noexcept", "not", "not_eq", "nullptr", "operator",
        "or", "or_eq", "private", "protected", "public", "register", "reinterpret_cast",
        "requires", "return", "short", "signed", "sizeof", "static", "static_assert",
        "static_cast", "struct", "switch", "template", "this", "thread_local", "throw",
        "true", "try", "typedef", "typeid", "typename", "union", "unsigned", "using",
        "virtual", "void", "volatile", "wchar_t", "while", "xor", "xor_eq"
    };

    for (string keyword : reservedWords) {
        if (token == keyword) {
            return false;
        }
    }

    return true;
}

bool checkInteger(string token) {
    for (char ch : token) {
        if (!isdigit(ch)) return false;  // Digits only for integers
    }
    return true;
}

int main() {
    ifstream inputFile("12.input.txt");  // Reads expressions from input file
    if (!inputFile) {
        cerr << "Error opening input file.\n";
        return 1;
    }

    while (getline(inputFile, lineInput)) {
        bool isExprValid = true;
        int operatorCount = 0;
        vector<string> operandList;
        string currentOperand;
        stack<char> parenthesesStack;

        for (char ch : lineInput) {
            if (ch != '+' && ch != '-' && ch != '*' && ch != '/') {  // Non-operator characters
                if (ch == '(') {
                    if (!currentOperand.empty()) { isExprValid = false; break; }
                    parenthesesStack.push('(');
                }
                else if (ch == ')') {
                    if (!parenthesesStack.empty() && !currentOperand.empty()) parenthesesStack.pop();
                    else { isExprValid = false; break; }
                }
                else {
                    currentOperand += ch;  // Add to operand
                }
            } else {  // Operator character
                if (!currentOperand.empty())
                    operandList.push_back(currentOperand);
                currentOperand = "";
                operatorCount++;
            }
        }

        if (!currentOperand.empty())  // Last operand
            operandList.push_back(currentOperand);

        for (string operand : operandList) {
            if (!checkIdentifier(operand) && !checkInteger(operand)) {
                isExprValid = false;
                break;
            }
        }

        // Validate operator count and parentheses balance
        if (isExprValid && (operandList.size() - 1 == operatorCount) && parenthesesStack.empty()) {
            cout << lineInput << ": Valid\n";
        } else {
            cout << lineInput << ": Invalid\n";
        }
    }

    inputFile.close();
    return 0;
}
