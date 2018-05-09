#ifndef WHILE_COMMAND_H
#define WHILE_COMMAND_H

#include "Command.h"

class Instance;
class Arguments;
class BoolExpr;

class WhileCommand : public Command {
    public:
        WhileCommand(BoolExpr* expr, Command* cmd, int line);
        ~WhileCommand();

        virtual void execute(Instance* self, Arguments* args);
    private:
        BoolExpr* m_expr;
        Command* m_cmd;

};

#endif
