#include "AccessExpr.h"
#include "../util/AccessPath.h"

AccessExpr::AccessExpr(AccessPath* path, int line)
    : Expr(line), m_path(path) {
}

AccessExpr::~AccessExpr() {
}

Type* AccessExpr::rhs(Instance* self, Arguments* args) {
    return m_path->value(self, args);
}
