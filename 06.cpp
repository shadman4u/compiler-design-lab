#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main() {
    string line;

    // Open the input file for reading
    freopen("06.input.txt", "r", stdin);

    while (getline(cin, line)) {
        bool valid = true;

        // Check for "ch_" or "bn_" followed by alphanumeric characters
        if (line.size() >= 4 && (line.substr(0, 3) == "ch_" || line.substr(0, 3) == "bn_") && isalnum(line[3])) {
            for (int i = 4; i < line.size(); i++) {
                if (!isalnum(line[i])) {
                    valid = false;
                    break;
                }
            }
            if (valid) {
                if (line.substr(0, 3) == "ch_") {
                    cout << line << " is a Character variable\n";
                } else {
                    cout << line << " is a Binary variable\n";
                }
            }
        }
        // Check if the input is a valid binary number
        else if (line.size() >= 2 && line[0] == '0' && (line[1] == '0' || line[1] == '1')) {
            for (int i = 2; i < line.size(); i++) {
                if (line[i] != '0' && line[i] != '1') {
                    valid = false;
                    break;
                }
            }
            if (valid) {
                cout << line << " is a Binary Number\n";
            }
        }
        else {
            valid = false;
        }

        // If the input is invalid, print an error message
        if (!valid) {
            cout << line << " is Invalid Input or Undefined\n";
        }
    }

    return 0;
}
