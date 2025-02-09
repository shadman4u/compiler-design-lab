#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>

using namespace std;

// List of C++ keywords
string cppKeywords[] = {"alignas", "alignof", "and", "and_eq", "asm", "auto", "bitand", "bitor",
                        "bool", "break", "case", "catch", "char", "char8_t", "char16_t", "char32_t",
                        "class", "compl", "concept", "const", "consteval", "constexpr", "const_cast",
                        "continue", "co_await", "co_return", "co_yield", "decltype", "default", "delete",
                        "do", "double", "dynamic_cast", "else", "enum", "explicit", "export", "extern",
                        "false", "float", "for", "friend", "goto", "if", "import", "inline", "include", "int",
                        "long", "module", "mutable", "namespace", "new", "noexcept", "not", "not_eq",
                        "nullptr", "operator", "or", "or_eq", "private", "protected", "public", "register",
                        "reinterpret_cast", "requires", "return", "short", "signed", "sizeof", "static",
                        "static_assert", "static_cast", "struct", "switch", "synchronized", "template",
                        "this", "thread_local", "throw", "true", "try", "typedef", "typeid", "typename",
                        "union", "unsigned", "using", "virtual", "void", "volatile", "wchar_t", "while",
                        "xor", "xor_eq"};

// List of C++ operators
string cppOperators[] = {
    "+", "-", "*", "/", "%",               // Arithmetic operators
    "==", "!=", "<", ">", "<=", ">=",      // Relational operators
    "&&", "||", "!",                       // Logical operators
    "&", "|", "^", "~", "<<", ">>",        // Bitwise operators
    "=", "+=", "-=", "*=", "/=", "%=", "&=", "|=", "^=", "<<=", ">>=", // Assignment operators
    "++", "--",                            // Increment and decrement operators
    "?", ":",                              // Conditional operator
    ",",                                   // Comma operator
    ".", "->",                             // Member access operators
    "::"                                   // Scope resolution operator
};

int main() {
    // Variable declarations
    string inputStr;
    bool isValid = true;
    
    // Open the input file
    freopen("07.input.txt", "r", stdin);

    // Read input line by line
    while (getline(cin, inputStr)) {
        isValid = true;
        
        // Check if the input is a keyword
        if (find(begin(cppKeywords), end(cppKeywords), inputStr) != end(cppKeywords)) {
            cout << inputStr << " : " << "Keyword\n";
        }
        // Check if the input is an operator
        else if (find(begin(cppOperators), end(cppOperators), inputStr) != end(cppOperators)) {
            cout << inputStr << " : " << "Operator\n";
        }
        // Check if the input is an identifier
        else if (isalpha(inputStr[0]) || inputStr[0] == '_') {
            for (int i = 1; i < inputStr.length(); i++) {
                if (!isalnum(inputStr[i]) && inputStr[i] != '_') {
                    isValid = false;
                    break;
                }
            }
            if (isValid) {
                cout << inputStr << " : " << "Identifier\n";
            }
        }
        // Check if the input is a constant (string literal)
        else if (inputStr[0] == '"' && inputStr[inputStr.length() - 1] == '"') {
            cout << inputStr << " : " << "Constant\n";
        }
        // Check if the input is a numeric constant
        else if (isdigit(inputStr[0]) || inputStr[0] == '.') {
            int dotCount = 0;
            for (char c : inputStr) {
                if (!isdigit(c) && c != '.') {
                    isValid = false;
                    break;
                }
                if (c == '.') {
                    dotCount++;
                }
            }
            if (isValid && dotCount < 2) {
                cout << inputStr << " : " << "Constant\n";
            } else {
                isValid = false;
            }
        }
        // Invalid lexeme
        else {
            isValid = false;
        }
        
        // Print invalid lexeme if not valid
        if (!isValid) {
            cout << inputStr << " : " << "Invalid Lexeme\n";
        }
    }

    return 0;
}
