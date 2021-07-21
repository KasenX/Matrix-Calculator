#include "OpAdd.h"
#include "../Exceptions/MatrixException.h"

using namespace std;

OpAdd::OpAdd(shared_ptr<CMatrix> left, shared_ptr<CMatrix> right)
: OpBinary(move(left), move(right))
{}

//======================================================================================================================

vector<vector<double>> OpAdd::perform() const {
    if (lhs->rows() != rhs->rows() || lhs->columns() != rhs->columns())
        throw MatrixException("Cannot add the matrix " + lhsToString() + " to the matrix " + rhsToString());

    vector<vector<double>> elements(lhs->rows());

    for (size_t i = 0; i < lhs->rows(); ++i) {
        for (size_t j = 0; j < lhs->columns(); ++j)
            elements[i].push_back(lhs->at(i, j) + rhs->at(i, j));
    }
    return elements;
}
