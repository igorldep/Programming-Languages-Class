#include "CompositeExpr.h"
#include "../util/InterpreterError.h"
#include "../value/IntegerValue.h"
#include "../value/StringValue.h"
#include "../value/Type.h"
#include <sstream>

CompositeExpr::CompositeExpr(Expr* left, CompOp op, Expr* right, int line)
 : Expr(line), m_left(left), m_right(right), m_op(op) {
}

CompositeExpr::~CompositeExpr() {
}

Type* CompositeExpr::rhs(Instance* self, Arguments* args) {

    Type* lf = m_left->rhs(self, args);
    Type* rf = m_right->rhs(self, args);

    if(lf->type() == Type::IntegerType && rf->type() == Type::IntegerType){
        int result = 0;
        int lvalue = ((IntegerValue*) lf)->value();
        int rvalue = ((IntegerValue*) rf)->value();
        switch(m_op){
            case ADD:
                result = lvalue + rvalue;
                break;
            case SUB:
                result = lvalue - rvalue;
                break;
            case MUL:
                result = lvalue * rvalue;
                break;
            case DIV:
                result = lvalue / rvalue;
                break;
            case MOD:
                result = lvalue % rvalue;
                break;
            default:
                InterpreterError::abort("compositeexpr: operacao invalida");
                break;
        }
        IntegerValue* n = new IntegerValue(result);
        return (Type*) n;
    // int int
    } else if (lf->type() == Type::IntegerType && rf->type() == Type::StringType){
    // int string
        std::string result;
        int lvalue = ((IntegerValue*) lf)->value();
        std::string rvalue = ((StringValue*) rf)->value();
        std::stringstream ss;
        switch(m_op){
            case ADD:
                ss  << lvalue << rvalue;
                result = ss.str();
                break;
            default:
                InterpreterError::abort("compositeexpr: operacao com string invalida");
                break;
        }
        StringValue* n = new StringValue(result);
        return (Type*) n;
    } else if (lf->type() == Type::StringType && rf->type() == Type::IntegerType){
    // string int
        std::string result;
        std::string lvalue = ((StringValue*) lf)->value();
        int rvalue = ((IntegerValue*) rf)->value();
        std::stringstream ss;
        switch(m_op){
            case ADD:
                ss  << lvalue << rvalue;
                result = ss.str();
                break;
            default:
                InterpreterError::abort("compositeexpr: operacao com string invalida");
                break;
        }
        StringValue* n = new StringValue(result);
        return (Type*) n;
    } else {
    // string string
        std::string result;
        std::string lvalue = ((StringValue*) lf)->value();
        std::string rvalue = ((StringValue*) rf)->value();
        switch(m_op){
            case ADD:
                result = lvalue + rvalue;
                break;
            default:
                InterpreterError::abort("compositeexpr: operacao com string invalida");
                break;
        }
        StringValue* n = new StringValue(result);
        return (Type*) n;
    }
    return 0;
}
