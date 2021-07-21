#include "OpMergeSide.h"
#include "../Exceptions/MatrixException.h"

using namespace std;

OpMergeSide::OpMergeSide(shared_ptr<CMatrix> left, shared_ptr<CMatrix> right)
: OpBinary(move(left), move(right))
{}

//======================================================================================================================

vector<vector<double>> OpMergeSide::perform() const {
    if (lhs->rows() != rhs->rows())
        throw MatrixException("Cannot side merge the matrix " + lhsToString() + " with the matrix " + rhsToString());

    vector<vector<double>> elements(lhs->rows(), vector<double>(lhs->columns() + rhs->columns()));

    for (size_t i = 0; i < lhs->rows(); ++i) {
        for (size_t j = 0; j < lhs->columns(); ++j)
            elements[i][j] = lhs->at(i, j);
        for (size_t j = 0; j < rhs->columns(); ++j)
            elements[i][lhs->columns() + j] = rhs->at(i, j);
    }

    return elements;
}
