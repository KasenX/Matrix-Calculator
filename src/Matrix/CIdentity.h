#ifndef MATRIXCALCULATOR_CIDENTITY_H
#define MATRIXCALCULATOR_CIDENTITY_H

#include "CMatrix.h"

class CIdentity : public CMatrix {
public:

    explicit CIdentity (size_t rows);

    double at (size_t i, size_t j) const override;

    double determinant () const override;

    size_t rank () const override;

    std::shared_ptr<CMatrix> clone () const override;

    void toFile (std::ofstream & file) const override;
};

#endif //MATRIXCALCULATOR_CIDENTITY_H
