#include "FunctionValue.h"

FunctionValue::FunctionValue(Function* value)
  : Value(Type::FunctionType), m_value(value) {
}

FunctionValue::~ FunctionValue() {
}

Function* FunctionValue::value() const {
    return m_value;
}
