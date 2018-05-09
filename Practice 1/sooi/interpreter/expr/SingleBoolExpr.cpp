#include "SingleBoolExpr.h"
#include "../util/InterpreterError.h"
#include "../value/FunctionValue.h"
#include "../value/IntegerValue.h"
#include "../value/StringValue.h"
#include "../value/Type.h"
#include "../value/Value.h"
#include "Rhs.h"
#include "Expr.h"
#include "ConstExpr.h"

SingleBoolExpr::SingleBoolExpr(Expr* left, enum RelOp op, Expr* right, int line)
    : BoolExpr(line), m_left(left), m_right(right), m_op(op) {
}

SingleBoolExpr::~SingleBoolExpr() {
}

bool SingleBoolExpr::expr(Instance* self, Arguments* args) {
    Type* lf = m_left->rhs(self, args);
    Type* rf = m_right->rhs(self, args);

    if ( lf->type() == Type::InstanceType || rf->type() == Type::InstanceType ||
        (lf->type() == Type::StringType   && rf->type() == Type::IntegerType) ||
        (lf->type() == Type::IntegerType  && rf->type() == Type::StringType)  ){
        //InterpreterError::abort(this->line());
        InterpreterError::abort("boolexpr: tentativa de comparar string com inteiro");
    }

    if(lf->type() == Type::IntegerType){
        IntegerValue* _left  = (IntegerValue*) lf;
        IntegerValue* _right = (IntegerValue*) rf;

        switch(m_op){
            case RELOP_EQUAL:
                if(_left->value() == _right->value())
                    return true;
                break;
            case RELOP_NOTEQUAL:
                if(_left->value() != _right->value())
                    return true;
                break;
            case RELOP_GREATEREQUAL:
                if(_left->value() >= _right->value())
                    return true;
                break;
            case RELOP_GREATER:
                if(_left->value() > _right->value())
                    return true;
                break;
            case RELOP_LOWEREQUAL:
                if(_left->value() <= _right->value())
                    return true;
                break;
            case RELOP_LOWER:
                if(_left->value() < _right->value())
                    return true;
                break;
            default:
                InterpreterError::abort(this->line());
                break;
        }

    } else if(lf->type() == Type::StringType){
        StringValue* _left  = (StringValue*) lf;
        StringValue* _right = (StringValue*) rf;

        switch(m_op){
            case RELOP_EQUAL:
                if(_left->value() == _right->value())
                    return true;
                break;
            case RELOP_NOTEQUAL:
                if(_left->value() != _right->value())
                    return true;
                break;
            case RELOP_GREATEREQUAL:
                if(_left->value() >= _right->value())
                    return true;
                break;
            case RELOP_GREATER:
                if(_left->value() > _right->value())
                    return true;
                break;
            case RELOP_LOWEREQUAL:
                if(_left->value() <= _right->value())
                    return true;
                break;
            case RELOP_LOWER:
                if(_left->value() < _right->value())
                    return true;
                break;
            default:
                InterpreterError::abort(this->line());
                break;
        }

    }

    return false;
}
