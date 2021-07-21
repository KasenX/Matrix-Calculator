#ifndef MATRIXCALCULATOR_CMATRIX_H
#define MATRIXCALCULATOR_CMATRIX_H

#include <memory>
#include <fstream>
#include <vector>

class CMatrix {
public:

    CMatrix (size_t rows, size_t columns);

    virtual ~CMatrix () = default;

    /**
     * @return number of rows
     */
    size_t rows () const;

    /**
     * @return number of columns
     */
    size_t columns () const;

    /**
     * Returns an element at given indexes.
     * @param i
     * @param j
     * @return value at indexes i, j
     */
    virtual double at (size_t i, size_t j) const = 0;

    /**
     * Prints the elements of the matrix.
     */
    void print () const;

    /**
     * Count determinant of the square matrix using recursion, if the matrix is not square throws a MatrixException.
     * @return determinant of the matrix
     */
    virtual double determinant () const;

    /**
     * Count rank of the matrix using Gaussian elimination.
     * @return rank of the matrix
     */
    virtual size_t rank () const;

    /**
     * Creates a deep copy of the matrix.
     * @return copy of the matrix in shared_ptr
     */
    virtual std::shared_ptr<CMatrix> clone () const = 0;

    /**
     * Stores matrix type and its elements into a file.
     * @param output file
     */
    virtual void toFile (std::ofstream & file) const = 0;

protected:

    const size_t m_Rows;
    const size_t m_Columns;

private:

    /**
     * Recursive function counting the determinant of the matrix.
     * Calculation by development of the first line.
     * @param matrix
     * @param n size of the matrix
     * @return determinant of the matrix
     */
    double detRec (std::vector<std::vector<double>> matrix, size_t n) const;
};

#endif //MATRIXCALCULATOR_CMATRIX_H
