#ifndef MATRIXCALCULATOR_OP_H
#define MATRIXCALCULATOR_OP_H

#include "../Matrix/CMatrix.h"

#include <memory>
#include <utility>
#include <vector>
#include <string>

class Op {
public:

    explicit Op (std::shared_ptr<CMatrix> left);

    virtual ~Op () = default;

    /**
     * Performs the operation.
     * Throws a matrix exception when working with matrices of incompatible sizes OR when trying to calculate
     * non-existent inversion.
     * @return elements of the new matrix after performed operation
     */
    virtual std::vector<std::vector<double>> perform () const = 0;

protected:

    std::shared_ptr<CMatrix> lhs; // Matrix on the left-hand side

    /**
     * @return rows and columns of the left-hand side matrix in fancy format
     */
    std::string lhsToString () const;
};

#endif //MATRIXCALCULATOR_OP_H
