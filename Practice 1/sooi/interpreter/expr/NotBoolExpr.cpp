#include "NotBoolExpr.h"

NotBoolExpr::NotBoolExpr(BoolExpr* expr, int line)
    : BoolExpr(line), m_expr(expr) {
}

NotBoolExpr::~NotBoolExpr() {
}

bool NotBoolExpr::expr(Instance* self, Arguments* args) {
    return !(m_expr->expr(self, args));
}
