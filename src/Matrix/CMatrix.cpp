#include "CMatrix.h"
#include "../Exceptions/MatrixException.h"
#include "../Operation/OpGEM.h"

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

CMatrix::CMatrix(size_t rows, size_t columns)
: m_Rows(rows), m_Columns(columns)
{}

//======================================================================================================================

size_t CMatrix::rows() const {
    return m_Rows;
}

//======================================================================================================================

size_t CMatrix::columns() const {
    return m_Columns;
}

//======================================================================================================================

void CMatrix::print() const {
    for (size_t i = 0; i < rows(); ++i) {
        for (size_t j = 0; j < columns(); ++j) {
            cout << fixed << setprecision(3) << (at(i, j) < 0.001 ? abs(at(i, j)) : at(i, j)) << ' ';
        }
        cout << '\n';
    }
    cout.flush();
}

//======================================================================================================================

double CMatrix::determinant() const {
    // The matrix must be square in order to count the determinant
    if (rows() != columns())
        throw MatrixException("Only the determinant of the SQUARE matrix can be calculated.");

    vector<vector<double>> matrix(rows(), vector<double>(columns()));
    for (size_t i = 0; i < rows(); ++i) {
        for (size_t j = 0; j < columns(); ++j)
            matrix[i][j] = at(i, j);
    }

    return detRec(matrix, rows());
}

//======================================================================================================================

double CMatrix::detRec(vector<vector<double>> matrix, size_t n) const {
    // Special case
    if (n == 1)
        return matrix[0][0];
    // End of recursion
    if (n == 2)
        return matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];

    vector<vector<double>> submatrix(n, vector<double>(n));
    double det = 0;

    for (size_t x = 0; x < n; ++x) {
        size_t subi = 0;
        for (size_t i = 1; i < n; ++i) {
            size_t subj = 0;
            for (size_t j = 0; j < n; ++j) {
                if (j == x)
                    continue;
                submatrix[subi][subj] = matrix[i][j];
                subj++;
            }
            subi++;
        }
        det += pow(-1, x) * matrix[0][x] * detRec(submatrix, n - 1);
    }
    return det;
}

//======================================================================================================================

size_t CMatrix::rank() const {
    // Get the elements of the matrix in the upper stepped shape
    vector<vector<double>> el = OpGEM(clone()).perform();
    // Count the number of non-zero rows
    for (int i = (int) rows() - 1; i >= 0; --i) {
        for (size_t j = 0; j < columns(); ++j)
            if (el[i][j] != 0)
                return i + 1;
    }
    return 0;
}
