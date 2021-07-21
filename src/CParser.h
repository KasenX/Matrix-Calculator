#ifndef MATRIXCALCULATOR_CPARSER_H
#define MATRIXCALCULATOR_CPARSER_H

#include "CDatabase.h"
#include "Operation/Op.h"
#include "Enums/EState.h"

#include <memory>
#include <vector>
#include <string>

class CParser {
public:

    /**
     * Parse one line from cin and call requested command or matrix operation.
     * @return state: RUN - on success, HELP - on help calling, QUIT - on quit calling, UNKNOWN - on unrecognized input
     */
    EState parseInput ();

    /**
     * Determine if the matrix name is allowed.
     * Matrix name cannot start with non-alpha character, contain delimiter character or be equal to any of the reserved words.
     * @param matrix name
     * @return true if the name is allowed, false otherwise
     */
    static bool checkName (const std::string & name);

private:

    CDatabase m_Database; // Stored matrices

    /**
     * Read and tokenize one line from cin, delimiters are: white-space characters, =, +, -, *, [, ], (, ) and ,.
     * Delimiters are also included in tokens except the whitespaces.
     * @return vector of tokens including delimiters (except whitespaces)
     */
    static std::vector<std::string> tokenizeLine ();

    /**
     * Based on the tokens return requested operation.
     * Throws a parsing exception if the name of the matrix is not allowed.
     * Throws an out of range exception if the required matrix does not exist.
     * @param tokens
     * @return requested operation or nullptr if no operation with proper syntax recognized
     */
    std::unique_ptr<Op> readOperation (const std::vector<std::string> & tokens) const;

    /**
     * Scan the elements of a matrix with given rows and columns. Scanning takes place in rows and is eventually
     * repeated on bad input.
     * Throws a parsing exception if the name of the matrix is not allowed OR if rows or columns are not natural numbers.
     * @param tokens
     * @return state: RUN - on success, UNKNOWN - more, less or certain tokens expected OR identity matrix is not square
     */
    EState scanMatrix (const std::vector<std::string> & tokens);

    /**
     * Based on the tokens prints elements of the given matrix or display all matrices in the database.
     * Throws an out of range exception if the required matrix does not exist.
     * @param tokens
     * @return state: RUN - on success, UNKNOWN - more or less tokens expected (expects 2 tokens)
     */
    EState printMatrix (const std::vector<std::string> & tokens) const;

    /**
     * Based on the tokens deletes the given matrix or all matrices from the database.
     * @param tokens
     * @return state: RUN - on success, UNKNOWN - more or less tokens expected (expects 2 tokens)
     */
    EState delMatrix (const std::vector<std::string> & tokens);

    /**
     * Prints the determinant of the given matrix.
     * Throws an out of range exception if the required matrix does not exist.
     * @param tokens
     * @return state: RUN - on success, UNKNOWN - more or less tokens expected (expects 2 tokens)
     */
    EState deterMatrix (const std::vector<std::string> & tokens) const;

    /**
     * Prints the rank of the given matrix.
     * Throws an out of range exception if the required matrix does not exist.
     * @param tokens
     * @return state: RUN - on success, UNKNOWN - more or less tokens expected (expects 2 tokens)
     */
    EState rankMatrix (const std::vector<std::string> & tokens) const;

    /**
     * Based on the tokens saves the given matrix or saves all the matrices in the database.
     * Save file is either given in tokens or auto-generated.
     * Throws an out of range exception if the required matrix does not exist.
     * @param tokens
     * @return state: RUN - on success, UNKNOWN - more or less tokens expected (expects 2 or 3 tokens)
     */
    EState saveMatrix (const std::vector<std::string> & tokens) const;

    /**
     * Load all matrices to the database from the given file.
     * @param tokens
     * @return state: RUN - on success, UNKNOWN - more or less tokens expected (expects 2 tokens)
     */
    EState loadMatrix (const std::vector<std::string> & tokens);

    /**
    * Decides which type of matrix is more advantageous (more than half of the elements are zero -> Sparse, else Dense)
    * and returns its instance.
    * @param elements of the matrix
    * @return CMatrix, either CDense or CSparse
    */
    static std::shared_ptr<CMatrix> buildMatrix (const std::vector<std::vector<double>> & elements) ;
};


#endif //MATRIXCALCULATOR_CPARSER_H
