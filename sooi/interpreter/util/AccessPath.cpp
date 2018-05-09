#include "AccessPath.h"

#include <sstream>

#include "Global.h"
#include "Memory.h"
#include "Instance.h"
#include "Arguments.h"
#include "InterpreterError.h"
#include "../value/Type.h"
#include "../value/IntegerValue.h"
#include "../value/InstanceValue.h"

AccessPath::AccessPath(std::string name, int line) : m_line(line) {
    m_names.push_back(name);
}

AccessPath::~AccessPath() {
}

void AccessPath::addName(std::string name) {
    m_names.push_back(name);
}

std::list<std::string> AccessPath::names() const {
    return m_names;
}

Type* AccessPath::value(Instance* self, Arguments* args) {
    Memory* ref;
    if (this->isSingleName()) {
        if (this->isSelf())
            return new InstanceValue(self);
        else if (this->isArgs())
            return new InstanceValue(args);

        ref = Global::getGlobalTable();
    } else {
        ref = this->reference(self, args);
    }

    Type* ret;
    std::string name = this->lastName();
    if (ref->contains(name))
        ret = ref->value(name);
    else {
        ret = IntegerValue::Zero;
        ref->setValue(name, ret);
    }

    return ret;
}

void AccessPath::setValue(Instance* self, Arguments* args, Type* value) {
    Memory* ref;
    if (this->isSingleName()) {
        if (this->isSelf() || this->isArgs())
            InterpreterError::abort(m_line);

        ref = Global::getGlobalTable();
    } else {
        ref = this->reference(self, args);
    }

    std::string name = this->lastName();
    ref->setValue(name, value);
}

Memory* AccessPath::reference(Instance* self, Arguments* args) {
    Memory* ref = 0;
    if (!this->isSingleName()) {
        std::string name;
        std::list<std::string>::iterator it, last;

        it = m_names.begin();
        name = *it;
        if (name == "self") {
            if (self == 0)
                InterpreterError::abort(m_line);

            ref = self;
            it++;
        } else if (name == "args") {
            if (self == 0)
                InterpreterError::abort(m_line);

            ref = args;
            it++;
        } else {
            ref = Global::getGlobalTable();
        }

        last = m_names.end();
        last--;

        for (; it != last; it++) {
            name = *it;

            Memory* new_ref;
            if (ref->contains(name) && ref->value(name)->type() == Type::InstanceType) {
                InstanceValue* iv = (InstanceValue*) ref->value(name);
                new_ref = iv->value();
            } else {
                // if there are more names, than it must be an instance (object) reference.
                new_ref = new Instance();
                ref->setValue(name, new InstanceValue((Instance*) new_ref));
            }

            ref = new_ref;
        }
    }

    return ref;
}

std::string AccessPath::lastName() const {
    return m_names.back();
}

bool AccessPath::isSingleName() const {
    return m_names.size() == 1;
}

bool AccessPath::isSelf() const {
    return this->isSingleName() && m_names.front() == "self";
}

bool AccessPath::isArgs() const {
    return this->isSingleName() && m_names.front() == "args";
}

std::string AccessPath::str() const {
    std::stringstream ss;
    
    std::list<std::string>::const_iterator it = m_names.begin();
    ss << *it;
    it++;

    for (; it != m_names.end(); it++) {
        ss << "." << *it;
    }

    return ss.str();
}
