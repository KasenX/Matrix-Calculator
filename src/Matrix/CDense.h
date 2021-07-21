#ifndef MATRIXCALCULATOR_CDENSE_H
#define MATRIXCALCULATOR_CDENSE_H

#include "CMatrix.h"

#include <vector>

class CDense : public CMatrix {
public:

    CDense (size_t rows, size_t columns, std::vector<std::vector<double>> elements);

    double at (size_t i, size_t j) const override;

    std::shared_ptr<CMatrix> clone () const override;

    void toFile (std::ofstream & file) const override;

protected:

    const std::vector<std::vector<double>> m_Elements;
};

#endif //MATRIXCALCULATOR_CDENSE_H
