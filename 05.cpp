#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main()
{
    string input_line;

    // Open the input file for reading
    freopen("05.input.txt", "r", stdin);

    while (getline(cin, input_line))
    {
        bool valid_input = true;

        // Check if the first character is a valid letter for a variable name
        if ((tolower(input_line[0]) >= 'a' && tolower(input_line[0]) <= 'h') || 
            (tolower(input_line[0]) >= 'o' && tolower(input_line[0]) <= 'z'))
        {
            // Check if the remaining characters are alphanumeric
            for (int i = 1; i < input_line.length(); i++)
            {
                if (!isalnum(input_line[i]))
                {
                    valid_input = false;
                    break;
                }
            }

            if (valid_input)
                cout << input_line << " is a valid Float variable\n";
        }
        else if (isdigit(input_line[0])) // If the first character is a digit
        {
            int dot_pos = -1, dot_count = 0;

            // Look for the position of the dot and count its occurrences
            for (int i = 1; i < input_line.length(); i++)
            {
                if (input_line[i] == '.')
                {
                    dot_pos = i;
                    dot_count++;
                }
                if (!isdigit(input_line[i]) && input_line[i] != '.')
                {
                    valid_input = false;
                    break;
                }
            }

            // If there's exactly one dot and it's placed correctly
            if (dot_pos != -1 && dot_count == 1 && valid_input)
            {
                int decimal_places = input_line.substr(dot_pos + 1).length();

                // Check if the number is a float or double based on decimal places
                if (decimal_places == 2)
                    cout << input_line << " is a Float Number\n";
                else if (decimal_places > 3)
                    cout << input_line << " is a Double Number\n";
                else
                    valid_input = false;
            }
            else
                valid_input = false;
        }
        else
        {
            valid_input = false;
        }

        // If the input doesn't match any valid format
        if (!valid_input)
            cout << input_line << " is Invalid or Undefined\n";
    }

    return 0;
}
