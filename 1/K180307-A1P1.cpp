/*

Given an array of dimension n,m of alphabets of English along with a dictionary of words to look
into the puzzled. You need to write a program in object oriented programming such that the puzzle
object has a function “solve” that return an array of positions(Point2D) if a dictionary word is
_found at the starting (x,y) location in either direction. Only up, down, left and right movement for
searching is allowed. Your puzzle class read an instance of a puzzle from the input file. The
solution should also be written in file.

Input file format: The first line of the input file for this problem contains size of the puzzle n and
m two integers both single digit. The next line contains the first row of n possible row with m
alphabets all lower case. After the puzzle the next line give how many word you need to search
maximum 10. From the next line the words are given per line. A sample input is given below:

Output file format: The output file contains starting position (x,y) for each word given in order,
if the word is not present in the puzzle just place n on the corresponding line. 

*/

// ! NOTE: Program is dependent on C++11 due to use of <tuple>

#include <cstring>
#include <string>
#include <fstream>
#include <vector>
#include <tuple>
#include <iostream>
using namespace std;

typedef tuple<string, bool> Dictionary;

class Maze
{
public:
    // ******************************** START RULE OF THREE ***************************** //

    // Parameterized constructor, takes in
    // a): Takes in string for the file output name
    // b): for the rows
    // c): for the columns
    Maze(int rows = 1, int cols = 1)
    {
        this->rows = rows;
        this->columns = cols;
        _buffer = new char[rows * columns];
        memset(_buffer, 'A', rows * columns);
    }

    // Copy Constructor
    Maze(const Maze &obj)
        : rows(obj.rows), columns(obj.columns)
    {
        _buffer = new char[obj.rows * obj.columns];

        memcpy(this->_buffer, obj._buffer, obj.rows * obj.columns);
    }

    // Assignment operator
    Maze &operator=(const Maze &rhs)
    {
        if (this == &rhs)
            return *this;

        delete[] _buffer;
        _buffer = 0; // Neccessary safety check

        this->rows = rhs.rows;
        this->columns = rhs.columns;
        this->_buffer = new char[rhs.rows * rhs.columns]{'\0'};
        memcpy(this->_buffer, rhs._buffer, rhs.rows * rhs.columns);
    }

    // ******************************** END RULE OF THREE ***************************** //

    // Sanity check ( to check if buffer was inputted correctly )
    void printBuffer(void) const
    {
        for (int i = 0, k = 0; i < rows; ++i, ++k)
        {
            for (int j = 0; j < columns; ++j)
                cout << _buffer[i * rows + j + k];
            cout << "\n";
        }
    }

    // 2nd Sanity Check ( print out the list, to check if it was inputted correctly )
    void printList(void) const
    {
        for (int i = 0; i < _dictionary.size(); ++i)
        {
            for (int j = 0; j < (get<0>(_dictionary[i])).size(); ++j)
            {
                cout << (get<0>(_dictionary[i])).at(j);
            }
            cout << endl;
        }
    }

    // Assigns inputted dictionary to the dictionary present in the class
    void setList(vector<Dictionary> &in_vect, size_t _size)
    {
        _dictionary = in_vect;
        _found = vector<string>(_size, "n");
    }

    // lvalue
    // return value if present, else return null ( compiler through warning, so I returned null instead )
    char &operator()(int i, int j, int offset)
    {
        if ((i < 0 || i > rows) || (j < 0 || j > columns))
            return _buffer[rows * i + j + offset];
        return null;
    }

    // rvalue
    // same as the lvalue, used const to differentiate
    const char &operator()(int i, int j, int offset) const
    {
        if ((i < 0 || i > rows) || (j < 0 || j > columns))
            return _buffer[rows * i + j + offset];
        return null;
    }

