#include "OpTranspose.h"

using namespace std;

OpTranspose::OpTranspose(shared_ptr<CMatrix> left)
: Op(move(left))
{}

//======================================================================================================================

vector<vector<double>> OpTranspose::perform() const {
    vector<vector<double>> elements(lhs->columns());

    for (size_t i = 0; i < lhs->columns(); ++i) {
        for (size_t j = 0; j < lhs->rows(); ++j)
            elements[i].push_back(lhs->at(j, i));
    }

    return elements;
}
