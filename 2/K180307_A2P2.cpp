/*
A palindrome is a word, phrase, number of sequence of words that reads the same backwards
as forwards. Punctuation and spaces betweent he words or lettering is allowed. Hence, there are
multiple categories of Palindromes. For example Single Word Palindrome like MAdam, Multiple
Word Palindromes like: "Step on no pets" and "was it a car I saw" Numeber Palindromes like 191
and 123321. Given an integer array of some content, an array palindrome is defined as the subarray
whose contents concatenated form a palindrome. For example, A[5] = {1, 21, 12, 1, 9} contains a 
palindrome from index 0 - 3, by seeing 121121 together. Similarly, we can have a palindrome in
a linked list, example given below:

    Linked List L1(Head) -> 12451 -> 11342 -> 11211 -> 4318 -> 12 -> 1 -> X

You need to find the largest such palindrome possible in the context of te linked list, assume
the singly linked list is used to store content. Your program should decide about the longest possible
palindrome
*/

#include <fstream>
#include <string>
#include <iostream>

// * Author: Saif Ul Islam
// * Last Edited: 26th October, 2019
// * Assignment# 2

// typdef'ed since it was too long to write
typedef unsigned long long ull;

// Make struct to store contents for nodes
struct Node {
    ull Data;
    Node * nxt;

    // Constructor for nodes
    Node(ull Data, Node * nxt = nullptr)
        :   Data(Data), nxt(nxt) {}
};

// Class for the actual Singly Linked List, inherits from Node
class SLL : public Node {

public:

    // Default constuctor, sets everything to default ...
    SLL()   :   head(nullptr), tail(nullptr), Node(0) {}

    // ... takes input of some data, initiates a node pointer with that data ...
    SLL(ull Data) : head(nullptr), tail(nullptr), Node(Data) {}

    // ... takes input of data, as well as a next pointer for the head of another SLL ...
    SLL(ull Data, Node * head) :    head(nullptr), tail(nullptr), Node(Data, head) {}

    // ... adds to head ...
    void push_front(int Data) {
        if ( head == nullptr ) 
            head = tail = new Node(Data);
        else 
            head = new Node(Data, head);
    }

    // ... adds to tail ...
    void push_back(int Data) {
        if ( tail == nullptr ) 
            head = tail = new Node(Data);
        else {
            tail->nxt = new Node(Data, nullptr);
            tail = tail->nxt;
        }
    }

    // ... removes from the front ...
    ull pop_front(void) {
        ull el = -9999;
        if ( head == nullptr ) {
            return el;
        } else {
            Node * ptr = head;
            el = ptr->Data;
            head = head->nxt;
            delete ptr;
            ptr = nullptr;
        }
        return el;
    }

    // ... removes from the back ...
    ull pop_back() {
        ull el = -9999;
        if ( tail == nullptr ) {
            return el;
        } else {
            Node * ptr = head;

            for ( ; ptr->nxt != tail ; ptr = ptr->nxt )
                ;

            el = tail->Data;
            tail = ptr;
            ptr = ptr->nxt;
            tail->nxt = nullptr;
            delete ptr;
            ptr = nullptr;
        }
        return el;
    }

    // ... displays the singly linked list
    void display(void) const {

        Node * ptr = head ;

        std::cout << ptr->Data;
        while (  ptr = ptr->nxt, ptr != nullptr ) 
            std::cout << " -> " << ptr->Data;
        std::cout << "\n";
    }

    // ... takes the data of all the nodes, concatenates them into a string, and returns that string
    std::string to_string(void) const {
        std::string hold = "";

        Node * ptr = head ;

        while ( hold += std::to_string(ptr->Data), ptr = ptr->nxt, ptr != nullptr ) ;
        
        return hold;
    }

    // ... finds the palindromic sequence, that is a sub-string of the data of all the nodes in the SLL
    std::string getPalindrome(const std::string & checkPalindrome) {
        
        // strings that hold the max_string that might occur, curr_string holds 
        // the current, temporary string
        std::string max_string = "", curr_string = "";

        // ... Redundant to check for the first and the last element ...
        for ( int i = 1 ; i < checkPalindrome.length() - 1; ++i ) {
            
            // Assuming string given has odd number of characters, check 
            // for a possible window, starting the element previous to our 
            // selected index, and ending at the the next immediate value
            curr_string = expandWindow(checkPalindrome, i - 1, i + 1);

            // If size of the window is greater than the already existing 
            // max_string, set that as the max_string
            if ( curr_string.length() > max_string.length() )
                max_string = curr_string;

            // Assuming string given has even number of characters, start by checking for
            // the element selected, and the immediately previous element 
            curr_string = expandWindow(checkPalindrome, i - 1, i);

            // Same condition, as above
            if ( curr_string.length() > max_string.length() )
                max_string = curr_string;
        }

        // returned the max string obtained
        return max_string;
    }

private:

    // Recursive function to expand for window size, checking for palindromes ...
    std::string expandWindow(std::string str, int start, int end) {

        // bound checking, a well as checking if the char at index 'start' and 
        // index 'end' are equal
        if ( start >= 0 && end < str.length() && ( str[start] == str[end]) )
            // if true, call again, with start--, and end++
            return expandWindow(str, start - 1, end + 1);

        // else just return the sub string to be obtained
        return str.substr(start + 1, end - start - 1);
    }

    // Private data members to keep track of head and tail
    Node * head, * tail;
};

int main(void) {

    // File handlers for IO format
    std::ifstream InFile("P2_input.txt");
    std::ofstream OutFile("P2_output.txt");

    // Gets back total sizes
    int totalSize;
    InFile >> totalSize;

    // ... create a new SLL ...
    SLL list;

    // ... start a loop, uptil the total size ...
    for ( int i = 0 ; i < totalSize ; ++i ) {
        // ... take input that value ...
        ull temp;
        InFile >> temp;

        // ... and add to tail of the SLL ...
        list.push_back(temp); 
    }
    
    // Output the palindromic sub-part of the SLL
    OutFile << list.getPalindrome(list.to_string());

    return 0;
}