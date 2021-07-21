#include "OpMultiply.h"
#include "../Exceptions/MatrixException.h"

using namespace std;

OpMultiply::OpMultiply(shared_ptr<CMatrix> left, shared_ptr<CMatrix> right)
: OpBinary(move(left), move(right))
{}

//======================================================================================================================

vector<vector<double>> OpMultiply::perform() const {
    if (lhs->columns() != rhs->rows())
        throw MatrixException("Cannot multiply the matrix " + lhsToString() + " with the matrix " + rhsToString());

    vector<vector<double>> elements(lhs->rows());

    for (size_t i = 0; i < lhs->rows(); ++i) {
        for (size_t j = 0; j < rhs->columns(); ++j)
            elements[i].push_back(getProductAt(i, j));
    }

    return elements;
}

//======================================================================================================================

double OpMultiply::getProductAt(size_t x, size_t y) const {
    double value = 0;
    for (size_t i = 0; i < lhs->columns(); ++i) {
        value += lhs->at(x, i) * rhs->at(i, y);
    }
    return value;
}