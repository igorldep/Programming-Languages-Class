#ifndef SPECIAL_FUNCTION_H
#define SPECIAL_FUNCTION_H

#include "Function.h"

class Arguments;
class Command;
class Instance;
class Rhs;
class Type;

class StandardFunction : public Function {
    public:

        StandardFunction(Command* cmds, Rhs* ret);
        StandardFunction(Command* cmds);
        virtual ~StandardFunction();

        virtual Type* call(Instance* self, Arguments* args);

    private:
        Command* m_cmds;
        Rhs* m_ret = 0;
};

#endif
