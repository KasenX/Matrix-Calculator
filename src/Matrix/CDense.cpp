#include "CDense.h"

using namespace std;

CDense::CDense(size_t rows, size_t columns, vector<vector<double>> elements)
: CMatrix(rows, columns), m_Elements(move(elements))
{}

//======================================================================================================================

double CDense::at(size_t i, size_t j) const {
    return m_Elements[i][j];
}

//======================================================================================================================

shared_ptr<CMatrix> CDense::clone() const {
    return make_shared<CDense>(*this);
}

//======================================================================================================================

void CDense::toFile(std::ofstream & file) const {
    file << "D";
    for (auto & row : m_Elements)
        for (auto el : row)
            file << " " << el;
}
