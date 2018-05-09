#include "SpecialFunction.h"

#include <ctime>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <iostream>

#include "Arguments.h"
#include "InterpreterError.h"
#include "../value/StringValue.h"
#include "../value/IntegerValue.h"
#include "../value/InstanceValue.h"
#include "../value/FunctionValue.h"

SpecialFunction::SpecialFunction(FunctionType type) : m_type(type) {
    srand(time(0));
}

SpecialFunction::~SpecialFunction() {
}

Type* SpecialFunction::call(Instance* self, Arguments* args) {
    Type* value;

    switch (m_type) {
        case PrintFunction:
            value = this->print(args);
            break;
        case PrintlnFunction:
            value = this->println(args);
            break;
        case ReadFunction:
            value = this->read(args);
            break;
        case RandomFunction:
            value = this->random(args);
            break;
        case CloneFunction:
            value = this->clone(args);
            break;
        case SetFunction:
            value = this->set(args);
            break;
        case GetFunction:
            value = this->get(args);
            break;
        case TypeFunction:
            value = this->type(args);
            break;
        case AbortFunction:
            value = this->abort(args);
            break;
        case LengthFunction:
            value = this->length(args);
            break;
        case SubstringFunction:
            value = this->substring(args);
            break;
        default:
            throw std::string("FIXME: Implement me!");
    }

    return value;
}

Type* SpecialFunction::print(Arguments* args) {
    if (args->contains("arg1")) {
        Type* v = args->value("arg1");
        if (v->type() == Type::IntegerType) {
            IntegerValue* iv = (IntegerValue*) v;
            printf("%d", iv->value());
        } else if (v->type() == Type::StringType) {
            StringValue* sv = (StringValue*) v;
            printf("%s", sv->value().c_str());
        } else {
            throw std::string("FIXME: Implement me!");
        }
    }

    return IntegerValue::Zero;
}

Type* SpecialFunction::println(Arguments* args) {
    Type* v = this->print(args);
    printf("\n");
    return v;
}

Type* SpecialFunction::read(Arguments* args) {
    // Print the argument.
    Type* v = this->print(args);

    std::string input;
    std::cin >> input;

    char* valid;
    int n = (int) strtol(input.c_str(), &valid, 10);

    if (*valid == 0) {
        IntegerValue* iv = new IntegerValue(n);
        return iv;
    } else {
        StringValue* sv = new StringValue(input);
        return sv;
    }

    return v;
}

Type* SpecialFunction::random(Arguments* args) {
    if (!args->contains("arg1"))
        InterpreterError::abort("random: primeiro argumento inexistente");
    else if (!args->contains("arg2"))
        InterpreterError::abort("random: segundo argumento inexistente");

    Type* v1 = args->value("arg1");
    Type* v2 = args->value("arg2");

    if (v1->type() != Type::IntegerType)
        InterpreterError::abort("random: primeiro argumento nao eh inteiro");
    else if (v2->type() != Type::IntegerType)
        InterpreterError::abort("random: segundo argumento nao eh inteiro");

    int n1 = ((IntegerValue*) v1)->value();
    int n2 = ((IntegerValue*) v2)->value();

    if (n2 <= n1)
        InterpreterError::abort("random: segundo argumento menor/igual ao primeiro");

    int r = (rand() % (n2 - n1 + 1)) + n1;
    IntegerValue* iv = new IntegerValue(r);
    return iv;
}

Type* SpecialFunction::clone(Arguments* args) {
    if (!args->contains("arg1"))
        InterpreterError::abort("clone: primeiro argumento inexistente");

    Type* v = args->value("arg1");
    if (v->type() != Type::InstanceType)
        InterpreterError::abort("clone: primeiro argumento nao eh instancia");

    Instance* i = ((InstanceValue*) v)->value();
    InstanceValue* iv = new InstanceValue(i->dup());
    return iv;
}

