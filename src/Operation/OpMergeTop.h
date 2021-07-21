#ifndef MATRIXCALCULATOR_OPMERGETOP_H
#define MATRIXCALCULATOR_OPMERGETOP_H

#include "OpBinary.h"

class OpMergeTop : public OpBinary {
public:

    OpMergeTop (std::shared_ptr<CMatrix> left, std::shared_ptr<CMatrix> right);

    std::vector<std::vector<double>> perform () const override;
};

#endif //MATRIXCALCULATOR_OPMERGETOP_H
