#ifndef MATRIXCALCULATOR_OPGEM_H
#define MATRIXCALCULATOR_OPGEM_H

#include "Op.h"

class OpGEM : public Op {
public:

    explicit OpGEM (std::shared_ptr<CMatrix> left);

    std::vector<std::vector<double>> perform () const override;

private:

    /**
     * Prepare pivot element at diagonal on indexes [idx][idx].
     * @param el elements
     * @param idx index
     */
    void pivotisation(std::vector<std::vector<double>> & el, size_t idx) const;

    /**
     * Perform elimination using pivot at given indexes [idx][idx].
     * @param el elements
     * @param idx index
     */
    void elimination(std::vector<std::vector<double>> & el, size_t idx) const;

    /**
     * Determine if the row contains only zeros.
     * @param row
     * @return true if the row contains only zeros, false otherwise
     */
    bool isZeroRow(const std::vector<double> & row) const;

    /**
     * Swap rows and zero rows so that zero rows are at the bottom.
     * @param el
     */
    void offsetZeroRows(std::vector<std::vector<double>> & el) const;

    /**
    * Swap two rows.
    * @param src elements of the matrix
    * @param i original position of the row
    * @param k requested position of the row
    */
    void swap_rows (std::vector<std::vector<double>> & src, size_t i, size_t k) const;
};

#endif //MATRIXCALCULATOR_OPGEM_H
