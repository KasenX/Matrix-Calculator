#include "OpGEM.h"

#include <algorithm>

using namespace std;

OpGEM::OpGEM(shared_ptr<CMatrix> left)
: Op(move(left))
{}

//======================================================================================================================

void OpGEM::pivotisation(vector<vector<double>> & el, size_t idx) const {
    size_t rows = el.size();
    pair<size_t, double> pivot = make_pair(idx, el[idx][idx]); // the current least pivot (index, value)
    for (size_t i = idx + 1; i < rows; ++i) {
        if ((pivot.second == 0) || (el[i][idx] != 0 && abs(el[i][idx]) < abs(pivot.second)))
            pivot = make_pair(i, el[i][idx]);
    }
    swap_rows(el, idx, pivot.first);
}

//======================================================================================================================

void OpGEM::elimination(vector<vector<double>> & el, size_t idx) const {
    size_t rows = el.size();
    if (el[idx][idx] == 0)
        return;
    for (size_t i = idx + 1; i < rows; ++i) {
        double d = el[i][idx] / el[idx][idx];
        for (size_t j = 0; j < el[idx].size(); ++j)
            el[i][j] -= d * el[idx][j];
    }
}

//======================================================================================================================

bool OpGEM::isZeroRow(const vector<double> & row) const {
    return all_of(row.begin(), row.end(), [] (double i){ return i == 0;});
}

//======================================================================================================================

void OpGEM::offsetZeroRows(vector<vector<double>> & el) const {
    for (size_t i = 0; i < el.size(); ++i) {
        if (isZeroRow(el[i])) {
            for (size_t k = el.size() - 1; k > i; --k) {
                if (!isZeroRow(el[k]))
                    swap_rows(el, i, k);
            }
        }
    }
}

//======================================================================================================================

vector<vector<double>> OpGEM::perform() const {
    size_t rows = lhs->rows();
    size_t columns = lhs->columns();
    vector<vector<double>> el(rows, vector<double>(columns));
    // Copy elements
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; j++)
            el[i][j] = lhs->at(i, j);
    }

    size_t max = rows > columns ? columns : rows;
    for (size_t i = 0; i < max; ++i) {
        pivotisation(el, i);
        elimination(el, i);
    }

    offsetZeroRows(el);

    return el;
}

//======================================================================================================================

void OpGEM::swap_rows(vector<vector<double>> & src, size_t i, size_t k) const {
    if (i == k)
        return;

    for (size_t j = 0; j < lhs->columns(); ++j) {
        double tmp = src[i][j];
        src[i][j] = src[k][j];
        src[k][j] = tmp;
    }
}
