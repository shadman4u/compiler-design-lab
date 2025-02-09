/*
Write a program that abbreviates the following code:
CSE-3141 as Computer Science & Engineering, 3rd year, 1st semester, Compiler Design, Theory.
*/

#include <iostream>  // Basic I/O library instead of bits/stdc++.h
#include <fstream>   // For file handling

using namespace std;

int main() {
    ifstream inputFile("03.input.txt"); // Open input file
    string fullCode, department = "";
    getline(inputFile, fullCode); // Read input line

    // Extract department code (before the dash)
    int idx = 0;
    while (fullCode[idx] != '-') {
        department += fullCode[idx];
        idx++;
    }

    // The rest of the code part after the dash
    string codePart = fullCode.substr(idx + 1);

    // Define simple mappings using arrays (less efficient, but common in beginner code)
    string deptList[2] = {"Computer Science & Engineering", "Information & Communication Engineering"};
    string yearList[4] = {"1st", "2nd", "3rd", "4th"};
    string subjectList[4] = {"Software Engineering", "Database Management Systems", "Web Engineering", "Compiler Design"};
    string courseType[2] = {"Theory", "Lab"};

    // Map the department abbreviation to the full name
    string deptFullName;
    if (department == "CSE") {
        deptFullName = deptList[0];
    } else if (department == "ICE") {
        deptFullName = deptList[1];
    }

    // Get year, semester, subject, and course type based on position in code
    int yearCode = codePart[0] - '1';
    int semesterCode = codePart[1] - '1';
    int subjectCode = codePart[2] - '1';
    int courseCode = codePart[3] - '1';

    // Display the full name format
    cout << fullCode << " : ";
    cout << deptFullName << ", " << yearList[yearCode] << " year, ";
    cout << yearList[semesterCode] << " semester, ";
    cout << subjectList[subjectCode] << ", " << courseType[courseCode] << endl;

    inputFile.close(); // Close file
    return 0;
}
