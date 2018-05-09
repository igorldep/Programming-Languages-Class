#ifndef INTEGER_VALUE_H
#define INTEGER_VALUE_H

#include "Value.h"

class IntegerValue : public Value<int> {
    public:
        static IntegerValue* Zero;

        IntegerValue(int value);
        virtual ~IntegerValue();

        int value() const;

    private:
        int m_value;
};

#endif
