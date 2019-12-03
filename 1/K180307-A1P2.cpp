/*

Consider a 2-dimensional array as maze containing 0 and 1, zero means a path and 1 means blocked
path. You need to count all possible paths someone can take in maze to reach the end. The starting
location is (0,0) and end location is (n,m). You can only move right and down for reaching the
destination.

Input file format: The first line of the input file contains two integers n and m both can be 0 <
n,m < 10, The maze is available from next line containing first row of m cells. Remember each
cell can contain 0 or 1.

Output file format: The first line of the output file contains possible paths p as integer. If there is
no path you should write “No Path” in the file.s

*/

#include <fstream>
#include <iostream>
#include <string>
using namespace std;
#define N 10            // N -> Rows for the buffer, set to 10 for max size
#define M 10            // M -> Cols for the buffer, set to 10 for max size

// rows, cols indicate dimensions of to-be accessed buffer, always less than 10 ( assumed, not corrected in code )
// count global var, to keep track of how many times the dest has been visited
size_t rows, cols, count = 0;
bool Board[N][M];                   // Created buffer
bool visited[N][M]{false};          // Create buffer to check if a coord has been visited 

// Coord class, for containing the coordinate tuple
struct Coord
{
    // since coord values are always positve, let size_t be their data type
    size_t X, Y;

    // To initialize the Coord object
    Coord(size_t X = 0, size_t Y = 0)
        : X(X), Y(Y) {}

    // Simplifying code by abstracting away the equality - checks if both are equal
    bool operator==(const Coord &rhs)
    {
        return this->X == rhs.X - 1 && this->Y == rhs.Y - 1;
    }
};

// isSafe function to check if step is i): in bounds of the buffer ii): is not into an obstacle, which here is 1
bool isSafe(const int X, const int Y)
{
    return (X < rows && Y < cols && Board[X][Y] == 0);
}

// Go through the buffer
// X is the x-coord
// Y is the y-coord
// _End is the destination coordinate
void Pathways(size_t X, size_t Y, const Coord &_End)
{
    // Syntax requires C++11
    if (Coord{X, Y} == _End)
    {
        ::count++;              // ... increment and then ...
        return;                 // ... simply return ...
    }

    // Current Coord has been just visited
    visited[X][Y] = true;

    // Move down!
    if (X + 1 < rows && isSafe(X + 1, Y) && !visited[X + 1][Y])
        Pathways(X + 1, Y, _End);

    // Move right!
    if (Y + 1 < cols && isSafe(X, Y + 1) && !visited[X][Y + 1])
        Pathways(X, Y + 1, _End);

    // Backtracking move ... it's magic!
    visited[X][Y] = false;
}

int main(void)
{

    // Basic IO, as usual business
    ifstream inFile("P2_input.txt");
    ofstream outFile("P2_output.txt");
    
    // string object to take in the values for the board
    string temp;                        

    inFile >> rows >> cols;

    // ... put input file pointer to start of the board ...
    inFile.seekg(5);

    // ... and then, for each row of the board ...
    for (int i = 0; i < rows; ++i)
    {
        // ... extract the line as a string ...
        getline(inFile, temp);

        // ... foreach char of the extracted string ... 
        for (int j = 0; j < temp.size(); ++j)

            // ... get whether it is a 0 or 1 in its place ...
            Board[i][j] = temp[j] - '0';
    }

    // Use function pathways, start at (0, 0) -> the src, go to dest coord
    Pathways(0, 0, {rows, cols});

    // ... and lastly output the resulting count value to the output file ...
    outFile << ::count;

    inFile.close();
    outFile.close();

    // ... and return!
    return 0;
}