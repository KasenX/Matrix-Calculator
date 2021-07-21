#include "Op.h"

using namespace std;

Op::Op(shared_ptr<CMatrix> left)
: lhs(move(left))
{}

//======================================================================================================================

string Op::lhsToString() const {
    return "[" + to_string(lhs->rows()) + "," + to_string(lhs->columns()) + "]";
}
