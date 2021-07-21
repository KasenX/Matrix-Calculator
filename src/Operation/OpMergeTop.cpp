#include "OpMergeTop.h"
#include "../Exceptions/MatrixException.h"

using namespace std;

OpMergeTop::OpMergeTop(shared_ptr<CMatrix> left, shared_ptr<CMatrix> right)
: OpBinary(move(left), move(right))
{}

//======================================================================================================================

vector<vector<double>> OpMergeTop::perform() const {
    if (lhs->columns() != rhs->columns())
        throw MatrixException("Cannot top merge the matrix " + lhsToString() + " with the matrix " + rhsToString());

    vector<vector<double>> elements(lhs->rows() + rhs->rows());

    for (size_t j = 0; j < lhs->columns(); ++j) {
        for (size_t i = 0; i < lhs->rows(); ++i)
            elements[i].push_back(lhs->at(i, j));
        for (size_t i = 0; i < rhs->rows(); ++i)
            elements[i + lhs->rows()].push_back(rhs->at(i, j));
    }

    return elements;
}
