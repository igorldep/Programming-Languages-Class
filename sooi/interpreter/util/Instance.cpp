#include "Instance.h"

Instance::Instance() {
}

Instance::~Instance() {
}

Instance* Instance::dup() const {
    std::map<std::string,Type*>::const_iterator it = m_memory.begin(),
        ed = m_memory.end();

    Instance* i = new Instance();
    for (; it != ed; it++)
        i->setValue(it->first, it->second);

    return i;
}
