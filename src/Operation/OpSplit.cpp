#include "OpSplit.h"
#include "../Exceptions/MatrixException.h"

using namespace std;

OpSplit::OpSplit(shared_ptr<CMatrix> left, size_t rows, size_t columns, size_t x, size_t y)
: Op(move(left)), m_Rows(rows), m_Columns(columns), m_X(x), m_Y(y)
{}

//======================================================================================================================

vector<vector<double>> OpSplit::perform() const {
    if (m_Rows + m_X - 1 > lhs->rows() || m_Columns + m_Y - 1 > lhs->columns() || m_Rows == 0 || m_Columns == 0 || m_X == 0 || m_Y == 0)
        throw MatrixException("Cannot split the matrix " + lhsToString() + " into the matrix "
        + "[" + to_string(m_Rows) + "][" + to_string(m_Columns) + "] from position x: " + to_string(m_X) + " y: " + to_string(m_Y));

    vector<vector<double>> elements(m_Rows);

    for (size_t i = 0; i < m_Rows; ++i) {
        for (size_t j = 0; j < m_Columns; ++j)
            elements[i].push_back(lhs->at(m_X - 1 + i, m_Y - 1 + j));
    }

    return elements;
}
