#ifndef SINGLE_BOOL_EXPR_H
#define SINGLE_BOOL_EXPR_H

#include "BoolExpr.h"
#include "RelOp.h"

class Arguments;
class Expr;
class Instance;

class SingleBoolExpr : public BoolExpr {
    public:
        SingleBoolExpr(Expr* left, enum RelOp op, Expr* right, int line);
        virtual ~SingleBoolExpr();

        virtual bool expr(Instance* self, Arguments* args);

    private:
        Expr* m_left;
        Expr* m_right;
        enum RelOp m_op;

};

#endif
