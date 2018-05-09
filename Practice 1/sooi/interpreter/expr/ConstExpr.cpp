#include "ConstExpr.h"

ConstExpr::ConstExpr(Type* value, int line)
    : Expr(line), m_value(value) {
}

ConstExpr::~ConstExpr() {
}

Type* ConstExpr::rhs(Instance* self, Arguments* args) {
    return m_value;
}
