#ifndef MATRIXCALCULATOR_CAPPLICATION_H
#define MATRIXCALCULATOR_CAPPLICATION_H

#include "CParser.h"

class CApplication {
public:

    /**
     * The main application loop.
     */
    void run ();

private:

    CParser m_Parser; // Parser used for parsing all input

    /**
     * Prints a welcome text.
     */
    static void printIntro ();

    /**
     * Prints a farewell text.
     */
    static void printOutro ();

    /**
     * Prints calculator help (all commands and calculator syntax).
     */
    static void printHelp ();
};

#endif //MATRIXCALCULATOR_CAPPLICATION_H
