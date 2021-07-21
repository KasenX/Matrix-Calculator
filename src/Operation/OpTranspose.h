#ifndef MATRIXCALCULATOR_OPTRANSPOSE_H
#define MATRIXCALCULATOR_OPTRANSPOSE_H

#include "Op.h"

class OpTranspose : public Op {
public:

    explicit OpTranspose (std::shared_ptr<CMatrix> left);

    std::vector<std::vector<double>> perform () const override;
};

#endif //MATRIXCALCULATOR_OPTRANSPOSE_H
