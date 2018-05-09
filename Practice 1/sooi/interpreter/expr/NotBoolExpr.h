#ifndef NOT_BOOL_EXPR_H
#define NOT_BOOL_EXPR_H

#include "BoolExpr.h"

class Arguments;
class BoolExpr;
class Instance;

class NotBoolExpr : public BoolExpr {
    public:
        NotBoolExpr(BoolExpr* expr, int line);
        virtual ~NotBoolExpr();

        virtual bool expr(Instance* self, Arguments* args);

    private:
        BoolExpr* m_expr;

};

#endif
