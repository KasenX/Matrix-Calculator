#include "OpScale.h"

using namespace std;

OpScale::OpScale(shared_ptr<CMatrix> left, double scalar)
: Op(move(left)), m_Scalar(scalar)
{}

//======================================================================================================================

vector<vector<double>> OpScale::perform() const {

    vector<vector<double>> elements(lhs->rows());

    for (size_t i = 0; i < lhs->rows(); ++i) {
        for (size_t j = 0; j < lhs->columns(); ++j)
            elements[i].push_back(m_Scalar * lhs->at(i, j));
    }
    return elements;
}
