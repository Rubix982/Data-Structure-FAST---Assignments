/*

In a Binary Search Tree (BST), you need to find the longest increasing sequence of nodes (contains 
+ values)- This is also a longest path that contains increasing or decreasing node values. You need 
to read a sequence of values from a file, this is the given order for which you need to insert these 
values into an empty BST. Consider the sequence 7,4,12,9,6,5,2,3,19,15,20,8, and 11 
  
The above tree contains all the values and it is a BST. You need to find the longest sequence of 
node that is increasing or decreasing of the node values. In the above tree. 7, 12, 19 and 20 is the 
largest such node sequences forming path 7->12->19 -> 20 

The main requirement for this assignment is to write your own BST code and utility functions that 
make the task easy for you to decide. 

Input file format: The input file contains values for each node in a given order. You need to insert 
each value in an empty BST. The tree thus formed is used to find the longest sequence of increasing 
or decreasing values. A sample input is given below:

Output file format: The output file contains length of longest ordering sequence from BST, and 
second line contains node values comma separated. 

*/

#include "bst.h"
using namespace std;

int main(void)
{

    std::ifstream InFile("P1_input.txt");

    bst<int> *tree = new bst<int>();
    std::string buffer;

    while (std::getline(InFile, buffer))
        tree->insert(std::stoi(buffer));

    tree->traverseTree();

    // std::cout << "Recursive: \n";
    // tree->preorderTraversal();
    // tree->inorderTraversal();
    // tree->postorderTraversal();

    // std::cout << "\nIterative: \n";
    // tree->preorderTraversal_Iter();
    // tree->inorderTraversal_Iter();
    // tree->postorderTraversal_Iter();

    // tree->bfs();

    // std::vector<int> maxVect = tree->findmax(maxVect),
    //                  minVect = tree->findmin(minVect);

    // for (const auto &x : maxVect)
    //     std::cout << x << " ";
    // std::cout << "\n";
    // for (const auto &x : minVect)
    //     std::cout << x << " ";
    // std::cout << "\n";

    return 0;
}