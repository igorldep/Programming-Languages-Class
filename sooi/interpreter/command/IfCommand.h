#ifndef IF_COMMAND_H
#define IF_COMMAND_H

#include "Command.h"

class Instance;
class Arguments;
class BoolExpr;

class IfCommand : public Command {
    public:
        IfCommand(BoolExpr* cond, Command* then, Command* ifelse, int line);
        IfCommand(BoolExpr* cond, Command* then, int line);
        ~IfCommand();

        virtual void execute(Instance* self, Arguments* args);
    private:
        BoolExpr* m_cond;
        Command* m_then;
        Command* m_else = 0;

};

#endif
