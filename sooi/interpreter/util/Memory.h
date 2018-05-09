#ifndef MEMORY_H
#define MEMORY_H

#include <map>
#include <string>

class Type;

class Memory {
    public:
        virtual ~Memory();

        bool contains(std::string name) const;
        Type* value(std::string name);
        void setValue(std::string name, Type* value);

    protected:
        Memory();
        std::map<std::string,Type*> m_memory;

};

#endif
