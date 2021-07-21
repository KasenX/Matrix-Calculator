#ifndef MATRIXCALCULATOR_OPSUBTRACT_H
#define MATRIXCALCULATOR_OPSUBTRACT_H

#include "OpBinary.h"

class OpSubtract : public OpBinary {
public:

    OpSubtract (std::shared_ptr<CMatrix> left, std::shared_ptr<CMatrix> right);

    std::vector<std::vector<double>> perform () const override;
};

#endif //MATRIXCALCULATOR_OPSUBTRACT_H
