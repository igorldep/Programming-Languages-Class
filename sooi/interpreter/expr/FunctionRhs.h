#ifndef FUNCTION_RHS_H
#define FUNCTION_RHS_H

#include "Rhs.h"

class Type;

class FunctionRhs : public Rhs {
    public:
        FunctionRhs(int line, Type* funct);
        virtual ~FunctionRhs();

        virtual Type* rhs(Instance* self, Arguments* args);

    private:
        Type* m_funct;
};

#endif
