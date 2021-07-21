#include "CApplication.h"

#include <iostream>

using namespace std;

void CApplication::run() {
    printIntro();
    EState state = EState::RUN;
    while (true) {
        switch (state) {
            case EState::RUN:
                state = m_Parser.parseInput();
                break;
            case EState::HELP:
                printHelp();
                state = EState::RUN;
                break;
            case EState::UNKNOWN:
                cout << "Unknown command, try: help." << endl;
                state = EState::RUN;
                break;
            case EState::QUIT:
                printOutro();
                return;
        }
    }
}

//======================================================================================================================

void CApplication::printIntro() {
    cout << ">>> Welcome to MATRIX CALCULATOR <<<" << endl;
}

//======================================================================================================================

void CApplication::printOutro() {
    cout << ">>> Thank you for using MATRIX CALCULATOR <<<" << endl;
}

//======================================================================================================================

void CApplication::printHelp() {
    cout << "Matrix calculator manual." << endl << endl;

    cout << "All commands and matrices names are case INSENSITIVE." << endl << endl;

    cout << "Matrix scanning:" << endl;
    cout << "SCAN X[3][3] (starts scanning matrix of size 3x3 and name X)" << endl;
    cout << "SCAN X[3][3] 1 (identity matrix of size 3x3 and name X)" << endl << endl;

    cout << "Matrix names:" << endl;
    cout << "Matrix names must begin with alpha character." << endl;
    cout << "The name must not be equal to the calculator keyword"
            "and must not contain special characters used by calculator" << endl << endl;

    cout << "Matrix operations (with given matrices X, Y, Z):" << endl;
    cout << "X = Y + Z" << endl;
    cout << "X = Y - Z" << endl;
    cout << "X = Y * Z" << endl;
    cout << "X = scalar * Z" << endl;
    cout << "X = TRANSPOSITION Z / X = TRANS Z" << endl;
    cout << "X = INVERSE Z / X = INV Z (only for square and regular matrices)" << endl;
    cout << "X = GEM Z" << endl;
    cout << "X = MERGE Y Z TOP" << endl;
    cout << "X = MERGE Y Z SIDE" << endl;
    cout << "X = SPLIT Z [3][3] (3,1) (we want matrix [3][3] from position (3,1))" << endl << endl;

    cout << "Matrix functions:" << endl;
    cout << "DETERMINANT X / DET X" << endl;
    cout << "RANK X" << endl << endl;

    cout << "Working with matrix database:" << endl;
    cout << "DELETE X (deletes matrix named X)" << endl;
    cout << "DELETE ALL (deletes all matrices from the database)" << endl;
    cout << "PRINT X (prints matrix named X)" << endl;
    cout << "PRINT ALL (displays name of all matrices in the database)" << endl;
    cout << "SAVE X [path] (saves matrix named X, file is either auto-generated or given in parameter)" << endl;
    cout << "SAVE ALL [path] (saves all matrices)" << endl;
    cout << "LOAD <path> (load matrices from given file)" << endl << endl;

    cout << "Termination of application:" << endl;
    cout << "QUIT" << endl;
}
