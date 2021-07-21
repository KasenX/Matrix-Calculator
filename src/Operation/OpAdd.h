#ifndef MATRIXCALCULATOR_OPADD_H
#define MATRIXCALCULATOR_OPADD_H

#include "OpBinary.h"

class OpAdd : public OpBinary {
public:

    OpAdd (std::shared_ptr<CMatrix> left, std::shared_ptr<CMatrix> right);

    std::vector<std::vector<double>> perform () const override;
};

#endif //MATRIXCALCULATOR_OPADD_H
