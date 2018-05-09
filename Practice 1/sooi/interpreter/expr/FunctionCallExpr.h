#ifndef FUNCTION_CALL_EXPR_H
#define FUNCTION_CALL_EXPR_H

#include "Expr.h"

#include <vector>

class Rhs;
class Type;
class Instance;
class Arguments;
class AccessPath;

class FunctionCallExpr : public Expr {
    public:
        FunctionCallExpr(AccessPath* path, int line);
        virtual ~FunctionCallExpr();

        void addParam(Rhs* rhs);
        Type* rhs(Instance* self, Arguments* args);

    private:
        AccessPath* m_path;
        std::vector<Rhs*> m_params;

};

#endif