    // The actual class member function to evaluate the inputted buffer
    vector<string> Evaluate(void)
    {
        vector<int> count; // Holds the common occurrence of words that have the same position for the starting letter

        // ... start iteration through each row ...
        for (int i = 0, k = 0, offset = 0; i < rows; ++i, ++offset)
        {
            // ... foreach column element in each row ...
            for (int j = 0; j < columns; ++j)
            {
                // ... get back a vector which hold the common position for the starting letter
                // for each word in the dictionary provided ...
                count = inBuffer(i, j, offset);

                // ... go through each of the elements of the new vector ...
                for (int q = 0; q < count.size(); ++q)
                {
                    // ... store value from each position of the vector into 'k' ...
                    k = count[q];

                    // ... check condition that ...
                    // ... if k is not -1, that is, the count vector is not empty AND
                    // the specific word in the dictionary has already not been found ...
                    if (k != -1 && !get<1>(_dictionary[k]))
                    {
                        bool Flag = false; // check if the word has been found or not
                        size_t limit;      // ... check until ... ( auxiliiary variable )

                        // Now, simply check by moving up, down, left and
                        // right if a word is completely present if it is, put the
                        // (i, j ) coordinates of the first char somewhere
                        // and set the bool of that tuple structure to true

                        // Right searching
                        // ... if word falls within range of buffer ...
                        limit = j + get<0>(_dictionary[k]).size();
                        if (limit - 1 <= columns && !Flag)
                        {
                            // ... start checking by moving right ...
                            for (int l = j, m = 0; l < limit; ++l, ++m)
                            {
                                // ... if a char mismatches, break.
                                if (_buffer[i * rows + l + offset] != get<0>(_dictionary[k])[m])
                                {
                                    Flag = false;
                                    break;
                                }

                                // .., if at last char, and equal, set flag to true
                                if (l + 1 == j + (get<0>(_dictionary[k])).size())
                                    Flag = true;
                            }
                        }

                        // Down Searching
                        // ... if word falls within range of buffer ...
                        limit = i + get<0>(_dictionary[k]).size();
                        if (limit - 1 <= rows && !Flag)
                        {
                            // ... start checking by moving right ...
                            for (int l = i, m = 0, temp_off = offset; l < limit; ++l, ++m, ++temp_off)
                            {
                                // ... if a char mismatches, break.
                                if (_buffer[l * rows + j + temp_off] != get<0>(_dictionary[k])[m])
                                {
                                    Flag = false;
                                    break;
                                }

                                // .., if at last char, and equal, set flag to true
                                if (l + 1 == i + (get<0>(_dictionary[k])).size())
                                    Flag = true;
                            }
                        }

                        // Left Searching
                        // ... if word falls within range of buffer ...
                        limit = j - get<0>(_dictionary[k]).size() + 1;
                        if (limit >= 0 && !Flag)
                        {
                            // ... start checking by moving right ...
                            for (int l = j, m = 0; l >= limit; --l, ++m)
                            {
                                // ... if a char mismatches, break.
                                if (_buffer[i * rows + l + offset] != get<0>(_dictionary[k])[m])
                                {
                                    Flag = false;
                                    break;
                                }

                                // .., if at last char, and equal, set flag to true
                                if (l == limit)
                                {
                                    Flag = true;
                                    break;
                                }
                            }
                        }

                        // Up Searching
                        // ... if word falls within range of buffer ...
                        limit = i - (get<0>(_dictionary[k]).size() - 1);
                        if (limit >= 0 && !Flag)
                        {
                            // ... start checking by moving right ...
                            for (int l = i, m = 0, temp_off = offset; l >= limit; --l, ++m, --temp_off)
                            {
                                // ... if a char mismatches, break.
                                if (_buffer[l * rows + j + temp_off] != get<0>(_dictionary[k])[m])
                                {
                                    Flag = false;
                                    break;
                                }

                                // .., if at last char, and equal, set flag to true
                                if (l == limit)
                                {
                                    Flag = true;
                                    break;
                                }
                            }
                        }

                        // if a word if finally found through any of the above ways, set tuple flag to true
                        // and set a string in the vector to current coords!
                        if (Flag)
                        {
                            (get<1>(_dictionary[k])) = true;
                            _found[k] = to_string(i) + to_string(j);
                        }
                    }
                }
            }
        }

        vector<string> return_vect; // finally, make a vector

        // push into vector the resulting answer
        for (int i = 0; i < _dictionary.size() - 1; ++i)
            return_vect.push_back(_found[i]);
        return_vect.push_back(_found[_dictionary.size() - 1]);

        // and return the vector
        return return_vect;
    }

