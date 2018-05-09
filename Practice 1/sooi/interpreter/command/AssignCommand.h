#ifndef ASSIGN_COMMAND_H
#define ASSIGN_COMMAND_H

#include "Command.h"

class Rhs;
class Instance;
class Arguments;
class AccessPath;

class AssignCommand : public Command {
    public:
        AssignCommand(AccessPath* lhs, Rhs* rhs, int line);
        ~AssignCommand();

        virtual void execute(Instance* self, Arguments* args);
    private:
        AccessPath* m_lhs;
        Rhs* m_rhs;

};

#endif
