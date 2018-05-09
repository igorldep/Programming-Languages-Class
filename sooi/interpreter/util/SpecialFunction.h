#ifndef SPECIAL_FUNCTION_H
#define SPECIAL_FUNCTION_H

#include "Function.h"

class SpecialFunction : public Function {
    public:
        enum FunctionType {
            PrintFunction,
            PrintlnFunction,
            ReadFunction,
            RandomFunction,
            GetFunction,
            SetFunction,
            AbortFunction,
            TypeFunction,
            LengthFunction,
            SubstringFunction,
            CloneFunction
        };

        SpecialFunction(FunctionType type);
        virtual ~SpecialFunction();

        virtual Type* call(Instance* self, Arguments* args);

    private:
        FunctionType m_type;

        Type* print(Arguments* args);
        Type* println(Arguments* args);
        Type* read(Arguments* args);
        Type* random(Arguments* args);

        Type* clone(Arguments* args);
        Type* set(Arguments* args);
        Type* get(Arguments* args);
        Type* type(Arguments* args);
        Type* abort(Arguments* args);
        Type* length(Arguments* args);
        Type* substring(Arguments* args);
};

#endif
