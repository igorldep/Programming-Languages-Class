#ifndef ACCESS_PATH_H
#define ACCESS_PATH_H

#include <list>
#include <string>

class Type;
class Memory;
class Instance;
class Arguments;

class AccessPath {
    public:
        AccessPath(std::string name, int line);
        virtual ~AccessPath();

        void addName(std::string name);
        std::list<std::string> names() const;

        Type* value(Instance* self, Arguments* args);
        void setValue(Instance* self, Arguments* args, Type* value);

        Memory* reference(Instance* self, Arguments* args);
        std::string lastName() const;

        bool isSingleName() const;
        bool isSelf() const;
        bool isArgs() const;

        std::string str() const;

    private:
        int m_line;
        std::list<std::string> m_names;

};

#endif
