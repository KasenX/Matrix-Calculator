#include "CSparse.h"

using namespace std;

CSparse::CSparse(size_t rows, size_t columns, map<pair<size_t, size_t>, double> elements)
: CMatrix(rows, columns), m_Elements(move(elements))
{}

//======================================================================================================================

double CSparse::at(size_t i, size_t j) const {
    auto idx = make_pair(i, j);
    try {
        return m_Elements.at(idx);
    } catch (out_of_range & e) {
        return 0;
    }
}

//======================================================================================================================

shared_ptr<CMatrix> CSparse::clone() const {
    return make_shared<CSparse>(*this);
}

//======================================================================================================================

void CSparse::toFile(ofstream & file) const {
    file << "S";
    for (auto & m : m_Elements) {
        file << " " << m.first.first << " " << m.first.second << " " << m.second;
    }
}
