#ifndef INSTANCE_VALUE_H
#define INSTANCE_VALUE_H

#include "Value.h"

class Instance;

class InstanceValue : public Value<Instance*> {
    public:
        InstanceValue(Instance* value);
        virtual ~InstanceValue();

        Instance* value() const;

    private:
        Instance* m_value;
};

#endif
