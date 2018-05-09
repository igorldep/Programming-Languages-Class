#ifndef ACCESS_EXPR_H
#define ACCESS_EXPR_H

#include "Expr.h"

class AccessPath;

class AccessExpr : public Expr {
    public:
        AccessExpr(AccessPath* path, int line);
        virtual ~AccessExpr();

        Type* rhs(Instance* self, Arguments* args);

    private:
        AccessPath* m_path;

};

#endif
