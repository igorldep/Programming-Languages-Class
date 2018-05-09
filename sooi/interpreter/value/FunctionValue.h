#ifndef FUNCTION_VALUE_H
#define FUNCTION_VALUE_H

#include "Value.h"

class Function;

class FunctionValue : public Value<Function*> {
    public:
        FunctionValue(Function* value);
        virtual ~ FunctionValue();

        Function* value() const;

    private:
        Function* m_value;
};

#endif
