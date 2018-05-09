#include "CompositeBoolExpr.h"
#include "../util/InterpreterError.h"
#include "../value/FunctionValue.h"
#include "../value/IntegerValue.h"
#include "../value/StringValue.h"
#include "../value/Type.h"
#include "../value/Value.h"
#include "Rhs.h"
#include "Expr.h"
#include "ConstExpr.h"

CompositeBoolExpr::CompositeBoolExpr(BoolExpr* left, enum BoolOp op, BoolExpr* right, int line)
    : BoolExpr(line), m_left(left), m_right(right), m_op(op) {
}

CompositeBoolExpr::~CompositeBoolExpr() {
}

bool CompositeBoolExpr::expr(Instance* self, Arguments* args) {

    if(m_op == BOOL_INVALID)
        InterpreterError::abort("compositeboolexpr: sinal inexistente");

    if(m_left->expr(self, args) && m_right->expr(self, args))
        return true;
    else if( (m_left->expr(self, args) && !m_right->expr(self, args)) || (!m_left->expr(self, args) && m_right->expr(self, args)) ){
        if(m_op == BOOL_OR)
            return true;
        else
            return false;
    }

    return false;
}
