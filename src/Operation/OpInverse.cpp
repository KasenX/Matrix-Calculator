#include "OpInverse.h"
#include "OpMergeSide.h"
#include "../Matrix/CIdentity.h"
#include "../Exceptions/MatrixException.h"

#include <vector>

using namespace std;

OpInverse::OpInverse(std::shared_ptr <CMatrix> left)
: Op(std::move(left))
{}

//======================================================================================================================

std::vector<std::vector<double>> OpInverse::perform() const {
    if (lhs->rows() != lhs->columns() || lhs->determinant() == 0)
        throw MatrixException("Inverse matrix does not exist.");

    // Merge matrix with the identity matrix
    size_t rows = lhs->rows();
    size_t cols = 2 * lhs->columns();
    vector<vector<double>> el = OpMergeSide(lhs, make_shared<CIdentity>(rows)).perform();

    // Elimination - zeros below pivots
    for (size_t i = 0; i < rows; ++i) { 
        // Pivot equal to zero -> swap with another row whose pivot is not zero
        if (el[i][i] == 0) {
            for (size_t k = i + 1; k < rows; ++k)
                if (el[k][i] != 0) {
                    swap_rows(el, i, k);
                    break;
                }
        }
        // Divide the row by the pivot
        double div = el[i][i];
        for (size_t j = 0; j < cols; ++j)
            el[i][j] /= div;
        // Eliminate rows below
        for (size_t k = i + 1; k < rows; ++k) {
            double mul = el[k][i];
            for (size_t j = 0; j < cols; ++j)
                el[k][j] -= mul * el[i][j];
        }
    }

    // Elimination - zeros above pivots
    for (size_t i = rows - 1; i > 0; --i) {
        for (int k = (int) i - 1; k >= 0; --k) {
            double mul = el[k][i];
            for (size_t j = 0; j < cols; ++j)
                el[k][j] -= mul * el[i][j];
        }
    }

    // Extract the result
    vector<vector<double>> res(rows);
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = cols / 2; j < cols; ++j)
            res[i].push_back(el[i][j]);

    return res;
}

//======================================================================================================================

void OpInverse::swap_rows(vector<vector<double>> & src, size_t i, size_t k) const {
    if (i == k)
        return;

    for (size_t j = 0; j < 2 * lhs->columns(); ++j) {
        double tmp = src[i][j];
        src[i][j] = src[k][j];
        src[k][j] = tmp;
    }
}
