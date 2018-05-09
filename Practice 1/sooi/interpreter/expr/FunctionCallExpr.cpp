#include "FunctionCallExpr.h"

#include <sstream>
#include <iostream>

#include "../util/Arguments.h"
#include "../util/Function.h"
#include "../util/AccessPath.h"
#include "../util/InterpreterError.h"
#include "../value/FunctionValue.h"

FunctionCallExpr::FunctionCallExpr(AccessPath* path, int line)
    : Expr(line), m_path(path) {
}

FunctionCallExpr::~FunctionCallExpr() {
}

void FunctionCallExpr::addParam(Rhs* rhs) {
    m_params.push_back(rhs);
}

Type* FunctionCallExpr::rhs(Instance* self, Arguments* args) {
    Type* funct = m_path->value(self, args);
    if (funct->type() != Type::FunctionType)
        InterpreterError::abort(this->line());

    FunctionValue* fv = (FunctionValue*) funct;
    Function* f = fv->value();

    Instance* fSelf = (Instance*) m_path->reference(self, args);
    Arguments* fArgs = new Arguments();
    for (unsigned int i = 0; i < m_params.size(); i++) {
        Rhs* p = m_params[i];
        Type* v = p->rhs(self, args);

        std::stringstream ss;
        ss << "arg" << i+1;
        fArgs->setValue(ss.str(), v);
    }

    Type* ret = f->call(fSelf, fArgs);
    return ret;
}
