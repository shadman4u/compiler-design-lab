/*
Program to generate a syntax tree for the expression a+b*c using basic grammar rules:
E —> E+E | E-E | E*E | E/E | (E) | a | b | c 
*/
#include <iostream>
#include <stack>
#include <string>
using namespace std;

struct TreeNode {
    char value;
    TreeNode* leftChild;
    TreeNode* rightChild;

    TreeNode(char val) {
        value = val;
        leftChild = NULL;
        rightChild = NULL;
    }
};

bool checkOperand(char ch);
bool checkOperator(char ch);
int getPrecedence(char op);
string convertToPostfix(string infix);
TreeNode* buildTree(string postfixExpr);
void displayTree(TreeNode* node, int space = 0, int indent = 4) { // Inorder traversal display
    if (node == NULL) return;
    space += indent;
    displayTree(node->rightChild, space);
    cout << endl;
    for (int i = indent; i < space; i++) {
        cout << " ";
    }
    cout << node->value;
    displayTree(node->leftChild, space);
}

int main() {
    freopen("11.input.txt", "r", stdin);  // Opens input file for reading
    string expression;
    getline(cin, expression);             // Reads input expression
    expression = convertToPostfix(expression);
    TreeNode* exprTree = buildTree(expression);
    displayTree(exprTree);
    cout << endl;
    return 0;
}

bool checkOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

bool checkOperand(char ch) {
    return isalnum(ch);  // Checks if it's an alphanumeric character
}

int getPrecedence(char op) {
    switch (op) {
        case '^': return 2;
        case '*':
        case '/': return 1;
        case '+':
        case '-': return 0;
        default: return -1;
    }
}

string convertToPostfix(string infix) {
    string postfix = "";
    stack<char> opStack;
    for(char ch : infix) {
        if (isalpha(ch)) {  // Adding operands to the postfix string
            postfix += ch;
        }
        else if (ch == '(') opStack.push(ch);  // Push '(' to stack
        else if (ch == ')') {
            while (opStack.top() != '(') {
                postfix += opStack.top();
                opStack.pop();
            }
            opStack.pop();
        }
        else if (checkOperator(ch)) {
            while (!opStack.empty() && getPrecedence(ch) <= getPrecedence(opStack.top())) {
                postfix += opStack.top();
                opStack.pop();
            }
            opStack.push(ch);
        }
    }
    while (!opStack.empty()) {
        postfix += opStack.top();
        opStack.pop();
    }
    return postfix;
}

TreeNode* buildTree(string postfixExpr) {
    stack<TreeNode*> exprStack;
    for (char ch : postfixExpr) {
        if (checkOperand(ch)) {
            exprStack.push(new TreeNode(ch));
        }
        else if (checkOperator(ch)) {
            TreeNode* node = new TreeNode(ch);
            node->rightChild = exprStack.top();
            exprStack.pop();
            node->leftChild = exprStack.top();
            exprStack.pop();
            exprStack.push(node);
        }
    }
    return exprStack.top();
}