    // Extraction, insertion
    friend std::ostream &operator<<(std::ostream &OutFile, const Maze &obj);
    friend std::istream &operator>>(std::istream &InFile, Maze &obj);

    // basic desctructor
    ~Maze()
    {
        delete[] _buffer;
    }

private:
    // Takes in the buffer coords: X, Y, and the row offset
    // to check if the letter at the pos matches any of the
    // starting characters of any of the first letters of the
    // words provided in the input
    vector<int> inBuffer(int ith, int jth, int offset) const
    {
        vector<int> count_common;
        for (int k = 0; k < _dictionary.size(); ++k)
            if (_buffer[rows * ith + jth + offset] == (get<0>(_dictionary[k]))[0])
                count_common.push_back(k);

        // If it did not match any word's first character, push -1 to indicate none was found
        if (count_common.empty())
        {
            count_common.push_back(-1);
            return count_common;
        }
        else
            return count_common;
    }

    vector<string> _found;          // Stores coords if a word is found, else writes 'n' in that place
    vector<Dictionary> _dictionary; // Dict to check if a word has been found, if found, sets the bool value to 'true', else 'false' by default
    static char null;               // Aux var, serves no purpose. Created to stop warning genereted by g++ in both overloadings of func operator()
    char *_buffer;                  // buffer to actually hold the maze
    int rows;                       // int to store the row dimensions
    int columns;                    // int to store the col dimensions
};

char Maze::null = '\0'; // setting 'null' to literally null

// Insertion operation, inserts the buffer from the input stream
std::istream &operator>>(std::istream &InFile, Maze &obj)
{
    for (int i = 0, k = 0; i < obj.rows; i++, k++)
        for (int j = 0; j < obj.columns; j++)
            InFile >> obj._buffer[i * obj.rows + j + k];

    return InFile;
}

// Extraction operation, to output the buffer
std::ostream &operator<<(std::ostream &OutFile, const Maze &obj)
{
    for (int i = 0, offset = 0; i < obj.rows; ++i, ++offset)
    {
        for (int j = 0; j < obj.columns; ++i)
            OutFile << obj(i, j, offset);
        cout << "\n";
    }

    return OutFile;
}

int main(void)
{

    // Basic IO operation
    ifstream inFile("P1_input.txt");
    ofstream outFile("P1_output.txt");

    // N -> Rows, M -> Cols
    int N, M;
    inFile >> N >> M;

    // Make buffer from N and M
    Maze maze(N, M);
    inFile >> maze;

    // Use func for sanity check
    // maze.printBuffer();

    // Take in maximum 10 words to search for in buffer
    size_t T;
    inFile >> T;
    T = T > 10 ? 10 : T;
    vector<Dictionary> Hold;
    std::string stringHold;

    // For each row in dictionary, take the row string, insert it, along with a default bool value 'false' into a vectorized tuple
    for (int i = 0; i < T; ++i)
    {
        inFile >> stringHold;
        Hold.push_back(make_tuple(stringHold, false));
    }

    // set the list created in main to the list created in the class, along with size T
    maze.setList(Hold, T);

    // 2nd sanity check
    // maze.printList();

    // Get back string of answers and coords, from Evaluate
    vector<string> evaluate = maze.Evaluate();

    // output the contents of the retrieved vector to the output file
    for (int i = 0; i < evaluate.size() - 1; ++i)
        outFile << evaluate[i] << "\n";
    outFile << evaluate[evaluate.size() - 1];

    // close the files
    inFile.close();
    outFile.close();

    return 0;
}