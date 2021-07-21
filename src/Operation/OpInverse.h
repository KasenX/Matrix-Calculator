#ifndef MATRIXCALCULATOR_OPINVERSE_H
#define MATRIXCALCULATOR_OPINVERSE_H

#include "Op.h"

class OpInverse : public Op {
public:

    OpInverse (std::shared_ptr<CMatrix> left);

    std::vector<std::vector<double>> perform () const override;

private:

    /**
    * Swap two rows (it swaps row of associated matrix as well).
    * @param src elements of the matrix
    * @param i original position of the row
    * @param k requested position of the row
    */
    void swap_rows (std::vector<std::vector<double>> & src, size_t i, size_t k) const;
};

#endif //MATRIXCALCULATOR_OPINVERSE_H
