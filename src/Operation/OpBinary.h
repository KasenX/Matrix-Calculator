#ifndef MATRIXCALCULATOR_OPBINARY_H
#define MATRIXCALCULATOR_OPBINARY_H

#include "Op.h"

class OpBinary : public Op {
public:

    OpBinary (std::shared_ptr<CMatrix> left, std::shared_ptr<CMatrix> right);

protected:

    std::shared_ptr<CMatrix> rhs; // Matrix on the right-hand side

    /**
    * @return rows and columns of the right-hand side matrix in fancy format
    */
    std::string rhsToString () const;
};

#endif //MATRIXCALCULATOR_OPBINARY_H