Type* SpecialFunction::set(Arguments* args) {
    if (!args->contains("arg1"))
        InterpreterError::abort("set: primeiro argumento inexistente");

    Type* v = args->value("arg1");
    if (v->type() != Type::InstanceType)
        InterpreterError::abort("set: primeiro argumento nao eh instancia");

    if (!args->contains("arg2"))
        InterpreterError::abort("set: segundo argumento inexistente");

    Type* v2 = args->value("arg2");
    //if (v2->type() != Type::StringType)
        //InterpreterError::abort("set: segundo argumento nao eh string");

    if (!args->contains("arg3"))
        InterpreterError::abort("set: terceiro argumento inexistente");

    Type* v3 = args->value("arg3");

    std::string str = ((StringValue*) v2)->value();
    Instance* i = ((InstanceValue*) v)->value();
    i->setValue(str, v3);

    return 0;
}

Type* SpecialFunction::get(Arguments* args) {
    if (!args->contains("arg1"))
        InterpreterError::abort("get: primeiro argumento inexistente");

    Type* v = args->value("arg1");
    if (v->type() != Type::InstanceType)
        InterpreterError::abort("get: primeiro argumento nao eh instancia");

    if (!args->contains("arg2"))
        InterpreterError::abort("get: segundo argumento inexistente");

    Type* v2 = args->value("arg2");
    //if (v2->type() != Type::StringType)
        //InterpreterError::abort("get: segundo argumento nao eh string");


    std::string str = ((StringValue*) v2)->value();
    Instance* i = ((InstanceValue*) v)->value();
    Type* ret = i->value(str);

    return ret;
}

Type* SpecialFunction::type(Arguments* args) {
    if (!args->contains("arg1"))
        InterpreterError::abort("type: primeiro argumento inexistente");

    Type* v = args->value("arg1");
    std::string ret;
    switch(v->type()){
        case Type::InstanceType:
            ret = "Instance"; break;
        case Type::StringType:
            ret = "String"; break;
        case Type::IntegerType:
            ret = "Integer"; break;
        case Type::FunctionType:
            ret = "Function"; break;
    }

    StringValue* sv = new StringValue(ret);
    return sv;
}

Type* SpecialFunction::abort(Arguments* args){
    std::string ret = "";
    if(args->contains("arg1")){
        Type* v = args->value("arg1");
        if (v->type() != Type::StringType && v->type() != Type::IntegerType)
            InterpreterError::abort("abort: primeiro argumento nao eh string");

        ret = ((StringValue*) v)->value();
    }
    InterpreterError::abort(ret);
    return 0;
}

Type* SpecialFunction::substring(Arguments* args){
    if (!args->contains("arg1"))
        InterpreterError::abort("substring: primeiro argumento inexistente");

    Type* v = args->value("arg1");
    if (v->type() != Type::StringType)
        InterpreterError::abort("substring: primeiro argumento nao eh string");

    if (!args->contains("arg2"))
        InterpreterError::abort("substring: segundo argumento inexistente");

    Type* v2 = args->value("arg2");
    if (v2->type() != Type::IntegerType)
        InterpreterError::abort("substring: segundo argumento nao eh inteiro");

    if (!args->contains("arg3"))
        InterpreterError::abort("substring: terceiro argumento inexistente");

    Type* v3 = args->value("arg3");
    if (v3->type() != Type::IntegerType)
        InterpreterError::abort("substring: terceiro argumento nao eh inteiro");

    std::string str = ((StringValue*) v)->value();
    int start = ((IntegerValue*) v2)->value();
    int siz = ((IntegerValue*) v3)->value();

    StringValue* ret = new StringValue(str.substr(start, siz));

    return ret;
}

Type* SpecialFunction::length(Arguments* args){
    if (!args->contains("arg1"))
        InterpreterError::abort("length: primeiro argumento inexistente");

    Type* v = args->value("arg1");
    if (v->type() != Type::StringType)
        InterpreterError::abort("length: primeiro argumento nao eh string");

    std::string str = ((StringValue*) v)->value();;
    IntegerValue* ret = new IntegerValue(str.length());

    return ret;
}

