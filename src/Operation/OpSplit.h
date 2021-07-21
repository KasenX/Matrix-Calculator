#ifndef MATRIXCALCULATOR_OPSPLIT_H
#define MATRIXCALCULATOR_OPSPLIT_H

#include "Op.h"

class OpSplit : public Op {
public:

    OpSplit (std::shared_ptr<CMatrix> left, size_t rows, size_t columns, size_t x, size_t y);

    std::vector<std::vector<double>> perform () const override;

private:
    size_t m_Rows, m_Columns; // Dimension of the new matrix
    size_t m_X, m_Y; // Coordinates of split
};

#endif //MATRIXCALCULATOR_OPSPLIT_H
