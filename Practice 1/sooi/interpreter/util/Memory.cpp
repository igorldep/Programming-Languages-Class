#include "Memory.h"
#include "../value/IntegerValue.h"

Memory::Memory() {
}

Memory::~Memory() {
}

bool Memory::contains(std::string name) const {
    return m_memory.find(name) != m_memory.end();
}

Type* Memory::value(std::string name) {
    Type* value;
    if (!this->contains(name)) {
        value = new IntegerValue(0);
        m_memory[name] = value;
    } else {
        value = m_memory[name];
    }

    return value;
}

void Memory::setValue(std::string name, Type* value) {
    m_memory[name] = value;
}
