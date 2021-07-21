#include "OpBinary.h"

using namespace std;

OpBinary::OpBinary(shared_ptr<CMatrix> left, shared_ptr<CMatrix> right)
: Op(move(left)), rhs(move(right))
{}

//======================================================================================================================

string OpBinary::rhsToString() const {
    return "[" + to_string(rhs->rows()) + "," + to_string(rhs->columns()) + "]";
}
