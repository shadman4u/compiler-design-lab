#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;

string keywordList[] = {"alignas", "alignof", "and", "and_eq", "asm", "auto", "bitand", "bitor",
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

string mathOps[] = {"+", "-", "*", "/", "%"};
string relOps[] = {"==", "!=", "<", ">", "<=", ">="};
string logicalOps[] = {"&&", "||", "!"};
string bitwiseOps[] = {"&", "|", "^", "~", "<<", ">>"};
string assignOps[] = {"=", "+=", "-=", "*=", "/=", "%=", "&=", "|=", "^=", "<<=", ">>="};
string incDecOps[] = {"++", "--"};

bool isKeyword(string word) {
    return find(begin(keywordList), end(keywordList), word) != end(keywordList);
}

bool isArithmeticOp(string word) {
    return find(begin(mathOps), end(mathOps), word) != end(mathOps);
}

bool isRelationalOp(string word) {
    return find(begin(relOps), end(relOps), word) != end(relOps);
}

bool isLogicalOp(string word) {
    return find(begin(logicalOps), end(logicalOps), word) != end(logicalOps);
}

bool isBitwiseOp(string word) {
    return find(begin(bitwiseOps), end(bitwiseOps), word) != end(bitwiseOps);
}

bool isAssignmentOp(string word) {
    return find(begin(assignOps), end(assignOps), word) != end(assignOps);
}

bool isIncrementDecrementOp(string word) {
    return find(begin(incDecOps), end(incDecOps), word) != end(incDecOps);
}

bool isIdentifier(string word) {
    if (word.empty()) return false;
    if (word[0] == '_' || isalpha(word[0])) {
        for (int i = 1; i < word.length(); i++) {
            if (!isalnum(word[i]) && word[i] != '_') {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool isNumber(string word) {
    int dotCount = 0;
    for (int i = 0; i < word.length(); i++) {
        if (word[i] == '.') {
            dotCount++;
        }
        if ((!isdigit(word[i]) && word[i] != '.') || dotCount > 1) {
            return false;
        }
    }
    return true;
}

int main() {
    // Open the file for reading input
    ifstream inputFile("08.input.txt"); // Adjust the file path if necessary

    // Check if the file is opened successfully
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open the file!" << endl;
        return 1;
    }

    string inputWord;

    // Read each word from the file
    while (inputFile >> inputWord) {
        bool valid = true;

        if (isKeyword(inputWord)) {
            cout << inputWord << " : Keyword\n";
        }
        else if (isArithmeticOp(inputWord)) {
            cout << inputWord << " : Arithmetic Operator\n";
        }
        else if (isRelationalOp(inputWord)) {
            cout << inputWord << " : Relational Operator\n";
        }
        else if (isLogicalOp(inputWord)) {
            cout << inputWord << " : Logical Operator\n";
        }
        else if (isBitwiseOp(inputWord)) {
            cout << inputWord << " : Bitwise Operator\n";
        }
        else if (isAssignmentOp(inputWord)) {
            cout << inputWord << " : Assignment Operator\n";
        }
        else if (isIncrementDecrementOp(inputWord)) {
            cout << inputWord << " : Increment/Decrement Operator\n";
        }
        else if (isIdentifier(inputWord)) {
            cout << inputWord << " : Identifier\n";
        }
        else if (inputWord[0] == '"' && inputWord[inputWord.length() - 1] == '"') {
            cout << inputWord << " : String Literal\n";
        }
        else if (isNumber(inputWord)) {
            if (inputWord.find('.') != string::npos) {
                cout << inputWord << " : Float\n";
            }
            else {
                cout << inputWord << " : Integer\n";
            }
        } else {
            cout << inputWord << " : Invalid Lexeme\n";
        }
    }

    // Close the file
    inputFile.close();

    return 0;
}
