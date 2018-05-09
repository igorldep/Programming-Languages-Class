#ifndef CONST_EXPR_H
#define CONST_EXPR_H

#include "Expr.h"

class ConstExpr : public Expr {
    public:
        ConstExpr(Type* value, int line);
        virtual ~ConstExpr();

        virtual Type* rhs(Instance* self, Arguments* args);

    private:
        Type* m_value;

};

#endif