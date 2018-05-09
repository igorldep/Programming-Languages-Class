#ifndef EXPR_H
#define EXPR_H

#include "Rhs.h"

class Expr : public Rhs {
    public:
        Expr(int line) : Rhs(line) {}
        virtual ~Expr() {}

        virtual Type* rhs(Instance* self, Arguments* args) = 0;

};

#endif
