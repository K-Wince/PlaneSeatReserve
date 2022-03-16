// MP3.cpp : 11.11.2021 : Kaden Wince
// Description: This program takes a continuous loop of user input and uses the input to reserve seats on
// an CRJ 200 Plane.

#include <iostream>
#include <string>
using namespace std;

// Global Variables
const int COLUMNS = 4;
const int ROWS = 13;

// Function Prototypes
int findRowIndex(int thisRow);
int findSeatIndex(char thisSeat);
void displaySeatColumn(char seats[][ROWS], int column);
bool checkSeatInput(char seats[][ROWS], int row, char col);
bool checkSeatTaken(char seats[][ROWS], int row, char col);

int main() {
    // Declaration of 2D array for plane
    char seatingChart[COLUMNS][ROWS] = {
        {'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', ' '},
        {'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', ' '},
        {'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B'},
        {'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A'}
    };

    // Count of Seats
    int seatCount = 50;

    // Print the initial seating chart
    displaySeatColumn(seatingChart, 0);
    displaySeatColumn(seatingChart, 1);
    displaySeatColumn(seatingChart, 2);
    displaySeatColumn(seatingChart, 3);
    cout << endl;

    // Loop through until the program finishes
    while (true) {
        // Variables
        string seat = "";
        int row = -99;
        char col = 'E';
        // Get the info for the seat being reserved
        bool inputDone = false;
        do {
            cout << "Enter a seat or Q to quit: ";
            cin >> seat;
            // Check if they want to quit
            if (seat == "Q" or seat == "q") {
                return 0;
            }
            // Get the row and column if its a length of two
            if (seat.length() == 2) {
                row = seat[0] - 48;
                col = seat[1];
            }
            // Get the row and column if its a length of three
            else if (seat.length() == 3) {
                row = (seat[0] - 48) * 10 + (seat[1] - 48);
                col = seat[2];
            }
            // Check the input on whether its correct or if seat is taken
            inputDone = checkSeatInput(seatingChart, row, col);
            if (!inputDone) {
                cout << "Sorry, no such seat exists on the CRJ 200.\n";
            }
            if (inputDone) {
                bool seatTaken = checkSeatTaken(seatingChart, findRowIndex(row), findSeatIndex(col));
                // If the seat is taken then say seat is taken and repeat
                if (seatTaken) {
                    cout << "Sorry, that seat is already occupied.\n";
                    inputDone = false;
                }
                // If the seat is not taken then reserve the seat
                if (!seatTaken) {
                    seatingChart[findSeatIndex(col)][findRowIndex(row)] = 'X';
                    seatCount--;
                }
            }
        } while (!inputDone);
        // Print out the airplane chart
        cout << endl;
        displaySeatColumn(seatingChart, 0);
        displaySeatColumn(seatingChart, 1);
        displaySeatColumn(seatingChart, 2);
        displaySeatColumn(seatingChart, 3);
        cout << endl;
        // If seat count = 0 then end program and say all seats are taken
        if (seatCount == 0) {
            cout << "Sorry, the plane is full.";
            return 0;
        }
    }
}

// findRowIndex: given user input, returns appropriate row index into arrays. 
// @param thisRow - integer indicating row selected by the user 
// @return appropriate index into 2-D array if the specified row is valid, ERROR otherwise 
int findRowIndex(int thisRow) {
    if (thisRow <= 13 && thisRow >= 1) {
        return thisRow - 1;
    }
    return -99;
}

// findSeatIndex: given user input, returns appropriate column index into seating chart array. 
// @param thisSeat - character indicating selected seat within row 
// @return appropriate index into 2-D array if the specified seat is valid, ERROR otherwise 
int findSeatIndex(char thisSeat) {
    switch(thisSeat){
    case 'A': return 3; break;
    case 'B': return 2; break;
    case 'C': return 1; break;
    case 'D': return 0; break;
    }
    return -99;
}

// displaySeatColumn: given a 2-D mapping of the seating chart in the form [columns][rows], 
// will print out a "column" of seats on one row of output (i.e., seat 'A' for all rows in the plane) 
// @param seats - reference to a 2-D character array 
// @param column - reference to which column of seats to display 
void displaySeatColumn(char seats[][ROWS], int column) {
    for (int i = 0; i < ROWS; i++) {
        cout << seats[column][i] << " ";
    }
    if (column == 1) {
        cout << "\n                  1 1 1 1\n";
        cout << "1 2 3 4 5 6 7 8 9 0 1 2 3\n";
    }
    cout << endl;
}

// checkSeatInput: given userInput, the function will check the input to make sure its valid seat on the plane
// @param seats - reference to a 2-D character array
// @param row - reference to which row the user inputted
// @param col - reference to which column the user inputted
// @return bool - returns true if userInput is a seat on the plane
bool checkSeatInput(char seats[][ROWS], int row, char col) {
    int rowCheck = findRowIndex(row);
    int colCheck = findSeatIndex(col);
    if (rowCheck == -99 or colCheck == -99) {
        return false;
    }
    if (colCheck == 0 && rowCheck == 12) {
        return false;
    }
    if (colCheck == 1 && rowCheck == 12) {
        return false;
    }
    return true;
}

// checkSeatTaken: given a proper seat on the plane, function will check if the seat is taken or not
// @param seats - reference to a 2-D character array
// @param row - reference to which row the user inputted
// @param col - reference to which column the user inputted
// @return bool - returns true if the seat on the plane is taken
bool checkSeatTaken(char seats[][ROWS], int row, char col) {
    if (seats[col][row] == 'X') {
        return true;
    }
    return false;
}
