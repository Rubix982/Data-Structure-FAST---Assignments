/*

You are given an array of string. You need to retain only the first appearance of each character in
the string and for all other repeating characters’ place “- “in the string. For example, given the
string “i love to play cricket and I hate hockey” is converted to “i love t- p-ay cr—k-- -nd – h--- -
-----“

Input file format: The file contains single line of text comprises of English character in lower
case. The length of the string is possibly 80-characters long.

Output file format: The output file contains the same string after mutating the string as per
requirements of the problem. 

*/

#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main(void) {

    // Basic input/output from the start
    ifstream inFile("P3_input.txt");
    ofstream outFile("P3_output.txt");

    // Make an array to store the frequency of each character from a given string
    const size_t ARRAY_SIZE = 27;
    size_t Array[ARRAY_SIZE]{0};

    // string object made to hold in the input from the file
    string original;
    getline(inFile, original);

    // Code to convert any uppercase to lower case, uses <algorithm>
    for_each(original.begin(), original.end(), [] ( char & c ) { c = ::tolower(c); });

    // ... for each element in the string ...
    for (int i = 0; i < original.length(); ++i) {
        
        // ... current char is unequal to a blank space ...
        if (original[i] != ' ') {
            // ... take the current char, and get the index of the english alphabet ...
            int val = original[i] - 95;

            // ... then increment accordingly in the above made array ...
            Array[val]++;

            // ... if element has already ocurred, assign to the original string a '-' instead in its place ...
            if (Array[val] > 1)
                original[i] = '-';
        }
    }
    
    // ... output manipulated string to a file ... 
    outFile << original;

    inFile.close();
    outFile.close();

    return 0;
}