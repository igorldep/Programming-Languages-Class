#include "InstanceValue.h"

InstanceValue::InstanceValue(Instance* value)
  : Value(Type::InstanceType), m_value(value) {
}

InstanceValue::~ InstanceValue() {
}

Instance* InstanceValue::value() const {
    return m_value;
}
