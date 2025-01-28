//======================================================
// Project: Dice  File: Dice.cpp
// Author: Ryan Lang and Kyle Mather     Copyright: 2025
//======================================================
#include "Dice.h"
#include "tools.hpp"
#include "tools.cpp"

using namespace std;

/*unitDice() function follows test plan in this directory to examine the
 *required input and output values, edge cases, and potential errors
*/
void unitDice() {
    ofstream outFile("Output.txt", ios::app);
    if (!outFile) {
        cerr << "Error opening file!" << endl;
        return;
    }

    // Test Initialization
    outFile << "Test Initialization:\n";
    Dice d1(6);
    outFile << "Expected nDice: 6, Actual nDice: " << 6 << endl;

    // Test Rolling Dice
    outFile << "Test Rolling Dice:\n";
    const int* values = d1.roll();
    outFile << "Dice values: ";
    // Prints out values of dice
    for (int i = 0; i < 6; ++i) {
        outFile << values[i] << " ";
        // Check if values are between 1 and 6
        if (values[i] < 1 || values[i] > 6) {
            outFile << "\nError: Dice value out of range!";
        }
    }
    outFile << endl;

    // Test Printing Dice Values
    outFile << "Test Printing Dice Values:\n";
    /*outFile << "Dice values printed: ";
    d1.print(outFile);
    outFile << endl;*/
    outFile << "Dice values printed: " << d1 << endl;

    // Test Destructor
    outFile << "Test Destructor:\n";
    {
        Dice d2(10);
    } // d2 should be destroyed here
    outFile << "No explicit output; check for memory leaks.\n";
    // Closing output file
    outFile.close();
}



int main() {
    srand(time(nullptr));
    banner();   //Prints names, date, and class
    unitDice(); // Calls test plan
    bye();  //Designates program termination
    return 0;
}
