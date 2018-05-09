#ifndef COMPOSITE_EXPR_H
#define COMPOSITE_EXPR_H

#include "Expr.h"

class CompositeExpr : public Expr {
    public:
        enum CompOp {
            INVALID = 0,
            ADD = 1,
            SUB = 2,
            MUL = 3,
            DIV = 4,
            MOD = 5,

        };
        CompositeExpr(Expr* left, CompOp op, Expr* right, int line);
        virtual ~CompositeExpr();

        virtual Type* rhs(Instance* self, Arguments* args);

    private:
    	Expr* m_left;
        Expr* m_right;
        CompOp m_op;

};

#endif
