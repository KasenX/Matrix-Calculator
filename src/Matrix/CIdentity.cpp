#include "CIdentity.h"

using namespace std;

CIdentity::CIdentity(size_t rows)
: CMatrix(rows, rows)
{}

//======================================================================================================================

double CIdentity::at(size_t i, size_t j) const {
    return i == j ? 1 : 0;
}

//======================================================================================================================

double CIdentity::determinant() const {
    return 1;
}

//======================================================================================================================

size_t CIdentity::rank() const {
    return m_Rows;
}

//======================================================================================================================

shared_ptr<CMatrix> CIdentity::clone() const {
    return make_shared<CIdentity>(*this);
}

//======================================================================================================================

void CIdentity::toFile(ofstream & file) const {
    file << "I";
}
