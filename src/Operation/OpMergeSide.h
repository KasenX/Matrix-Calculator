#ifndef MATRIXCALCULATOR_OPMERGESIDE_H
#define MATRIXCALCULATOR_OPMERGESIDE_H

#include "OpBinary.h"

class OpMergeSide : public OpBinary {
public:

    OpMergeSide (std::shared_ptr<CMatrix> left, std::shared_ptr<CMatrix> right);

    std::vector<std::vector<double>> perform () const override;
};

#endif //MATRIXCALCULATOR_OPMERGESIDE_H
