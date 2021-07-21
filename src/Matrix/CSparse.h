#ifndef MATRIXCALCULATOR_CSPARSE_H
#define MATRIXCALCULATOR_CSPARSE_H

#include "CMatrix.h"

#include <map>

class CSparse : public CMatrix {
public:

    CSparse (size_t rows, size_t columns, std::map<std::pair<size_t, size_t>, double> elements);

    double at (size_t i, size_t j) const override;

    std::shared_ptr<CMatrix> clone () const override;

    void toFile (std::ofstream & file) const override;

protected:

    const std::map<std::pair<size_t, size_t>, double> m_Elements;
};

#endif //MATRIXCALCULATOR_CSPARSE_H
