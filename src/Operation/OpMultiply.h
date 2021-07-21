#ifndef MATRIXCALCULATOR_OPMULTIPLY_H
#define MATRIXCALCULATOR_OPMULTIPLY_H

#include "OpBinary.h"

class OpMultiply : public OpBinary {
public:

    OpMultiply (std::shared_ptr<CMatrix> left, std::shared_ptr<CMatrix> right);

    std::vector<std::vector<double>> perform () const override;

private:

    /**
     * Multiplies the elements (with corresponding indexes) of the two rows by each other and then adds them.
     * @param x index of the first row
     * @param y index of the second row
     * @return the sum of the products of the two rows
     */
    double getProductAt (size_t x, size_t y) const;
};

#endif //MATRIXCALCULATOR_OPMULTIPLY_H
