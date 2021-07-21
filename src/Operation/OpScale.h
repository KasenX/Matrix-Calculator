#ifndef MATRIXCALCULATOR_OPSCALE_H
#define MATRIXCALCULATOR_OPSCALE_H

#include "Op.h"

class OpScale : public Op {
public:

    OpScale (std::shared_ptr<CMatrix> left, double scalar);

    std::vector<std::vector<double>> perform () const override;

private:

    double m_Scalar; // The number by which the matrix will be multiplied
};

#endif //MATRIXCALCULATOR_OPSCALE_H
