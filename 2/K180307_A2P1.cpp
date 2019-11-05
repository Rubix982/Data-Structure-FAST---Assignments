/*
Polynomial equations are equations that have multiple terms made up of numbers and variables.
You are required to design a solution in order to represnet polynomial for computer manipulation

The main requirement is to make use of linekd list to hold each term of the polynomial for example

Linked List1: 4x^7+2x^6+4x^3+3=0
Linked List2: 2x^8+3x^3-2=0
Resultant Linked List: 2x^7+4x^7+2x^6+2x^3+4x^2+1=0

For above given lsit1 the firs node of th elist1 conttains a strucute of co-efficients=+4, Base = X,
and exponent = 7, and int he very same fashion rest of the terms are stored. The polynomial linked list is
always stored in descending order of power and in single variable ( BASE );

a): You are required to write a program that can add two instances o this lists and store its
    result in another list. Within the inpout file each list equation is entered. You have to
    read each equation and form a linked list of them first; then form resultant linked list by 
    adding the equations up.

b):  Differentiation is the action of computing a derivative. The derivative of a funciton y = f(x)
    of a variable x is a measure of the rate at which the value y of the function changes with respect
    to the change of the variable x. Next you are required to calculate the derivative of the resultant
    linked list created in the above part. The output file created in above part will be used as input
    file to read off for this part.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>

// * Author: Saif Ul Islam
// * Last Edited: 26th October, 2019
// * Assignment# 2

// ! Program can handle any number of equations entered given as input, and
// ! can perform additions on all of them

// Struct polynomial to define the coeff, exponent for a term
struct Polynomial {
    int Coefficient;
    int Exponent;

    // Constructor for polynomial
    Polynomial(int Coefficient, int Exponent)
        :  Coefficient(Coefficient), Exponent(Exponent) {} 
};

// Node to define each term, and to link it back and forth using DLL
struct PolynomialNode : public Polynomial {
    PolynomialNode * next;
    PolynomialNode * prev;

    // Constructor for PolynomialNode
    PolynomialNode(int Coefficient, int Exponent, PolynomialNode * prev = nullptr, PolynomialNode * next = nullptr)
        : Polynomial(Coefficient, Exponent), prev(prev), next(next) {}
};

// Helper function, to easily intialize an object
PolynomialNode * newTerm(int Coefficient, int Exponent, PolynomialNode * prev = nullptr, PolynomialNode * next = nullptr) {
    return new PolynomialNode(Coefficient, Exponent, prev, next);
}

// class DoublyLinkedList implements PolynomialNode interface
class DoublyLinkedList : public PolynomialNode {

public:

    // Constructor for DLL
    DoublyLinkedList()
    :   PolynomialNode(0, 0) {
        head = tail = nullptr;
    }

    // Constructor that initializes 'numOfTerms' number of PolynomialNodes
    DoublyLinkedList(int numOfTerms)
    :   PolynomialNode(0, 0) {
        head = tail = nullptr;

        // For loop, inserts terms in descending nomral, as is standard form
        for ( int i = numOfTerms; i >= 0 ; --i )
            push_back(0, i);
    }

    // Initialize DLL with a collection of coeffs, exponenets in the contained
    // form of a tuple
    DoublyLinkedList(std::vector<std::tuple<int, int>> list)
    :   PolynomialNode(0, 0) {
        head = tail = nullptr;

        // ... Listing through each item in the list of tuples ...
        for ( const auto & term : list )
            push_back(std::get<0>(term), std::get<1>(term));
    }

    // ... Insert polynomials, later on after object is created ... 
    // created just in case RAII - Resouce Acquisition Is Initilization 
    // isn't followed
    void insertPolynomial(std::vector<std::tuple<int, int>> list) {
        for ( const auto & term : list )
            push_back(std::get<0>(term), std::get<1>(term));
    }

    // Push to the front of the DLL
    void push_front(int coefficient, int exponent) {
        if ( head == nullptr ) {
            head = tail = newTerm(coefficient, exponent);
        } else {
            head = newTerm(coefficient, exponent, nullptr, head);
        }
    }

    // Push a polynomial term at th end of the DLL
    void push_back(int coefficient, int exponent) {
        if ( tail == nullptr ) {
            head = tail = newTerm(coefficient, exponent);
        } else {
            tail = newTerm(coefficient, exponent, tail, nullptr);
            tail->prev->next = tail;
        }
    }

    // Remove from the front of the DLL the PolynomialNode, and return Polynomial Object
    Polynomial pop_front() {
        Polynomial element(head->Coefficient, head->Exponent);
        if ( head == tail ) {   //  Only one node
            delete tail;
            head = tail = nullptr;
        } else {
            head = head->next;
            delete head->prev;
            head->prev = nullptr;
        }
        return element;
    }

    // Remove from the back of the DLL the PolynomialNode, and return Polynomial Object
    Polynomial pop_back() {
        Polynomial element(tail->Coefficient, tail->Exponent);
        if ( head == tail ) {
            delete head;
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            delete tail->next;
            tail->next = nullptr;
        }
        return element;
    }

    // Show DLL normally
    void display(void) const {
        PolynomialNode * ptr = head;

        while ( ptr->next != nullptr ) {
            if ( ptr->Coefficient != 0) {
                std::cout << ptr->Coefficient << "X^" << ptr->Exponent << " -> ";  
            }
            ptr = ptr->next;
        }
        std::cout << ptr->Coefficient << "X^" << ptr->Exponent;  
        std::cout << "\n";
    }

    // Output DLL contents to a file, in the required format
    void displayOutput(std::ofstream & OutFile) const {
        PolynomialNode * ptr = head;

        while ( ptr != nullptr ) {
            if ( ptr->Coefficient != 0) {
                if ( ptr->Coefficient == 1 )
                    OutFile << "+X^" << ptr->Exponent;  
                else if ( ptr->Coefficient == -1 )
                    OutFile << "-X^" << ptr->Exponent;
                else if ( ptr->Coefficient > 0 && ptr->prev != nullptr )
                    OutFile << "+" << ptr->Coefficient << "X^" << ptr->Exponent;
                else
                    OutFile << ptr->Coefficient << "X^" << ptr->Exponent;  
            }
            ptr = ptr->next;
        }

        // ... explicitly add =0 at the end of the term
        OutFile << "=0";
    }

    // ... returning size of the DLL ...
    size_t getSize(void) const {
        size_t size = 0;
        PolynomialNode * ptr = head;

        while ( ptr ) {
            ptr = ptr->next;
            size++;
        }

        return size;
    }

    // Adds two DLLs together, and returns an address to a new DLL that is the sum of the two
    DoublyLinkedList * operator+(const DoublyLinkedList other) {
        DoublyLinkedList * temp = new DoublyLinkedList;

        PolynomialNode * hold = this->head;

        for ( PolynomialNode * ptr = other.head ; ptr != nullptr ; ptr = ptr->next ) {
            int exponent = ptr->Exponent;
            int coefficient = ptr->Coefficient;

            for ( PolynomialNode * ptr2 = hold ; ptr2 != nullptr ; ptr2 = ptr2->next ) {
                if ( ptr2->Exponent == exponent ) {

                    if ( hold->next != nullptr ) {
                        hold = hold->next;
                    } else {
                        hold = nullptr;
                    }

                    coefficient += ptr2->Coefficient;
                    temp->push_back(coefficient, exponent);
                    break;
                }

                if ( ptr2->Exponent > exponent ) {

                    temp->push_back(ptr2->Coefficient, ptr2->Exponent);

                    if ( hold->next != nullptr )
                        hold = hold->next;
                    else
                        hold = nullptr;
                }

                if ( ptr2->Exponent < exponent ) 
                    temp->push_back(coefficient, exponent);
            }
        }
        return temp;
    }

    // Returns a pointer to the object, after performing derivation on it
    DoublyLinkedList * getDerivate(void) {
        for ( PolynomialNode * ptr = this->head ; ptr != nullptr ; ptr = ptr->next ) {
            if ( ptr->Exponent == 0 ) {
                pop_back();
                break;
            }
            
            int exponent = ptr->Exponent;
            ptr->Coefficient = ptr->Coefficient * exponent;
            ptr->Exponent--;
        }

        return this;
    }


private:

    // private members that only contain addresses for the head and the tail
    PolynomialNode * head, * tail;
};

int main(void) {

    // Open the three required files 
    std::ifstream InFile("P1_input.txt");
    std::ofstream OutFile_Sum("P1_output_sum.txt");
    std::ofstream OutFile_Derivative("P1_output_derivate.txt");

    // Counter to store total number of equations entered as input
    int counter = 0;

    // Buffer, to hold the equation being picked from the input file
    std::string buffer;
    while ( std::getline(InFile, buffer) )
        counter++;
    
    // Total stores the total number of equations that are fed as input
    size_t total = counter;

    // Clears, and resets the pointer to the input file to the absolute start
    InFile.clear();
    InFile.seekg(0, std::ios::beg);

    // Creates a tuple for storing the coefficient, and the exponent. Has size 'counter'
    std::vector<std::tuple<int, int>> Values[counter];

    // Stores the equations themselves
    std::vector<std::string> Equations[counter];

    // ... iterate through all the equations ...
    for ( auto & equation : Equations ) {

        // ... get the required equation from the input file ...
        std::getline(InFile, buffer);

        // ... setting the counter to 0 ...
        // ... using the counter because the equation is broken up according to symbols ...
        // ... the first term can be extracted only when we see the second term ...
        counter = 0;

        // prev, and pos, to extract the substring
        size_t prev = 0, pos = 0;

        // Iterating through the equation ...
        for ( const auto & x : buffer ) {

            // if '+', '-', '=' is encountered ...
            if ( ( x == '+' || x == '-' || x == '=' ) && counter != 0 ) {
                
                // Extract the term from the given equation
                equation.push_back(buffer.substr(prev, pos - prev));
                
                // Setting iterators correctly
                prev = pos;
            }

            // Incrementing counter, pos itself;
            ++counter;
            ++pos;
        }

        // If there was a '-' at the start, prepend a '+' to the extracted equation, else do nothing
        buffer[0] != '-' ? equation[0] = '+' + equation[0] : equation[0] = equation[0];    
        equation.shrink_to_fit();
    }

    // ... Start the counter to keep a track of the equations ...
    counter = 0;

    // ... using a for range loop, through the vector of all the equations ...
    // ... for each equation in equations ...
    for ( const auto & equation : Equations ) {

        // ... for each term in the equation ...
        for ( const auto & term : equation ) {

            // ... first initialize some variables ...
            // ... add a check to see if the first term is negative or not ...
            int coefficient = 0, exponent = 0, check = ( term[1] == 'X' ? 1 : 2 );
        
            // ... if it is negative ...
            if ( check == 1 ) {
                // ... convert number to string ...
                coefficient = std::stoi(term[0] + std::string("1") );
            } else {
                // ... else extract the required sub string
                coefficient = std::stoi(term.substr(0, 2 ));
            }    

            // ... if the length of the term is only 2, that means it is a coefficient, thus let exp be 0 ...
            if ( term.length() == 2 ) 
                exponent = 0;
            else 
                // ... or convert the exp to an int, by subtracting from character '0' ...
                exponent = term[term.length() - 1] - '0';

            // insert into tuple as coefficient, and exponenet
            Values[counter].push_back(std::make_tuple(coefficient, exponent));
        }

        // ... finally, increment the counter ...
        counter++;
    }

    // ... make a array of DLLS, for each equation in input file
    DoublyLinkedList list[total];

    counter = 0;
    // ... using for range loop to insert the values ...
    for ( const auto & tuple : Values ) {
        list[counter].insertPolynomial(tuple);
        counter++;
    }

    // ... add to equations together, and get back the address of newly created DLL, assign it to sum ...
    DoublyLinkedList * sum = list[0] + list[1];

    // .. display sum ...
    sum->displayOutput(OutFile_Sum);

    // ... get back derivate of 'sum' in the DLL 'derivative'
    DoublyLinkedList * derivative = sum->getDerivate();

    // ... and finally use displayOutput to write to output file in the required format ...
    derivative->displayOutput(OutFile_Derivative);

    return 0;    
}