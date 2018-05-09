#ifndef COMPOSITE_BOOL_EXPR_H
#define COMPOSITE_BOOL_EXPR_H

#include "BoolExpr.h"
#include "BoolOp.h"

class Arguments;
class BoolExpr;
class Instance;

class CompositeBoolExpr : public BoolExpr {
    public:
        CompositeBoolExpr(BoolExpr* left, enum BoolOp op, BoolExpr* right, int line);
        virtual ~CompositeBoolExpr();

        virtual bool expr(Instance* self, Arguments* args);

    private:
        BoolExpr* m_left;
        BoolExpr* m_right;
        enum BoolOp m_op;

};

#endif
