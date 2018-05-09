#include "Global.h"
#include "Instance.h"
#include "SpecialFunction.h"
#include "../value/FunctionValue.h"
#include "../value/InstanceValue.h"

Global* Global::global = 0;

Global::Global() {
    Instance* system = new Instance();
    system->setValue("print", new FunctionValue(new SpecialFunction(SpecialFunction::PrintFunction)));
    system->setValue("println", new FunctionValue(new SpecialFunction(SpecialFunction::PrintlnFunction)));
    system->setValue("read", new FunctionValue(new SpecialFunction(SpecialFunction::ReadFunction)));
    system->setValue("random", new FunctionValue(new SpecialFunction(SpecialFunction::RandomFunction)));
    system->setValue("clone", new FunctionValue(new SpecialFunction(SpecialFunction::CloneFunction)));
    system->setValue("set", new FunctionValue(new SpecialFunction(SpecialFunction::SetFunction)));
    system->setValue("get", new FunctionValue(new SpecialFunction(SpecialFunction::GetFunction)));
    system->setValue("type", new FunctionValue(new SpecialFunction(SpecialFunction::TypeFunction)));
    system->setValue("abort", new FunctionValue(new SpecialFunction(SpecialFunction::AbortFunction)));
    system->setValue("length", new FunctionValue(new SpecialFunction(SpecialFunction::LengthFunction)));
    system->setValue("substring", new FunctionValue(new SpecialFunction(SpecialFunction::SubstringFunction)));
    // FIXME: Add the others.

    this->setValue("system", new InstanceValue(system));
}

Global::~Global() {
}

Global* Global::getGlobalTable() {
    if (global == 0)
        global = new Global();

    return global;
}
