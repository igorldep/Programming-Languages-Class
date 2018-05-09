#include "FunctionRhs.h"

FunctionRhs::FunctionRhs(int line, Type* funct)
    : Rhs(line), m_funct(funct) {
}

FunctionRhs::~FunctionRhs() {
}

Type* FunctionRhs::rhs(Instance* self, Arguments* args) {
    return m_funct;
}
